#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

// declare functions
void printIntro();
int checkStartingPlayer();

int main()
{

  // declare variables
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
          "   If you pick up the last stick you win\n";
}

int checkStartingPlayer()
{
  // ask user if they want to start
  cout << "Do you wish to go first? (y/n), if you want to exit the program press q\n";

  // gets input from user descarding charaters after the first one and puts it in input
  // this stops buffer overflow attacks.
  char input = getchar();

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

  cout << "error: please enter a valid character\n Try again\n";

  return checkStartingPlayer();
}