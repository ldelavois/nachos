// addrspace.h 
//      Data structures to keep track of executing user programs 
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "translate.h"
#include "bitmap.h"
#include "pageprovider.h"

#define UserStacksAreaSize		1024	// increase this as necessary!

class Semaphore;

class AddrSpace:dontcopythis
{
  public:
    AddrSpace (OpenFile * executable);	// Create an address space,
    // initializing it with the program
    // stored in the file "executable"
    ~AddrSpace ();		// De-allocate an address space

    void InitRegisters ();	// Initialize user-level CPU registers,
    // before jumping to user code

    void SaveState ();		// Save/restore address space-specific
    void RestoreState ();	// info on a context switch 

#ifdef CHANGED
    void DecNbThreads();    // Decrement nbThreads
    void IncNbThreads();    // Increment nbThreads
    int GetNbThreads();     
	int AllocateUserStack();
    void synchroThreadsP();
    void synchroThreadsV();
    void ClearBitMap(int n);
    int FindBitMap();
    static void ReadAtVirtual(OpenFile *executable, 
        int virtualaddr, 
        int numBytes, 
        int position, 
        TranslationEntry *pageTable, 
        unsigned numPages);
    void SetEnoughSpaceTrue();
    void SetEnoughSpaceFalse();
    bool GetEnoughSpace();
    
#endif //CHANGED

  private:
      TranslationEntry * pageTable;	// Assume linear page table translation
    // for now!
    unsigned int numPages;	// Number of pages in the virtual 
    // address space

    #ifdef CHANGED
    int nbThreads;
    Semaphore *lock;
    Semaphore *synchroThreads;
    BitMap *mapStack;
    bool enoughSpace;   // Vrai par défaut, faux si la place que veux prendre 
                        // le thread est trop grande par rapport à NumAvailPage()
    #endif //CHANGED
};

#endif // ADDRSPACE_H
