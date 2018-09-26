#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include "console.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }


SynchConsole::SynchConsole(const char *in, const char *out){
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole(){
    delete console;
    delete writeDone;
    delete readAvail;
}

void SynchConsole::SynchPutChar(int ch){
    if(ch!= EOF && ch!='\n'){
        console->PutChar('<');
        writeDone->P();
        console->PutChar(ch);
        writeDone->P();
        console->PutChar('>');
        writeDone->P();
    }
    if (ch == 'q'){
            printf ("Nothing more, bye!\n");
        }
    if(ch==EOF){
        printf("Au revoir !\n");
    }
    
}

int SynchConsole::SynchGetChar(){
    readAvail->P();
    console->GetChar();
}

void SynchConsole::SynchPutString(const char s[]){
    for (int i=0;i!='\0';i++)
    {
        if(s[i]!=EOF && s[i]!='\n')
        {
            synchconsole->SynchPutChar(s[i]);
            writeDone->P();
        }
    }
}

void SynchConsole::SynchGetString(char *s, int n){
// ...
}

int copyStringFromMachine(int from, char *to, unsigned size){

    int tmp;
    for(int i = 0; i<size; i++){
        tmp = machine->ReadMem(from+i, 1, &tmp);
        if( (char)tmp !='\0'){
            to[i] = (char)tmp;
        }
        else{
            to[i] = '\0';
            return i+1;
        }        
    }
    return size;
}
#endif // CHANGED
