#include <iostream>

#include <cstdlib>
#include <ctime>
using namespace std;

void displayGame(int *n);
void initializeGame(int *n);
void gameLoop(int * n);
int* n = new int[24];
bool isGameFinished = false;
bool firstPlayer = true;
int firstPlayersHand = 0;
int secondPlayersHand = 0;

int main() {
    initializeGame(n);
    displayGame(n);
    while (!isGameFinished) {
        gameLoop(n);
        displayGame(n);
    }
    return 0;
}
void gameLoop(int *n) {
    bool isGameOver1 = true;
    bool isGameOver2 = true;
    int movement;
    int movementAmount;
    bool trueStone = false;
    for (int i = 0; i < 24; i++) {
        if (n[i] > 0) {
            isGameOver1 = false;
        }else {
            isGameOver2 = false;
        }
    }
    if (isGameOver1 || isGameOver2) {
        if (isGameOver1)
            cout << "Game Over. Player 1 won!!!" << endl;
        else
            cout << "Game Over. Player 2 won!!!" << endl;
        cout << "Press R to start again or Q to quit. ";
        char c;
        do {
            cin>> c;
        }while(c != 'r' || c != 'q');
        if (c == 'r') {
            initializeGame(n);
        }
        else {
            isGameFinished = true;
        }
    }
    else{
        if (firstPlayer) {
            cout << "O's turn: " << endl;
            char temp = 'e';
            cin>>temp;

            srand(time(0));
            int dice1 = (rand() % 6) + 1;
            int dice2 = (rand() % 6) + 1;

            cout << "The dices: " << dice1 << " " << dice2 << endl;
            firstPlayer = false;
            int coef =1;
            if (dice1 == dice2) {
                coef = 2;
            }
            for (int l = 0; l < coef *2 ; l++) {
                do {
                    cout << "Enter the movement: " << endl;
                    cin>>movement;
                    cout << "Enter the movement amount: " << endl;
                    cin>>movementAmount;
                    if (movement >= 0 && movement< 24 && n[movement] > 0 && movementAmount>0&&
                        movement >= movementAmount && n[movement-movementAmount] >= -1 &&
                        (movementAmount == dice1 || movementAmount == dice2)) {
                        trueStone = true;
                        }
                    else {
                        cout << "Invalid input." << endl;
                    }
                }while (!trueStone);
                n[movement]--;
                if (n[movement - movementAmount] == -1) {
                    secondPlayersHand++;
                    n[movement - movementAmount] = 1;
                }
                else {
                    n[movement - movementAmount]++;
                }

                if (dice1 == movementAmount && dice1 != dice2)
                    dice1 = -1;
                else if (dice2 == movementAmount && dice1 != dice2)
                    dice2 = -1;

                displayGame(n);

                movement = -1;
                movementAmount = -1;
                trueStone = false;
            }
        }
        else { //for second players turn
            firstPlayer = true;
            cout << "X's turn: " << endl;
            char temp = 'e';
            cin>>temp;

            srand(time(0));
            int dice1 = (rand() % 6) + 1;
            int dice2 = (rand() % 6) + 1;

            cout << "The dices: " << dice1 << " " << dice2 << endl;
            int coef =1;
            if (dice1 == dice2) {
                coef = 2;
            }
            for (int l = 0; l < coef *2 ; l++) {
                do {
                    cout << "Enter the movement: " << endl;
                    cin>>movement;
                    cout << "Enter the movements amount: " << endl;
                    cin>>movementAmount;
                    if (movement >= 0 && movement< 24 && n[movement] < 0 && movementAmount>0 &&
                        movement + movementAmount <24 && n[movement+movementAmount] <= 1 &&
                        (movementAmount == dice1 || movementAmount == dice2)) {
                        trueStone = true;
                        }
                    else {
                        cout << "Invalid input." << endl;
                    }
                }while (!trueStone);
                n[movement]++;
                if (n[movement + movementAmount] == 1) {
                    firstPlayersHand++;
                    n[movement + movementAmount] = -1;
                }
                else {
                    n[movement + movementAmount]--;
                }

                if (dice1 == movementAmount && dice1 != dice2)
                    dice1 = -1;
                else if (dice2 == movementAmount && dice1 != dice2)
                    dice2 = -1;

                displayGame(n);

                movement = -1;
                movementAmount = -1;
                trueStone = false;
            }
        }
    }

}
void initializeGame(int *n) {
    for (int i = 0; i < 24; i++) {
        n[i] = 0;
    }
    n[23] = -2;
    n[12] = -5;
    n[7] = -3;
    n[5] = 5;
    n[18] = 5;
    n[16] = 3;
    n[11] = 5;
    n[0] = 2;
    firstPlayer = true;
    firstPlayersHand = 0;
    secondPlayersHand = 0;
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
            if (abs(n[i]) >= row ) {
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
