#include<iostream>
#include<vector>                
using namespace std;
//首先采用的是自底向上的调整算法，首先是找到第一个非叶子节点，直到根结束
//每次选出一个然后直到根
void upsort(vector<int>& array,int len){
    int pos=len/2-1;
    for(int i=pos;i>=0;i--){
        if(((i*2+2)<len)&&array[i*2+2]>array[i*+1]){
            int tmp=array[i*2+1];
            array[i*2+1]=array[i*2+2];
            array[i*2+2]=tmp;
        }
        if(array[i]<array[i*2+1]){
            int tmp=array[i*2+1];
            array[i*2+1]=array[i];
            array[i]=tmp;
        }
    }
}
void heapsort(vector<int>& array){
    int len=array.size();
    for(int i=len-1;i>=0;i--){
        upsort(array,i+1);
        for(int j=0;j<(int)array.size();j++){
            cout<<array[j]<<" ";
        }
        cout<<endl;

        int tmp=array[0];
        array[0]=array[i];
        array[i]=tmp;
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
    heapsort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
