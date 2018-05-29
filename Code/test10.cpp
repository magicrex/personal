//2018-5-29 二维数组中的查找
//杨氏矩阵
//剑指offer 面试题3
//首先是从后往前推，只能从大到小，逐渐缩小范围
//z只能选取右上或者左下
//先压缩列，再压缩行
#include<iostream>
#include<vector>
class Solution{
public:
    bool Find(int target,std::vector<std::vector<int>> array){
        //从右上角开始
        //从右上开始则结束条件为左下角
        int row=array.size();
        int col=array[0].size();
        int i=0,j=col-1;        
        while(i<=row-1&&j>=0){
            if(array[i][j]==target){
                return true;
            }else if(array[i][j]>target){
                j--;
            }else if(array[i][j]<target){
                i++;
            }
        }
        return false;
    }
};

//首先一个数字与对比数字有大于，等于，小于三种情况

int main(){
    std::vector<std::vector<int>> arr={{1,7,9},{4,8,10},{5,9,11}};
    Solution s;
    std::cout<<s.Find(1,arr);
    return 0;
}
