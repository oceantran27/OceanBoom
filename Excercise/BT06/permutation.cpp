#include <iostream>
using namespace std;

int n, k;
int arr[100];
bool mark[200] = {};

void print() {
	char tmp = 'a';
	for (int  i = 0; i < k; i++) {
		char tmp1 = tmp + arr[i];
		cout << tmp1;
	}
	cout << " ";
}

void dq(int l) {
	if (l >= k) print();
	else {
		for (int i = 0; i < n; i++) {
			if (mark[i]) continue;
			else {
				arr[l] = i;
				mark[i] = true;
				dq(l+1);
				mark[i] = false;
			}
		}
	}
}

int main() {
	//n >= k
	cin >> n >> k;
	dq(0);
	
	return 0;
}