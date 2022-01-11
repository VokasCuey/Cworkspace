#include <iostream>
using namespace std;

int main()
{
	int man[6] = {0};
	int num = 0;
	int word[6][2] = {0};
	for (int i = 1; i <= 5; i++)
		cin >> word[i][0] >> word[i][1];
	for (man[1] = 0; man[1] < 2; man[1]++)
		for (man[2] = 0; man[2] < 2; man[2]++)
			for (man[3] = 0; man[3] < 2; man[3]++)
				for (man[4] = 0; man[4] < 2; man[4]++)
					for (man[5] = 0; man[5] < 2; man[5]++)
					{
						int sum = 0;
						for (int i = 1; i <= 5; i++)
							sum += man[i];
						if (sum != 3)
							continue;
						for (int i = 1; i <= 6; i++)
						{
							if (i == 6)
								num++;
							else
							{
								if (man[i] == 1)
									if (man[word[i][0]] != word[i][1])
										break;
								if (man[i] == 0)
									if (man[word[i][0]] == word[i][1])
										break;
							}
						}
					}
	cout << num << endl;
	return 0;
}
