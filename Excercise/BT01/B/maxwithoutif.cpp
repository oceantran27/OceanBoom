#include <iostream>
using namespace std;
int main() {
    int a,b; cin >> a >> b;
    int s = (a > b) * a + (a < b) * b;
    cout << s;
    return 0;
}
