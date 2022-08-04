/* This include is needed in order to process the arguments, it declares the getopt_long() function and "struct option" structure. */
	#include <getopt.h>
	/* This is here now mainly to declare the NULL pointer */
	#include <stdlib.h>

#include "processArguments.h"
	
	/* This static array defines the arguments we want to use. One for each structure element. The array should be terminated by the all-zeroed element (remember, that NULL pointer is a pointer filled with zeros). */
	static struct option _LongOptionList[] = {
		{ "average", 0, NULL, 'a' },		/* This is an example of just a flag argument, which has no parameter (second column is 0). Long variant of the argument would be "--arg-flag", short variant would be "-f". */
		{ "variance",  0, NULL, 'v' },		/* This is an example of argument with a value (second column is 1). Long variant of the argument would be "--arg-val=VAL", short variant would be "-v VAL". */
		{ NULL,       0, NULL, 0   },		/* This is a zeroed element, which terminates the list of argument specifications. */
	};
	
	int process_arguments (int argc, char **argv)
	{
		int _Ret;

		while (1) {
			/* This is the main argument processing function-call. In the third argument string, there each of the arguments specified
			   in the _LongOptionList array should have its short form letter. If the second columnt of the array is specified as 1 (having an argument),
			   then the particular letter in this string should be followed by a ':' character. Also, if we want to process positional parameters
			   (those not beginning with "-" or "--") we should put '-' as the the first letter of the string. */
			_Ret = getopt_long (argc, argv, "-av", _LongOptionList, NULL);
			if (_Ret < 0) {
				/* Something went wrong with the givent parameters, you can handle the error here. */
				break;
			}
			switch (_Ret) {
				case 'a':
					/* If we get here, it means that the flag "--average" or "-a" was specified, note it somewhere ... */
					//break;
					return 1;

				case 'v':
					/* If we get here, it means that the flag "--variance" or "-v" was specified, note it somewhere ... */
					//break;
					return 2;

				case '?':
					/* If we get here, it means, we have been given an unknown argument
					   (which was not specified in the 3rd argument of getopt_long() call) on position given by "optind-1",
					   so, the argument itself is "argv[optind-1]" and it is up to us, if we want to brag about it or ignore it. */
					//break;
					return 0;

				case 1:
					/* If we get here, it means, that the currently processed argument is so-called a positional argument,
					   i.e., does not begin with "-" or "--" and usually it is some generic string. There can be more of these
					   arguments and we can count them, if we want to. Like for example, if the command has two input files as arguments:
						cmd file1 file2
					   then we would be called here twice, first with "file1" then "file2". The parameter string is again
					   pointed to by the "optarg" variable each time. */
					break;
					//return 0;
			}
		}
		return 0;
	}
	
	/* argc is the number of given command-line arguments and argv is an array of pointers
	   to the static strings with those arguments, where argv[0] is the actual executable command
	   and argv[1] points to the first argument. */
