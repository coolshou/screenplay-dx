/* Copyright (C) 2004, REDSonic, inc.
 * Author: Charles Wang <cwang@redsonic.com>
 */
#ifndef __MINIGETTEXT_H__
#define __MINIGETTEXT_H__

void load_locale(const char *locale);
void load_mofile(const char *mofilename);
void unload_mofile(void);
const char *gettext(const char *msgid);

#define _(str)    gettext(str)
#define N_(str)   (str)
#define X_(str)   ("$$"str)

#endif
