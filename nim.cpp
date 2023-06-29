#include <cstdio>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <unistd.h>

using namespace std;

// declare functions
void printIntro();

int checkStartingPlayer();

void addValuesToList(int numberOfPiles);

void printBoard();

void updatePiles(int isPlayer);

int findSticks(int pileNumber, int isPlayer);

int checkRemainingPiles();

int checkForWinner();

int findNumberOfPiles();

// define namespace Random
namespace Random {
// Random number generator engine
    mt19937 gen(random_device{}());

// Function to generate a random number in a given range
    int getRandomNumber(int max) {
        uniform_int_distribution<int> dis(1, max);
        return dis(gen);
    }
} // namespace Random

// initialize an instance of a list of Piles
vector<int> piles;

int main() {

    // declare variables
    int isPlayer;
    bool winnerFound = false;

    // call printIntro
    printIntro();
    int numberOfPiles = findNumberOfPiles();

    // ask player if they want to go first and update isPlayer
    isPlayer = checkStartingPlayer();
    if (isPlayer == 2) {
        cout << "Thank you for playing " << endl;
        return 0;
    }

    addValuesToList(numberOfPiles);
    printBoard();

    while (checkRemainingPiles() > 0) {
        if (isPlayer == 1) {
            if (checkForWinner() == 1) {
                cout << "\n\nThe winner is Player 1" << endl;
                winnerFound = true;
                break;
            } else if (checkForWinner() == 2) {
                cout << "\n\nThe winner is the Computer" << endl;
            }
            cout << "\n\nIt is your turn player 1" << endl;
            updatePiles(isPlayer);
            printBoard();
            isPlayer = 0;
        } else {

            cout << "The computer is thinking:" << endl;
            sleep(2);
            if (checkForWinner() == 1) {
                cout << "\n\nThe winner is the Computer" << endl;
                winnerFound = true;
                break;
            } else if (checkForWinner() == 2) {
                cout << "\n\nThe winner is Player 1" << endl;
            }
            updatePiles(isPlayer);
            printBoard();
            isPlayer = 1;
        }
    }

    // catering for if the player took all the remaining stick and didn't leave
    // 1
    if (!winnerFound) {
        if (isPlayer == 1) {
            cout << "\n\nThe winner is the computer" << endl;
        } else {
            cout << "\n\nThe winner is Player 1" << endl;
        }
    }

    cout << "Thank you for playing" << endl;
    return 0;
}

void printIntro() {

    // print out the introduction
    cout << "Welcome to Nim!! \n"
            "This is a stick picking up game.\n"
            "The rules are as follows:\n"
            "   You may pick sticks from 1 of the three piles\n"
            "   You can pick up as many sticks as you want from that pile\n"
            "   You have to pick up at least 1 stick each turn\n"
            "   If you pick up the last stick you win"
         << endl;
}

int findNumberOfPiles(){
    int numPiles;

    do {
        std::cout << "Enter the number of piles (1-20): ";
        while (!(cin >> numPiles)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number of piles (1-20): ";
        }
    } while (numPiles < 1 || numPiles > 20);

    return numPiles;
}
int checkStartingPlayer() {
    // ask user if they want to start
    cout << "Do you wish to go first? (y/n), if you want to exit the program "
            "press q"
         << endl;

    // gets pileNumber from user discarding characters after the first one and puts
    // it in pileNumber this stops buffer overflow attacks.
    char input = getchar();

    // this clears the buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (input == 'n') {
        return 0;
    } else if (input == 'y') {
        return 1;
    } else if (input == 'q') {
        return 2;
    }

    cout << "error: please enter a valid character\n Try again" << endl;

    return checkStartingPlayer();
}

void addValuesToList(int numberOfPiles) {
    // loop through and add values to the list.

    // adds value of i to maxNumberOfPiles and currentNumberOfPiles
    for (int i = 0; i < numberOfPiles; i++) {
        piles.push_back(i + 3);
    }
}

void printBoard() {
    cout << "Current Board:\n";

    // Loop through each pile and print the "|" for currentSizeOfPile
    for (const auto &pile: piles) {
        for (int i = 0; i < pile; i++) {
            cout << "|";
        }
        cout << endl;
    }
}

int findPile(int isPlayer) {
    // initiate variable pileNumber and isValidPileNumber
    int pileNumber = 0;
    bool isValidPileNumber = false;

    // check if it is the player or computer
    if (isPlayer == true) {
        // ask user for pileNumber
        while (!isValidPileNumber) {
            cout << "Enter the index of the pile number you want to pick up from "
                    "between 1 and "
                 << checkRemainingPiles() << ": ";
            if (cin >> pileNumber) {
                if (pileNumber < 1 || pileNumber > checkRemainingPiles()) {

                    cout << "PileNumber is outside the valid range. Try again." << endl;
                } else {
                    isValidPileNumber = true;
                }
            } else {
                cout << "Invalid pileNumber. Please enter an integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } else {

        cout << "Finding number of piles" << endl;
        sleep(1);
        pileNumber = Random::getRandomNumber(checkRemainingPiles());
    }

    pileNumber--;
    return pileNumber;
}

int findSticks(int pileNumber, int isPlayer) {
    // initiate variable stickNumber
    int stickNumber = 0;

    bool isValidStickNumber = false;

    int numberOfSticks = piles[pileNumber];

    // check if isPlayer == true
    if (isPlayer == true) {
        // ask user for pileNumber
        while (!isValidStickNumber) {
            // TODO for the pile entered above get currentPileNumber
            cout << "Enter the number of sticks you want to pick up between 1 and " << numberOfSticks << ": ";
            if (cin >> stickNumber) {
                if (stickNumber >= 1 && stickNumber <= numberOfSticks) {
                    isValidStickNumber = true;
                } else {
                    cout << "StickNumber is outside the valid range. Try again." << endl;
                }
            } else {
                cout << "Invalid StickNumber. Please enter an integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } else {
        cout << "The computer is finding number of Sticks" << endl;
        sleep(1);
        stickNumber = Random::getRandomNumber(numberOfSticks);
    }
    return stickNumber;
}

void updatePiles(int isPlayer) {
    // declare variables
    int pileNumber = findPile(isPlayer);
    int stickNumber = findSticks(pileNumber, isPlayer);

    // tell player their move or computer move.

    if (isPlayer == 1) {
        cout << "Player 1, you picked up " << stickNumber << " stick(s) from pile "
             << (pileNumber + 1) << "\n"
             << endl;
    } else {
        cout << "The computer picked up " << stickNumber << " stick(s) from pile "
             << (pileNumber + 1) << "\n"
             << endl;
    }

    // as I have already checked if the value of stickNumber is between 1 and
    // currentSizeOfPile I can just take stick number off.
    piles[pileNumber] -= stickNumber;

    // if pileAtPileNumber.currentSizeOfPile is now equal to 0, change bool in
    // structure to false
    if (piles[pileNumber] == 0) {
        piles.erase(piles.begin() + pileNumber);
    }
}

int checkRemainingPiles() { return piles.size(); }

int checkForWinner() {
    int remainingPiles = checkRemainingPiles();

    if (remainingPiles == 1) {

        for (const auto &pile: piles) {
            if (pile == 1) {
                return 1;
            }
        }
    } else if (remainingPiles == 0) {
        return 2;
    }
    return 0;
}
