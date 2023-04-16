#include<iostream>

using namespace std;

void doubleValue(int& x)
{
  x *= 2;
}

int main()
{
  int x = 10;
  cout << "x = " << x << endl; // 输出 x = 10

  doubleValue(x); // 将 x 的值加倍
  cout << "x = " << x << endl; // 输出 x = 20

  return 0;
}

