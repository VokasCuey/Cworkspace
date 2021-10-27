#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//将一个数字高低位反转
void reverse(char *&num)
{
    char *ans = new char;
    int k = 0;
    for (int i = strlen(num); i > 0; i--, k++)
    {
        ans[k] = num[i - 1];
    }
    ans[k] = '\0'; //结束字符串
    num = ans;
}
//计算两个数的和，并将结果储存在ans中
void add(char *num1, char *num2, char *&ans)
{
    bool carryTag = false; //进位标志，有进位为true，否则为false
    for (int i = strlen(num1) - 1, j = strlen(num2) - 1, k = 0;; i--, j--, k++)
    //从num1和num2的最低位开始依次相加，并将结果倒序储存在ans中
    //num1当前位：第strlen(num1)-i位
    //num2当前位：第strlen(num2)-j位
    //ans当前位：第k+1位
    {
        if ((i < 0) && (j < 0)) //所有位均运算完毕
        {
            if (carryTag)
                ans[k++] = '1'; //若此时有进位，则最高位仅可能为1，并后移一位
            ans[k] = '\0';      //结束ans字符串
            break;              //结束运算
        }
        else if (i < 0) //若num1所有位均已运算完毕，则ans当前位仅与num2当前位相加
            ans[k] = num2[j];
        else if (j < 0) //若num2所有位均已运算完毕，则ans当前位仅与num1当前位相加
            ans[k] = num1[i];
        else //若num1，num2均有剩余位未运算，则ans当前位等于num1，num2当前位之和
            ans[k] = num1[i] + num2[j] - '0';
        if (carryTag) //若上一位运算有进位，则ans当前位+1，并将进位标志置为false
        {
            ans[k]++;
            carryTag = false;
        }
        if (ans[k] - '0' >= 10) //若ans当前位大于10，则ans当前位-10，并将进位标志置为true
        {
            ans[k] -= 10;
            carryTag = true;
        }
    }
    reverse(ans); //反转ans
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
    add(num1, num2, ans);   //求和，ans=num1+num2
    print(num1, num2, ans); //输出计算式
    return 0;
}