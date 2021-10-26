#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

void reverse(char *&num)
{
    char *ans = new char;
    int k = 0;
    for (int i = strlen(num); i > 0; i--, k++)
    {
        ans[k] = num[i - 1];
    }
    ans[k] = '\0';
    num = ans;
}
void add(char *num1, char *num2, char *&ans)
{
    bool carryTag = false;
    for (int i = strlen(num1) - 1, j = strlen(num2) - 1, k = 0;; i--, j--, k++)
    {
        if ((i < 0) && (j < 0))
        {
            if (carryTag)
                ans[k++] = '1';
            ans[k] = '\0';
            break;
        }
        else if (i < 0)
            ans[k] = num2[j];
        else if (j < 0)
            ans[k] = num1[i];
        else
            ans[k] = num1[i] + num2[j] - '0';
        if (carryTag)
        {
            ans[k]++;
            carryTag = false;
        }
        if (ans[k] - '0' >= 10)
        {
            ans[k] -= 10;
            carryTag = true;
        }
    }
    reverse(ans);
}
void print(char *num1, char *num2, char *ans)
{
    int sub = strlen(num1) - strlen(num2);
    sub = sub > 0 ? sub : -sub;
    cout << " ";
    if (strlen(num1) > strlen(num2))
    {
        cout << num1 << endl;
        cout << "+";
        for (int i = 0; i < sub; i++)
            cout << " ";
        cout << num2 << endl;
    }
    else
    {
        for (int i = 0; i < sub; i++)
            cout << " ";
        cout << num1 << endl;
        cout << "+" << num2 << endl;
    }
    for (int i = 0; i < ((strlen(num1) > strlen(num2)) ? strlen(num1) : strlen(num2)) + 1; i++)
        cout << "-";
    cout << endl;
    if (!(strlen(ans) > (strlen(num1) > strlen(num2) ? strlen(num1) : strlen(num2))))
        cout << " ";
    cout << ans << endl;
}

int main()
{
    char *num1 = new char;
    char *num2 = new char;
    char *ans = new char;
    cin >> num1 >> num2;
    add(num1, num2, ans);
    print(num1, num2, ans);
    return 0;
}