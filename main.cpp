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
bool firstPlayerReady = false;
bool secondPlayerReady = false;

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
                bool readyO = true;
                bool readyX = true;
                for (int i = 0; i < 24; i++) {
                    if (i > 5 && n[i] > 0) {
                        readyO = false;
                    }
                    if (i < 17 && n[i] < 0) {
                        readyX = false;
                    }
                }
                if (readyO && firstPlayersHand!=0)
                    firstPlayerReady = true;
                if (readyX && secondPlayersHand!=0)
                    secondPlayerReady = true;
                do {
                    cout << "Enter the movement: (to call from stack)" << endl;
                    if (firstPlayersHand != 0)
                        cout << "Warning! There is " << firstPlayersHand<< " stone. In the stack."<< endl;
                    if (firstPlayerReady)
                        cout << "Ready!!!"<< endl;
                    else
                        cout << "not Ready!!!" << endl;

                    cin>>movement;
                    cout << "Enter the movements amount: (to abort press -1)" << endl;
                    cin>>movementAmount;
                    if ((firstPlayersHand!=0 && n[24-movementAmount]>=-1 && movement == -1) ||
                        firstPlayersHand == 0 && movement >= 0 && movement< 24 &&
                        n[movement] > 0 && movementAmount>0&&
                        movement >= movementAmount && n[movement-movementAmount] >= -1 &&
                        (movementAmount == dice1 || movementAmount == dice2) ||
                        (firstPlayerReady && movement >= 0 && movement< 6 &&
                        n[movement] > 0 && movementAmount>0 &&
                        (movementAmount == dice1 || movementAmount == dice2))) {
                        trueStone = true;
                        }
                    else {
                        cout << "Invalid input." << endl;
                    }
                }while (!trueStone&& movementAmount !=-1);

                if (movementAmount != -1) {
                    n[movement]--;
                    if (firstPlayersHand == 0 && n[movement - movementAmount] == -1) {
                        secondPlayersHand++;
                        n[movement - movementAmount] = 1;
                    }
                    else if (movement != -1) {
                        n[movement - movementAmount]++;
                    }
                    else if (movement == -1 && firstPlayersHand != 0) {
                        if (n[24-movementAmount] == -1) {
                            secondPlayersHand++;
                            n[24- movementAmount] = 1;
                            firstPlayersHand--;
                        }
                        else {
                            n[24- movementAmount]++;
                            firstPlayersHand--;
                        }
                    }
                    else if (movementAmount > movement) {
                        n[movement]--;
                    }

                    if (dice1 == movementAmount && dice1 != dice2)
                        dice1 = -1;
                    else if (dice2 == movementAmount && dice1 != dice2)
                        dice2 = -1;

                    displayGame(n);

                    movement = -2;
                    movementAmount = -2;
                    trueStone = false;
                }
            }
        }
        else if (!firstPlayer && !secondPlayerReady){ //for second players turn
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
                    cout << "Enter the movement: (to call from stack)" << endl;
                    if (secondPlayersHand != 0)
                        cout << "Warning! There is " << secondPlayersHand<< " stone. In the stack."<< endl;
                    cin>>movement;
                    cout << "Enter the movements amount: (to abort press -1)" << endl;
                    cin>>movementAmount;
                    if ((secondPlayersHand!=0 && n[movementAmount] <= 1 && movement ==-1) ||
                        (secondPlayersHand==0 &&
                        movement >= 0 && movement< 24 && n[movement] < 0 && movementAmount>0 &&
                        movement + movementAmount <24 && n[movement+movementAmount] <= 1 &&
                        (movementAmount == dice1 || movementAmount == dice2))) {
                        trueStone = true;
                        }
                    else {
                        cout << "Invalid input." << endl;
                    }
                }while (!trueStone && movementAmount !=-1);

                if (movementAmount != -1) {
                    n[movement]++;
                    if ( secondPlayersHand == 0 && n[movement + movementAmount] == 1) {
                        firstPlayersHand++;
                        n[movement + movementAmount] = -1;
                    }
                    else if (movement != -1) {
                        n[movement + movementAmount]--;
                    }
                    else if ( movement == -1 && secondPlayersHand != 0) {
                        if (n[movementAmount] == 1) {
                            firstPlayersHand++;
                            n[movementAmount] = -1;
                            secondPlayersHand--;
                        }
                        else {
                            n[ movementAmount]--;
                            secondPlayersHand--;
                        }
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
                else {
                    cout << "Passed." << endl;
                }
            }
        }

    }

}
void initializeGame(int *n) {
    for (int i = 0; i < 24; i++) {
        n[i] = 0;
    }
    //n[23] = 2;
    //n[12] = 5;
    n[18] = -5;
    n[16] = -3;
    n[11] = -5;
    //n[7] = 3;
    n[7]=1;
    n[5] = 5;
    n[0] = -2;
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
