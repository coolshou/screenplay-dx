
/* constant for an easy to read calculations */
#define SAMPLERATE 44100.0
#define MSEC 1000.0
#define PI 3.14159265358979323846  
#define PI2 2*PI 

/* Macro to saturate singal */
#define sat(x) (short)(x>32767?32767:(x<-32768?-32768:x));

/* Current Module's IDs */
#define FX_VOICE 0
#define FX_PITCH 1
#define FX_PAN 2
#define FX_MOD 3
#define FX_REVERB 4

/* Standard FX Module Struct */
typedef struct {
	int id;					/* FX ID */
	int enabled;			/* Is enabled? */
	int nParams;			/* Number of parameters */
	void (*handle)(int param, int value); /* Parameter handling routine */
	int (*process)(signed short *data, int len); /* FX processing routine */
	void (*init)();			/* module initialization */
	void (*done)();			/* module cleanup */
} FX;

/* Global entry points */
extern void defx_init();
extern void defx_done();
extern void defx_process(signed short *data, int len);
extern void defx_param(int id, int param, int value);

/* specific entry points */
static void fx_handle(int param, int value);
static int fx_process(signed short *data, int len);
static void fx_init();
static void fx_done();

