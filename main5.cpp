#include <iostream>
#include <clocale>
using namespace std;
int board[8][8] = {0};
int bx[8] = { 0 };
int by[8] = { 0 };

void setN(int x, int y, int num) {
    if ((x < 8) && (y < 8) && (x >= 0) && (y >= 0))
        if (board[x][y] == 0)
            board[x][y] = num;
}

void setZeroIfN(int x, int y, int num) {
    if ((x < 8) && (y < 8) && (x >= 0) && (y >= 0))
        if (board[x][y] == num)
            board[x][y] = 0;
}

void egor3(int x, int y, int num) {
    for (int x1 = 0; x1 < 8; ++x1) {
        setZeroIfN(x1, y, num);
        setZeroIfN(x, x1, num);
    }

    for (int k = 1; k < 8; ++k) {
        setZeroIfN(x + k, y + k, num);
        setZeroIfN(x - k, y + k, num);
        setZeroIfN(x + k, y - k, num);
        setZeroIfN(x - k, y - k, num);
    }
}

void printBoard() {
    cout << endl;
    int tboard[8][8] = { 0 };
    for (int k = 0; k < 8; ++k)
    {
        tboard[bx[k]][by[k]] = k+1;
    }
    for (int x1 = 0; x1 < 8; ++x1) {
        for (int y1 = 0; y1 < 8; ++y1) {
            cout << tboard[x1][y1] << " ";
        }
        cout << endl;
    }
}

void egor2(int x, int y, int num) {
    for (int x1 = 0; x1 < 8; ++x1) {
        setN(x1, y, num);
    }
    for (int y1 = 0; y1 < 8; ++y1) {
        setN(x, y1, num);
    }
    for (int k = 1; k < 8; ++k) {
        setN(x + k, y + k, num);
        setN(x - k, y + k, num);
        setN(x + k, y - k, num);
        setN(x - k, y - k, num);
    }
    board[x][y] = num;
    bx[num] = x;
    by[num] = y;

}



bool egor(int num) {
    bool pos = false;

    for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 8; ++y)
            {

                if (board[x][y] == 0 && !pos)
                {
                    
                    egor2(x, y, num);

                    if (num > 1)
                    {
                        pos = egor(num - 1);
                        if (!pos) {
                            egor3(x, y, num);
                        }
                    } else {
                        pos = true;
                        printBoard();
                    }
                }
            }
        }
    return pos;
}

int main() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board[x][y] = 0;
        }
    }
    egor(8);
}