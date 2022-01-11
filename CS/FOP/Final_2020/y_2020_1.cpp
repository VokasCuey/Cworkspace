#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)

int main()
{
	int n = 0, xmax = 0, ymax = 0, xmin = 0, ymin = 0, x = 0, y = 0;
	cin >> n >> x >> y;
	xmax = x;
	xmin = x;
	ymax = y;
	ymin = y;
	for (int i = 1; i < n; i++)
	{
		cin >> x >> y;
		if (x > xmax)
			xmax = x;
		if (x < xmin)
			xmin = x;
		if (y > ymax)
			ymax = y;
		if (y < ymin)
			ymin = y;
	}
	int len = MAX(xmax - xmin, ymax - ymin);
	cout << len << endl;
	return 0;
}
