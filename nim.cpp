#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <limits>
#include <iterator>

using namespace std;

// declare functions
void printIntro();
int checkStartingPlayer();
void addValuesToList(int numberOfPiles);
void printBoard();
void updatePiles(int numberOfPiles);
int findPile(int numberOfPiles);
int findSticks(int pileNumber);
int checkRemainingPiles(int numberOfPiles);

// Define a structure
struct Pile
{
  int maxSizeOfPile;
  int currentSizeOfPile;
  bool isActivePile = true;

  Pile(int h, int c) : maxSizeOfPile(h), currentSizeOfPile(c) {}
};

// initilize a instance of a list of Piles
list<Pile> piles;

int main()
{

  // declare variables
  int numberOfPiles = 3;
  int isPlayer;

  // call printIntro
  printIntro();

  // ask player if they want to go first and update isPlayer
  isPlayer = checkStartingPlayer();
  if (isPlayer == 2)
  {
    cout << "Thank you for playing\n";
    return 0;
  }

  addValuesToList(numberOfPiles);
  printBoard();

  while (checkRemainingPiles(numberOfPiles) > 0)
  {
    updatePiles(numberOfPiles);
    printBoard();
  }


  return 0;
}

void printIntro()
{

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

int checkStartingPlayer()
{
  // ask user if they want to start
  cout << "Do you wish to go first? (y/n), if you want to exit the program press q" << endl;

  // gets pileNumber from user descarding charaters after the first one and puts it in pileNumber
  // this stops buffer overflow attacks.
  char input = getchar();

  // this clears the buffer.
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }

  if (input == 'n')
  {
    return 0;
  }
  else if (input == 'y')
  {
    return 1;
  }
  else if (input == 'q')
  {
    return 2;
  }

  cout << "error: please enter a valid character\n Try again" << endl;

  return checkStartingPlayer();
}

void addValuesToList(int numberOfPiles)
{
  // loop through and add values to the list.

  for (int i = 0; i < numberOfPiles; i++)
  { // adds value of i to maxNumberOfPiles and currentNumberOfPiles
    piles.push_back(Pile(i + 3, i + 3));
  }
}

void printBoard()
{
  cout << "Current Board:\n";

  // Loop through each pile and print the "|" for currentSizeOfPile
  for (const auto &pile : piles)
  {
    for (int i = 0; i < pile.currentSizeOfPile; i++)
    {
      cout << "|";
    }
    cout << endl;
  }
}

int findPile(int numberOfPiles)
{
  // initiate variable pileNumber and isValudPileNumber
  int pileNumber = 0;
  bool isValidPileNumber = false;
  numberOfPiles--;

  // ask user for pileNumber
  while (!isValidPileNumber)
  {
    cout << "Enter the index of the pile number you want to pick up from between 0 and " << numberOfPiles << ": ";
    if (cin >> pileNumber)
    {
      if (pileNumber >= 0 && pileNumber <= numberOfPiles)
      {
        // Access the element at index 0
        Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

        if (pileAtPileNumber.isActivePile == true)
        {
          isValidPileNumber = true;
        }
        else
        {
          cout << "Error: that pile is empty, please try again." << endl;
        }
      }
      else
      {
        cout << "PileNumber is outside the valid range. Try again." << endl;
      }
    }
    else
    {
      cout << "Invalid pileNumber. Please enter an integer." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  return pileNumber;
}

int findSticks(int pileNumber)
{
  // initiate variable stickNumber
  int stickNumber = 0;

  bool isValidStickNumber = false;

  // Access the element at index pileNumber
  Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

  // ask user for pileNumber
  while (!isValidStickNumber)
  {
    // TODO for the pile entered above get currentPileNumber
    cout << "Enter the number of sticks you want to pick up between 1 and " << pileAtPileNumber.currentSizeOfPile << ": ";
    if (cin >> stickNumber)
    {
      if (stickNumber >= 1 && stickNumber <= pileAtPileNumber.currentSizeOfPile)
      {
        isValidStickNumber = true;
      }
      else
      {
        cout << "StickNumber is outside the valid range. Try again." << endl;
      }
    }
    else
    {
      cout << "Invalid StickNumber. Please enter an integer." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  return stickNumber;
}

void updatePiles(int numberOfPiles)
{
  // declare variables
  int pileNumber = findPile(numberOfPiles);
  int stickNumber = findSticks(pileNumber);

  // Access the element at index pileNumber
  Pile &pileAtPileNumber = *next(piles.begin(), pileNumber);

  // as I have already checked if the value of stickNumber is between 1 and currentSizeOfPile
  // I can just take stick number off.
  pileAtPileNumber.currentSizeOfPile -= stickNumber;

  // if pileAtPileNumber.currentSozeOfPile is now equal to 0, change bool in structure to false
  if (pileAtPileNumber.currentSizeOfPile == 0)
  {
    pileAtPileNumber.isActivePile = false;
  }
}

int checkRemainingPiles(int numberOfPiles)
{
  int remainingPiles = 0;

  for (int i = 0; i < numberOfPiles; i++)
  {
    Pile &pileAtPileNumber = *next(piles.begin(), i); // creates a pointer to the pile at index i

    // check if pileAtPileNumber.isActivePile == true add 1 to remainingPiles
    if (pileAtPileNumber.isActivePile == true)
    {
      remainingPiles++;
    }
  }
  cout << "The Remaining Number Of Piles is, " << remainingPiles << endl;
  return remainingPiles;
}