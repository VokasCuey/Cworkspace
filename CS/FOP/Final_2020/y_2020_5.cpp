#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)

int n = 0, m = 0, **h = NULL, **v = NULL, **val = NULL;

int main()
{
	cin >> n >> m;
	h = new int *[n + 1]();
	v = new int *[n + 1]();
	val = new int *[n + 1]();
	for (int i = 1; i <= n; i++)
	{
		h[i] = new int[m + 1]();
		v[i] = new int[m + 1]();
		val[i] = new int[m + 1]();
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> h[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> v[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (i == 1 && j == 1)
				continue;
			if (i == 1)
				val[i][j] = val[i][j - 1] + h[i][j - 1];
			else if (j == 1)
				val[i][j] = val[i - 1][j] + v[i - 1][j];
			else
				val[i][j] = MAX(val[i - 1][j] + v[i - 1][j], val[i][j - 1] + h[i][j - 1]);
		}
	cout << val[n][m] << endl;
	return 0;
}
