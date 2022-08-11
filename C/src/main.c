#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "average.c"
#include "procArgs.c"
#include "roundoff.c"
#include "variance.c"

//#define DEBUG

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
		fprintf(stderr, "Dzachistics error: Too few arguments!\n");
		return 1;
	}
	if(argc > 3)
	{
#ifdef DEBUG
		printf("Too much arguments!\n");
#endif
		fprintf(stderr, "Dzachistics error: Too much arguments!\n");
		return 1;
	}
	short operation;
	unsigned const int N = strtoul(argv[1], NULL, 10);
	unsigned int i = 0;
	FILE *fin = NULL;
	int data[N];
        float avg;
	if(N == 0)
	{
#ifdef DEBUG
		printf("Can't read interval.\n");
#endif
		fprintf(stderr, "Dzachistics error: Can't read interval.\n");
		return 1;
	}
#ifdef DEBUG
	printf("Interval is %d \n", N);
#endif
	//data reading
	fin = fopen("/home/Jachym/Dokumenty/Škola/FJFI/Třeťák/GNUprog/zapocetGNU/data/data1.dat", "rb");
	if(fin == NULL)
	{
		fprintf(stderr, "Dzachistics error: Input not opened.\n");
		return 1;
	}
#ifdef DEBUG
        printf("Data file opened!\n");
#endif
	operation = process_arguments(argc, argv);
	if(!operation || operation > 2)
	{
		fprintf(stderr, "Dzachistics error: Statistics method not specified.");
		return 1;
	}
#ifdef DEBUG
	switch(operation)
        {
                case 1 :
                        printf("Average compute selected.\n");
                           break;
                case 2 :
                           printf("Variance compute selected.\n");
                           break;
	}
#endif

	while(fread(&data[i], 4, 1, fin))
	{
#ifdef DEBUG
                printf("Read data[%d]: %d\n", i, data[i]);
		printf("Binary of the number is: ");
		convertToBinary(data[i]);
		printf("\n");
#endif
		data[i] = (data[i] & 0xFFFF8000) >> 15; //Selecting and shifting needed bits.
		data[i] = (data[i] > 0x0000FFFF) * (0 - (data[i] ^ 0x0001FFFF) - 1 - data[i]) + data[i]; //Computing the right number stored as 17 bit 2's complement.
#ifdef DEBUG
		printf("Right data: %d\n", data[i]);
		printf("Binary of the number is: ");
                convertToBinary(data[i]);
                printf("\n");
#endif
		i += 1;
		if(i == N)
		{
			avg = average(data, N);
			if(operation == 2)
			{
				avg = variance(data, avg, N);
			}
			printf("%.f\n", Round_off(avg, 3));
			i = 0;
			avg = 0;
#ifdef DEBUG
			return 0;
#endif
		}
	}

	return 0;
}
