#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	int *num = new int[n + 1]();
	num[1] = 2;
	num[2] = 4;
	for (int i = 3; i <= n; i++)
		num[i] = ((2 * num[i - 1]) % 1000007 + 4 * num[i - 2] % 1000007) % 1000007;
	cout << num[n] << endl;
	return 0;
}