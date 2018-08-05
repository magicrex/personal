#include<iostream>
#include<vector>
using namespace std;
void insertsort(vector<int>& array){
    int len=array.size();
    int i=0,j=0;
    for(i=1;i<len;i++){
        int tmp=array[i];
        for(j=i-1;j>=0;j--){
            if(array[j]>tmp){
                array[j+1]=array[j];
            }else{
                break;
            }
        }
        array[j+1]=tmp;

    }
}

int main(){
    vector<int> v;
    v.push_back(3);
    v.push_back(8);
    v.push_back(9);
    v.push_back(5);
    v.push_back(4);
    v.push_back(7);
    v.push_back(1);
    v.push_back(0);
    v.push_back(8);
    v.push_back(3);
    insertsort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
