// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     unsigned long long a;
//     cin>>a;
//     if(a==0 || a<0) cout<<"Panta Pasha"<<endl;
//     else if(a<200) cout<<"Fuchka Feroze"<<endl;
//     else cout<<"Biryani Burhan"<<endl;
// }
#include<bits/stdc++.h>
using namespace std;
int main(){
    unsigned long long w,m;
    cin>>w>>m;
    if(w<101){
        if(m>499){
            cout<<"Biriyani"<<endl;
        }
        else{
            cout<<"Khichuri"<<endl;
        }

    }
    else{
        if(m>499){
            cout<<"Fruits"<<endl;
        }
        else{
            cout<<"Salad"<<endl;
        }
    }

}