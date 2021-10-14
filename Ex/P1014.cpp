#include <iostream>
using namespace std;

int sum(int n)
{
    return 0.5*n*(n+1);
}

int main()
{
    int N=0,n=0;
    cin >> N;
    for (n=1;;n++)
        if (N>sum(n-1)&&N<=sum(n))
            break;
    return 0;
}