#ifndef __REGULAR_EXPRESSION_H__
#define __REGULAR_EXPRESSION_H__
#include <pcre.h>

#define OVECCOUNT (9+1)*3 /* should be a multiple of 3 */

typedef struct regular_expression_s {
	pcre *re;
	const char *error;
	int erroffset;
	int ovector[OVECCOUNT];
	int rc;
	char *match[10];
	int match_length[10];
} regular_expression_t;

regular_expression_t *regular_expression_create(void);
int regular_expression_compile(regular_expression_t *regexp, const char *str);
#ifdef CONF_PRODUCT_EXT_IOM
int regular_expression_compile_ignore_case(regular_expression_t *regexp, const char *str);
#endif
int regular_expression_find(regular_expression_t *regexp, const char *data, int startoffset);
char *regular_expression_replace(regular_expression_t *regexp, const char *src);
char *regular_expression_string_replace(char *buffer, int size, char *src_string, char *dest_string);
char *regular_expression_getmatch(regular_expression_t *regexp, int no);
void regular_expression_destroy(regular_expression_t *regexp);
#endif
