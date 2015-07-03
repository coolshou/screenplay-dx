#ifndef __SUBTITLE_API_H
#define __SUBTITLE_API_H

#define NUMBER_SUBFILE 64
#define LENGTH_SUBFILE_NAME 50
#define NUM_SUB_SHOW 5

#define MAX_SUBTITLE_COLOR_NUM 5

typedef enum ENUM_MEDIA_TYPE_s {
	MEDIA_TYPE_AUDIO = 0,
	MEDIA_TYPE_VIDEO,
} ENUM_MEDIA_TYPE;

typedef enum ENUM_SOURCE_TYPE_s {
	SOURCE_TYPE_LOCAL = 0,
	SOURCE_TYPE_SERVER,
}ENUM_SOURCE_TYPE;

typedef	enum subtitle_attribute_e {
	SUBTITLE_ATTRIBUTE_NONE,
	SUBTITLE_ATTRIBUTE_STRING,
	SUBTITLE_ATTRIBUTE_PICTURE,
} subtitle_attribute_t;

typedef struct {
	long        	 time_on;
	long        	 time_off;
	char        	*text[2];
	int          	fillpos;

	subtitle_attribute_t	attrib;
	/*
	 * Below parameters MUST BE filled if the attrib is SUBTITLE_ATTRIBUTE_PICTURE
	 */ 
	int		x,y,w,h;
	int		frame_width;
	int		frame_height;
	char		*pvob_buf;
	unsigned long int	vob_size;
	unsigned int palette[16];
	int alpha[16];
	int default_spu_keycolor_index;
} subtitle_content_t;

struct	subtitle_plugin_s; 
typedef struct {
	subtitle_content_t	*content;
	int           curpos;
	int           total;
	void		*priv;
	struct	subtitle_plugin_s	*ref_plugin;
	/* for get property */
	int		frame_width;
	int		frame_height;
} subtitle_object_t;

typedef struct {
	int           frame_width;
	int           frame_height;
	int           is_vobsub;
	int		get_vobsub_palette;
	int		default_spu_keycolor_index;
	int		palette[4];
	int		alpha[4];
} subtitle_property_t;

typedef enum ENUM_SUBTITLE_TYPE_s {
	SUBTITLE_TYPE_NONE = 0,
	SUBTITLE_TYPE_SRT,
	SUBTITLE_TYPE_SUB,
	SUBTITLE_TYPE_SMI,
	SUBTITLE_TYPE_SSA,
	SUBTITLE_TYPE_ASS,
	SUBTITLE_TYPE_SUBVIEWER,
	SUBTITLE_TYPE_SUBVIEWER2,
	SUBTITLE_TYPE_LRC,
	SUBTITLE_TYPE_VOBSUB,
	SUBTITLE_TYPE_PSB,
}ENUM_SUBTITLE_TYPE;

typedef enum {
	SUBTITLE_OK = 0,
	SUBTITLE_INEXISTENCE,
	SUBTITLE_CAN_NOT_OPEN,
	SUBTITLE_NOT_UTF8,
	SUBTITLE_ERROR,
}ENUM_SUBTITLE_STATE;

typedef struct {
	ENUM_MEDIA_TYPE		media_type;
	ENUM_SOURCE_TYPE	source_type;
	ENUM_SUBTITLE_TYPE	subtitle_type;
} subtitle_desc_t;

typedef struct subtitle_plugin_s {
	int type;
	int media_type;
	subtitle_object_t 	*(*set)(const char *subfilepath,int id, int frame_rate);
	int 			(*check)(const char *ext,FILE *fp, int *ptr_num_subtitles);
	subtitle_content_t 	*(*parse)(subtitle_object_t *object, long time);
	void			(*destroy)(subtitle_object_t *object );
	void			(*get_property)(subtitle_property_t *property, subtitle_object_t *sub);
}subtitle_plugin_t;

/*
 * External API
 */
void	subtitle_plugin_factory(void);
int	subtitle_get_count(subtitle_desc_t *desc, char *fullpath);
int	subtitle_get_property(subtitle_property_t *property);
/*
 * Parameter frame_rate is for MicroDVD subtilte to calcualate time.
 * If you want to call this API, just fill it as zero.
 */
int	subtitle_set(int id, int frame_rate);
subtitle_content_t	*subtitle_display(long time);
void	subtitle_reset(void);
char *subtitle_getname(int id);
int subtitle_get_font_color(int index, unsigned int *bg_color, unsigned int *text_color, unsigned int *outline_color);

typedef struct subtitle_vobsub_dec_data_s {
	char		*pbmp_buf;
	int		bmp_size;
	int		x,y,w,h;
	char		*pvob_buf;
	unsigned long int	vob_size;
	unsigned int palette[16];
	int alpha[16];
	int color[4];
	int default_spu_keycolor_index;
} subtitle_vobsub_dec_data_t;

void *vobsub_dec_open(unsigned int *palette, unsigned int *cuspal, unsigned int custom, unsigned int frame_width, unsigned int frame_height, unsigned int tridx);
void vobsub_dec_assemble(void *this, unsigned char *packet, unsigned int len, long pts_ms);
void vobsub_dec_close(void *this);
void vobsub_dec_get(void *this,subtitle_vobsub_dec_data_t *subtitle);
unsigned int vobsub_rgb_to_vyu(unsigned int rgb);
subtitle_vobsub_dec_data_t * subtitle_vobsub_dec_data_init(int w, int h);
void subtitle_vobsub_dec_data_uninit(subtitle_vobsub_dec_data_t *subtitle);
char *subtitle_skip_tag(char *buf,int remove_all_tags, int remove_crlf);
subtitle_vobsub_dec_data_t *xsub_dec_init(unsigned char *data, int data_size,int is_DXSA);
void xsub_dec_close(subtitle_vobsub_dec_data_t *subtitle);
#ifdef CONF_PGS_SUBTITLE_SUPPORT
void parse_pes_stream(unsigned char *pBuffer1,unsigned long size1,
	void (*cb)(int id,int w,int h,int x,int y,unsigned char *data,int size,unsigned long int *palette, int pal_size,long long int pts, int frame_width, int frame_height),int idx,int video_w,int video_h);
void PGS_Context_Free(void);
#endif
/*
 * Internal API
 */
void	subtitle_object_destroy(subtitle_object_t **object);
char	*subtitle_ignore_line_break(char *text);
void	subtitle_get_property_common(subtitle_property_t *property, subtitle_object_t *sub);
int subtitle_sort(subtitle_content_t  *content,subtitle_content_t  *tmp_content,int l,int r);

subtitle_content_t	*subtitle_get_subtitle_content_by_time(subtitle_object_t *object, long time);


#endif
