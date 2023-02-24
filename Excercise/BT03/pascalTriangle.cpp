#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int arr[n+2] = {};
	arr[1] = 1;
	cout << arr[1] << endl;
	int i = 1;
	while (i <= n) {
		for (int j = 1; j <= i+1; j++) {
			arr[i] += arr[i-1];
			cout << arr[i] << " ";
		}
		cout << endl;
		i++;
	}
	return 0;
}