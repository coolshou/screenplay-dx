#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>


#define DIR_INPUT		    0
#define DIR_OUTPUT		    1

#define	ACTIVE_HIGH		    1
#define	ACTIVE_LOW		    0

/* T4 & X2 GPIO Pin definition */
#define PIN_I2C_SCL		    0
#define PIN_I2C_SDA		    1
#define PIN_FACTORY_RESET_BUTTON    2
#define	PIN_POWER_LED		    3
#define PIN_HW_MUTE		    4
#define PIN_USB_ENABLE0		    5
#define PIN_BOOTUP_LED		    6
#define PIN_USB_ENABLE1		    7
#define PIN_INT_MICROP		    9
#define PIN_USB_OC2		    10
#define PIN_USB_ENABLE2             11
#define PIN_IRDA		    12
#define PIN_HDMI_CEC		    13
#define PIN_SMP_STANDBY		    14
#define PIN_SMP_BOOTUP		    15
#define PIN_USB_OC1		    50
/* X2 Only */
#define PIN_USB_OC0		    33
#define PIN_HDD_POWER		    34
#define PIN_SATA_RESET		    35
#define PIN_USB_DETECT		    36
#define PIN_USB_SELECT		    37
#define PIN_THERMAL_INT		    40
#define PIN_POWER_BUTTON	    42
/**************************************/


/* Proc commands for write */
/* ROOT_GPIO */
#define CMD_POWER_LED_ON	    "power led on"
#define CMD_POWER_LED_OFF           "power led off"
#define CMD_POWER_LED_BLINK_ONCE    "power led blink once"
#define CMD_GPIO_LEADING	    "gpio"
/* ROOT_MISC */
#define CMD_MICROP_LED_ON	    "uP led on"
#define CMD_MICROP_LED_OFF	    "uP led off"
#define CMD_MICROP_LED_BLINK	    "uP led blink"
#define CMD_SMP_STANDBY		    "standby"
#define CMD_SMP_BOOTUP	            "bootup"
/* ROOT_POWER */
#define CMD_USB_POWER_ON	    "usb on"
#define CMD_USB_POWER_OFF	    "usb off"
#define CMD_SELECT_TO_PC	    "select pc"
#define CMD_SELECT_TO_BOARD	    "select board"
/* ROOT_FAN */
#define CMD_FAN_LOW		    "fan low"
#define CMD_FAN_HIGH		    "fan high"
#define CMD_FAN_OFF		    "fan off"
#define CMD_FAN_DUTY		    "fan duty"
/* ROOT_BUTTON */
#define CMD_EVENT_HDD_HEAT	    "HDD heat"
#define CMD_EVENT_HDD_OVER_HEAT	    "HDD over heat"
#define CMD_BTN_POWER_PUSH	    "Power pushed"
#define CMD_BTN_RESET_PUSH	    "Reset pushed"
/**********************************************************/

#define SECOND_OF_RESET_DEFAULT	    5

/* Proc nodes for IOMEGA */
#define	PROC_ROOT		    "iomega"
#define	PROC_ROOT_GPIO		    "gpio"
#define	PROC_ROOT_RTC		    "rtc"
#define	PROC_ROOT_CPU		    "cpu"
#define	PROC_ROOT_FAN		    "fan"
#define PROC_ROOT_POWER		    "power"
#define PROC_ROOT_BUTTON	    "button"
#define PROC_ROOT_MISC		    "misc"

/**********************************************************/
#define BUTTON_DEVICE		    "button"
#define BUTTON_MAJOR		    220
#define STATUS_POWER_PUSHED	    'P'
#define STATUS_RESET_PUSHED	    'R'
#define STATUS_HDD_HEAT		    'H'
#define STATUS_HDD_OVER_HEAT	    'O'
static wait_queue_head_t	    wait_queue;
static char			    button_status = 0;

/* GPIO initialize state and data, it should be the same as the value in ezboot */
//#define GPIO_DIRECTION          0x0000e8fd
//#define GPIO_DATA               0x000008a0

#define EM86XX_CHIP EM86XX_CHIPID_TANGO3
#include <linux/interrupt.h>
#include <asm/tango3/rmem86xxid.h>
#include <asm/tango3/rmdefs.h>
#include <asm/tango3/emhwlib_dram.h>
#include <asm/tango3/tango3_gbus.h>
#include <asm/tango3/tango3.h>
#include <asm/tango3/tango3api.h>
#include <asm/tango3/hardware.h>

/*
 * Hardware independent below
 */

