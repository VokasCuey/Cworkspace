#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream in("stock.in");
	ofstream out("stock.out");
	int n = 0;
	long sum = 0;
	in >> n;
	long *price = new long[n + 1]();
	for (int i = 1; i <= n; i++)
		in >> price[i];
	in.close();
	for (int i = 1; i < n; i++)
	{
		if (price[i] >= price[i + 1])
			continue;
		if (price[i] < price[i + 1])
			sum += price[i + 1] - price[i];
	}
	out << sum << endl;
	out.close();
	return 0;
}