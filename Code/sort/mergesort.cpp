#include<iostream>
#include<vector>                
using namespace std;

void merge(vector<int>& array,int left,int right){
    if(left>=right)
        return ;
    vector<int> tmp=array;
    int mid=(left+right)/2;
    merge(array,left,mid);
    merge(array,mid+1,right);
    int i=left,j=mid+1,pos=left;
    while(i<=mid&&j<=right){
        if(array[i]<=array[j]){
            tmp[pos]=array[i];
            pos++;
            i++;
        }else{
            tmp[pos]=array[j];
            pos++;
            j++;
        }
    }
    while(i>mid&&j<=right){
        tmp[pos]=array[j];
        pos++;
        j++;
    }
    while(j>right&&i<=mid){
        tmp[pos]=array[i];
        pos++;
        i++;
    }
    array=tmp;
}

void mergesort(vector<int>& array){
    int len=array.size();
    merge(array,0,len-1);
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
    mergesort(v);
    for(int i=0;i<(int)v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
