#include <iostream>

using namespace std;

int main() {
	int m, n, j;
	cin >> m >> n;
	char map[m+1][n+1];
	
	for (int i = 1; i <= m; i++) {
		char tmp;
		j = 1;
		while (j <= n) {
			cin >> tmp;
			if (tmp == ' ') continue;
			map[i][j] = tmp;
			j++;
		}
	}
	
	int arr[m+1][n+1] = {};
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == '*') {
				arr[i][j] = -1;
				continue;
			}
			if (map[i-1][j] == '*') arr[i][j]++;
			if (map[i-1][j-1] == '*') arr[i][j]++; 
			if (map[i-1][j+1] == '*') arr[i][j]++;
			
			if (map[i][j] == '*') arr[i][j]++;
			if (map[i][j-1] == '*') arr[i][j]++; 
			if (map[i][j+1] == '*') arr[i][j]++;
			
			if (map[i+1][j] == '*') arr[i][j]++;
			if (map[i+1][j-1] == '*') arr[i][j]++; 
			if (map[i+1][j+1] == '*') arr[i][j]++;
			
		}
	}
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if(arr[i][j] == -1) cout << "* ";
			else cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}