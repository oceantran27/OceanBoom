#include <iostream>
using namespace std;

int ternarySearch(int ar[], int l, int r, int key) {
	int m1 = l + (r-l)/3;
	int m2 = r - (r-l)/3;
	
	if (m2 < m1) return -1;
	
	if (ar[m1] == key) return m1;
	else if (ar[m2] == key) return m2;
	else if (ar[m1] > key) return ternarySearch(ar,l,m1-1,key);
	else if (ar[m2] < key) return ternarySearch(ar,m2+1,r,key);
	else return ternarySearch(ar,m1+1,m2-1,key);
	//return -1;	
}

int main() {
	
 	int l, r, p, key;
  
    // Get the array
    // Sort the array if not sorted
    int ar[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  
    // Starting index
    l = 0;
  
    // length of array
    r = 9;
  
    // Checking for 5
  
    // Key to be searched in the array
    key = 9;
    
    p = ternarySearch(ar,l,r,key);
    
    cout << p;
	
	return 0;
}