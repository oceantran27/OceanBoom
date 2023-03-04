#include <iostream>
using namespace std;

int GCD(int a, int b)
{
	if (b == 0) return a;
	if (a%b==0) return b;
	return (b, a%b);
}

int main() {
	int a,b;
	cin >> a >> b;
	if (a < b) swap(a,b);
	int tmp = GCD(a,b);
	cout << tmp << endl;
	if (tmp == 1) cout << "YES";
	else cout << "NO";
	 
	return 0;
}