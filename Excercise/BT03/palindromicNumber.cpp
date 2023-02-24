#include <iostream>

using namespace std;

bool check(int num);

int main() {
	int t, a, b, res;
	cin >> t;
	while (t--) {
		res = 0;
		cin >> a >> b;
		for (int i = a; i <= b; i++) {
			if (check(i)) res++;
		}
		cout << res << endl;
	}
}

bool check(int num) {
	int tmp = num;
	int _num = 0;
	while (tmp != 0) {
		_num = _num*10 + (tmp % 10);
		tmp /= 10;
	}
	return _num == num;
}