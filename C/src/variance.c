float variance(const int *data, float avg, const unsigned int N)
{
	float var = 0;
	for(unsigned int i = 0; i < N; i++)
	{
		var += (data[i] - avg) * (data[i] - avg);
	}
	var = var/N;
	return var;
}