/* The major device number and name */
#define DRIVER_VERSION         "0.4"

/* GPIO functions prototype declaration */
static void gpio_setdirection( int gpio, int dir );
static void gpio_write( int gpio, int val );
static int  gpio_read( int gpio );
static void fetch_gpio_param( char *ptr, int *g_pin, int *g_val );
static int  parse_date_param( char *ptr, unsigned char *date_ptr );
/* Global data for GPIO */
static int  proc_data_gpio = 0;
static int  app_bootup = 0;


/* I2C function prototype declaration */
#define WRITE_SLAVE_ADDRESS	    0x26
#define READ_SLAVE_ADDRESS	    0x27
static void I2C_Clock( int clock );
static void I2C_Data( int data );
static void I2C_WrBit( int data );
static void I2C_RdBit( int *data );
static void I2C_Start( void );
static void I2C_Stop( void );
static void I2C_SendNack( void );
static void I2C_SendAck( void );
static int  I2C_WaitAck( void );
static void I2C_WrByte( unsigned char ByteIn );
static void I2C_RdByte( unsigned char *data );
static int  I2C_Write( unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n );
static int  I2C_Read( unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n );
static int  I2C_Device_Detect( unsigned char SlaveAddress );
/* Global data for I2C */
static      DECLARE_MUTEX( lock );

#define DATE_STRING_LENGTH	7

extern unsigned long	tangox_chip_id( void );

/************************************ GPIO Driver ********************************************/
static int ktask_gpio(void *_data)
{
	int	usb_init = 0;
	int	usb_select = 2;	    /* Set a invalid number to force initialize at the first time */
	int	usb_detect;
	int	reset_counter = 0;


	while( 1 )
	{
	    //msleep_interruptible( 500 );
	    if( kthread_should_stop() )
		break;

	    /* This loop will be entered when this driver had been installed */
	    /* It will enable the power of HDD, USB0, USB1, USB2 */
	    if( !usb_init )
	    {
		/* Init the HDD and USB power here to avoid the burst current */
		printk( KERN_INFO "[IOM-554H] Enable HDD and USB power.\n" );
		usb_init = !usb_init;
		gpio_write( PIN_HDD_POWER, ACTIVE_HIGH );
		msleep_interruptible( 3000 );
		gpio_write( PIN_USB_ENABLE0, ACTIVE_HIGH );
		msleep_interruptible( 1000 );
		gpio_write( PIN_USB_ENABLE1, ACTIVE_HIGH );
		msleep_interruptible( 1000 );
		gpio_write( PIN_USB_ENABLE2, ACTIVE_HIGH );
	    }

	    /* Check USB detection to set HDD will be an internal or external storage for IOM-X2 only */
	    usb_detect = gpio_read( PIN_USB_DETECT );
	    if( usb_detect != usb_select )
	    {
		usb_select = usb_detect;
		if( usb_select )
		    printk( KERN_INFO "[IOM-554H] USB select to PC.\n" );
		else
		    printk( KERN_INFO "[IOM-554H] USB select to Board.\n" );
		gpio_write( PIN_USB_SELECT, usb_select );
		/* Reset SATA after the selection has been changed */
		gpio_write( PIN_SATA_RESET, ACTIVE_LOW );
		msleep_interruptible( 100 );
		gpio_write( PIN_SATA_RESET, ACTIVE_HIGH );
	    }

	    /* Check Power Button here for IOM-X2 only */
	    if( !gpio_read( PIN_POWER_BUTTON ) )
	    {
		button_status = STATUS_POWER_PUSHED;
		wake_up_interruptible( &wait_queue );
	    }

	    /* Check Reset Default Button, count reset defualt tick when it is pressed */
	    if( !gpio_read( PIN_FACTORY_RESET_BUTTON ) )
	    {
		reset_counter++;
		if( reset_counter == SECOND_OF_RESET_DEFAULT )
		{
                    button_status = STATUS_RESET_PUSHED;  /* Indicate system to reset default */
		    wake_up_interruptible( &wait_queue );
		    reset_counter = 0;
		}
	    }	
	    else
		reset_counter = 0;

	    msleep_interruptible( 1000 );
	}

	return 0;
}


