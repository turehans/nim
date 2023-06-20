#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iterator>
#include <limits>
#include <list>
#include <random>
#include <string.h>


using namespace std;

// Structure for each pile
struct Pile {
  int currentSizeOfPile;
  bool isActivePile;
};

// Class for generating random numbers
class Random {
public:
  static void init() {
    srand(static_cast<unsigned>(time(0)));
  }

  static int getRandomNumber(int max) {
    return rand() % max + 1;
  }
};

vector<Pile> piles;

void initializePiles(int numberOfPiles) {
  piles.clear();

  for (int i = 0; i < numberOfPiles; i++) {
    Pile pile;
    pile.currentSizeOfPile = Random::getRandomNumber(10);
    pile.isActivePile = true;
    piles.push_back(pile);
  }
}

int findPile(int numberOfPiles, int isPlayer) {
  int pileNumber = 0;
  bool isValidPileNumber = false;

  while (!isValidPileNumber) {
    cout << "Player " << (isPlayer + 1) << ", enter the pile number you want to pick from (1-" << numberOfPiles << "): ";
    if (cin >> pileNumber) {
      if (pileNumber >= 1 && pileNumber <= numberOfPiles && piles[pileNumber - 1].isActivePile) {
        isValidPileNumber = true;
      } else {
        cout << "Invalid pile number. Please try again." << endl;
      }
    } else {
      cout << "Invalid input. Please enter an integer." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  return pileNumber;
}

int findSticks(int pileNumber, int isPlayer) {
  int stickNumber = 0;
  bool isValidStickNumber = false;

  Pile& pileAtPileNumber = piles[pileNumber - 1];

  if (isPlayer == 1) {
    while (!isValidStickNumber) {
      cout << "Enter the number of sticks you want to pick up from pile " << pileNumber << " (1-" << pileAtPileNumber.currentSizeOfPile << "): ";
      if (cin >> stickNumber) {
        if (stickNumber >= 1 && stickNumber <= pileAtPileNumber.currentSizeOfPile) {
          isValidStickNumber = true;
        } else {
          cout << "Invalid stick number. Please try again." << endl;
        }
      } else {
        cout << "Invalid input. Please enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
    }
  } else {
    if (pileAtPileNumber.currentSizeOfPile > 0) {
      stickNumber = Random::getRandomNumber(pileAtPileNumber.currentSizeOfPile);
    } else {
      cout << "The computer can't pick a move because the current pile size is not above 0. This error will be fixed when the winner function is implemented." << endl;
    }
  }

  return stickNumber;
}

void updatePiles(int numberOfPiles, int isPlayer) {
  int pileNumber = findPile(numberOfPiles, isPlayer);
  int stickNumber = findSticks(pileNumber, isPlayer);

  Pile& pileAtPileNumber = piles[pileNumber - 1];

  if (isPlayer == 1) {
    cout << "Player 1 picked up " << stickNumber << " stick(s) from pile " << pileNumber << "." << endl;
  } else {
    cout << "The computer picked up " << stickNumber << " stick(s) from pile " << pileNumber << "." << endl;
  }

  pileAtPileNumber.currentSizeOfPile -= stickNumber;

  if (pileAtPileNumber.currentSizeOfPile <= 0) {
    pileAtPileNumber.isActivePile = false;
  }
}

int checkRemainingPiles(int numberOfPiles) {
  int remainingPiles = 0;

  for (int i = 0; i < numberOfPiles; i++) {
    Pile& pileAtPileNumber = piles[i];

    if (pileAtPileNumber.isActivePile) {
      remainingPiles++;
    }
  }

  return remainingPiles;
}

bool checkForWinner(int numberOfPiles) {
  int remainingPiles = checkRemainingPiles(numberOfPiles);

  if (remainingPiles == 1) {
    return true;
  }

  return false;
}

void playGame(int numberOfPiles) {
  int currentPlayer = 1;
  bool gameOver = false;

  initializePiles(numberOfPiles);

  while (!gameOver) {
    cout << endl << "Current state of piles:" << endl;

    for (int i = 0; i < numberOfPiles; i++) {
      const Pile& pileAtPileNumber = piles[i];

      if (pileAtPileNumber.isActivePile) {
        cout << "Pile " << (i + 1) << ": ";

        for (int j = 0; j < pileAtPileNumber.currentSizeOfPile; j++) {
          cout << "|";
        }

        cout << endl;
      }
    }

    cout << endl;

    updatePiles(numberOfPiles, currentPlayer);

    if (checkForWinner(numberOfPiles)) {
      cout << "Player " << currentPlayer << " wins!" << endl;
      gameOver = true;
    } else {
      currentPlayer = currentPlayer == 1 ? 2 : 1;
    }
  }
}

int main() {
  Random::init();

  int numberOfPiles;

  cout << "Welcome to the Stick Game!" << endl;

  cout << "Enter the number of piles you want to play with: ";
  cin >> numberOfPiles;

  playGame(numberOfPiles);

  return 0;
}
