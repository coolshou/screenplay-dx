#ifndef __SQLITE3_WRAPPER__
#define __SQLITE3_WRAPPER__

typedef int db_status_t;
/*For simplisity, the db status return value is the same with sqlite3 status value */
#define db_status_is_success db_sqlite3_is_success
#define db_status_is_busy db_sqlite3_is_busy
#define db_mutex_lock do {}while(0)
#define db_mutex_unlock do {}while(0)

#define MAX_RETRY_COUNT 10
#define MAX_RETRY_SLEEP 300000

/**
 * Mapping of C to SQL types, used for prepared statements.
 */
typedef enum {
    DB_TYPE_NONE,
    DB_TYPE_TINY,       /**< \%hhd : in, out: char* */
    DB_TYPE_UTINY,      /**< \%hhu : in, out: unsigned char* */
    DB_TYPE_SHORT,      /**< \%hd  : in, out: short* */
    DB_TYPE_USHORT,     /**< \%hu  : in, out: unsigned short* */
    DB_TYPE_INT,        /**< \%d   : in, out: int* */
    DB_TYPE_UINT,       /**< \%u   : in, out: unsigned int* */
    DB_TYPE_LONG,       /**< \%ld  : in, out: long* */
    DB_TYPE_ULONG,      /**< \%lu  : in, out: unsigned long* */
    DB_TYPE_LONGLONG,   /**< \%lld : in, out: apr_int64_t* */
    DB_TYPE_ULONGLONG,  /**< \%llu : in, out: apr_uint64_t* */
    DB_TYPE_FLOAT,      /**< \%f   : in, out: float* */
    DB_TYPE_DOUBLE,     /**< \%lf  : in, out: double* */
    DB_TYPE_STRING,     /**< \%s   : in: char*, out: char** */
    DB_TYPE_TEXT,       /**< \%pDt : in: char*, out: char** */
    DB_TYPE_TIME,       /**< \%pDi : in: char*, out: char** */
    DB_TYPE_DATE,       /**< \%pDd : in: char*, out: char** */
    DB_TYPE_DATETIME,   /**< \%pDa : in: char*, out: char** */
    DB_TYPE_TIMESTAMP,  /**< \%pDs : in: char*, out: char** */
    DB_TYPE_ZTIMESTAMP, /**< \%pDz : in: char*, out: char** */
    DB_TYPE_BLOB,       /**< \%pDb : in: char* apr_size_t* char* char*, out: apr_bucket_brigade* */
    DB_TYPE_CLOB,       /**< \%pDc : in: char* apr_size_t* char* char*, out: apr_bucket_brigade* */
    DB_TYPE_NULL        /**< \%pDn : in: void*, out: void** */
} db_type_t;

typedef struct db_transaction_t db_transaction_t;
typedef struct db_prepared_t db_prepared_t;
typedef struct db_t db_t;
typedef struct db_column_t db_column_t;
typedef struct db_row_t db_row_t;
typedef struct db_results_t db_results_t;

struct db_transaction_t {
	int mode;
	int errnum;
	db_t *handle;
};

struct db_prepared_t {
	sqlite3_stmt *stmt;
	struct db_prepared_t *next;
	int nargs;
	int nvals;
	db_type_t *types;
};

struct db_t {
	sqlite3 *conn;
	db_transaction_t *trans;
	db_prepared_t *prep;
};

struct db_column_t {
	char *name;
	char *value;
	size_t size;
	int type;
};

struct db_row_t {
	db_results_t *res;
	db_column_t **columns;
	db_row_t *next_row;
	int columnCount;
	int rownum;
};

struct db_results_t {
	int random;
	sqlite3 *handle;
	sqlite3_stmt *stmt;
	db_row_t *next_row;
	size_t sz;
	int tuples;
	char **col_names;
};

const char *db_error(db_t * sql);
int db_sqlite3_is_success(int x);
int db_sqlite3_is_busy(int x);

db_t *db_open(const char *db_file, char **error);
db_status_t db_close(db_t * handle);
db_status_t db_select(db_t * sql, db_results_t ** results, const char *query, int seek);
db_status_t db_query(db_t * sql, int *nrows, const char *query);
db_status_t db_prepare(db_t * sql, const char *query, const char *label,
		      int nargs, int nvals, db_prepared_t ** statement);
db_status_t db_get_row(db_results_t * res, db_row_t ** rowp, int rownum);
char *db_get_entry(const db_row_t * row, int n);
db_status_t db_clear_row(db_row_t **row);
db_status_t db_clear_results(db_results_t **results);
db_status_t db_start_transaction(db_t * handle, db_transaction_t ** trans);
db_status_t db_end_transaction(db_transaction_t * trans);

/*
 * return 
 *    -1 for unknown error
 *     0 if table is not exist
 *     1 if table is exist
 */

db_status_t db_is_table_exist(db_t *handle, const char *table);
#endif
