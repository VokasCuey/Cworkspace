#include <iostream>
using namespace std;

int main()
{
	int n = 0, tmp = 0;
	cin >> n;
	int score[10] = {0};
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		for (int j = 0; j < 10; j++)
			if (tmp >= 10 * j && tmp < 10 * (j + 1))
			{
				score[j]++;
				break;
			}
		if (tmp == 100)
			score[9]++;
	}
	for (int i = 0; i < 10; i++)
	{
		if (score[i] > 10)
			score[i] = 10;
		for (int j = 0; j < score[i]; j++)
			cout << '@';
		for (int j = 10 - score[i]; j > 0; j--)
			cout << '.';
		cout << endl;
	}
	return 0;
}
