/*************************************************************************
>> File Name: key.h
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月28日 星期日 00时03分52秒

>> 此程序的功能是：
************************************************************************/


#ifndef KEY_H
#define KEY_H



/*
功能：
 向密码机申请一定数量的用于加密数据的密钥，如果不设置新的keygen，那么生成的密码会顺序产生下去，每次申请密钥都会记录上次生成的密钥的偏移，下次在申请的时候，都会从上一位置继续分配密钥
参数：
 sync：同步码，密码机依据此同步产生随机序列的密钥
 key_num：申请的密钥个数
 key：申请的密钥存储的缓存
返回值:
 实际返回密钥个数
 */

int request_key(int sync,int key_num,char key[]);



/*
功能：
 向密码机设置keygen，设置后会影响产生的随机密钥序列
参数：
 key：密钥
返回值:
 无
*/

void set_keygen(int key);


/*
功能：
 根据同步码和keygen生成随机密钥种子
参数：
    sync：同步码
 key：密钥
返回值:
 种子
*/

int born_seed(int sync,int key);


/*
 功能：
 重置keygen，会影响生成的随机数序列
 */

void reset_keygen();



#endif
