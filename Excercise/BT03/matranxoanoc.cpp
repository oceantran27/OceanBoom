#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	
	int x, y;
	cin >> x >> y;
	int a[x][y] = {};
	int count = 1;
	int left = 0, right = y-1, top = 0, bot = x-1;
	while (count <= x*y) {
		for (int i = left; i <= right; i++) {
			a[top][i] = count;
			count++;
		}
		top++;
		for (int i = top; i <= bot; i++) {
			a[i][right] = count;
			count++;
		}
		for (int i = right - 1; i >= left; i--) {
			a[bot][i] = count;
			count++;
		}
		for (int i = bot - 1; i >= top; i--) {
			a[i][left] = count;
			count++;
		}
		left++;
		right--;
		bot--;
	}
	for (int i = 0; i < x; i++) {
		for (int j =0; j < y; j++) cout << setfill(' ') << setw(5) << a[i][j];
		cout << endl;
	}
}