static int  proc_write_gpio( struct file *file, const char *buffer, unsigned long count, void *data )
{
	char	buf[128];
	int	len;
	int	pin, val;


	len = (count > sizeof(buf)) ? sizeof(buf) : count;
	copy_from_user( buf, buffer, len );

	/* Put the blink check at the first, because it will be called frequently */
	if( !strncmp( buf, CMD_POWER_LED_BLINK_ONCE, strlen(CMD_POWER_LED_BLINK_ONCE) ) )
	{
	    if( app_bootup )
	    {
		gpio_write( PIN_POWER_LED, ACTIVE_LOW );
		msleep_interruptible( 20 );
		gpio_write( PIN_POWER_LED, ACTIVE_HIGH );
	    }
	}
        else if( !strncmp( buf, CMD_POWER_LED_ON, strlen(CMD_POWER_LED_ON) ) )
	{
	    gpio_write( PIN_POWER_LED, ACTIVE_HIGH );
	}
	else if( !strncmp( buf, CMD_POWER_LED_OFF, strlen(CMD_POWER_LED_OFF) ) )
	{
	    gpio_write( PIN_POWER_LED, ACTIVE_LOW );
	}
	/* GPIOn */
	else if( !strncmp( buf, CMD_GPIO_LEADING, strlen(CMD_GPIO_LEADING) ) )
	{
	    fetch_gpio_param( buf+strlen(CMD_GPIO_LEADING), (int*)&pin, (int*)&val );
	    if( pin != -1 ) /* Check the PIN number has been assigned or not */
	    {
		if( val != -1 )
		    gpio_write( pin, val );	/* Write to GPIO, if PIN and VALUE have been assigned */
		else
		    *((int *)data) = pin;   /* If PIN was assigned without a VALUE, then keep the PIN number for read */
	    }
	}

	return count;
}


static int  proc_read_gpio( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int		len;

	/* GPIO purpose */
	if( gpio_read( *((int *)data) ) )
	    len = sprintf( page + off, "PIN%d: 1\n", *((int *)data) );
	else
	    len = sprintf( page + off, "PIN%d: 0\n", *((int *)data) );

	*eof = 1;
	return len;
}


static int  proc_write_rtc( struct file *file, const char *buffer, unsigned long count, void *data )
{
        char		buf[128];
	unsigned char   date_str[DATE_STRING_LENGTH];
	int		len;


        len = (count > sizeof(buf)) ? sizeof(buf) : count;
	copy_from_user( buf, buffer, len );

	if( parse_date_param( buf, date_str ) == 0 )
	{
	    /* Set RTC time to uP */
            I2C_Write( WRITE_SLAVE_ADDRESS, 0x21, date_str, DATE_STRING_LENGTH );   /* Date formate: SSMMHHDDWWMMYY */
	}

	return count;
}


static int  proc_read_rtc( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int		len;
	unsigned char   date_str[DATE_STRING_LENGTH];


	I2C_Read( WRITE_SLAVE_ADDRESS, 0x21, date_str, DATE_STRING_LENGTH );
	/* Get RTC time from uP */
        len = sprintf( page + off, "S%02d M%02d H%02d D%02d W%02d M%02d Y%02d\n", date_str[0], date_str[1], date_str[2], date_str[3], date_str[4], date_str[5], date_str[6] );

	*eof = 1;
	return len;
}



static int  proc_read_cpu( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int		len;
	unsigned long	chip_id;
	unsigned long	chip_rev;


	chip_id = (tangox_chip_id() >> 16) & 0xffff;
	chip_rev = tangox_chip_id() & 0xff;

	len = sprintf( page + off, "%lx R%lx\n", chip_id, chip_rev );

	*eof = 1;
	return len;
}


static int  proc_write_fan( struct file *file, const char *buffer, unsigned long count, void *data )
{
	char    buf[128], i2c_data;
	int     len, duty;


	len = (count > sizeof(buf)) ? sizeof(buf) : count;
	copy_from_user( buf, buffer, len );

	if( !strncmp( buf, CMD_FAN_LOW, strlen(CMD_FAN_LOW) ) )
	{
	    i2c_data = 0x05;
            I2C_Write( WRITE_SLAVE_ADDRESS, 0x07, &i2c_data, sizeof(i2c_data) );    /* Fan 50% duty */
	}
	else if( !strncmp( buf, CMD_FAN_HIGH, strlen(CMD_FAN_HIGH) ) )
	{
	    i2c_data = 0x08;
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x07, &i2c_data, sizeof(i2c_data) );    /* Fan 80% duty */
	}
	else if( !strncmp( buf, CMD_FAN_OFF, strlen(CMD_FAN_OFF) ) )
	{
	    i2c_data = 0x00;
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x07, &i2c_data, sizeof(i2c_data) );    /* Fan OFF */
	}
	else if( !strncmp( buf, CMD_FAN_DUTY, strlen(CMD_FAN_DUTY) ) )
        {
	    fetch_gpio_param( buf+strlen(CMD_FAN_DUTY), (int*)&duty, (int*)&len );
	    if( duty != -1 )
	    {
		i2c_data = (char)(duty / 10);
		I2C_Write( WRITE_SLAVE_ADDRESS, 0x07, &i2c_data, sizeof(i2c_data) );    /* Fan Duty xx */
	    }
	}

	return count;
}


