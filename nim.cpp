#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <random>
#include <string.h>

using namespace std;

// declare functions
void printIntro();
int checkStartingPlayer();
void addValuesToList(int numberOfPiles);
void printBoard();
void updatePiles(int numberOfPiles, int isPlayer);
int findPile(int numberOfPiles, int isPlayer);
int findSticks(int pileNumber, int isPlayer);
int checkRemainingPiles(int numberOfPiles);
bool checkForWinner(int numberOfPiles);

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

// Define a structure
struct Pile {
  int maxSizeOfPile;
  int currentSizeOfPile;
  bool isActivePile = true;

  Pile(int h, int c) : maxSizeOfPile(h), currentSizeOfPile(c) {}
};

// initilize a instance of a list of Piles
list<Pile> piles;

int main() {

  // declare variables
  int numberOfPiles = 3;
  int isPlayer;
  bool winnerFound = false;

  // call printIntro
  printIntro();

  // ask player if they want to go first and update isPlayer
  isPlayer = checkStartingPlayer();
  if (isPlayer == 2) {
    cout << "Thank you for playing " << endl;
    return 0;
  }

  addValuesToList(numberOfPiles);
  printBoard();

  while (checkRemainingPiles(numberOfPiles) > 0) {
    if (isPlayer == 1) {
      cout << "\n\nIt is your turn player 1" << endl;
      updatePiles(numberOfPiles, isPlayer);
      printBoard();
      if (checkForWinner(numberOfPiles)) {
        cout << "The winner is the Computer" << endl;
        winnerFound = true;
        break;
      }
      isPlayer = 0;
    } else {
      updatePiles(numberOfPiles, isPlayer);
      printBoard();
      if (checkForWinner(numberOfPiles)) {
        cout << "The winner is Player 1" << endl;
        winnerFound = true;
        break;
      }
      isPlayer = 1;
    }
  }

  // catering for if the player took all of the remaining stick and didn't leave
  // 1
  if (winnerFound == false) {
    if (isPlayer == 1) {
      cout << "The winner is the computer" << endl;
    } else {
      cout << "The winner is Player 1" << endl;
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

int checkStartingPlayer() {
  // ask user if they want to start
  cout << "Do you wish to go first? (y/n), if you want to exit the program "
          "press q"
       << endl;

  // gets pileNumber from user descarding charaters after the first one and puts
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
    piles.push_back(Pile(i + 3, i + 3));
  }
}

void printBoard() {
  cout << "Current Board:\n";

  // Loop through each pile and print the "|" for currentSizeOfPile
  for (const auto &pile : piles) {
    for (int i = 0; i < pile.currentSizeOfPile; i++) {
      cout << "|";
    }
    cout << endl;
  }
}

int findPile(int numberOfPiles, int isPlayer) {
  // initiate variable pileNumber and isValudPileNumber
  int pileNumber = 0;
  bool isValidPileNumber = false;
  numberOfPiles--;

  // check if it is the player or computer
  if (isPlayer == true) {
    // ask user for pileNumber
    while (!isValidPileNumber) {
      cout << "Enter the index of the pile number you want to pick up from "
              "between 0 and "
           << numberOfPiles << ": ";
      if (cin >> pileNumber) {
        if (pileNumber >= 0 && pileNumber <= numberOfPiles) {
          // Access the element at index 0
          Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

          if (pileAtPileNumber.isActivePile == true) {
            isValidPileNumber = true;
          } else {
            cout << "Error: that pile is empty, please try again." << endl;
          }
        } else {
          cout << "PileNumber is outside the valid range. Try again." << endl;
        }
      } else {
        cout << "Invalid pileNumber. Please enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
    }
  } else {
    while (isValidPileNumber == false) {

      pileNumber = Random::getRandomNumber(numberOfPiles);
      // Access the element at index 0
      Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

      if (pileAtPileNumber.isActivePile == true) {
        isValidPileNumber = true;
      }
    }
  }

  return pileNumber;
}

int findSticks(int pileNumber, int isPlayer) {
  // initiate variable stickNumber
  int stickNumber = 0;

  bool isValidStickNumber = false;

  // Access the element at index pileNumber
  Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

  // check if isPlayer == true
  if (isPlayer == true) {
    // ask user for pileNumber
    while (!isValidStickNumber) {
      // TODO for the pile entered above get currentPileNumber
      cout << "Enter the number of sticks you want to pick up between 1 and "
           << pileAtPileNumber.currentSizeOfPile << ": ";
      if (cin >> stickNumber) {
        if (stickNumber >= 1 &&
            stickNumber <= pileAtPileNumber.currentSizeOfPile) {
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
    if (pileAtPileNumber.currentSizeOfPile > 0) {
      stickNumber = Random::getRandomNumber(pileAtPileNumber.currentSizeOfPile);
    } else {
      cout << "The computer can't pick a move because currentSizeOfPile is not "
              "above 0,"
           << "this error will be fixed when I implement a winner function"
           << endl;
    }
  }
  return stickNumber;
}

void updatePiles(int numberOfPiles, int isPlayer) {
  // declare variables
  int pileNumber = findPile(numberOfPiles, isPlayer);
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

  // Access the element at index pileNumber
  Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

  // as I have already checked if the value of stickNumber is between 1 and
  // currentSizeOfPile I can just take stick number off.
  pileAtPileNumber.currentSizeOfPile -= stickNumber;

  // if pileAtPileNumber.currentSozeOfPile is now equal to 0, change bool in
  // structure to false
  if (pileAtPileNumber.currentSizeOfPile == 0) {
    pileAtPileNumber.isActivePile = false;
  }
}

int checkRemainingPiles(int numberOfPiles) {
  int remainingPiles = 0;
  for (int i = 0; i < numberOfPiles; i++) {
    // creates a pointer to the pile at index i
    Pile &pileAtPileNumber = *next(piles.begin(), i);

    // check if pileAtPileNumber.isActivePile == true add 1 to remainingPiles
    if (pileAtPileNumber.isActivePile == true) {
      remainingPiles++;
    }
  }
  return remainingPiles;
}

bool checkForWinner(int numberOfPiles) {
  int remainingPiles = checkRemainingPiles(numberOfPiles);

  if (remainingPiles == 1) {
    for (int i = 0; i < numberOfPiles; i++) {
      Pile &pileAtPileNumber = *next(piles.begin(), i);

      if (pileAtPileNumber.isActivePile &&
          pileAtPileNumber.currentSizeOfPile <= 1) {
        return true;
      }
    }
  }

  return false;
}
