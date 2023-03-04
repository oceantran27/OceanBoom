#include <iostream>
using namespace std;

int n, k;
int arr[100];

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
				arr[l] = i;
				dq(l+1);
		}
	}
}

int main() {
	//n >= k
	cin >> n >> k;
	dq(0);
	
	return 0;
}