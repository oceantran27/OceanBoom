#include<iostream>
using namespace std;
int main() {
    int n; cin >> n;
    int arr[n];
    int maxx = 0, minn = 999999, sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        maxx = (arr[i] > maxx) ? arr[i] : maxx;
        minn = (arr[i] < minn) ? arr[i] : minn;
        sum += arr[i];
    }
    double avr = (double) sum / n;
    cout << avr << endl;
    cout << maxx << endl;
    cout << minn << endl;
}
