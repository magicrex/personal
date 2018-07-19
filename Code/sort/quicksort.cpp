#include<iostream>
#include<vector>
using namespace std;

void quick(vector<int>& array,int left,int right){
    if(left>=right)
        return ;
    int i=left,j=right;
    int tmp=array[left];
    while(i<j){
        while(j>i&&array[j]>=tmp)
            j--;
        array[i]=array[j];
        array[j]=tmp;
        while(i<j&&array[i]<tmp)
            i++;
        array[j]=array[i];
        array[i]=tmp;
    }
    quick(array,left,j);
    quick(array,j+1,right);
}

void quicksort(vector<int>& array){
    int len=array.size();
    quick(array,0,len-1);
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
    quicksort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
