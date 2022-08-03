#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

int main(int argc, char *argv[])
{
	int N = atoi(argv[1]);
#ifdef DEBUG
	printf("Interval is %d \n", N);
#endif
	/*switch(argv[1]){
		case 'a' : // approx(data);
			   break;
		case 'v' : // variance(data);
			   break;
		default : printf("Statistics method not specified.\n");
			  break;
	}*/

	return 0;
}
