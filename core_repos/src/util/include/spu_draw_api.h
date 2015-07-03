#ifndef _SPU_DRAW_API_H_
#define _SPU_DRAW_API_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#define SPU_SCALER_HEIGHT 720
#define SPU_SCALER_WIDTH 1280
#define SPU_POSITION_X 100
#define SPU_POSITION_Y 525
/* adjustment the font size if we change the SPU_SCALER_WIDTH and SPU_SCALER_HEIGHT
 * 1920x1080 FONT_SIZE_OFFSET is 26 
 * 1280x720 FONT_SIZE_OFFSET is 0 
 * */
#define FONT_SIZE_OFFSET 0
typedef enum{
	SUBTITLE_ON_SMP863X_SPU,
	SUBTITLE_ON_SMP863X_OSD,
	SUBTITLE_ON_SMP863X_DFB
}spu_plugin_type;

struct spu_hal_s {
	/* open the hal and do necessary initialization job, such as open scaler, setup the window size to default value */
	int (*open)(void *, void **, int, int, unsigned long int *, size_t, int);
	/* draw subtitle buffer on scaler or frame buffer */
	int (*draw)(void *, void *, unsigned char *,unsigned long int,unsigned long int, size_t, int, int);
	/* destroy the necessary resources */
	int (*close)(void *, void*);
	int (*set_palette)(void *, void *, unsigned long int *, size_t);
};

enum _SPU_FONT_TYPE {
	SPU_FONT_TYPE_DEFAULT = 0,
	SPU_FONT_TYPE_MBF = 1,
	SPU_FONT_TYPE_FREETYPE =2,
};

typedef struct spu_hal_s spu_hal_t;

struct spu_handler_s {
	spu_hal_t 		op;
	int 			x; 
	int 			y;
	int 			spu_width;
	int 			spu_height;
	int 			x_gap;			// x_gap: the gap between two words.
	int 			y_gap;			// y_gap: the gap between two string line.
	int 			font_size;
	int 			subtitle_outline;
	unsigned char	*bmp_buf;		// screen buffer (as large as screen w*h*1)
	unsigned long 	bmp_buf_size;		// screen buffer size
	unsigned char 	*line_buf;		// all text draw in a row (line) buffer
	unsigned long 	line_buf_size;		// line buffer size
	unsigned int 	line_height;
	unsigned int 	line_width;
	void 			*font;
	void 			*scaler_data;
	void 			*scaler_info;
	char 			additional_encoding[20];
	int			is_arabic;	// 1: Text direction from right to left. 0 : English style.
	int			last_bmp_buf_size;
	enum _SPU_FONT_TYPE font_type;
};

typedef struct spu_handler_s spu_handler_t;

spu_handler_t *spu_init(void *_scaler_data, spu_plugin_type pt, int font_size, int width, int height, unsigned int x, unsigned int y, unsigned long int *spu_lut, size_t lut_size, char *font_file, int keycolor_index);
spu_handler_t *spu_init_font_type(void *_scaler_data, spu_plugin_type pt, int font_size, int width, int height, unsigned int x, unsigned int y, unsigned long int *spu_lut, size_t lut_size, char *font_file, int keycolor_index,enum _SPU_FONT_TYPE font_type);
int spu_set(spu_handler_t *handler, unsigned char *str1, int len1, unsigned char *str2, int len2, int keycolor_index);
int spu_set_bitmap(spu_handler_t *handler, char *bmp_buf, int buf_size, int x, int y, int width, int height, int keycolr_index);
int spu_get_default_palette(unsigned long int *palette, size_t size);
int spu_freetype_get_default_palette (unsigned long int *palette, size_t size);
int spu_get_font_file(char *store_file, char *font, size_t size);
int spu_uninit(void *_scaler_data, spu_handler_t *handler);
int spu_set_palette(spu_handler_t *handler, unsigned long int *palette, size_t size);
int spu_update_position(spu_handler_t *handler, int keycolor_index);
int spu_get_palette(unsigned long int *palette, size_t size, unsigned int bg_color, unsigned int text_color, unsigned int outline_color);

#define X_DEFAULT_POSITION 1
/* 
 * FONT_Y_BASELINE: * set the subtitle Y position
 */
#define FONT_Y_BASELINE 660
#define MAX_WORDS_OF_SUBTITLE 2048
#define TEXT_EFFECT_NONE 0
#define TEXT_EFFECT_OUTLINE 1
#define TEXT_EFFECT_OUTLINE_BOLD 2
#define MAX_LINE_NUMBER 32

#endif

