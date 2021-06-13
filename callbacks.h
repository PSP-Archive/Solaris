//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	callbacks.c : contient les callbacks
//*********************************************************



#ifndef common_callbacks__
#define common_callbacks__


/**
 * Sets up the callback thread and returns its thread id
 */
int SetupCallbacks(void);

/**
 * Callback thread
 */
int CallbackThread(SceSize args, void *argp);

/**
 * Exit callback
 */
int exitCallback(int arg1, int arg2, void *common);


#endif
