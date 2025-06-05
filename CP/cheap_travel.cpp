// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     int n,ans;
//     int m,a,b;
//     cin>>n>>m>>a>>b;
//     if(n%2==0){
//         // if(a==b){
//         //     ans= (n*b);
//         // }
//         //else 
//         if(a>b){
//             ans= (n/m)+b;
//         }
//        else if(a<b){
//         ans= (n/a);
//        }

//     }
//     else{
//         // ans=0;
//         ans= (b*(n%b))+a;
//     }
//     cout<<ans<<endl;
// }

#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b;
    cin>>a>>b;
    long long count=0;
    long long arr[a];
    long long i=0;
    for(i=0;i<a;i++){
        cin>>arr[i];
        if(arr[i]%b==0){
            count++;
        }
    }
cout<<count<<endl;
}