#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "procArgs.c"

#define DEBUG

#ifdef DEBUG
void convertToBinary(unsigned a)
{
    /* step 1 */
    if (a > 1)
        convertToBinary(a / 2);

    /* step 2 */
    printf("%d", a % 2);
}
#endif

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
	unsigned int i = 0;
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
	//data reading
	FILE *f;
	f = fopen("/home/Jachym/Dokumenty/Škola/FJFI/Třeťák/GNUprog/zapocetGNU/data/data1.dat", "rb");
	if(f == NULL)
	{
#ifdef DEBUG
		printf("File not opened.\n");
#endif
		return 1;
	}
#ifdef DEBUG
	//testing 2's complement implementation
	data[0] = (0xF1^0xFF)+1;
	data[1] = (0x0F^0xFF)+1;
	printf("%ld \n%ld \n", data[0], data[1]);
#endif
	while(fread(&data[i], 4, 1, f))
	{
#ifdef DEBUG
                printf("Read data: %ld \n", data[i]);
		printf("Binary of the number is: ");
		convertToBinary(data[i]);
		printf("\n");
#endif
		data[i] = (data[i] & 0xFFFF8000) >> 15;
#ifdef DEBUG
		printf("Right data: %ld \n", data[i]);
		printf("Binary of the number is: ");
                convertToBinary(data[i]);
                printf("\n");
#endif
		i += 1;
		if(i == N)
		{
			break;
		}
	}
	
	operation = process_arguments(argc, argv);

	switch(operation)
	{
		case 1 :
#ifdef DEBUG
			printf("Average compute selected.\n");
#endif
			//approx(data);
			   break;
		case 2 :
#ifdef DEBUG
			   printf("Variance compute selected.\n");
#endif
			   //variance(data);
			   break;
		default : 
#ifdef DEBUG
			  printf("Statistics method not specified.\n");
#endif
			  return 1;
	}



	return 0;
}
