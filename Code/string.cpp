#include<string>
#include<iostream>
using namespace std;
int main(){
    cout<<"======定义======"<<endl;
    //string的定义
    std::string s0("Hello Wrold!");
    cout<<s0<<endl;
    std::string s1;//实例化一个空的string对象
    cout<<s1<<endl;
    std::string s2(s0);//通告拷贝构造得到一个对象
    cout<<s2<<endl;
    std::string s3(s0,6,5);//在拷贝一个对象时，还可以指定其位置和长度
    cout<<s3<<endl;
    std::string s4("hello wrold");//传一个字符数组作为参数
    cout<<s4<<endl;
    std::string s5("hello wrold",10);//传一个字符数组并指定大小
    cout<<s5<<endl;
    std::string s6(10,'x');//指定大小并传一个指定一个字符作为初始化内容
    cout<<s6<<endl;
    std::string s7(10,42);//传一个数字，作为ASCII码，进行初始化
    cout<<s7<<endl;
    std::string s8(s0.begin(),s0.begin()+5);//传一个迭代器区间作为参数
    cout<<s8<<endl;
    cout<<"======结束======"<<endl;
    
    cout<<"=====赋值运算符====="<<endl;
    //赋值运算符的重载
    s0=s3;//将一个对象赋值给另一个对象
    cout<<s0<<endl;
    s0="hello";//将一个字符串或者字符数组赋值给一个对象
    cout<<s0<<endl;
    s0='x';//将一个字符传给一个string对象
    cout<<s0<<endl;
    s0=s6+s7;//将两个对象使用+合并并赋值给第三个对象
    cout<<s0<<endl;
    cout<<"=======结束======="<<endl;

    cout<<"======迭代器定义======"<<endl;
    //迭代器定义
    //begin() end() rbegin() rend() 正向和反向的迭代器
    std::string::iterator it=s0.begin();
    cout<<*it<<endl;
    it=s0.end();
    std::string::reverse_iterator rit=s0.rbegin();
    cout<<*rit<<endl;
    rit=s0.rend();
    //cbegin() cend() crbegin() crend() const正向和反向迭代器
    std::string::const_iterator cit=s0.cbegin();
    cout<<*cit<<endl;
    cit=s0.cend();
    std::string::const_reverse_iterator crit=s0.crbegin();
    cout<<*crit<<endl;
    crit=s0.crend();
    cout<<"=========结束========="<<endl;

    s0="hello wrold!\0";
    cout<<"========容量函数=========="<<endl;
    cout<<s0.size()<<endl;//用来描述整个string的元素个数
    cout<<s0.length()<<endl;//用来描述整个char数组的长度
    cout<<s0.max_size()<<endl;//表示一个string的最大长度
    cout<<s0.capacity()<<endl;//表示当前string开辟的容量，不一定与size相等
    cout<<s0<<endl;
    s0.resize(3);//重置元素个数，可以比原来小，也可以比原来大
    cout<<s0<<endl;
    s0.reserve(9);//重置string的容量但是不会对新开辟的空间进行初始化
    cout<<s0.capacity()<<endl;
    s0.clear();//清理整个string
    cout<<s0<<endl;
    s0.empty();//检查string对象是否为空
    cout<<s0.empty()<<endl;
    s0.shrink_to_fit();//如果string开辟的容量大于当前元素个数，就将没有用到的空间销毁
    cout<<s0.size()<<endl;
    cout<<"==========结束============"<<endl;

    cout<<"==========元素查找============"<<endl;
    //重载[]使得操作更加方便:w
    
    cout<<"============结束=============="<<endl;


    return 0;
}
