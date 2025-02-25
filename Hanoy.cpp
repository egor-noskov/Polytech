#include <iostream>
using namespace std;

void F2(int point1, int point2)
{
    cout << "Перекладываем диск со стержня " << point1 <<" на стержень " << point2 << endl;
}

void F1(int amount, int start, int point)
{
    if(amount == 1)
        F2(start, point);
    else
    {
    int temp = 6-start-point;
    F1(amount - 1, start, temp);
    F2(start, point);
    F1(amount - 1, temp, point);
    }
}

int main()
{
    setlocale(LC_ALL,"Rus");
    F1(3, 1, 3);
    return 0;
}
