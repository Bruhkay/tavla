#include <iostream>
using namespace std;
void displayGame(int *n);
int main() {
    int* n = new int[24];
    for (int i = 0; i < 24; i++) {
        n[i] = 4;
    }
    n[4] = -3;
    n[6] = -3;
    n[8] = -3;
    n[9] = 3;
    n[22] = -5;
    n[19] = 8;
    displayGame(n);
    return 0;
}
void displayGame(int * n) {
    cout << "+------------------------------------------------------+"<<endl;
    cout << "| 12  13  14  15  16  17 |BAR| 18  19  20  21  22  23  |"<<endl;
    int row =0;
    int max;
    for (int j = 12; j < 24; j++) {
        if (abs(n[j])> max) {
            max = abs(n[j]);
        }
    }
    do {
        cout << "|";
        row++;
        for (int i = 12; i < 24; i++) {


            if (abs(n[i]) >= row) {
                if (n[i] < 0) {
                    cout << " x  ";
                }else {
                    cout << " o  ";
                }
            }else {
                cout << "    ";
            }
            if (i == 17 || i ==6) {
                cout << "|   |";
            }
        }
        cout << " |" << endl;
    }while (row < max+2);

    max = 0;
    for (int j = 0; j < 12; j++) {
        if (abs(n[j])> max) {
            max = abs(n[j]);
        }
    }
    row = max;
    do {
        cout << "|";
        for (int i = 11; i > -1; i--) {
            if (abs(n[i]) >= row) {
                if (n[i] < 0) {
                    cout << " x  ";
                }else {
                    cout << " o  ";
                }
            }else {
                cout << "    ";
            }
            if (i == 17 || i ==6) {
                cout << "|   |";
            }
        }
        cout << " |" << endl;
        row--;
    }while (row != 0);
    cout << "| 11  10  9   8   7   6  |BAR| 5   4   3   2   1   0   |"<<endl;
    cout << "+------------------------------------------------------+"<<endl;
}
