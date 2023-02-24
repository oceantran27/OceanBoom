#include <iostream>
#include <vector>

using namespace std;

long long combination(long long n) {
	return n*(n-1)/2;
}

long long exclusion(string s) {
	long long l = s.length();
	s += '0';
	vector<long long> v;
	long long tmp1 = 1, tmp2 = l;
	for (long long i = 0; i < l; i++) {
		if (s[i] == s[i+1]) tmp1++;
		else {
			v.push_back(tmp1);
			tmp1 = 1;
		}
	}
	
	long long tmp3 = v.size();
	long long sum = 0;
	for (auto i : v) {
		tmp2 -= i;
		tmp3--;
		sum += tmp2*i - tmp3;
		if (i > 2) sum += combination(i) - 1;
	}
	
	for (long long i = 1; i < l-2; i++) {
		if (s[i-1] == s[i+1] && s[i] != s[i-1]) sum ++;
	}
	
	return sum;
}

int main() {
	string s; cin >> s;
	long long l = s.length();
	long long r = combination(l) - exclusion(s);
	cout << r;
	
	return 0;
}