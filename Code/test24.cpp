#include<iostream>
using namespace std;
#include<vector>

bool find_m(vector<vector<int> > arr,int x,int y,int P,vector<vector<int> > &path){
    if(P==0||x<0||y<0||x==(int)arr.size()||y==(int)arr[0].size() )
        return false;
    if(x==0&&y==(int)arr[0].size()-1){
        path[:wq
        ]
        return P;
    }

    if(find_m(arr,x-1,y,P-3 ,path)){

    }
    if(find_m(arr,x+1,y,P ,path)){

    }
    if(find_m(arr,x,y+1,P-1 ,path)){

    }
    if(find_m(arr,x,y+1,P-1 ,path)){

    }
}

int main(){
    int n,m,P;
    cin>>n>>m>>P;
    vector<vector<int> > arr;
    for(int i = 0; i < n; i++){
        vector<int> tmp;
        for(int j = 0; j < n; j++){
            int x;
            cin>>x;
            tmp.push_back(x);
        }
        arr.push_back(tmp);
    }

    vector<vector<int> > path;
    find_m(arr,0,0,P,path);
    return 0;
}