static int  proc_read_fan( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int		len;
	unsigned char	fan_hi = 0;
	unsigned char	fan_low = 0;
	unsigned int	fan_freq = 0;


	I2C_Read( WRITE_SLAVE_ADDRESS, 0x0C, &fan_hi, sizeof(fan_hi) );
	I2C_Read( WRITE_SLAVE_ADDRESS, 0x0D, &fan_low, sizeof(fan_low) );

	fan_freq = (fan_hi * 256) + fan_low;

	len = sprintf( page + off, "%d Hz\n", fan_freq );

	*eof = 1;
	return len;
}


static int  proc_write_power( struct file *file, const char *buffer, unsigned long count, void *data )
{
	char    buf[128];
	int     len;


	len = (count > sizeof(buf)) ? sizeof(buf) : count;
	copy_from_user( buf, buffer, len );

	if( !strncmp( buf, CMD_USB_POWER_ON, strlen(CMD_USB_POWER_ON) ) )
	{
	    gpio_write( PIN_HDD_POWER, ACTIVE_HIGH );
	    msleep_interruptible( 3000 );
	    gpio_write( PIN_USB_ENABLE0, ACTIVE_HIGH );
	    msleep_interruptible( 1000 );
	    gpio_write( PIN_USB_ENABLE1, ACTIVE_HIGH );
	    msleep_interruptible( 1000 );
	    gpio_write( PIN_USB_ENABLE2, ACTIVE_HIGH );
	}
	else if( !strncmp( buf, CMD_USB_POWER_OFF, strlen(CMD_USB_POWER_OFF) ) )
	{
	    gpio_write( PIN_HDD_POWER, ACTIVE_LOW );
	    msleep_interruptible( 3000 );
	    gpio_write( PIN_USB_ENABLE0, ACTIVE_LOW );
	    msleep_interruptible( 1000 );
	    gpio_write( PIN_USB_ENABLE1, ACTIVE_LOW );
	    msleep_interruptible( 1000 );
	    gpio_write( PIN_USB_ENABLE2, ACTIVE_LOW );
	}
	else if( !strncmp( buf, CMD_SELECT_TO_PC, strlen(CMD_SELECT_TO_PC) ) )
	{
	    gpio_write( PIN_USB_SELECT, ACTIVE_HIGH );
            /* Reset SATA after the selection has been changed */
            gpio_write( PIN_SATA_RESET, ACTIVE_LOW );
            msleep_interruptible( 100 );
            gpio_write( PIN_SATA_RESET, ACTIVE_HIGH );
	}
	else if( !strncmp( buf, CMD_SELECT_TO_BOARD, strlen(CMD_SELECT_TO_BOARD) ) )
	{
	    gpio_write( PIN_USB_SELECT, ACTIVE_LOW );
            /* Reset SATA after the selection has been changed */
            gpio_write( PIN_SATA_RESET, ACTIVE_LOW );
            msleep_interruptible( 100 );
            gpio_write( PIN_SATA_RESET, ACTIVE_HIGH );
	}

	return count;
}


static int  proc_write_button( struct file *file, const char *buffer, unsigned long count, void *data )
{
	char    buf[128];
        int     len;


        len = (count > sizeof(buf)) ? sizeof(buf) : count;
        copy_from_user( buf, buffer, len );

	if( !strncmp( buf, CMD_EVENT_HDD_HEAT, strlen(CMD_EVENT_HDD_HEAT) ) )
	{
	    button_status = STATUS_HDD_HEAT;
	    wake_up_interruptible( &wait_queue );
	}
	else if( !strncmp( buf, CMD_EVENT_HDD_OVER_HEAT, strlen(CMD_EVENT_HDD_OVER_HEAT) ) )
	{
	    button_status = STATUS_HDD_OVER_HEAT;
	    wake_up_interruptible( &wait_queue );
	}
	else if( !strncmp( buf, CMD_BTN_POWER_PUSH, strlen(CMD_BTN_POWER_PUSH) ) )
	{
	    button_status = STATUS_POWER_PUSHED;
	    wake_up_interruptible( &wait_queue );
	}
	else if( !strncmp( buf, CMD_BTN_RESET_PUSH, strlen(CMD_BTN_RESET_PUSH) ) )
	{
	    button_status = STATUS_RESET_PUSHED;
	    wake_up_interruptible( &wait_queue );
	}
	
	return count;
}


