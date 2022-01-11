#include <iostream>
#include <cmath>
using namespace std;

bool IsPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

int main()
{
	int l = 0, u = 0;
	int min[2] = {0}, max[2] = {0}, prime[10000] = {0};
	int num = 0;
	cin >> l >> u;
	for (int i = l; i <= u; i++)
	{
		if (IsPrime(i))
		{
			prime[num++] = i;
			if (num != 1)
			{
				if (((prime[num - 1] - prime[num - 2]) < (min[1] - min[0])) || min[1] == 0)
				{
					min[0] = prime[num - 2];
					min[1] = prime[num - 1];
				}
				if ((prime[num - 1] - prime[num - 2]) > (max[1] - max[0]))
				{
					max[0] = prime[num - 2];
					max[1] = prime[num - 1];
				}
			}
		}
	}
	if (max[1] == 0)
		cout << -1 << endl;
	else
	{
		cout << min[0] << ' ' << min[1] << endl;
		cout << max[0] << ' ' << max[1] << endl;
	}
	return 0;
}