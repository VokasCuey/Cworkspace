#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str[1010] = {0};
	int q = 0, num[26] = {0}, l = 0, r = 0;
	cin >> str >> q;
	for (int i = 0; i < q; i++)
	{
		memset(num, 0, sizeof(num));
		cin >> l >> r;
		for (int j = l; j <= r; j++)
			num[str[j] - 'a']++;
		for (int j = 0; j < 26; j++)
			if (num[j])
				cout << (char)('a' + j) << ':' << num[j] << ' ';
		cout << endl;
	}
	return 0;
}