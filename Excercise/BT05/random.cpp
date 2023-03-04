#include <iostream>
#include <random>
#include <ctime>
using namespace std;

int rand(int n) {
	return rand() % n;
}

int main() {
	int n;
	cin >> n;
	srand(time(NULL));
	cout << rand(n);
	
	return 0;
}