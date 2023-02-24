#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
		}
	}
}

void printArr(int arr[], int n) {
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';
} 

int main() {
	int n = 10;
	int arr[10] = {9, 6, 4, 5, 7, 2, 3, 1, 0 ,8};
	bubbleSort(arr,n);
	printArr(arr,n);
	
	return 0;
}
