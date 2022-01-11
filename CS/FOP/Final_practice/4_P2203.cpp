#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX 10000

void convert(char *inStr, ofstream &out)
{
	if (strlen(inStr) == 0)
		return;
	if (inStr[0] == '#')
	{
		char outStr[MAX] = {0};
		int num = 1;
		for (int i = 1; inStr[i] == '#'; i++)
			num++;
		char head[10] = "<h >", tail[10] = "</h >";
		head[2] = '0' + num;
		tail[3] = '0' + num;
		for (int i = num + 1, j = 0; inStr[i] && (inStr[i] != '\n') && (inStr[i] != '\r'); i++, j++)
			outStr[j] = inStr[i];
		out << head << outStr << tail;
	}
	else
	{
		char head[10] = "<p>", tail[10] = "</p>", word[MAX] = {0};
		bool bold = false, italic = false;
		out << head;
		for (int i = 0, j = 0;; i++, j++)
		{
			if (!(inStr[i] && (inStr[i] != '\n') && (inStr[i] != '\r')))
			{
				out << word;
				break;
			}
			if (inStr[i] == ' ')
			{
				word[j] = inStr[i];
				if (!(bold && italic))
				{
					out << word;
					memset(word, 0, sizeof(word));
					j = -1;
				}
			}
			else if (inStr[i] == '*')
			{
				if (bold || italic)
				{
					if (bold)
						out << "<strong>";
					if (italic)
						out << "<em>";
					out << word;
					if (italic)
						out << "</em>";
					if (bold)
						out << "</strong>";
					if (bold)
					{
						if (italic)
							i += 2;
						else
							i += 1;
					}
					memset(word, 0, sizeof(word));
					bold = false;
					italic = false;
					j = -1;
				}
				else
				{
					if (j != 0)
					{
						out << word;
						j = -1;
					}
					int k = 1;
					for (; k < 3; k++)
						if (inStr[i + k] != '*')
							break;
					if (k > 1)
						bold = true;
					if (k != 2)
						italic = true;
					i += k - 1;
					if (j != -1)
						j--;
				}
			}
			else
				word[j] = inStr[i];
		}
		out << tail;
	}
	out << endl;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	if (!(in && out))
		return -1;
	else
	{
		char inStr[MAX] = {0}, outStr[MAX] = {0};
		while (!in.eof())
		{
			memset(inStr, 0, sizeof(inStr));
			memset(outStr, 0, sizeof(outStr));
			in.getline(inStr, MAX);
			convert(inStr, out);
		}
	}
	return 0;
}
