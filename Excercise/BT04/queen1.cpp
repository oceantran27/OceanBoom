#include <iostream>
#include <set>

using namespace std; 

bool check(int n, int x[], int y[]) {
	int tmp;
	
	//vertical
	bool vert[10000] = {};
	for (int i = 0; i < n; i++) {
		if (vert[x[i]]) return false;
		else vert[x[i]] = true;
	}
	
	//horizontal
	bool horz[10000] = {};
	for (int i = 0; i < n; i++) {
		if (horz[y[i]]) return false;
		else horz[y[i]] = true;
	}
	
	//primary diagonal
	set<int> pd;
	for (int i = 0; i < n ; i++) {
		tmp = x[i] - y[i];
		if (pd.find(tmp) != pd.end()) return false;
		else pd.insert(tmp);
	}
	
	//secondary diagonal
	set<int> sd;
	for (int i = 0; i < n ; i++) {
		tmp = x[i] + y[i];
		if (sd.find(tmp) != sd.end())return false;
		else pd.insert(tmp);
	}
	
	return true;
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int n;
	cin >> n;
	
	int x[n], y[n];
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	
	if (check(n,x,y)) cout << "no";
	else cout << "yes";
	
	return 0;
}
