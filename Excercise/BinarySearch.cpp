#include <iostream>

using namespace std;

void binarySearch(int arr[], int low, int high, int k);

int main() {
	
	int n, k;
	cin >> n;
	int arr[n];
	for (int i = 0; i < n; i++) cin >> arr[i];	
	cin >> k;
	binarySearch(arr, 0, n-1, k);
	
	return 0;
}

void binarySearch(int arr[], int low, int high, int k) {
	int mid = (low + high) / 2;
	if (low > high) cout << "khong tim thay";
	else if (arr[mid] > k) binarySearch(arr, low, mid-1, k);
	else if (arr[mid] < k) binarySearch(arr, mid+1, high, k);
	else cout << mid;
}