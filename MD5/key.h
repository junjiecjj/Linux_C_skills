#ifndef _KEY_STATION
#define _KEY_STATION
#define MAX_KEY_REQUEST 512


void set_keygen(int key);
int born_seed(int sync,int key);
int request_key(int sync,int key_num,char key[]);


#endif
