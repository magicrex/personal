#include<iostream>
#include<vector>
using namespace std;
//比较相邻元素。升序如果第一个比第二大就交换他们
//先找到最大的，接下来是次大的
//每次比较的元素总数会依次减少
void bubblesort(vector<int>& array){
    int len=array.size();
    for(int i=0;i<len;i++){
        for(int j=0;j<len-i-1;j++){
            if(array[j]>array[j+1]){
                int tmp=array[j];
                array[j]=array[j+1];
                array[j+1]=tmp;
            }
        }
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
    bubblesort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
