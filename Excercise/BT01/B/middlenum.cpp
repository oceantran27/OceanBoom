#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int arr[5];
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    double _arr[5];
    double avr = sum / 5;
    for (int i = 0; i < 5; i++) {
        _arr[i] = avr - arr[i];
        if (_arr[i] < _arr[ind]) ind = i;
    }
    cout << arr[ind];
}
