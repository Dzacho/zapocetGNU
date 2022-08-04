#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processArguments.h"

#define DEBUG

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
#ifdef DEBUG
		printf("Too few arguments!\n");
#endif
		return 1;
	}
	if(argc > 3)
	{
#ifdef DEBUG
		printf("Too much arguments!\n");
#endif
		return 1;
	}
	short operation;
	unsigned const int N = strtoul(argv[1], NULL, 10);
	if(N == 0)
	{
#ifdef DEBUG
		printf("Can't read interval.\n");
#endif
		return 1;
	}
#ifdef DEBUG
	printf("Interval is %d \n", N);
#endif

	long data[N];
	//TODO: data reading
	
	operation = process_arguments(argc, argv);

	switch(operation)
	{
		case 1 : // approx(data);
			   break;
		case 2 : // variance(data);
			   break;
		default : 
#ifdef DEBUG
			  printf("Statistics method not specified.\n");
#endif
			  return 1;
	}



	return 0;
}
