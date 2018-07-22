#include<iostream>
#include<sstream>
using namespace std;
#include<time.h>
class CookieUtil{
public:
    static std::string GetCookie(const char* username){
        //整个Cookie由用户名和时间组成
        std::string names(username);
        std::string timestring;
        time_t t=time(NULL);
        std::stringstream ss;
        ss << t;
        ss >> timestring;
        return names+timestring;
    }
};//end CookieUtil
int main(){
    cout<<CookieUtil::GetCookie("root_name")<<endl;
    return 0;
}
