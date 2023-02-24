#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n;
	cin >> n;
	int arr[n][n] = {};
	int i = 0, j = n/2;
	for (int k = 1; k <= n*n; k++) {
		arr[i][j] = k;
		i--;
		j++;
		
		if (k%n == 0) {
			i+=2;
			j--;
		}
		
		if (i < 0) {
			i+=n;
		}
		
		if (j==n) {
			j-=n;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j =0; j < n; j++) cout << setfill(' ') << setw(5) << arr[i][j];
		cout << endl;
	}
}