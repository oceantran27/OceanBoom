#include "HangMan.h"

int main()
{
	srand(time(0));
	string secretWord = randWord();
	string guessedWord = string(secretWord.length(), '-');
	char guessedLetter;
	bool mark[128] = {};
	int badGuessCount = 0;

	do {
		cout << FIGURE[badGuessCount];
		cout << guessedWord << endl;
		guessedLetter = playerGuess(mark);
		if (contain(secretWord, guessedLetter))
		{
			update(secretWord, guessedWord, guessedLetter);
		}
		else
		{
			badGuessCount++;
		}
		system("cls");
	} while (badGuessCount < 7 && guessedWord != secretWord);

	if (badGuessCount < 7) cout << "Congratulation! You win!\n";
	else
	{
		cout << FIGURE[badGuessCount];
		cout << "You lost. The right word is: " << secretWord;
	}
}