#include <bits/stdc++.h>
using namespace std;
#define ass return 0
#define ll unsigned long long
#define dd double
int main(){
ll t;
cin>>t;
for (ll i = 1; i <=t; i++)
{
char a[100];
scanf("%s",a);
//cout<<a<<endl;
int len=0;
int palindrome =  1;
 while (a[len] != '\0') {
        len++;
    }
//printf("%d\n",len);
//int n= len/2;
//cout<<n<<endl;
for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (a[i] != a[j]) {
            palindrome = 0;
            break;
        }
}

  if (palindrome) {
        cout<<"Case "<<i<<":" << " Yes" << endl;
    } else {
        cout<<"Case "<<i<<":" << " No" << endl;
    }
}
}