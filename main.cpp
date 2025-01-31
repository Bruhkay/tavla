#include <iostream>

#include <cstdlib>
#include <ctime>
using namespace std;

void displayGameO(int *n);
void displayGameX(int *n);
void initializeGame(int *n);
void gameLoop(int * n);
int* n = new int[24];
bool isGameFinished = false;
bool firstPlayer = true;
int firstPlayersHand = 0;
int secondPlayersHand = 0;
bool firstPlayerReady = false;
bool secondPlayerReady = false;

int main() {
    initializeGame(n);
    displayGameO(n);
    while (!isGameFinished) {
        gameLoop(n);
    }
    return 0;
}
void gameLoop(int *n) {
    int movement, movementAmount;

    bool isGameOver1 = true, isGameOver2 = true;
    for (int i = 0; i < 24; i++) {
        if (n[i] > 0)
            isGameOver1 = false;
        if (n[i] < 0)
            isGameOver2 = false;
    }

    if (isGameOver1 || isGameOver2) {
        cout << "Game Over. " << (isGameOver1 ? "Player 1 won!!!" : "Player 2 won!!!") << endl;
        cout << "Press R to restart or Q to quit: ";
        char choice;
        while (true) {
            cin >> choice;
            if (choice == 'r' || choice == 'R') {
                initializeGame(n);
                return;
            }
            if (choice == 'q' || choice == 'Q') {
                isGameFinished = true;
                return;
            }
            cout << "Invalid input. Press R to restart or Q to quit: ";
        }
    }

    srand(time(0));
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;
    int coef = (dice1 == dice2) ? 2 : 1;

    cout << (firstPlayer ? "O" : "X") << "'s turn: " << endl;
    cout << "Rolled Dice: " << dice1 << " " << dice2 << endl;

    for (int l = 0; l < coef * 2; l++) {

        bool trueStone = false;
        do {
            cout << "Enter movement (-1 to use stack): ";
            cin >> movement;
            if (firstPlayer)
                if (firstPlayersHand != 0)
                    cout << "Warning!! There is " <<  firstPlayersHand << " at stack."<< endl;
            if (!firstPlayer)
                if (secondPlayersHand != 0)
                    cout << "Warning!! There is " <<  secondPlayersHand << " at stack."<< endl;
            cout << "Enter movement amount (-1 to pass): ";
            cin >> movementAmount;

            if (movementAmount == -1) {
                cout << "Passed turn." << endl;
                firstPlayer = !firstPlayer;
                return;
            }

            firstPlayerReady = true;
            secondPlayerReady = true;
            for (int i = 0; i < 24; i++) {
                if (n[i] < 0 && i<18)
                    secondPlayerReady = false;
                if (n[i] > 0 && i>5)
                    firstPlayerReady = false;
            }

            if (firstPlayer) {
                if ((firstPlayersHand != 0 && n[24 - movementAmount] >= -1 && movement == -1) ||
                    (firstPlayersHand == 0 && movement >= 0 && movement < 24 && n[movement] > 0 &&
                     movementAmount > 0 && (movement >= movementAmount  || firstPlayerReady) &&
                     (movementAmount == dice1 || movementAmount == dice2))) {
                    if (firstPlayersHand == 0 && n[movement - movementAmount] >= -1) {
                        trueStone = true;
                    }
                }
            } else {
                if ((secondPlayersHand != 0 && n[movementAmount] <= 1 && movement == -1) ||
                    (secondPlayersHand == 0 && movement >= 0 && movement < 24 && n[movement] < 0 &&
                     movementAmount > 0 && (movement + movementAmount < 24 || secondPlayerReady)&&
                     (movementAmount == dice1 || movementAmount == dice2))) {
                    if (secondPlayersHand == 0 && n[movement + movementAmount] <= 1 ) {
                        trueStone = true;
                    }
                }
            }

            if (!trueStone) {
                cout << "Invalid move, try again." << endl;
            }
        } while (!trueStone);

        if (firstPlayer) {
            if (!firstPlayerReady) {
                if (movement != -1) {
                    n[movement]--;
                    if (n[movement - movementAmount] == -1) {
                        secondPlayersHand++;
                        n[movement - movementAmount] = 1;
                    } else {
                        n[movement - movementAmount]++;
                    }
                }
                else {
                    secondPlayersHand--;
                    if (n[24 - movementAmount] == -1) {
                        secondPlayersHand++;
                        n[24 - movementAmount] = 1;
                    } else {
                        n[24 - movementAmount]++;
                    }
                }
            }
            else {
                n[movement]--;
                if (movement - movementAmount > 0) {
                    n[movement - movementAmount]++;
                }
            }
        } else {
            if (!secondPlayerReady) {
                if (movement != -1) {
                    n[movement]++;
                    if (n[movement + movementAmount] == 1) {
                        secondPlayersHand++;
                        n[movement + movementAmount] = -1;
                    } else {
                        n[movement + movementAmount]--;
                    }
                }
                else {
                    secondPlayersHand--;
                    if (n[movementAmount] == 1) {
                        secondPlayersHand++;
                        n[movementAmount] = -1;
                    } else {
                        n[movementAmount]--;
                    }
                }
            }
            else {
                n[movement]++;
                if (movement - movementAmount > 0) {
                    n[movement - movementAmount]++;
                }
            }
        }
        if (firstPlayer && l+1 !=coef*2) {
            displayGameO(n);
        }
        if (!firstPlayer && l+1 !=coef*2) {
            displayGameX(n);
        }
    }
    if (firstPlayer) {
        displayGameX(n);
    }
    if (!firstPlayer) {
        displayGameO(n);
    }
    firstPlayer = !firstPlayer;
}
void initializeGame(int *n) {
    for (int i = 0; i < 24; i++) {
        n[i] = 0;
    }
    n[23] = 2;
    n[12] = 5;
    n[18] = -5;
    n[16] = -3;
    n[11] = -5;
    n[7] = 3;
    n[5] = 5;
    n[0] = -2;
    firstPlayer = true;
    firstPlayersHand = 0;
    secondPlayersHand = 0;
    isGameFinished = false;
    firstPlayerReady = false;
    secondPlayerReady = false;

}
void displayGameO(int * n) {
    cout << "+------------------------------------------------------+"<<endl;
    cout << "| 12  13  14  15  16  17 |BAR| 18  19  20  21  22  23  |"<<endl;
    int row =0;
    int max = 0;
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
void displayGameX(int * n) {
    cout << "+------------------------------------------------------+"<<endl;
    cout << "| 0   1   2   3   4   5  |BAR|  6  7   8   9  10   11   |"<<endl;
    int row =0;
    int max = 0;
    for (int j = 0; j < 12; j++) {
        if (abs(n[j])> max) {
            max = abs(n[j]);
        }
    }
    do {
        cout << "|";
        row++;
        for (int i = 0; i < 12; i++) {
            if (abs(n[i]) >= row ) {
                if (n[i] < 0) {
                    cout << " x  ";
                }else {
                    cout << " o  ";
                }
            }else {
                cout << "    ";
            }
            if (i == 5 || i ==18) {
                cout << "|   |";
            }
        }
        cout << " |" << endl;
    }while (row < max+2);

    max = 0;
    for (int j = 12; j < 23; j++) {
        if (abs(n[j])> max) {
            max = abs(n[j]);
        }
    }
    row = max;
    do {
        cout << "|";
        for (int i = 23; i > 11; i--) {
            if (abs(n[i]) >= row) {
                if (n[i] < 0) {
                    cout << " x  ";
                }else {
                    cout << " o  ";
                }
            }else {
                cout << "    ";
            }
            if (i == 18 || i ==5) {
                cout << "|   |";
            }
        }
        cout << " |" << endl;
        row--;
    }while (row != 0);
    cout << "| 23  22  21  20  19  18 |BAR| 17  16  15  14  13  12  |"<<endl;
    cout << "+------------------------------------------------------+"<<endl;
}