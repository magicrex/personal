//如果全为负，那么max_sum的最值为0x80000000为负的2的32次方



#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        int x; scanf("%d",&x);
        v[i]=x;
    }
    cout<<endl;
    int max_sum=0;
    int sum=0;
    for(int i=0;i<n;i++){
        if(sum<=0){
            sum=v[i];
        }else{
            sum+=v[i];
        }
        if(sum>max_sum){
            max_sum=sum;
        }
    }
    cout<<max_sum<<endl;
    return 0;
}
