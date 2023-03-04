#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 101;

void input(int arr[], int n) {
    int tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arr[tmp]++;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n;
    cin >> n;
    int arr1[MAX] = {};
    int arr2[MAX] = {};
    
    input(arr1,n);
    input(arr2,n+1);
    
    
    for (int i = 0; i < MAX; i++) {
        if (arr1[i] != arr2[i]) cout << i << endl;
    }
        
    return 0;
}