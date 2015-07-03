#ifndef __CHARSET_DETECTOR_WRAP__
#define __CHARSET_DETECTOR_WRAP__

void perform_charset_detection_buf(char* buf, char* encoding);
void perform_charset_detection_file(FILE* fp, char* encoding);
int charset_translate(char *from_code, char *to_code, char *inbuf, int insz, char *outbuf, int outsz);
int charset_convert(char *inbuf, int insz, char *outbuf, int outsz);
int charset_guess(char *buf, char *charset);
#endif // __CHARSET_DETECTOR_WRAP__ 
