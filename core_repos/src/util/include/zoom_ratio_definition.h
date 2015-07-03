#ifndef _ZOOM_RATIO_DEFINITION_H_


typedef enum _ZOOM_RATIO_IDX {
	ZOOM_NORMAL = 0,
	ZOOM_IN_1_1X, 	//1.1X
	ZOOM_IN_1_2X,	//1.2X
	ZOOM_IN_2X,
	ZOOM_IN_4X,
	ZOOM_IN_8X,
	ZOOM_OUT_2X,
	ZOOM_OUT_4X,
	ZOOM_OUT_8X,
	ZOOM_OUT_0_9X,
	ZOOM_OUT_0_8X,
	ZOOM_INVALID,
} ZOOM_RATIO_IDX;

typedef struct _ZOOM_RATIO_DATA {
	int idx;
	const char *default_name;
	double ratio;
} ZOOM_RATIO_DATA;

static ZOOM_RATIO_DATA ZoomRatioData[] =  //note: please make sure the order is the same with ZOOM_RATIO_IDX
	{
		{ZOOM_NORMAL,"1X",1.0f},
		{ZOOM_IN_1_1X,"1.1X",1.1f},
		{ZOOM_IN_1_2X,"1.2X",1.2f},
		{ZOOM_IN_2X,"2X",2.0f},
		{ZOOM_IN_4X,"4X",4.0f},
		{ZOOM_IN_8X,"8X",8.0f},
		{ZOOM_OUT_2X,"1/2X",1.0/2},
		{ZOOM_OUT_4X,"1/4X",1.0/4},
		{ZOOM_OUT_8X,"1/8X",1.0/8},
		{ZOOM_OUT_0_9X,"0.9X",0.9f},
		{ZOOM_OUT_0_9X,"0.8X",0.8f},
		{ZOOM_INVALID,"invalid",1.0f},
	};

typedef struct _ZOOM_RATIO_CUSTOM_DATA {
	int idx;
	int zoom_in_idx;
	int zoom_out_idx;
	const char *custom_name;
} ZOOM_RATIO_CUSTOM_DATA;

#define ZOOM_BEGIN_VALUE ZOOM_NORMAL 
#ifdef CONF_ZOOM_IN_OUT_CASE1

#define ZOOM_MAX_VAUE 7
//sizeof(ZoomRatioCustomZoomRule) / sizeof(ZOOM_RATIO_CUSTOM_DATA)

static ZOOM_RATIO_CUSTOM_DATA ZoomRatioCustomZoomRule[] =
	{
		{ZOOM_NORMAL,1,4,"1X"}, 	// 0 	: 1X -> 2X or 1/2X
		{ZOOM_IN_2X,2,0,"2X"},		// 1	: 2X -> 4X or 1X
		{ZOOM_IN_4X,3,1,"4X"},		// 2	: 4X -> 8X or 2X
		{ZOOM_IN_8X,0,2,"8X"},		// 3	: 8X -> 1X or 4X
		{ZOOM_OUT_2X,0,5,"1/2X"}, 	// 4	: 1/2 -> 1X or 1/4X
		{ZOOM_OUT_4X,4,6,"1/4X"},	// 5	: 1/4 -> 1/2 or 1/8X
		{ZOOM_OUT_8X,5,0,"1/8X"},	// 6	: 1/8 X -> 1/4X or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 7
	};
		
#define ZOOM_ZoomRatio1_2XZoomRule_MAX_VAUE 5
static ZOOM_RATIO_CUSTOM_DATA ZoomRatio1_2XZoomRule[] =
	{
		{ZOOM_NORMAL,1,3,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,0,1,"1.2X"}, 	// 2 	: 1.2X -> 1X or 1.1X
		{ZOOM_OUT_2X,0,4,"1/2X"}, 	// 3	: 1/2 -> 1X or 1/2X
		{ZOOM_OUT_4X,3,0,"1/4X"},	// 4	: 1/4 -> 1/2 or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 5
	};
#endif
#ifdef CONF_ZOOM_IN_OUT_CASE2

#define ZOOM_MAX_VAUE 9

