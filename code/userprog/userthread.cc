#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "synch.h"
#include "userthread.h"
#include "thread.h"

typedef struct farg{
    int f;
    int arg;
}

int do_ThreadCreate(void f(void *arg), void *arg){
    Thread *t = new Thread("newThread");
    
}

void do_ThreadExit(void);




