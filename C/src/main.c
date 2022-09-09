#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "procArgs.h"

//#define DEBUG

short operation = 2;
unsigned long N = 1000;

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

void average()
{
	long long sum = 0;
	int data;
	unsigned long i = 0;
	long double res = 0;

	while(fread(&data, 4, 1, stdin))
        {
#ifdef DEBUG
                printf("Read data: %d\n", data);
                printf("Binary of the number is: ");
                convertToBinary(data);
                printf("\n");
#endif
                data = (data & 0xFFFF8000) >> 15; //Selecting and shifting needed bits.
                data = (data > 0x0000FFFF) * (0 - (data ^ 0x0001FFFF) - 1 - data) + data; //Computing the right number stored as 17 bit 2's complement.
#ifdef DEBUG
                printf("Right data: %d\n", data);
                printf("Binary of the number is: ");
                convertToBinary(data);
                printf("\n");
#endif
		if((0x7FFFFFFFFFFF0000 < sum) || (0x800000000001FFFF > sum)) //testing risk of over- and underflow
		{
			res += sum;
			sum = 0;
		}
		sum += data;
		i += 1;
                if(i == N)
                {
			res += sum;
                        res = res/N;
                        printf("%.15Lg\n", res);
                        i = 0;
                        sum = 0;
			res = 0;
#ifdef DEBUG
                        return;
#endif
                }
        }
}

void variance()
{
	long long sum = 0;
	long double bigsum = 0;
        int data;
        unsigned long i = 0;
	long double var = 0;

        while(fread(&data, 4, 1, stdin))
        {
#ifdef DEBUG
                printf("Read data: %d\n", data);
                printf("Binary of the number is: ");
                convertToBinary(data);
                printf("\n");
#endif
                data = (data & 0xFFFF8000) >> 15; //Selecting and shifting needed bits.
                data = (data > 0x0000FFFF) * (0 - (data ^ 0x0001FFFF) - 1 - data) + data; //Computing the right number stored as 17 bit 2's complement.
#ifdef DEBUG
                printf("Right data: %d\n", data);
                printf("Binary of the number is: ");
                convertToBinary(data);
                printf("\n");
#endif
		if((0x7FFFFFFFFFFF0000 < sum) || (0x800000000001FFFF > sum)) //testing risk of over- and underflow
                {
                        bigsum += sum;
                        sum = 0;
                }
                sum += data;
		var += (N + 1) * data * data - 2 * data * (sum + bigsum);
                i += 1;
                if(i == N)
                {
			var = var / (N * N);
                        printf("%.15Lg\n", var);
                        i = 0;
                        sum = 0;
			bigsum = 0;
			var = 0;
#ifdef DEBUG
                        return;
#endif
                }
        }
}

int main(int argc, char *argv[])
{
	if(process_arguments(argc, argv))
	{
		return 1;
	}

	if(N == 0)
	{
#ifdef DEBUG
		printf("Can't read interval.\n");
#endif
		fprintf(stderr, "Dzachistics error: Can't read interval.\n");
		return 1;
	}

#ifdef DEBUG
	printf("Interval is %ld \n", N);
#endif

	if(!operation || operation > 2)
	{
		fprintf(stderr, "Dzachistics error: Statistics method not specified, operation == %d.\n", operation);
		return 1;
	}

	freopen(NULL, "rb", stdin);

	switch(operation)
        {
                case 1 :
#ifdef DEBUG
                        printf("Average compute selected.\n");
#endif
			average();
                           break;
                case 2 :
#ifdef DEBUG
                           printf("Variance compute selected.\n");
#endif
			   variance();
                           break;
	}
	return 0;
}
