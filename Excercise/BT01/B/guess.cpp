#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
        int seed, num1 , num2;
        srand(time(NULL));
        cin >> num1;
        num2 = rand() % 100 + 1;
        cout << "num2: " << num2 << endl;
        if (num1 > 50) cout << num1;
        else cout << num2;
}
