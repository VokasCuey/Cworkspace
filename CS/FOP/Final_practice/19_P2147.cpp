#include <iostream>
using namespace std;

#define MAX(a,b) ((a>b)?a:b)

int main()
{
	int n=0, m=0;
	cin >> n >> m;
	int *val=new int[n+1];
	int **max=new int*[n+1];
	max[0]=new int[m+1]();
	for (int i=1;i<=n;i++)
	{
		cin >> val[i];
		max[i]=new int[m+1]();
	}
	for (int i=0;i<=m;i++)
		max[0][i]=i;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (val[i]>j)
				max[i][j]=max[i-1][j];
			else
				max[i][j]=MAX(max[i-1][j],max[i-1][j%val[i]]);
		}
	return 0;
}