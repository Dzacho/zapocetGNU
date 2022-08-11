float average(const int *data, const unsigned int N)
{
	float avg = 0;
	for(unsigned int i = 0; i < N; i++)
	{
		avg += data[i];
	}
	avg = avg/N;
	return avg;
}