static ZOOM_RATIO_CUSTOM_DATA ZoomRatioCustomZoomRule[] =
	{
		{ZOOM_NORMAL,1,6,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,3,1,"1.2X"}, 	// 2 	: 1.2X -> 2X or 1.1X
		{ZOOM_IN_2X,4,2,"2X"},		// 3	: 2X -> 4X or 1.2X
		{ZOOM_IN_4X,5,3,"4X"},		// 4	: 4X -> 8X or 2X
		{ZOOM_IN_8X,0,4,"8X"},		// 5	: 8X -> 1X or 4X
		{ZOOM_OUT_2X,0,7,"1/2X"}, 	// 6	: 1/2 -> 1X or 1/4X
		{ZOOM_OUT_4X,6,8,"1/4X"},	// 7	: 1/4 -> 1/2 or 1/8X
		{ZOOM_OUT_8X,7,0,"1/8X"},	// 8	: 1/8 X -> 1/4X or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 9
	};
#define ZOOM_ZoomRatio1_2XZoomRule_MAX_VAUE 5
static ZOOM_RATIO_CUSTOM_DATA ZoomRatio1_2XZoomRule[] =
	{
		{ZOOM_NORMAL,1,3,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,0,1,"1.2X"}, 	// 2 	: 1.2X -> 1X or 1.1X
		{ZOOM_OUT_2X,0,4,"1/2X"}, 	// 3	: 1/2 -> 1X or 1/2X
		{ZOOM_OUT_4X,3,0,"1/4X"},	// 4	: 1/4 -> 1/2 or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 5
	};
#endif
#ifdef CONF_ZOOM_IN_OUT_CASE3
#define ZOOM_MAX_VAUE 11

static ZOOM_RATIO_CUSTOM_DATA ZoomRatioCustomZoomRule[] =
	{
		{ZOOM_NORMAL,1,6,"1X"}, 	// 0 	: 1X -> 1.1X or 0.9X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,3,1,"1.2X"}, 	// 2 	: 1.2X -> 2X or 1.1X
		{ZOOM_IN_2X,4,2,"2X"},		// 3	: 2X -> 4X or 1.2X
		{ZOOM_IN_4X,5,3,"4X"},		// 4	: 4X -> 8X or 2X
		{ZOOM_IN_8X,0,4,"8X"},		// 5	: 8X -> 1X or 4X
		{ZOOM_OUT_0_9X,0,7,"0.9X"}, // 6	: 0.9 -> 1X or 0.8X
		{ZOOM_OUT_0_8X,6,8,"0.8X"}, // 7	: 0.8 -> 0.9X or 1/2X
		{ZOOM_OUT_2X,7,9,"1/2X"}, 	// 8	: 1/2 -> 0.8X or 1/4X
		{ZOOM_OUT_4X,8,10,"1/4X"},	// 9	: 1/4 -> 1/2 or 1/8X
		{ZOOM_OUT_8X,9,0,"1/8X"},	// 10	: 1/8 X -> 1/4X or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 11
	};

#define ZOOM_ZoomRatio1_2XZoomRule_MAX_VAUE 7
static ZOOM_RATIO_CUSTOM_DATA ZoomRatio1_2XZoomRule[] =
	{
		{ZOOM_NORMAL,1,3,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,0,1,"1.2X"}, 	// 2 	: 1.2X -> 1X or 1.1X
		{ZOOM_OUT_0_9X,0,4,"0.9X"}, // 3	: 0.9 -> 1X or 0.8X
		{ZOOM_OUT_0_8X,3,5,"0.8X"}, // 4	: 0.8 -> 0.9X or 1/2X
		{ZOOM_OUT_2X,4,6,"1/2X"}, 	// 5	: 1/2 -> 0.8X or 1/2X
		{ZOOM_OUT_4X,5,0,"1/4X"},	// 6	: 1/4 -> 1/2 or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 7
	};
#endif

