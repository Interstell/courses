#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(stack_t self, char* str) {
    return (stack_getCount(self) > 10)?1:0;
}

void reaction(stack_t self, char* str){
    for (int i = 0; i<strlen(str); i++){
        printf("Popped: %s\n", stack_pop(self));
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
