#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void print(vector<int> v) {
	for (int i = 1; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
}

void dq(vector<int> v, int n) {
	if (n == 0) print(v);
	else {
		for (int i = min(n,v.back()); i >= 1; i--) {
			v.push_back(i);
			dq(v,n-i);
			v.pop_back();
		}
	}
}

int main () {
	int n;
	cin >> n;
	vector<int> v = {99999999};
	dq(v,n);
	
	return 0;
}