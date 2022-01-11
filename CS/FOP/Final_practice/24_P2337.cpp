#include <iostream>
using namespace std;

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	int num = n;
	bool *able = new bool[n + 1]();
	int *a = new int[m]();
	for (int i = 0; i < m; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++)
		for (int j = 1; a[i] * j <= n; j++)
			if (!able[a[i] * j])
			{
				able[a[i] * j] = true;
				num--;
			}
	cout << num << endl;
	return 0;
}