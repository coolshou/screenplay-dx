/* -*- mode: C; c-basic-offset: 8; indent-tabs-mode: nil; tab-width: 8 -*- */

//#include "config.h"

#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <stdio.h>
#include "url.h"
typedef struct _Progress Progress;

struct _Progress {
        unsigned char tty;	/* if we have a tty */
        long int length;	/* total length */
        long int current;	/* current position */
        long int offset;	/* if we're resuming, save the offset */
        int max_hashes;		/* max number of hashes to print */
        int cur_hashes;		/* total hashes printed so far*/
        int overflow;		/* save the remainder */
        unsigned char frame;	/* frame for the spinny animation */
        double start_time;	/* for calculating k/sec */
        UrlResource *rsrc;	/* Info such as file name and offset */
};

enum report_levels { DEBUG, WARN, ERR };

#ifdef PROTOTYPES

Progress *progress_new(void);
int progress_init(Progress *, UrlResource *, long int);
void progress_update(Progress *, long int);
void progress_destroy(Progress *);
double double_time(void);

char *string_lowercase(char *);
char *get_proxy(const char *);
int dump_data(UrlResource *, int, FILE *);
char *strconcat(char *, ...);
char *base64(char *, int);
void report(enum report_levels, char *, ...);
int tcp_connect(char *, int);
off_t get_file_size(const char *);
void repchar(FILE *fp, char ch, int count);
long long int util_strtoll(char *p);

#if 0
int transfer(UrlResource *rsrc);
#endif


#ifndef HAVE_STRDUP
//char *strdup(const char *s);
#endif

#endif /* PROTOTYPES */

extern int debug_enabled;

#define open_outfile(x)  (((x)->outfile[0] == '-') ? stdout : real_open_outfile(x))
#define real_open_outfile(x)  (((x)->options & OPT_RESUME && !((x)->options & OPT_NORESUME)) ? (fopen((x)->outfile, "a")) : (fopen((x)->outfile, "w")))

#define safe_free(x)                             \
	do {                                     \
		if (x) {                         \
			free(x);                 \
			x = NULL;                \
		}                                \
	} while (0)

#define safe_strdup(x)		( (x) ? strdup(x) : NULL )
#define BUFSIZE (8*2048)



#endif
