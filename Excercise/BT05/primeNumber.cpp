#include <iostream>
#include <cmath>
using namespace std;

bool primeNumber(int n) {
	bool arr[n+1] = {};
	int l1 = sqrt(n);
	for (int i = 2; i <= l1+1; i++) {
		if (!arr[i]) {
			int tmp = n / i;
			for (int j = 2; j <= tmp; j++) arr[i*j] = true;
		}
	}
	for (int i = 2; i < n; i++) 
		if (!arr[i]) cout << i << " ";
	cout << endl;
	return !arr[n];
}

int main() {
	int n;
	cin >> n;
	cout << primeNumber(n);
	
	return 0;
}