static int  proc_read_button( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	int		len;


	len = 0;
	if( button_status )
	{
	    len = sprintf( page + off, "%c", button_status );
	    button_status = 0;   /* Status dropped after key has been read */
	}

	*eof = 1;
	return len;
}


static int  proc_write_misc( struct file *file, const char *buffer, unsigned long count, void *data )
{
	char	buf[128], i2c_data;
	int	len;


	len = (count > sizeof(buf)) ? sizeof(buf) : count;
	copy_from_user( buf, buffer, len );

	if( !strncmp( buf, CMD_MICROP_LED_OFF, strlen(CMD_MICROP_LED_OFF) ) )
	{
	    i2c_data = 0x00;
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x08, &i2c_data, sizeof(i2c_data) );
	}
	else if( !strncmp( buf, CMD_MICROP_LED_ON, strlen(CMD_MICROP_LED_ON) ) )
	{
	    i2c_data = 0x01;
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x08, &i2c_data, sizeof(i2c_data) );
	}
	else if( !strncmp( buf, CMD_MICROP_LED_BLINK, strlen(CMD_MICROP_LED_BLINK) ) )
	{
	    i2c_data = 0x02;
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x08, &i2c_data, sizeof(i2c_data) );
	}
	else if( !strncmp( buf, CMD_SMP_STANDBY, strlen(CMD_SMP_STANDBY) ) )
	{
	    gpio_write( PIN_POWER_LED, ACTIVE_LOW );	/* Turn off BLUE led */

	    gpio_write( PIN_SMP_STANDBY, ACTIVE_HIGH );

	    i2c_data = 0x11;	/* Standby Mode */
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x04, &i2c_data, sizeof(i2c_data) );    /* Inform to uP to enter standby mode for new uP code */
	    
	    i2c_data = 0x00;	/* Power down device */
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x01, &i2c_data, sizeof(i2c_data) );

	    app_bootup = 0;
	}
        else if( !strncmp( buf, CMD_SMP_BOOTUP, strlen(CMD_SMP_BOOTUP) ) )
	{
	    /* Send a signal to MicroP to make the red blinking off */
	    gpio_write( PIN_SMP_BOOTUP, ACTIVE_HIGH );
	    
	    i2c_data = 0x00;   /* Turn off RED led */
	    I2C_Write( WRITE_SLAVE_ADDRESS, 0x08, &i2c_data, sizeof(i2c_data) );
            
	    i2c_data = 0x00;	/* Run Mode */
            I2C_Write( WRITE_SLAVE_ADDRESS, 0x04, &i2c_data, sizeof(i2c_data) );    /* Inform uP to enter run mode for new uP code */

            gpio_write( PIN_POWER_LED, ACTIVE_HIGH );	/* Light on BLUE led */

            i2c_data = 0x08;	/* Fan 80% duty */
            I2C_Write( WRITE_SLAVE_ADDRESS, 0x07, &i2c_data, sizeof(i2c_data) );
            
	    app_bootup = 1;     /* Set this flag to allow power led blink for irda received */
        }

	return count;
}


static int  proc_read_misc( char *page, char **start, off_t off, int count, int *eof, void *data )
{
	*eof = 1;
	return 0;
}


static void fetch_gpio_param( char *ptr, int *g_pin, int *g_val )
{
	while( *ptr == ' ' )	/* Skip space char */
	    ptr++;

	*g_pin = -1;
	if( *ptr != 0x00 ) /* Make sure string can be process */
	{
	    *g_pin = 0;
	    while( *ptr != 0x00 && *ptr >= '0' && *ptr <= '9' )
	    {
		*g_pin *= 10;
		*g_pin += (*ptr++ - '0');
	    }
	}

	while( *ptr == ' ' )	/* Skip space char */
	*g_val = -1;
	if( *ptr >= ' ' )
	{
	    if( *(ptr+1) == '0' || *(ptr+1) == 0x00 )
		*g_val = 0;
	    else
		*g_val = 1;
	}
}

