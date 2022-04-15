/*
    Hoonhwi
*/
#ifndef SHARED_h
#define SHARED_h

#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>

#define SUCCESS 0
#define FAIL -1

const int  KEY_NUM =  1234;
const int  SHARED_SIZE = 4096;

char buffer[SHARED_SIZE] = {0,};
int buffer_type;

// defined memory
int shmid;

  
int SharedMemoryInit()
{
    // memory address
    void *shmaddr;

    // request shared memory to kernel
    if((shmid = shmget((key_t)KEY_NUM, 0, 0)) == -1)
    {
        perror("Shmid key failed");
    }
    return SUCCESS;
}

int SharedMemoryCreate()
{
 if((shmid = shmget((key_t)KEY_NUM, SHARED_SIZE, IPC_CREAT| IPC_EXCL | 0666)) == -1)
  {
    printf("Redefinition of Shared-Key, reset key\n");

	// if fail to create shared memory 
    shmid = shmget((key_t)KEY_NUM, SHARED_SIZE, IPC_CREAT| 0666);
    if(shmid == -1)
    {
        perror("Shared memory resest fail");
        return FAIL;
    }
	else
	{
		// delete shared memory
		if(shmctl(shmid, IPC_RMID, 0) == -1) 
		{
			perror("Shared memory delete fail");
            return FAIL;
		}

		// create shared memory
		shmid = shmget((key_t)KEY_NUM, SHARED_SIZE, IPC_CREAT| 0666);
		if(shmid == -1)
		{
			perror("Shared memory create fail");
            return FAIL;
		}
	}
  }
  return SUCCESS;
}

int SharedMemoryRead(char *buffer)
{
    // memory address
    void *shmaddr;

    // attach shmid
    if((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
    {
        perror("Shmat shmid failed");
    }

    // read
    memcpy(buffer, (char *)shmaddr, sizeof(buffer));

    // detach shmaddr
    if(shmdt(shmaddr) == -1)
    {
        perror("Shmdt shmaddr failed");
    }
    return SUCCESS;
}

int SharedMemoryWrite(char *buffer)
{
    void *shmaddr;
    if(sizeof(buffer) > SHARED_SIZE)
    {
        printf("Shared memory size over");
        return FAIL;
    }
    
    // attach memory
    if((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1) 
    {
        perror("Shmat failed");
        return FAIL;
    }

    // buffer to memory
    printf("size(%d) write buffer: %d\n", sizeof(buffer), atoi(buffer));
    memcpy((char *)shmaddr, buffer, sizeof(buffer));
    
    // detach memory
    if(shmdt(shmaddr) == -1) 
    {
        perror("Shmdt failed");
    }
    printf("write success\n");
}

int SharedMemoryFree()
{
    if(shmctl(shmid, IPC_RMID, 0) == -1) 
    {
        perror("Remove shared memory failed");
        return FAIL;
    }

    printf("Shared memory removed");
    return SUCCESS;
}


#endif