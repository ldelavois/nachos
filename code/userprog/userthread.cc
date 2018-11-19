#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "synch.h"
#include "userthread.h"
#include "thread.h"


//Structure (schmurtz)contenant la fonction et ses arguments, à passer au thread créé 
typedef struct schmurtz schmurtz;
struct schmurtz{
    int f;
    int arg;
    int numThread;
};

static void StartUserThread(void *arg){

    schmurtz *threadArgs = (schmurtz* )arg;

    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister (i, 0);
    machine->WriteRegister (PCReg, threadArgs->f);
    machine->WriteRegister (4, threadArgs->arg);
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
    machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack());
    DEBUG ('a', "Initializing stack register to 0x%x\n",
	   currentThread->space->AllocateUserStack());
    
    machine->Run();
}

int do_ThreadCreate(int f, int arg){
    int tmp = currentThread->space->FindBitMap(); 
    if(tmp == -1)
        return -1;
    
    Thread *t = new Thread("newThread");
    struct schmurtz *argStart = (struct schmurtz*)malloc(sizeof(struct schmurtz));
    argStart->f = f;
    argStart->arg = arg;
    argStart->numThread = currentThread->nThread;
    t->nThread = tmp;
    t->Start (StartUserThread, argStart);

    return 0;
    
}

void do_ThreadExit(void){
    currentThread->space->ClearBitMap(currentThread->nThread);
    currentThread->Finish();
};




#endif  //CHANGED
