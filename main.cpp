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
        cout << endl<< endl<< "Game Over. " << (isGameOver1 ? "Player 1 won!!!" : "Player 2 won!!!") << endl;
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
            if (firstPlayer)
                if (firstPlayersHand != 0)
                    cout << "Warning!! There is " <<  firstPlayersHand << " rock at stack of O"<< endl;
            if (!firstPlayer)
                if (secondPlayersHand != 0)
                    cout << "Warning!! There is " <<  secondPlayersHand << " rock at stack of X"<< endl;

            cout << "Enter movement (-1 to use stack): ";
            cin >> movement;
            movement--;
            cout << "Enter movement amount (-1 to pass): ";
            cin >> movementAmount;
            if (movementAmount == -1) {
                cout << "Passed turn." << endl;
                if (firstPlayer) {
                    displayGameX(n);
                }
                if (!firstPlayer) {
                    displayGameO(n);
                }
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
                if (firstPlayersHand != 0 && n[24 - movementAmount] >= -1 && movement == -2)
                    trueStone = true;
                if ((firstPlayersHand != 0 && n[24 - movementAmount] >= -1 && movement == -2) ||
                    (firstPlayersHand == 0 && movement >= 0 && movement < 24 && n[movement] > 0 &&
                     movementAmount > 0 && (movement >= movementAmount  || firstPlayerReady) &&
                     (movementAmount == dice1 || movementAmount == dice2))) {
                    if (firstPlayersHand == 0 && n[movement - movementAmount] >= -1) {
                        trueStone = true;
                    }
                }
            } else {
                if (secondPlayersHand != 0 && n[movementAmount-1] <= 1 && movement == -2)
                    trueStone = true;
                if ((secondPlayersHand != 0 && n[movementAmount-1] <= 1 && movement == -2) ||
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
                if (firstPlayersHand ==0 && movement != -2) {
                    n[movement]--;
                    if (n[movement - movementAmount] == -1) {
                        secondPlayersHand++;
                        n[movement - movementAmount] = 1;
                    } else {
                        n[movement - movementAmount]++;
                    }
                }
                else {
                    firstPlayersHand--;
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
                if (movement - movementAmount >= 0) {
                    n[movement - movementAmount]++;
                }
            }
        } else { // second player
            if (!secondPlayerReady) {
                if (secondPlayersHand == 0 && movement != -2) {
                    n[movement]++;
                    if (n[movement + movementAmount] == 1) {
                        firstPlayersHand++;
                        n[movement + movementAmount] = -1;
                    } else {
                        n[movement + movementAmount]--;
                    }
                }
                else if (secondPlayersHand != 0 && movement == -2){
                    secondPlayersHand--;
                    if (n[movementAmount-1] == 1) {
                        firstPlayersHand++;
                        n[movementAmount-1] = -1;
                    } else {
                        n[movementAmount-1]--;
                    }
                }
            }
            else {
                n[movement]++;
                if (movement + movementAmount <= 23) {
                    n[movement + movementAmount]--;
                }
            }
        }
        if (dice1 == movementAmount && dice1 != dice2)
            dice1 = -1;
        if (dice2 == movementAmount && dice1 != dice2)
            dice2 = -1;
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
    cout << "| 13  14  15  16  17  18 |BAR| 19  20  21  22  23  24  |"<<endl;
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
    }while (row > 0);
    cout << "| 12  11  10  9   8   7  |BAR| 6   5   4   3   2   1   |"<<endl;
    cout << "+------------------------------------------------------+"<<endl;
}

void displayGameX(int * n) {
    cout << "+------------------------------------------------------+"<<endl;
    cout << "| 12  11  10  9   8   7  |BAR| 6   5   4   3   2   1   |"<<endl;
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
        for (int i = 11; i >-1; i--) {
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
    for (int j = 12; j < 23; j++) {
        if (abs(n[j])> max) {
            max = abs(n[j]);
        }
    }
    row = max;
    do {
        cout << "|";
        for (int i = 12; i <24 ; i++) {
            if (abs(n[i]) >= row) {
                if (n[i] < 0) {
                    cout << " x  ";
                }else {
                    cout << " o  ";
                }
            }else {
                cout << "    ";
            }
            if (i == 17 || i ==7) {
                cout << "|   |";
            }
        }
        cout << " |" << endl;
        row--;
    }while (row > 0 );
    cout << "| 13  14  15  16  17  18 |BAR| 19  20  21  22  23  24  |"<<endl;
    cout << "+------------------------------------------------------+"<<endl;
}