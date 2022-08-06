#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#include <limits.h>
#include <float.h>*/

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
		fprintf(stderr, "Too few arguments!\n");
		return 1;
	}
	if(argc > 3)
	{
#ifdef DEBUG
		printf("Too much arguments!\n");
#endif
		fprintf(stderr, "Too much arguments!\n");
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
		fprintf(stderr, "Can't read interval.\n");
		return 1;
	}
#ifdef DEBUG
	printf("Interval is %d \n", N);
/*
	printf("CHAR_BIT    :   %d\n", CHAR_BIT);
    printf("CHAR_MAX    :   %d\n", CHAR_MAX);
    printf("CHAR_MIN    :   %d\n", CHAR_MIN);
    printf("INT_MAX     :   %d\n", INT_MAX);
    printf("INT_MIN     :   %d\n", INT_MIN);
    printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
    printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
    printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
    printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
    printf("SHRT_MAX    :   %d\n", SHRT_MAX);
    printf("SHRT_MIN    :   %d\n", SHRT_MIN);
    printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
    printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
    printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
    printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);*/
#endif
	int data[N];
	//data reading
	FILE *fin;
	fin = fopen("/home/Jachym/Dokumenty/Škola/FJFI/Třeťák/GNUprog/zapocetGNU/data/data1.dat", "rb");
	FILE *fout;
	fout = fopen("/home/Jachym/Dokumenty/Škola/FJFI/Třeťák/GNUprog/zapocetGNU/data/output1.dat", "wb");
	if(fin == NULL)
	{
#ifdef DEBUG
		printf("Input not opened.\n");
#endif
		fprintf(stderr, "Input not opened.\n");
		return 1;
	}
	if(fout == NULL)
        {
#ifdef DEBUG
                printf("Output not opened.\n");
#endif
		fprintf(stderr, "Output not opened.\n");
                return 1;
        }/*
#ifdef DEBUG
	//testing 2's complement implementation
	int minuspatnact = 0xFFFFFFF1;
	int patnact = 0x0000000F;
	printf("%d \n%d \n", minuspatnact, patnact);
	data[0] = (minuspatnact > 0x7FFFFFFF) ? (minuspatnact - 0xFFFFFFFF) - 1 : minuspatnact;
	data[1] = (patnact > 0x7FFFFFFF) ? (patnact - 0xFFFFFFFF) - 1 : patnact;
	printf("%d \n%d \n", data[0], data[1]);
	data[0] = (minuspatnact > 0x7FFFFFFF) ? 0-(minuspatnact ^ 0xFFFFFFFF) - 1 : minuspatnact;
	data[1] = (patnact > 0x7FFFFFFF) ? 0-(patnact ^ 0xFFFFFFFF) - 1 : patnact;
	printf("%d \n%d \n", data[0], data[1]);
	data[0] = (minuspatnact > 0x7FFFFFFF) * (0 - (minuspatnact ^ 0xFFFFFFFF) - 1 - minuspatnact) + minuspatnact;
        data[1] = (patnact > 0x7FFFFFFF) * (0 - (patnact ^ 0xFFFFFFFF) - 1 - patnact) + patnact;
        printf("%d \n%d \n", data[0], data[1]);
#endif*/
	while(fread(&data[i], 4, 1, fin))
	{
#ifdef DEBUG
                printf("Read data: %d \n", data[i]);
		printf("Binary of the number is: ");
		convertToBinary(data[i]);
		printf("\n");
#endif
		data[i] = (data[i] & 0xFFFF8000) >> 15; //Selecting and shifting needed bits.
		data[i] = (data[i] > 0x0000FFFF) * (0 - (data[i] ^ 0x0001FFFF) - 1 - data[i]) + data[i]; //Computing the right number stored as 17 bit 2's complement.
#ifdef DEBUG
		printf("Right data: %d \n", data[i]);
		printf("Binary of the number is: ");
                convertToBinary(data[i]);
                printf("\n");
#endif
		if(!fwrite(&data[i], 4, 1, fout))
		{
#ifdef DEBUG
			printf("Outputting data error.\n");
#endif
			fprintf(stderr, "Outputting data error.\n");
			return 1;
		}
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
			  fprintf(stderr, "Statistics method not specified.\n");
			  return 1;
	}



	return 0;
}
