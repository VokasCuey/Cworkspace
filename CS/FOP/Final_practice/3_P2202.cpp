#include <iostream>
using namespace std;

void write(int x, int y, int cur, int *a)
{
	if (cur > y)
		return;
	for (int i = 0; i < x; i++)
	{
		a[cur - 1] = i + 1;
		for (int j = 0; j < cur; j++)
			cout << a[j] << '.';
		cout << ' ' << "Title" << endl;
		write(x, y, cur + 1, a);
	}
}

int main()
{
	int x = 0, y = 0;
	cin >> x >> y;
	int a[100] = {0};
	write(x, y, 1, a);
	return 0;
}
