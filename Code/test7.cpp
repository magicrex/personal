//2018-5-27 倒置字符串

#include<iostream>
int main(){
    std::string str;
    getline(std::cin,str);
    int len=str.size()-1;
    int i=0,j=0;
    j=len/2;
    char c='\0';
    for(i=0;i<=j;i++){
        c=str[i];
        str[i]=str[len];
        str[len]=c;
        len--;
    }
    i=0;
    len=str.size()-1;
    while(i<len){
        j=i;
        while(str[i]!=' '){
            i++;
        }
        int m=i-1;
        for(;j<m;j++){
            c=str[j];
            str[j]=str[m];
            str[m]=c;
            m--;
        }
        i=i+1;
    }
    std::cout<<str<<std::endl;
    return 0;
}
