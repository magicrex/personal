#include<iostream>
#include<vector>
using namespace std;
//认为前n个元素已经有序
//从前扫描将元素放到合适的位置
void selectsort(vector<int>& array){
    int len=array.size();
    int i=0,j=0;
    for(i=0;i<len;i++){
        int pos=i;
        for(j=i+1;j<len;j++){
            if(array[j]<array[pos])
                pos=j;
        }
        int tmp=array[i];
        array[i]=array[pos];
        array[pos]=tmp;
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
    selectsort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
