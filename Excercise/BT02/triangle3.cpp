#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int x; cin >> x;
	for (int i = x-1; i >= 0; i--) {
		for (int j = -x; j <= x; j++){
			if (abs(j) - i <= 0) cout << '*';
			else cout << ' ';
		}
		cout << endl;
	}
	
	return 0;
}