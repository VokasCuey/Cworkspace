#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

int main()
{
	int a = 0, b = 0, cur = 0, num = 0;
	cin >> a >> b;
	bool *luck = new bool[b]();
	for (int i = 0; i < b; i++)
	{
		char str[100] = {0};
		sprintf(str, "%d", i + 1);
		for (int j = 0; j < strlen(str); j++)
			if (str[j] == '7')
			{
				luck[i] = true;
				break;
			}
	}
	for (cur = a; cur <= b; cur++)
	{
		bool lucky = false;
		if (luck[cur - 1])
			continue;
		for (int i = 1; i < cur; i++)
			if (luck[i - 1])
				if (cur % i == 0)
				{
					lucky = true;
					break;
				}
		if (!lucky)
			num++;
	}
	cout << num << endl;
	return 0;
}
