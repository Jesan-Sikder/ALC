#include <bits/stdc++.h>
using namespace std;

int main() {
    // string a;
    // cin >> a;

    // int b = a.length();
    char a[100];
   
    //cout << "Length of the string: " << b << endl;
    int t;
    cin>>t;
    while(t--){
        cin>>a;
        string z = a;
        int b = strlen(a);

if(b>10){
    cout<<a[0]<<b-2<<a[b-1]<<endl;
}
else{
    cout<<z<<endl;
}
    }
    return 0;
}
