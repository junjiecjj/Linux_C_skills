/*************************************************************************
>> File Name: example1_A.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月05日 星期五 15时25分14秒

>> 此程序的功能是：
************************************************************************/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_PATH "/tmp/shm"
#define SHM_SIZE 128

int main(int argc, char *argv[]) {
  int shmid;
  char *addr;
  key_t key = ftok(SHM_PATH, 0x6666);

  shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
  if (shmid < 0) {
    printf("failed to create share memory\n");
    return -1;
  }

  addr = shmat(shmid, NULL, 0);
  if (addr <= 0) {
    printf("failed to map share memory\n");
    return -1;
  }

  sprintf(addr, "%s", "Hello World\n");

  return 0;
}
