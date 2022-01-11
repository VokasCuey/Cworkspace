#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	float gray = 0, black = 0, x = 0, y = 0;
	int t = 0;
	cin >> gray >> black >> x >> y >> t;
	int sum = gray + black;
	x = x / 100;
	y = y / 100;
	for (int i = 0; i < t; i++)
	{
		float curG = gray, curB = black;
		gray = curG * (1 - x + x * y) + curB * y;
		black = sum - gray;
	}
	cout << fixed << setprecision(4) << gray << ' ' << black << endl;
	return 0;
}
