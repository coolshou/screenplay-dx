#ifndef __BMPREADER_H
#define __BMPREADER_H
typedef struct {
	int w,h;
	unsigned int *palette;
	unsigned char *image;
} BMPData;


/**
 *  Description
 *      Load an 4bpp BMP file. This loader can only load 4bpp image whose palette is 16 entries.
 */
BMPData *BMPCursor_Load(const char *name);


/**
 *   Description
 *      Free the data allocated in BMPCursor_Load.
 *
 *
 */
void BMPCursor_Free(BMPData *bmp);
	
#endif
