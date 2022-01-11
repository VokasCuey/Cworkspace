#include <iostream>
using namespace std;

void sort(int *a, int **b, int pos, int k, int n)
{
	if (k<=0)
		return;
	for (
	sort(a,b,pos+4*n-4,k-2,n);
}

int luck(int **b)
{
}

int main()
{
	int n=0;
	cin >> n;
	int *a=new int[n*n+1]();
	int **b=new int*[n+1]();
	for (int i=1;i<=n;i++)
		b[i]=new int[n+1]();
	for (int i=1;i<=n*n;i++)
		cin >> a[i];
	sort(a,b,1,n,n);
	cout << luck(b) << endl;
	return 0;
}
