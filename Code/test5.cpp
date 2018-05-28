//2018-5-27 数组中出现次数超过一半的数字
#include<unordered_map>
#include<vector>
class Solution{
public:
    int MoreThanHalfNum_Solution(std::vector<int> numbers){
        int num=0;
        std::unordered_map<int,int> map;
        std::unordered_map<int,int>::iterator it=map.begin();
        for(int i= 0;i<(int)numbers.size();i++){
            it=map.find(numbers[i]);
            if(it!=map.end()){
                (*it).second++;
                if((*it).second>=(int)numbers.size()){
                    num=(*it).first;
                    break;
                }
            }else{
                map.insert(numbers[i],1);
            }
        }
        return num;
    };
};

int main(){
    int  arr[9]={1,2,3,2,2,2,5,4,2};
    std::vector<int> m(arr,arr+9);
    Solution* s=new Solution();
    s->MoreThanHalfNum_Solution(m);
    return 0;
}
