#include<iostream>
#include<vector>
using namespace std;

class SetOfStacks {
public:
    vector<vector<int> > setOfStacks(vector<vector<int> > ope, int size) {
        vector<vector<int> > v;
        vector<int> tmp;
        //用一个辅助栈来存放数据，当辅助栈满时就将其压入v中
        for(int i=0;i<(int)ope.size();i++){
            if(ope[i][0]==1){
                if((int)tmp.size()==size){
                    v.push_back(tmp);
                    while(!tmp.empty()){
                        tmp.pop_back();
                    }
                }
                tmp.push_back(ope[i][1]);
            }else{
                if(tmp.empty()){
                    if(!v.empty()){
                        tmp=v[v.size()-1];
                        v.pop_back();
                        tmp.pop_back();
                    }
                }else
                    tmp.pop_back();
            }
        }
        v.push_back(tmp);
        return v;
    }

};
