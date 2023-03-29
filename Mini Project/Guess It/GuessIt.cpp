#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int generateNumber();
int getPlayerGuess();
void gameProcess(int guess, int secretNumber);


int main(int argc, char* argv[]) {
	
	int guess;
	int secretNumber = generateNumber();
	
	do {
		
		guess = getPlayerGuess();
		gameProcess(guess, secretNumber);
		
	} while(guess != secretNumber);
	
	cout << "Done!";
	
	return 0;
}

int generateNumber() {
	srand(time(0));
	int secretNumber = rand() % 100 + 1;
	return secretNumber;
}

int getPlayerGuess() {
	cout << "Let's choose a number (1..100): ";
	int guess; cin >> guess;
	return guess;
}

void gameProcess(int guess, int secretNumber) {
	if (guess < secretNumber) cout << "Your number is too small !\n";
	else if (guess > secretNumber) cout << "Your number is too big !\n";
	else cout << "Congratulation, you've won !\n";
}