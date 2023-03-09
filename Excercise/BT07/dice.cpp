#include <iostream>
#include <ctime>
#include <random>
using namespace std;

int opt1(int *p1, int *p2, int count)
{
	if (*p1 == 100) return 1;
	else if (*p2 == 100) return 2; 
	else if (*p1 > 100 && *p2 > 100) return 0;
		
	int tmp = rand() % 6 + 1;
	
	if (count % 2 == 0){
		*p1	+= tmp;
		cout << "xuc xac nguoi choi 1:" << tmp << "     Tong nguoi 1:" << *p1 << endl;
	}
	else{
		*p2 += tmp;
		cout << "xuc xac nguoi choi 2:" << tmp << "     Tong nguoi 2:" << *p2 << endl;
	}
	
	return opt1(p1, p2, count+1);
}

int main() {
	int p1 = 0, p2 = 0;
	srand(time(NULL));
	int check = opt1(&p1, &p2, 0);
	if (check == 0) cout << "tie";
	else if (check == 1) cout << "p1 win";
	else cout << "p2 win";
	
return 0;
}