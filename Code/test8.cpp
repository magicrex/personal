//2018-5-28 数组中的逆序对
//首先要将排序和拷贝放在一起
//而且不能显示赋值既array=tmp这会导致时间超时
//所以采用了一个小技巧传参时将tmp和array调整，这样每次传参会使得两个数组轮流做被拷贝和拷贝
#include<iostream>
#include<vector>
class Solution {
public:
    long long num(std::vector<int> &array,std::vector<int>& tmp ,int left,int right){
        if(left==right){
            return 0;
        }
        int mid=(left+right)/2;
        long long left_num=num(tmp,array,left,mid);
        long long right_num=num(tmp,array,mid+1,right);
        long long num=0;
        int i=mid,j=right,m=right;
        //首先从后面向前比较
        //如果大于最后一个说明比前面都大
        while(i>=left&&j>=mid+1){    
            if(array[i]>array[j]){
                num+=(j-mid);
                tmp[m]=array[i];
                i--;
                m--;
            }else{
                tmp[m]=array[j];
                m--;
                j--;
            }
        }
        while(i>=left){
            tmp[m]=array[i];
            i--;
            m--;
        }
        while(j>=mid+1){
            tmp[m]=array[j];
            m--;
            j--;
        }
        //将数组排序并赋值给array
        return num+left_num+right_num;
    }
    int InversePairs(std::vector<int> data) {
        std::vector<int> tmp(data);
        long long ret=num(data,tmp,0,data.size()-1);
        return ret%1000000007;

    }
};


int main(){
    Solution* S=new Solution();
    std::vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(0);
    int ret=S->InversePairs(arr);
        std::cout<<ret;
    return 0;
}
