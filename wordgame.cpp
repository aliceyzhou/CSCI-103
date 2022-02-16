#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  char word[80];  // a blank array to use to build up the answer

  //initializes the word to all *
  for (int i = 0; i < strlen(targetWord); i++){
    word[i]='*';
  }
  //honestly not sure if this does anything..?
  word[strlen(targetWord)] = '\0';

  // A game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (numTurns > 0) {
    cout<< "Current word: ";
    cout << word << endl;
    cout << numTurns << " guess remaining...Enter a letter to guess:" << endl;
    cin >> guess;

    //letter guessed was not inside, lose a turn
    if (processGuess(word, targetWord, guess) == 0) {
      numTurns--;
    }

    //to determine if they won
    if (strcmp(word, targetWord) == 0){
      wordGuessed = true;
      break;
    }
}

  // Print out end of game status
  if (wordGuessed) {
    cout << "The word was " << targetWord << ". You win!" << endl;
  }
  else {
    cout <<"Too many turns...You lose!" << endl;
  }
  
  return 0;
}

// Given the current version of the word, target/selected word, and user guess
// change the word to "turn on" any occurrences the guess character
// Returns a count of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
  int count = 0;
  //standard loop
  /*
  for (int i = 0; i < strlen(word); i++) {
    if (guess == targetWord[i]) {
      count++;
      word[i] = guess;
    }
  }
  */

  //pointer version
  const char* p = targetWord;
  char* q = word;

  while (*p != '\0') {
    if (*p == guess) {
        *q = guess;
        count++;
    }
    p++;
    q++;
  }
  return count;

}