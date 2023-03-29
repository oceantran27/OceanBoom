#include <iostream>

using namespace std;

struct String
{
	int n;
	char* str;

	String();
	String (const char* _str) 
	{ 
		n = sizeof(_str) / sizeof(_str[0]);
		str = new char[n];
		for (int i = 0; i <= n; i++)
		{
			str[i] = _str[i];
		}
		delete [] _str;
	}
	~String() { delete str; }

	void append(const char* _str) 
	{
		int n1 = sizeof(_str) / sizeof(_str[0]);
		int n2 = n + n1 + 3;
		char* temp = new char[n2];

		for (int i = 0; i <= n; i++)
		{
			temp[i] = str[i];
		}		

		for (int i = 0; i <= n1; i++)
		{
			temp[n + i + 1] = _str[i];
		}

		n = n2;
		str = new char[n2];
		for (int i = 0; i <= n2; i++)
		{
			str[i] = temp[i];
		}
		delete [] _str;
		delete [] temp;
	}

	void print() 
	{
		for(int i = 0; i < n; i++)
		{
			cout << str[i];
		}
	}
};

int main() 
{
	String s("Hello");
	s.append(" there");
	s.print();
}