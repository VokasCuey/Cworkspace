#include <iostream>
using namespace std;

int n = 0, m = 0, q = 0;

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void A(int **a, int x1, int y1, int x2, int y2, int d)
{
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			a[i][j] += d;
}

void E(int **a, int x1, int x2)
{
	for (int i = 1; i <= m; i++)
		swap(a[x1][i], a[x2][i]);
}

void Q(int **a, int x, int y)
{
	cout << a[x][y] << endl;
}

int main()
{
	cin >> n >> m;
	int **a = new int *[n + 1]();
	for (int i = 1; i <= n; i++)
		a[i] = new int[m + 1]();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		char cmd = '\0';
		cin >> cmd;
		if (cmd == 'A')
		{
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0, d = 0;
			cin >> x1 >> y1 >> x2 >> y2 >> d;
			A(a, x1, y1, x2, y2, d);
		}
		else if (cmd == 'E')
		{
			int x1 = 0, x2 = 0;
			cin >> x1 >> x2;
			E(a, x1, x2);
		}
		else if (cmd == 'Q')
		{
			int x = 0, y = 0;
			cin >> x >> y;
			Q(a, x, y);
		}
	}
	return 0;
}