//2018-5-28 数组中的逆序对
#include<iostream>
class Solution {
public:
    int InversePairs(std::vector<int> data) {
        int P=0;
        for(int i =data.size()-1;i>0;i--){
            for(int j=i-1;j>=0;j--){
                if(data[j]>data[i])
                    P++;
            }
        }
        return P%1000000007;
    }
};
