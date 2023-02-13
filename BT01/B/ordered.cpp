#include <iostream>
using namespace std;
int main() {
    int x,y,z; cin >> x >> y >> z;
    bool b = false;
    if ((x-y)*(y-z) > 0) b = true;
    cout << b;

    return 0;
}