static int  parse_date_param( char *ptr, unsigned char *date_ptr )
{
        char    buf[14];
	int     i;


	while( *ptr <= ' ' )
	    ptr++;
        if( strlen( ptr ) < (DATE_STRING_LENGTH*2) )
	    return -1;

	for( i=0; i<(DATE_STRING_LENGTH*2); i++ )
	{
	    if( *ptr < '0' || *ptr > '9' )
	        return -1;
	    buf[i] = *ptr - '0';
	    ptr++;
	}

	ptr = buf;
	for( i=0; i<DATE_STRING_LENGTH; i++ )
	{
	    *date_ptr = (*ptr++) * 10;
	    *date_ptr += *ptr++;
	    date_ptr++;
	}

	return 0;
}

static void gpio_setdirection( int gpio, int dir )
{
	em86xx_gpio_setdirection( gpio, dir );
}

static void gpio_write( int gpio, int val )
{
	em86xx_gpio_write( gpio, val );
}

static int  gpio_read( int gpio )
{
	return em86xx_gpio_read( gpio );
}


/************************************ Device Driver *************************************/
static int  button_open( struct inode *inode, struct file *file )
{
	return 0;
}

static int  button_read( struct file *filp, char *buf, size_t count, loff_t *ppos )
{
	if( wait_event_interruptible( wait_queue, (int)button_status ) < 0 )
	    return -1;

	if( copy_to_user( buf, &button_status, sizeof(button_status) ) )
	    return -EFAULT;

	/* Clean button status after read */
	button_status = 0;

	return sizeof(button_status);
}

static unsigned int button_poll( struct file *filp, struct poll_table_struct *wait )
{
	poll_wait( filp, &wait_queue, wait );

	/* If there is any data avilable then return POLLIN | POLLRDNORM */
	if( button_status )
	    return POLLIN | POLLRDNORM;

	return 0;
}

static int  button_release( struct inode *inode, struct file *file )
{
	return 0;
}


/************************************** I2C Driver **************************************/
static void I2C_Clock( int clock )
{
	gpio_setdirection( PIN_I2C_SCL, DIR_OUTPUT );
        gpio_write( PIN_I2C_SCL, clock );
	udelay( 10 );
}

static void I2C_Data( int data )
{
	gpio_setdirection( PIN_I2C_SDA, DIR_OUTPUT );
	gpio_write( PIN_I2C_SDA, data );
	udelay( 10 );
}

static void I2C_WrBit( int data )
{
	I2C_Data( data );
	I2C_Clock( ACTIVE_HIGH );
	I2C_Clock( ACTIVE_LOW );
}

static void I2C_RdBit( int *data )
{
	I2C_Clock( ACTIVE_HIGH );
	gpio_setdirection( PIN_I2C_SDA, DIR_INPUT );
	*data = gpio_read( PIN_I2C_SDA );
	I2C_Clock( ACTIVE_LOW );
}

static void I2C_Start( void )
{
#if 0
	/* A HIGH to LOW transition on the SDA line while SCL is HIGH indicates a START condition */
	I2C_Clock( ACTIVE_HIGH );
	I2C_Data( ACTIVE_HIGH );
	I2C_Data( ACTIVE_LOW );

	/* Hold the clock line SCL LOW to force the master into a wait state. Data transfer then continues when the slave is ready for another byte of data and releases clock line SCL */
	I2C_Clock( ACTIVE_LOW );
#else
	I2C_Data( ACTIVE_HIGH );
	I2C_Clock( ACTIVE_HIGH );
	I2C_Data( ACTIVE_LOW );
	I2C_Clock( ACTIVE_LOW );
#endif
}

static void I2C_Stop( void )
{
#if 0
	/* A LOW to HIGH transition on the SDA line while SCL is HIGH defines a STOP condition */
	I2C_Clock( ACTIVE_HIGH );
	I2C_Data( ACTIVE_LOW );
	I2C_Data( ACTIVE_HIGH );
#else
	I2C_Data( ACTIVE_LOW );
	I2C_Clock( ACTIVE_HIGH );
	I2C_Clock( ACTIVE_HIGH );
	I2C_Data( ACTIVE_HIGH );
#endif
}

static void I2C_SendNack( void )
{
	/* A HIGH to LOW transition on the SCL line while SDA is HIGH defines a NACK */
        I2C_Data( ACTIVE_HIGH );
        I2C_Clock( ACTIVE_HIGH );
        I2C_Clock( ACTIVE_LOW );
}

static void I2C_SendAck( void )
{
	/* A HIGH to LOW transition on the SCL line while SDA is LOW defines a ACK */
        I2C_Data( ACTIVE_LOW );
        I2C_Clock( ACTIVE_HIGH );
        I2C_Clock( ACTIVE_LOW );
}

