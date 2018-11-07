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
    int i = 0;
    while(s[i]!='\0')
    {
        synchconsole->SynchPutChar(s[i]);
        i++;
    }
}

void SynchConsole::SynchGetString(char *s, int n){
    if( s != NULL){
        char ch=0;
        
        for(int i=0; i < n; i++){
            ch = SynchGetChar();
            if(ch=='\0' || ch =='\n')
                break;
            s[i] = ch;
        }
    }
}

int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size){

    int tmp;
    for(unsigned i = 0; i<size; i++){
        machine->ReadMem(from+i, 1, &tmp);
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

int SynchConsole::copyStringToMachine(int to, char *from, unsigned size){

  for(unsigned i=0; i<size; i++){
      machine->WriteMem(to+i, 1, from[i]); 
      
  }
  return size;

}  
#endif // CHANGED
