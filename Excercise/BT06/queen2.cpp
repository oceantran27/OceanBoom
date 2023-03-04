#include <iostream>
#include <algorithm>

 const int N = 20;

using namespace std;

int x[N] = {};
bool vert[N] = {};
bool pd[N] = {};
bool sd[N] = {};

void printChess() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (x[i] == j) cout << "x ";
			else cout << "o ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check(int i, int j) {
	if (!(vert[j] || pd[i-j+N] || sd[i+j])) 
		return true;
	return false; 
}

void mark (int i, int j) {
	x[i] = j;
	vert[j] = true;
	pd[i-j+N] = true;
	sd[i+j] = true;
}

void unMark(int i, int j) {
	x[i] = -1;
	vert[j] = false;
	pd[i-j+N] = false;
	sd[i+j] = false;
}

void Try(int i) {
	for (int j = 0; j < N; j++) {
		if (check(i, j)) {
			mark(i,j);
			if (i == N-1) 
				printChess();
			else
				Try(i+1);
			unMark(i,j);
		}
	}
	
}


int main() {
	freopen("output.txt","w",stdout);
	fill_n(x,N,-1);
	Try(0);
	
	return 0;
}
