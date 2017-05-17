//filler code

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

void createWord(int randomNumber, string& word, vector<char>& displayWord);
void createDisplayWord(vector<char> Word, vector<char>& displayWord);
void initialScreen(vector<char> displayWord);
bool isValidLetter(vector<char> Word, vector<char> displayWord, char guessedLetter, int& PENALTY, vector<char>& guessedLetters);
void displayGame(vector<char> displayWord, vector<char> guessedLetters, int PENALTY);
void hangman(int PENALTY);
bool winLoseCheck(vector<char> displayWord, int PENALTY, string word);

int main() {
	srand(time(NULL));
	int randomNumber = 0;
	string word;
	char guessedLetter;
	vector<char> guessedLetters;
	vector<char> displayWord;
	int PENALTY = 0;

	//Choose a word randomly from the file and change string into vector of chars to be displayed
	createWord(randomNumber, word, displayWord);
	vector<char> Word(word.begin(), word.end());
	createDisplayWord(Word, displayWord);
	//

	//Displaying initial screen
	initialScreen(displayWord);
	//

	//Infinite loop to play the game
	while (true) {

		//Player guesses a letter
		cout << endl << "What letter would you like to guess?" << endl << "> ";
		cin >> guessedLetter;
		//

		//Checks for validity of letter
		if (isValidLetter(Word, displayWord, guessedLetter, PENALTY, guessedLetters)) {
		//

			//Searches for letter and changes it in the display word
			for (int i = 0; i < displayWord.size(); i++) {
				if (guessedLetter == Word[i]) {
					displayWord[i] = Word[i];
				}
			}
		}
		//

		//Displays the word up to this point
		displayGame(displayWord, guessedLetters, PENALTY);
		//

		//Conditions to end the game
		if (winLoseCheck(displayWord, PENALTY, word)) {
			bool stop; cin >> stop;
			return 0;
		}
		//
	}
	//
}

//Choose a word randomly from the file and change string into vector of chars to be displayed
void createWord(int randomNumber, string& word, vector<char>& displayWord) {
	random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<long long unsigned> distribution(0, 354910);
	ifstream file;
	file.open("words_no_numbers.txt");
	if (!file.is_open()) cout << "Essential word file not found.";
	randomNumber = distribution(generator);
	for (int i = 0; i < randomNumber; i++) {
		file >> word;
	}
}
//

//Change string into vector of chars to be displayed
void createDisplayWord(vector<char> Word, vector<char>& displayWord) {
	for (int i = 0; i < Word.size(); i++) {
		if (Word[i] == 39) {
			displayWord.push_back(39);
		}
		else {
			displayWord.push_back('_');
		}
	}
}
//

//Displaying initial screen
void initialScreen(vector<char> displayWord) {
	cout << "Welcome to hangman...  May the odds be ever in your favor." << endl << endl << endl;
	for (int i = 0; i < displayWord.size(); i++) {
		cout << displayWord[i] << " ";
	}
	cout << endl << "Letters you have guessed:" << endl << endl;
	hangman(0);
	cout << endl;

	cout << endl << "PENALTY: 0" << endl;
}
//

//Logic to determine if that guess is valid, if it has already been guessed, or if it is part of the word
bool isValidLetter(vector<char> Word, vector<char> displayWord, char guessedLetter, int& PENALTY, vector<char>& guessedLetters) {

	//Checks if the guessedLetter is in range
	if ((guessedLetter < 'a') || (guessedLetter > 'z')) {
		system("cls");
		cout << "Not an acceptable letter." << "\n\n\n";
		return false;
	}
	//

	for (int i = 0; i < guessedLetters.size(); i++) {

		//Checks if the guessedLetter has already been guessed
		if (guessedLetter == guessedLetters[i]) {
			system("cls");
			cout << "This letter has already been guessed" << "\n\n\n";
			return false;
		}
	}
	//

	for (int i = 0; i < Word.size(); i++) {
		//Checks if the guessedLetter is in the word
		if (guessedLetter == Word[i]) {
			guessedLetters.push_back(guessedLetter);
			system("cls");
			cout << "You guessed a letter" << "\n\n\n";
			return true;
		}
		//
	}

	//If the guessed letter is not in the word, they recieve a penalty
	guessedLetters.push_back(guessedLetter);
	system("cls");
	cout << "This letter is not in the word" << "\n\n\n";
	PENALTY++;
	return false;
}
//

//Display the hangman
void hangman(int PENALTY)
{
	string head = "|   O\n", body = "|   |\n", rightArmLeg = "|   |_\n", bothArmsLegs = "|  _|_\n", top = "_____\n", emptyRope = "|   |\n", emptyWood = "|\n";
	cout << top << emptyRope;
	if (PENALTY == 0) cout << emptyWood << emptyWood << emptyWood << emptyWood;
	else if (PENALTY == 1) cout << head << emptyWood << emptyWood << emptyWood;
	else if (PENALTY == 2) cout << head << body << emptyWood << emptyWood;
	else if (PENALTY == 3) cout << head << rightArmLeg << emptyWood << emptyWood;
	else if (PENALTY == 4) cout << head << bothArmsLegs << emptyWood << emptyWood;
	else if (PENALTY == 5) cout << head << bothArmsLegs << body << emptyWood;
	else if (PENALTY == 6) cout << head << bothArmsLegs << body << body;
	else if (PENALTY == 7) cout << head << bothArmsLegs << body << rightArmLeg;
	else cout << head << bothArmsLegs << body << bothArmsLegs;
	cout << emptyWood;
}
//

//Displays the hangman, their word so far, their guessed letters, and their PENALTY number
void displayGame(vector<char> displayWord, vector<char> guessedLetters, int PENALTY) {

	//Displays the word
	for (int i = 0; i < displayWord.size(); i++) {
		cout << displayWord[i] << " ";
	}
	//

	//Displays the guessed letters
	cout << endl << "Letters you have guessed: ";
	for (int i = 0; i < guessedLetters.size(); i++) {
		cout << guessedLetters[i] << ", ";
	}
	cout << endl << endl;
	//	

	//Display hangman
	hangman(PENALTY);
	cout << endl;
	//

	cout << endl << "PENALTY: " << PENALTY << endl;
}
//

//Checks if you have won or lost the game. If so, the game is over
bool winLoseCheck(vector<char> displayWord, int PENALTY, string word) {

	//Checks if the player has won the game
	bool hasWon = true;
	for (int i = 0; i < displayWord.size(); i++) {
		if (displayWord[i] == '_')
			hasWon = false;
	}
	if (hasWon == true) {
		cout << "Yay! You won!" << endl;
		return true;
	}
	//

	//Checks if the player has lost the game
	else if (PENALTY > 7) {
		cout << "Boo, you lost. The word was: " << word << endl;
		return true;
	}
	//

	return false;
}
//