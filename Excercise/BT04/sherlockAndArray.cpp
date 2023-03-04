#include <iostream>
using namespace std;

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int t, n, tmp;
	cin >> t;
	
	while(t--) {
		cin >> n;
		int arr[n+1] = {};
		int sum[n+1] = {};
		bool check = false;
		cin >> arr[1];
		sum[1] = arr[1];
		
		for (int i = 1; i <= n; i++) {
			cin >> arr[i];
			sum[i] = sum[i-1] + arr[i];
		}
		
		for (int i = 1; i <= n; i++) {
			int tmp1 = sum[n] - sum[i];
			int tmp2 = sum[i-1];
			if (tmp1 == tmp2) {
				check = true;
				break;
			}
		}
		if (check) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
