/*
 * vim:cindent:ts=8
 */
#ifndef	__CONFIG_ACCESS_H__
#define	__CONFIG_ACCESS_H__

enum TUPLE_TYPE{
	TUPLE_UNKNOWN=0,
	TUPLE_STRING,
	TUPLE_INT,
	TUPLE_STRING_DUP
};

struct	tuple_s	{
	char	*label;
	void	*container;
	enum TUPLE_TYPE   type;
};

typedef	struct	tuple_s	tuple_t;

#define	SECURESOHO_CONFIG	CONF_RELATIVE_PATH_FOR_RESOURCES  CONF_SETTING_CONFIG_FILE_DIR "/" CONF_SETTING_CONFIG_FILE_NAME

#define	SECURESOHO_TMP_CONFIG	CONF_RELATIVE_PATH_FOR_RESOURCES "/tmp/config"
#define	SECURESOHO_CONFIG_LOCK	CONF_RELATIVE_PATH_FOR_RESOURCES "/tmp/config_lock"

#define BROWSER_CONFIG_TXT	CONF_RELATIVE_PATH_FOR_RESOURCES "/tmp/conf/browser_config.txt"

#define	SOURCE_DIR		CONF_RELATIVE_PATH_FOR_RESOURCES CONF_SETTING_CONFIG_FILE_DIR

extern	int	securesoho_config_lock(void);
extern	void	securesoho_config_unlock(int fd);

extern	int	securesoho_values_set( tuple_t *);
extern	int	securesoho_values_get( tuple_t *);
extern	void	securesoho_string_get_from_file( const char *filename, const char *label, char *container );
extern	int	securesoho_string_set_to_file( const char *filename, const char *label, const char *target );
extern	void	securesoho_string_get( const char *label, char *container);
extern	int	securesoho_string_set( const char *label, const char *target );
extern	int	securesoho_int_get( const char *label );
extern	int	securesoho_int_set( const char *label, int val );

extern	void	securesoho_replace_config( char *path );

extern  int	securesoho_parse_value(char *buf, char *key, char *value);
extern	int	safe_rename( char *, char *);
extern	int	safe_cp( char *, char *);

#ifdef CONF_SAVE_DEFAULT_SETTING_IN_LAST_PARTITON
extern void    securesoho_string_get_from_last_partition(const char *label, char *container);
#endif

#endif
