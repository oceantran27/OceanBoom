#include <iostream>
using namespace std;

int main() {
	int a, b = -999999;
	do {
		cin >> a;
		if (a == b) continue;
		else {
			cout << a << " ";
			b = a;
		}
	} while (a >= 0);
	
	return 0;
}