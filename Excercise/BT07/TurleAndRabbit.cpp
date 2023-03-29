#include <iostream>
#include <ctime>
#include <random>

using namespace std;

char turle[70];
char rabbit[70];

int random_step(char type) {
	int dice_ = rand() % 100 + 1;
	if (type == 'R') {
		if (dice_ <= 50) return 3;
		else if (dice_ > 50 && dice_ <= 80) return 1;
		else return -6;
	}
	else {
		if (dice_ <= 20) return 0;
		else if (dice_ > 20 && dice_ <= 40) return 9;
		else if (dice_ > 40 && dice_ <= 50) return -12;
		else if (dice_ > 50 && dice_ <= 80) return 1;
		else return -2;
	}
}

bool run(char type, int& pos, int step)
{
	bool win = false;
	int new_pos = pos + step;
	if (new_pos < 0) new_pos = 0;
	if (new_pos >= 70) {
		new_pos = 70 - 1;
		win = true;
	}
	if (type == 'R') {
		swap(turle[pos], turle[new_pos]);
		for (int i = 0; i < 70; i++) {
			cout << turle[i] << ' ';
		}
	}
	else {
		swap(rabbit[pos], rabbit[new_pos]);
		for (int i = 0; i < 70; i++) {
			cout << rabbit[i] << ' ';
		}
	}
	cout << endl;
	swap(pos, new_pos);
	return win;
}

int main() 
{
	srand(time(NULL));
	for (int i = 1; i < 70 - 1; i++) {
		turle[i] = '.';
		rabbit[i] = '.';
	}
	turle[0] = 'R';
	rabbit[0] = 'T'; 

	turle[70-1] = '@';
	rabbit[70-1] = '@';

	int pos_T = 0;
	int pos_R = 0;

	bool win = false;
	do {
		win = run('R', pos_R, random_step('R')) || run('T', pos_T, random_step('T'));
		cout << endl;
	} while (!win);
}