#ifndef _TWO_WAY_INDEX_TABLE_H_
#define _TWO_WAY_INDEX_TABLE_H_


typedef enum _TWO_WAY_INDEX_TABLE_RETURN {
	TWO_WAY_INDEX_TABLE_INFO_OK = 0,
	TWO_WAY_INDEX_TABLE_INFO_ERRPR = -1,	
	TWO_WAY_INDEX_TABLE_INFO_MEMORY = -2, // allocate memory error
} TWO_WAY_INDEX_TABLE_RETURN;

typedef int (*TWIT_User_Relase_Value) (void *value);  //TWO_WAY_INDEX_TABLE relase value function prototype

/*
	purpose : to create the instance used for two way index table search
	remarks:
		1) the max_static_index_number is indicate the size of static index table in the two_way index_table search
		2) if the max_static_index_number is 0, we will use default value : 5K
		3) the func is used for free the value pointer from two_way_index_table_add function.
*/
void *two_way_index_table_create(int max_static_index_number,TWIT_User_Relase_Value func);

/*
	purpose : destroy the two way index table search instance
*/
void two_way_index_table_destroy(void *_pdata);

/*
	purpose : add a data in to two_way_index_table
	remarks:
		1) success return TWO_WAY_INDEX_TABLE_INFO_OK 
		2) the target that the user wants to build in the index table.
*/
TWO_WAY_INDEX_TABLE_RETURN two_way_index_table_add(void *_pdata,char *target,void *value);

/*
	purpose : remove a data from two_way_index_table
	remarks:
		1) return TWO_WAY_INDEX_TABLE_INFO_OK means success
*/
TWO_WAY_INDEX_TABLE_RETURN two_way_index_table_del(void *_pdata,char *target);

/*
	purpose : search a data from two_way_index_table
	remarks:
		1) return the value pointer that the user add in the two_way_index_table_add function
*/
void *two_way_index_table_search(void *_pdata, char *target);

#endif
