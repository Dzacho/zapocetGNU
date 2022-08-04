#ifndef __PROCESS_ARGUMENTS_H__
#define __PROCESS_ARGUMENTS_H__
/* This include is needed in order to process the arguments, it declares the getopt_long() function and "struct option" structure. */
	#include <getopt.h>
	/* This is here now mainly to declare the NULL pointer */
	#include <stdlib.h>
	
	/* This static array defines the arguments we want to use. One for each structure element. The array should be terminated by the all-zeroed element (remember, that NULL pointer is a pointer filled with zeros). */
	static struct option _LongOptionList[3];
	
	int process_arguments (int argc, char **argv);
	
	/* argc is the number of given command-line arguments and argv is an array of pointers
	   to the static strings with those arguments, where argv[0] is the actual executable command
	   and argv[1] points to the first argument. */
#endif
