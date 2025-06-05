#include<iostream>
using namespace std;
int main(){
    int a;
    cin>>a;
   int flag =0;
        int arr[a];

    for (int i = 0; i < a; i++)
    {
        cin>>arr[i];

    }
    for (int i = 0; i < a; i++)
    {
        if(arr[i]!=0){
            flag=1;
            break;

        }
       
        
    }
    if(flag){
        cout<<"HARD";
    }
else
{
    cout<<"EASY";
}
    
}