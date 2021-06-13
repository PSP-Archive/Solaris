//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	callbacks.c : contient les callbacks
//*********************************************************



	#include <pspkernel.h>
	#include "callbacks.h"


int SetupCallbacks(void){

    int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    
	if(thid >= 0)
	{sceKernelStartThread(thid, 0, 0);}

    return thid;
}
int CallbackThread(SceSize args, void *argp){

	int cbid;
    cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}
int exitCallback(int arg1, int arg2, void *common){

    sceKernelExitGame();
    return 0;
}
