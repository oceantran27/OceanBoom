#include <iostream>
using namespace std;
void rectangularGame(int n)
{
    unsigned long long int a,b, minA, minB;
    for(int i=0; i<n; i++)
    {
        cin>>a>>b;
        if(i==0)
        {
            minA=a;
            minB=b;
        }
        if(a<minA)
        {
            minA=a;
        }
        if(b<minB)
        {
            minB=b;
        }
    }
    cout<<minA*minB;
}
int main()
{
    int n;
    cin>>n;
    rectangularGame(n);
    return 0;
}