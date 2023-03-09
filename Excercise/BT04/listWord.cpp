#include <iostream>
using namespace std;

int d[100000];
string s;
int len;

void print(int n) {
	for (int i = 0; i < n; i++) {
		cout << s[d[i]];
	}
	cout << " ";
}

void dq(int k) {
	if (k >= 3) {
		print(k);
	} else {
		if (k == 2) print(k);
		for (int i = 0; i < len; i++) {
			d[k] = i;
			dq(k+1);
		}
	}
}

int main() {
	cin >> s;
	len = s.length();
	dq(0);
	return 0;
}