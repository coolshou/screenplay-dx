#ifndef __LED_API_H_ 

typedef enum {
        IO_EXPANDER_READY,
        IO_EXPANDER_BUSY
} io_expander_state_t;

#define LED_IOC_MAGIC           's'
#define POWER_LED_A_ON		_IO(LED_IOC_MAGIC, 0)
#define POWER_LED_A_OFF		_IO(LED_IOC_MAGIC, 1)
#define POWER_LED_G_ON		_IO(LED_IOC_MAGIC, 2)
#define POWER_LED_G_OFF		_IO(LED_IOC_MAGIC, 3)
#define POWER_LED_STATUS	_IO(LED_IOC_MAGIC, 4)
#define NETWORK_LED_ON 		_IO(LED_IOC_MAGIC, 5)
#define NETWORK_LED_OFF		_IO(LED_IOC_MAGIC, 6)
#define NETWORK_LED_BLINKING	_IO(LED_IOC_MAGIC, 7)

#define GPIO_SCART_ENABLE		_IO(LED_IOC_MAGIC, 8)
#define GPIO_SCART_DISABLE		_IO(LED_IOC_MAGIC, 9)
#define SEL_HD_L_ENABLE		_IO(LED_IOC_MAGIC, 11)
#define SEL_HD_L_DISABLE	_IO(LED_IOC_MAGIC, 12)
#define PAL_NTSC_L		_IO(LED_IOC_MAGIC, 13)
#define ASPECT_RATIO_16_9 	_IO(LED_IOC_MAGIC, 14)
#define ASPECT_RATIO_4_3	_IO(LED_IOC_MAGIC, 15)
#define AUDIO_LR		_IO(LED_IOC_MAGIC, 16)
#define AUDIO_7_1		_IO(LED_IOC_MAGIC, 17)
#define TYPE_RGB_OUTPUT		_IO(LED_IOC_MAGIC, 18)
#define TYPE_CVBS_OUTPUT	_IO(LED_IOC_MAGIC, 19)
#define SCT_S_SEL_S_VIDEO		_IO(LED_IOC_MAGIC, 20)
#define SCT_S_SEL_CVBS_RGB		_IO(LED_IOC_MAGIC, 21)

extern void GPIO_set_SCART(int enable);
extern void GPIO_set_HDTV(int enable);
extern void GPIO_set_aspect_ratio(int is_16_9);
extern void GPIO_set_audio(int is_7_1);
extern void GPIO_set_SCART_output(int is_RGB);
extern void GPIO_set_S_video(int enable);

int acer_gpio_get_set(unsigned short mask, unsigned short value, int get_set);

void Power_Led_A_On(void);
void Power_Led_A_Off(void);
void Power_Led_G_On(void);
void Power_Led_G_Off(void);
/*
        name
                Power_Led_Status  - Get power led status.
        synopsis
                #include <led_api.h>
		void Power_Led_Status(int *status);

        description
                Get power led status function.
        input parameters
		int *status
				0 is off 
				1 is on
	return value
                None
*/
void Power_Led_Status(int *status);
void Network_Led_On(void);
void Network_Led_Off(void);
void Network_Led_Blinking(void);
/*
        name
                Power_Led_Status  - Get power led status.
        synopsis
                #include <led_api.h>
		void Power_Led_Status(int *status);
		void Network_Led_Status(int *status);

        description
                Get power led status function.
        input parameters
		int *status
				0 is off 
				1 is on
				2 is blinking
	return value
                None
*/
void Network_Led_Status(int *status);


#endif /* _WCN_LED_API_H_ */
