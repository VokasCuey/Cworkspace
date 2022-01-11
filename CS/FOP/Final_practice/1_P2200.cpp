#include <iostream>
using namespace std;

int fun(int n, int x)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return x;
	else
		return fun(n - 1, x) + fun(n / 2, x) + fun(n / 3, x);
}

int main()
{
	int x = 0, n = 0;
	cin >> x >> n;
	cout << fun(n, x) << endl;
	return 0;
}
