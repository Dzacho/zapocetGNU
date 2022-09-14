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

int inline convert(int data)
{
    data = data & 0x0001FFFF; //Selecting and shifting needed bits.
    data += !!(data & 0x00010000) * 0xFFFE0000;
    //data = (data > 0x0000FFFF) * (0 - (data ^ 0x0001FFFF) - 1 - data) + data; //Computing the right number stored as 17 bit 2's complement.
    return data;
}

#ifdef DEBUG
void convertToBinary(unsigned a)
{
    /* step 1 */
    if (a > 1)
        convertToBinary(a / 2);

    /* step 2 */
    fprintf(stderr, "%d", a % 2);
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
                fprintf(stderr, "Read data: %d\n", data);
                fprintf(stderr, "Binary of the number is: ");
                convertToBinary(data);
                fprintf(stderr, "\n");
#endif
                data = convert(data);
#ifdef DEBUG
                fprintf(stderr, "Right data: %d\n", data);
                fprintf(stderr, "Binary of the number is: ");
                convertToBinary(data);
                fprintf(stderr, "\n");
#endif
		if((0x7FFFFFFFFFFF0000 < sum) || (0x800000000001FFFF > sum)) //testing risk of over- and underflow
		{
			res += sum;
			sum = 0;
		}
		sum += data;
                if(++i == N)
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
	res += sum;
        res = res/N;
        printf("%.15Lg\n", res);
	return;
}

void variance()
{
	long long sum = 0;
	long double bigsum = 0;
	int data;
	unsigned long i = 0;
	long long var = 0;
	long double bigvar = 0;

        while(fread(&data, 4, 1, stdin))
        {
#ifdef DEBUG
                fprintf(stderr, "Read data: %d\n", data);
                fprintf(stderr, "Binary of the number is: ");
                convertToBinary(data);
                fprintf(stderr, "\n");
#endif
                data = convert(data);
#ifdef DEBUG
                fprintf(stderr, "Right data: %d\n", data);
                fprintf(stderr, "Binary of the number is: ");
                convertToBinary(data);
                fprintf(stderr, "\n");
#endif
		if((0x7FFFFFFFFFFF0000 < sum) || (0x800000000001FFFF > sum)) //testing risk of over- and underflow
                {
                        bigsum += sum;
                        sum = 0;
                }
                sum += data;
		//var += (N + 1) * data * data - 2 * data * (sum + bigsum);
        if(var > LLONG_MAX - data * data)
        {
		bigvar += var;
		var = 0;
        }
        var += data * data;
                i++;
                if(i == N)
                {
			bigsum += sum;
			bigvar += var;
			bigvar = (bigvar / N) - bigsum * bigsum / (N * N);
                        printf("%.15Lg\n", bigvar);
                        i = 0;
                        sum = 0;
			bigsum = 0;
			var = 0;
			bigvar = 0;
#ifdef DEBUG
                        return;
#endif
                }
        }
	bigsum += sum;
        bigvar += var;
        bigvar = (bigvar / N) - bigsum * bigsum / (N * N);
        printf("%.15Lg\n", bigvar);
        return;
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
		fprintf(stderr, "Can't read interval.\n");
#endif
		fprintf(stderr, "Dzachistics error: Can't read interval.\n");
		return 1;
	}

#ifdef DEBUG
	fprintf(stderr, "Interval is %ld \n", N);
#endif

	if(!operation || operation > 2)
	{
		fprintf(stderr, "Dzachistics error: Statistics method not specified, operation == %d.\n", operation);
		return 1;
	}

	//freopen(NULL, "rb", stdin);

	switch(operation)
        {
                case 1 :
#ifdef DEBUG
                        fprintf(stderr, "Average compute selected.\n");
#endif
			average();
                        break;
                case 2 :
#ifdef DEBUG
                        fprintf(stderr, "Variance compute selected.\n");
#endif
			variance();
                        break;
	}
	return 0;
}
