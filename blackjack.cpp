#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

//look up tables
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};


//Fisher-Yates / Durstenfeld shuffle algorithm
void shuffle(int cards[])
{
  for (int i = 51; i > 0; i--) {
    int j = rand() % (i + 1);
    int placeholder = cards[j];
    cards[j] = cards[i];
    cards[i] = placeholder; 
  }
}

//Prints the card in a readable format: "type-suit"
void printCard(int id)
{
  cout << type[id%13];
  cout << '-';
  cout << suit[id/13];
}

//Returns the numeric value of the card.
int cardValue(int id)
{
    return value[id%13];
}

//Prints out each card in the hand separated by a space
void printHand(int hand[], int numCards)
{
  for (int i = 0; i < numCards; i++) {
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;
}

//Returns the total score of the provided hand.  
int getBestScore(int hand[], int numCards)
{
  int sum = 0;
  bool containsAce = false;
  for (int i = 0; i < numCards; i++) {
    if (cardValue(hand[i]) == 11) {
      containsAce = true;
    } 
    sum += cardValue(hand[i]);
  }
  //doesn't need to account for aces
  if (sum <= 21) {
    return sum;
  }
  //there's 1 ace
  else if (containsAce) {
    return sum - 10; 
  }
  //if it busts with no ace
  return sum;
}

//Main program 
int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];

  //since playing again is repeating the whole thing
  char playAgain = 'y';
  while (playAgain == 'y') {
    //initialize the deck
    for (int i = 0; i < 52; i++) {
      cards[i] = i;
    }
    shuffle(cards);

    //initializing hands
    phand[0] = cards[0];
    dhand[0] = cards[1];
    phand[1] = cards[2];
    dhand[1] = cards[3];
    int nextdHand = 2;
    int nextpHand = 2;
    int nextCard = 4;

    cout << "Dealer: ? " ;
    printCard(dhand[1]); 
    cout << endl;
    cout << "Player: ";
    printHand(phand, 2);

    //in charge of everything player related
    char response;
    while (true) { 
      //player gets lucky and immediately hits 21, dealer still has to play
      if (getBestScore(phand, nextpHand) == 21) {
        break;
      }

      cout << "Type 'h' to hit and 's' to stay: " << endl;
      cin >> response;

      if (response == 'h') {
        phand[nextpHand++] = cards[nextCard++];
      }
      else {
        break;
      }
      cout << "Player: ";
      printHand(phand, nextpHand);

      if (getBestScore(phand, nextpHand) > 21) {
        cout << "Player busts \nLose ";
        break;
      }
    }

    //dealer's "turn" given player did not bust
    if (getBestScore(phand, nextpHand) <= 21) {
      while (getBestScore(dhand, nextdHand) <= 16) {
        dhand[nextdHand++] = cards[nextCard++];
      }

      cout << "Dealer: ";
      printHand(dhand, nextdHand);

      if (getBestScore(dhand, nextdHand) > 21) {
        cout << "Dealer busts" << endl;
        cout << "Win ";
      }

      //if neither busts, go here
      else if (getBestScore(dhand, nextdHand) > getBestScore(phand, nextpHand)) {
        cout << "Lose ";
      }
      else if (getBestScore(dhand, nextdHand) < getBestScore(phand, nextpHand)) {
        cout << "Win ";
      }
      else {
        cout << "Tie ";
      }
    }
    
    //print the scores
    cout << getBestScore(phand, nextpHand);
    cout << " ";
    cout << getBestScore(dhand, nextdHand);
    cout << "\n\n";

    //the last thing to do
    cout << "Play again? [y/n]" << endl;
    cin >> playAgain;
  }
  return 0;
}
