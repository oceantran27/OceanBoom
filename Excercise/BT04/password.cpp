#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	set<string> s;
	bool check  = true;
	while (n--) {
		string str, r_str;
		cin >> str;
		r_str = string(str.rbegin(),str.rend());
		auto ind = s.find(r_str);
		if (ind == s.end()) {
			s.insert(str);
		} else {
			string tmp = *ind;
			int len = tmp.length();
			cout << len << endl;
			cout << tmp[len/2];	
			break;
		}
	}
	return 0;
}