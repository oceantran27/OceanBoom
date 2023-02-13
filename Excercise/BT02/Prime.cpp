#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int x; cin >> x;
	int l = sqrt(x);
	bool check = true;
	for (int i = 2; i <= l; i++) {
		if (x % i == 0) check = false;
	}
	if (check) cout << "yes";
	else cout << "no";
	
	return 0;
}