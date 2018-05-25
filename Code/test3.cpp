//2018-5-25 字符串装换成整数
#include<string>
class Solution{
public:
    int strToInt(std::string str){
        std::string::reverse_iterator it=str.rbegin();
        int num=0,i=1,flag=0;
        for(;it!=str.rend();++it){
            if(*it>'0'&&*it<'9'){
                if(flag==0){
                    int n=*it-'0';
                    num=num+(n*i);
                    i=i*10;
                }else{
                    num=0;
                    break;
                }
            }else if(*it=='+'||*it=='-'){
                if(flag==0){
                    if(*it=='-'){
                        num=0-num;
                    }
                    flag=1;
                }else{
                    num=0;
                    break;
                }
            }else if(*it==' '){
                if(num!=0){
                    flag=1;
                }
            }else{
                num=0;
                break;
            }
        }
        return num;
    }
};
