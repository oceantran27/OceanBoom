#include <iostream>
#include <cmath>
using namespace std;

string decToBin(int n) {
	string s;
	while (n > 0) {
		int r = n % 2;
		char tmp = r + '0';
		s = tmp + s;
		n /= 2;
	}
	return s;
}

int binToDec(string s) {
	int n = 0;
	int len = s.length();
	for (int i = 0; i < len; i++) {
		int tmp = s[i] - '0';
		n += pow(2,len - i - 1)*tmp;
	}
	return n;
}

int main() {
	int n;
	cin >> n;
	string tmp = decToBin(n);
	int num = binToDec(tmp);
	cout << tmp << endl;
	cout << num;
	
	return 0;
}