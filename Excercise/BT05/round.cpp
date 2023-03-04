#include <iostream>
#include <cmath>

int rnd(double n) {
	int tmp = n;
	double tmp1 = (double) tmp + 0.5;
	if (n >= tmp1) return ceil(n);
	return floor(n);
}

using namespace std;
int main() {
	double n;
	cin >> n;
	cout << rnd(n);
	return 0;
}