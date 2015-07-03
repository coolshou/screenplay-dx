#ifndef __REDSONIC_DBG_UTIL_H__
#define __REDSONIC_DBG_UTIL_H__

#define NORMAL_OUTPUT() printf("[0m\n")
#define RED_OUTPUT() printf("[1;41m")
#define GREEN_OUTPUT() printf("[1;42m")
#define BLUE_OUTPUT() printf("[1;44m")

#define EVIDENT_OUTPUT(msg) printf("[1;33;44m%s():%d %s[0m\n",__FUNCTION__,__LINE__,msg)
#define ERROR_OUTPUT(msg) printf("[1;33;41mERROR[0m %s():%d %s\n",__FUNCTION__,__LINE__,msg)

#endif //__REDSONIC_DBG_UTIL_H__

