#include "syscall.h"

void tcho(int i){
        PutChar('a'+i);
    ThreadExit();
}

int main(){

    volatile int i = 0;
    volatile int j = 0;
    for(j,i ; j<4,i<4 ; j++,i++){
        ThreadCreate(tcho, i);
    }
}
