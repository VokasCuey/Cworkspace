#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b ? a : b))

int main()
{
	int n = 0, p = 0, q = 0;
	cin >> n >> p >> q;
	int *a = new int[n + 1]();
	int *max = new int[n + 1]();
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if (a[i] == -1)
			max[i] = -1;
	}
	max[1] = a[1];
	for (int i = 2; i <= n; i++)
	{
		if (max[i] != -1)
		{
			if (i - p < 1 && i - q < 1)
				max[i] = -1;
			else if (i - p < 1 && i - q > 1)
			{
				if (max[i - q] == -1)
					max[i] = -1;
				else
					max[i] = max[i - q] + a[i];
			}
			else if (i - q < 1 && i - p > 1)
			{
				if (max[i - p] == -1)
					max[i] = -1;
				else
					max[i] = max[i - p] + a[i];
			}
			else
			{
				if (max[i - p] == -1 && max[i - q] == -1)
					max[i] = -1;
				else
					max[i] = MAX(max[i - p], max[i - q]) + a[i];
			}
		}
	}
	cout << max[n] << endl;
	return 0;
}