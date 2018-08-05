#include<iostream>
#include<vector>
using namespace std;
void shellsort(vector<int>& array){
    int len=array.size();
    int dis=len/2;
    int i,j,tmp;
    while(dis>=1){
        for(i=dis;i<len;i++){
            tmp=array[i];
            j=i-dis;
            while(j>=0&&array[j]>tmp){
                array[j+dis]=array[j];
                j=j-dis;
            }
            array[j+dis]=tmp;
        }
        dis=dis/2;
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
    shellsort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
