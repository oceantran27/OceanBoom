#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n = 5; 
	//cin >> n;
	int arr[] = {1, -2, 1, 0, 5};
	//for (int i = 0; i < n; i++) cin >> arr[i];
	sort(arr, arr+n);
	for (int i = 0; i < n; i++) {
		int l = i+1;
		int r = n-1;
		while (l < r) {
			if (arr[l] + arr[r] + arr[i] == 0) {
				cout << arr[i] << " " << arr[l] << " " << arr[r] << endl;
				l++;
				r--;
			} else if (arr[l] + arr[r] + arr[i] < 0) {
				l++;
			} else {
				r--;
			}
		}
	}	
	return 0;
}