static int  I2C_WaitAck( void )
{
	unsigned int lastRecvMs;

	gpio_setdirection( PIN_I2C_SDA, DIR_INPUT );

	I2C_Clock( ACTIVE_HIGH );

	lastRecvMs = jiffies_to_msecs( jiffies );

	while( gpio_read( PIN_I2C_SDA ) & ACTIVE_HIGH )
	{
	    if( (jiffies_to_msecs(jiffies) - lastRecvMs) > 0 )
		return -1;
	}

	I2C_Clock( ACTIVE_LOW );

	udelay(100);
	return 0;
}

static void I2C_WrByte( unsigned char ByteIn )
{
	int	i;

	for( i = 0; i < 8; i++ )
	{
	    I2C_WrBit( ByteIn & 0x80 );
	    ByteIn <<= 1;
	}
}

static void I2C_RdByte( unsigned char *data )
{
	int	i, bit;

	for( i = 0; i < 8; i++ )
	{
	    I2C_RdBit( &bit );
	    *data = (*data << 1) | (bit ? ACTIVE_HIGH : ACTIVE_LOW);
	}
}

static int  I2C_Write( unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n )
{
	unsigned int i;


	down( &lock );

	I2C_Start();
	I2C_WrByte( SlaveAddress|0x0 );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	I2C_WrByte( SubAddress );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	//I2C_SendAck();
	for( i = 0; i < n; i++ )
	{
	    I2C_WrByte( data[i] );
	    if( I2C_WaitAck() < 0 )
	    {
		up( &lock );
		return -1;
	    }
	}
	I2C_Stop();

	up( &lock );
	return 0;
}

static int  I2C_Read( unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n )
{
	unsigned int i;


	down( &lock );

	I2C_Start();
	I2C_WrByte( SlaveAddress|0x0 );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	I2C_WrByte( SubAddress );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	//I2C_SendAck();
	I2C_Start();
	I2C_WrByte( SlaveAddress|0x1 );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	for( i = 0; i < n; i++ )
	{
	    I2C_RdByte( &(data[i]) );
	    if( i == (n - 1) )
		I2C_SendNack();
	    else
		I2C_SendAck();
	}
	I2C_Stop();

	up( &lock );
	return 0;
}

static int  I2C_Device_Detect( unsigned char SlaveAddress )
{
	down( &lock );

	I2C_Start();
	I2C_WrByte( SlaveAddress|0x0 );
	if( I2C_WaitAck() < 0 )
	{
	    up( &lock );
	    return -1;
	}
	I2C_Stop();

	up( &lock );
	return 0;
}
/*******************************************************************************************************/
static struct	file_operations button_fops =
{
	.owner =	THIS_MODULE,
	.open =         button_open,
	.read =         button_read,
	.poll =         button_poll,
	.release =	button_release,
};

static struct	proc_dir_entry	*ent_root = NULL;
static struct	proc_dir_entry	*ent_gpio = NULL;
static struct	proc_dir_entry	*ent_cpu = NULL;
static struct	proc_dir_entry	*ent_rtc = NULL;
static struct	proc_dir_entry	*ent_fan = NULL;
static struct	proc_dir_entry	*ent_power = NULL;
static struct	proc_dir_entry	*ent_button = NULL;
static struct	proc_dir_entry	*ent_misc = NULL;

