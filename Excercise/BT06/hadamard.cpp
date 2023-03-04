#include <iostream>
#include <cmath>
using namespace std;

const int n = 16;
int arr[n][n];

void print() {
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (arr[i][j] == 1) cout << '.' << ' ';
			else cout << 'o' << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
void dq(int l, int r, int t, int b) {
	if (r-l <= 1) return;
	else {
		int tmp1 = (t+b)/2;
		int tmp2 = (l+r)/2;
		for (int i = t; i < b; i++){
			for (int j = l; j < r; j++){
				if (i >= tmp1 && j >= tmp2) arr[i][j] = arr[t][l] *(-1);
				else arr[i][j] = arr[t][l];			
			}
		}
		dq(l,tmp2,t,tmp1);
		dq(tmp2,r,t,tmp1);
		dq(l,tmp2,tmp1,b);
		dq(tmp2,r,tmp1,b);
	}
}

int main() {
	arr[0][0] = 1;
	dq(0,n,0,n);
	print();
	
	return 0;
}