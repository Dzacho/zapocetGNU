#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "charToInt.h"

#define DEBUG

// using namespace std;

// int charToInt(string* argument);

int main(int argc, char *argv[])
{
	int N = atoi(argv[0]);
#ifdef DEBUG
	printf("Interval is %d \n", N);
#endif
	switch(argv[1]){
		case 'a' : approx(data);
			   break;
		case 'v' : variance(data);
			   break;
		default : printf("Statistics method not specified.\n");
			  break;
	}

	return 0;
}
