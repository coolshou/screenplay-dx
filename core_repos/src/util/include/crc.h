#ifndef	__CRC_H__
#define	__CRC_H__

unsigned long update_crc (unsigned long crc, char *buf, int len);
void make_crc_table (void);
unsigned long calculate_file_crc( const char *filename, int maxlen );

#endif	// __CRC_H__

