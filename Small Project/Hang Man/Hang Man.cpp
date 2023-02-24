#include <iostream>

using namespace std;

string randWord();
char playerGuess(bool mark[]);
bool contain(string secretWord, char guessedLetter);
string update(string secretWord, string guessedWord, char guessedLetter);

int main() {
	string secretWord = randWord();
	string guessedWord = string(secretWord.length(), '-');
	char guessedLetter;
	bool mark[128] = {};
	int badGuessCount = 0;
	
	do {
		cout << guessedWord << endl;
		guessedLetter = playerGuess(mark);
		if (contain(secretWord, guessedLetter)) {
			guessedWord = update(secretWord, guessedWord, guessedLetter);
		} else {
			badGuessCount++;
		}
	} while(badGuessCount < 7 && guessedWord != secretWord);
	
	if (badGuessCount < 7) cout << "Congratulation! You win!\n";
	else cout << "You lost. The right word is: " << secretWord;
}

string randWord() {
	return "Duong";
}

char playerGuess(bool mark[]) {
	char letter;
	do {
		cin >> letter;
	} while (mark[letter]);
	mark[letter] = true;
	return letter;
}

bool contain(string secretWord, char guessedLetter) {
	return secretWord.find_first_of(guessedLetter) != string::npos;
}

string update(string secretWord, string guessedWord, char guessedLetter) {
	for (int i = 0; i < secretWord.length(); i++) {
		if (guessedLetter == secretWord[i]) guessedWord[i] = secretWord[i];
	}
	return guessedWord;
}