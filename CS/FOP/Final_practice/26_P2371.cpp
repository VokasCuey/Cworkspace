#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int l = 0, r = 0, num = 0;
	cin >> l >> r;
	bool *notPrime = new bool[r - l + 1]();
	for (int i = 2; i < sqrt(r); i++)
		for (int j = l / i; i * j <= r; j++)
			if (i * j >= l && i * j <= r && j != 1)
				notPrime[i * j - l] = true;
	int last = 0, first = 0;
	for (int i = 0; i <= r - l; i++)
		if (!notPrime[i])
		{
			last = i;
			first = i;
			break;
		}
	for (int i = first + 1; i <= r - l; i++)
		if (!notPrime[i])
		{
			if (i - last == 2)
				num++;
			last = i;
		}
	cout << num << endl;
	return 0;
}