#define ZOOM_ZoomRatio2XZoomRule_MAX_VAUE 6
static ZOOM_RATIO_CUSTOM_DATA ZoomRatio2XZoomRule[] =
	{
		{ZOOM_NORMAL,1,4,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,3,1,"1.2X"}, 	// 2 	: 1.2X -> 2X or 1.1X
		{ZOOM_IN_2X,0,2,"2X"},		// 3	: 2X -> 1X or 1.2X
		{ZOOM_OUT_2X,0,5,"1/2X"}, 	// 4	: 1/2 -> 1X or 1/2X
		{ZOOM_OUT_4X,4,0,"1/4X"},	// 5	: 1/4 -> 1/2 or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 6
	};



#define ZOOM_ZoomRatio2X__0x_8XZoomRule_MAX_VAUE 8
static ZOOM_RATIO_CUSTOM_DATA ZoomRatio2X__0_8XZoomRule[] =
	{
		{ZOOM_NORMAL,1,4,"1X"}, 	// 0 	: 1X -> 1.1X or 1/2X
		{ZOOM_IN_1_1X,2,0,"1.1X"}, 	// 1 	: 1.1X -> 1.2X or 1X
		{ZOOM_IN_1_2X,3,1,"1.2X"}, 	// 2 	: 1.2X -> 2X or 1.1X
		{ZOOM_IN_2X,0,2,"2X"},		// 3	: 2X -> 1X or 1.2X
		{ZOOM_OUT_0_9X,0,5,"0.9X"}, // 4	: 0.9 -> 1X or 0.8X
		{ZOOM_OUT_0_8X,4,6,"0.8X"}, // 5	: 0.8 -> 0.9X or 1/2X
		{ZOOM_OUT_2X,5,7,"1/2X"}, 	// 6	: 1/2 -> 0.8X or 1/2X
		{ZOOM_OUT_4X,6,0,"1/4X"},	// 7	: 1/4 -> 1/2 or 1X
		{ZOOM_INVALID,0,0,"1X"},	// 8
	};


static ZOOM_RATIO_CUSTOM_DATA *ZoomRatioRule = ZoomRatioCustomZoomRule;
static int ZoomRatioMaxValue = ZOOM_MAX_VAUE;
#define ZOOM_RATIO_DEFAULT_RULE 0
#define ZOOM_RATIO_ZoomRatio2XZoomRule 1
#define ZOOM_RATIO_ZoomRatio1_2XZoomRule 2  //the max zoom in value is 1.2X

#define SetZoomRule(x) \
{					\
	ZoomRatioRule = ZoomRatioCustomZoomRule ; \
	ZoomRatioMaxValue = ZOOM_MAX_VAUE;	\
	if (x == ZOOM_RATIO_DEFAULT_RULE) { \
		ZoomRatioRule = ZoomRatioCustomZoomRule ; \
		ZoomRatioMaxValue = ZOOM_MAX_VAUE;	\
	} else if (x == ZOOM_RATIO_ZoomRatio2XZoomRule) { \
		ZoomRatioRule = ZoomRatio2XZoomRule;	\
		ZoomRatioMaxValue = ZOOM_ZoomRatio2XZoomRule_MAX_VAUE ; \
	} else if (x == ZOOM_RATIO_ZoomRatio1_2XZoomRule) { \
		ZoomRatioRule = ZoomRatio1_2XZoomRule;	\
		ZoomRatioMaxValue = ZOOM_ZoomRatio1_2XZoomRule_MAX_VAUE ; \
	} \
}
#define GetZoomInValue(x) ((x<ZoomRatioMaxValue && ZoomRatioRule) ? ZoomRatioRule[x].zoom_in_idx : ZOOM_BEGIN_VALUE)
#define GetZoomOutValue(x) ((x<ZoomRatioMaxValue && ZoomRatioRule) ? ZoomRatioRule[x].zoom_out_idx: ZOOM_BEGIN_VALUE)
#define GetZoomText(x) ((x<ZoomRatioMaxValue && ZoomRatioRule) ? ZoomRatioRule[x].custom_name : "")
#define GetZoomRatioValue(x) ((x<ZoomRatioMaxValue && ZoomRatioRule) ? ZoomRatioData[ZoomRatioRule[x].idx].ratio : 1.0)

#endif
