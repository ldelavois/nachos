#include "syscall.h"

void tcho(int i){
        PutChar('a'+i);
    ThreadExit();
}

int main(){

    volatile int i = 0;
    volatile int j = 0;
    for(j,i ; j<100,i<100 ; j++,i++){
        ThreadCreate(tcho, i);
    }
}