static struct	task_struct	*kthread_gpio = NULL;
int __init iomega_init_module( void )
{
	if( I2C_Device_Detect( WRITE_SLAVE_ADDRESS ) == 0 )
	{
	    printk( KERN_INFO "[IOM-554H] Found WT69P3 uP.\n" );
	}
	/* General and EHT0 GPIO direction will be programed in EZBOOT, and General GPIO 0~15 data will be initialized in EZBOOT also */
	/* ETH0 will be programed in EZBOOT if the target board is IOM-X2 */
	gpio_setdirection( PIN_USB_OC0, DIR_INPUT );
	gpio_setdirection( PIN_HDD_POWER, DIR_OUTPUT );
	gpio_setdirection( PIN_SATA_RESET, DIR_OUTPUT );
	gpio_setdirection( PIN_USB_DETECT, DIR_INPUT );
	gpio_setdirection( PIN_USB_SELECT, DIR_OUTPUT );
	gpio_setdirection( PIN_THERMAL_INT, DIR_INPUT );
	gpio_setdirection( PIN_POWER_BUTTON, DIR_INPUT );

	init_waitqueue_head( &wait_queue );

        if( register_chrdev( BUTTON_MAJOR, BUTTON_DEVICE, &button_fops) < 0 )
        {
	    printk( KERN_WARNING "[IOM-554H] Can't register device node.\n" );
	    return -1;
	}

	kthread_gpio = kthread_create( ktask_gpio, NULL, "ktask_gpio" );
	if( IS_ERR(kthread_gpio) )
	{
	    printk( KERN_INFO "[IOM-554H] Can't create GPIO monitor thread.\n" );
	    return -1;
	}
	wake_up_process( kthread_gpio );

	ent_root = proc_mkdir( PROC_ROOT, NULL );
	if( ent_root )
	{
	    ent_gpio = create_proc_entry( PROC_ROOT_GPIO, S_IFREG | 0666, ent_root );
	    if( ent_gpio )
	    {
		ent_gpio->nlink = 1;
                ent_gpio->write_proc = proc_write_gpio;
                ent_gpio->read_proc = proc_read_gpio;
	        ent_gpio->data = (void *)&proc_data_gpio;
	    }
	    ent_rtc = create_proc_entry( PROC_ROOT_RTC, S_IFREG | 0666, ent_root );
	    if( ent_rtc )
	    {
		ent_rtc->nlink = 1;
                ent_rtc->write_proc = proc_write_rtc;
                ent_rtc->read_proc = proc_read_rtc;
	    }
	    ent_cpu = create_proc_entry( PROC_ROOT_CPU, S_IFREG | 0444, ent_root );
	    if( ent_cpu )
	    {
		ent_cpu->nlink = 1;
                ent_cpu->read_proc = proc_read_cpu;
	    }
	    ent_fan = create_proc_entry( PROC_ROOT_FAN, S_IFREG | 0666, ent_root );
	    if( ent_fan )
	    {
		ent_fan->nlink = 1;
                ent_fan->write_proc = proc_write_fan;
		ent_fan->read_proc = proc_read_fan;
	    }
	    ent_power = create_proc_entry( PROC_ROOT_POWER, S_IFREG | 0222, ent_root );
            if( ent_power )
	    {
	        ent_power->nlink = 1;
		ent_power->write_proc = proc_write_power;
	    }
            ent_button = create_proc_entry( PROC_ROOT_BUTTON, S_IFREG | 0666, ent_root );
	    if( ent_button )
	    {
	        ent_button->nlink = 1;
		ent_button->write_proc = proc_write_button;
	        ent_button->read_proc = proc_read_button;
	    }
	    ent_misc = create_proc_entry( PROC_ROOT_MISC, S_IFREG | 0666, ent_root );
	    if( ent_misc )
	    {
		ent_misc->nlink = 1;
                ent_misc->write_proc = proc_write_misc;
                ent_misc->read_proc = proc_read_misc;
	        /* ent_misc->data = (void *)&proc_data_misc; */
	    }
	}
	else
	{
	    printk( KERN_WARNING "[IOM-554H] Can't create proc entry: %s\n", PROC_ROOT );
	    return -1;
	}

	printk( KERN_INFO "[IOM-554H] kernel driver %s has been installed.\n", DRIVER_VERSION );

	return 0;
}

void __exit iomega_cleanup_module( void )
{
	unregister_chrdev( BUTTON_MAJOR, BUTTON_DEVICE );

	if( ent_root )
	{
	    if( ent_gpio )
		remove_proc_entry( PROC_ROOT_GPIO, ent_root );
	    if( ent_rtc )
		remove_proc_entry( PROC_ROOT_RTC, ent_root );
	    if( ent_cpu )
		remove_proc_entry( PROC_ROOT_CPU, ent_root );
	    if( ent_fan )
		remove_proc_entry( PROC_ROOT_FAN, ent_root );
	    if( ent_power )
		remove_proc_entry( PROC_ROOT_POWER, ent_root );
	    if( ent_button )
		remove_proc_entry( PROC_ROOT_BUTTON, ent_root );
	    if( ent_misc )
		remove_proc_entry( PROC_ROOT_MISC, ent_root );

	    remove_proc_entry( PROC_ROOT, NULL );
	}

	if( kthread_gpio )
	    kthread_stop( kthread_gpio );

	printk( KERN_INFO "[IOM-554H] kernel driver %s has been removed.\n", DRIVER_VERSION );
}

module_init( iomega_init_module );
module_exit( iomega_cleanup_module );

MODULE_DESCRIPTION( "IOM-554H Kernel Driver" );
MODULE_AUTHOR( "Rance Chen" );
MODULE_LICENSE( "GPL" );
MODULE_VERSION( DRIVER_VERSION );

