#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n = 0, num = 0;
	cin >> n;
	for (int i = 1;; i++)
	{
		char str[100] = {0};
		sprintf(str, "%d", i);
		if (strlen(str) > n)
			break;
		int curNum = 0;
		for (int j = 0; j < strlen(str); j++)
			if (str[j] == '3')
				curNum++;
		if (curNum % 2 == 0)
			num++;
	}
	cout << num << endl;
	return 0;
}
