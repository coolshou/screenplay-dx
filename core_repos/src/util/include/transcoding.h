/* 
 * Copyright (C) 2007, ALPHA Networks, inc.
 * vim:cindent:ts=8:
 */
#ifndef __AUTO_TRANSCODING__
#define __AUTO_TRANSCODING__

#define CHARDET_NAME_UTF8			"UTF-8"
#define CHARDET_NAME_WESTERN_EUROPE		"ISO-8859-1"
#define CHARDET_NAME_WESTERN_EUROPE_WINDOWS_1252 "WINDOWS-1252"
#define CHARDET_NAME_CENTRAL_EUROPE		"ISO-8859-2"
#define CHARDET_NAME_CENTRAL_EUROPE_WINDOWS_1250 "WINDOWS-1250"
#define CHARDET_NAME_TRADITIONAL_CHINESE	"BIG-5"
#define CHARDET_NAME_SIMPLIFIED_CHINESE         "GB18030"
#define CHARDET_NAME_JAPANESE                   "SHIFT_JIS"
#define CHARDET_NAME_KOREAN                     "EUC-KR"
#define CHARDET_NAME_CYRILLIC_WINDOWS_1251	"WINDOWS-1251"
#define CHARDET_NAME_CYRILLIC_KOI8_R		"KOI8-R"
#define CHARDET_NAME_GREEK			"ISO-8859-7"
#define CHARDET_NAME_GREEK_WINDOWS_1253		"WINDOWS-1253"
#define CHARDET_NAME_TURKISH_WINDOWS_1254	"WINDOWS-1254"
#define CHARDET_NAME_ARABIC_WINDOWS_1256	"WINDOWS-1256"
#define CHARDET_NAME_THAI_WINDOWS_874		"WINDOWS-874"
#define CHARDET_NAME_HEBREW                 "ISO-8859-8"

const char *string_transcoding_to_utf8(char *from_code, char *inbuf);
int string_additional_encoding_translate(char *from_code, char *to_code, char *inbuf, int insz, char *outbuf, int outsz);
int string_is_legalutf8sequence(char *source, int len);
#endif

