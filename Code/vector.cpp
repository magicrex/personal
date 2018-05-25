#include<iostream>
#include<vector>
using namespace std;

void printvetor(vector<int> v){
    vector<int>::iterator it=v.begin();
    for(it;it!=v.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}


int main(){
    //第一种：不传参数
    vector<int> vint;
    vector<char> vchar;
    vector<string> vstring;

    //第二种：传一个参数 相当于开辟了一个数组
    vector<int> vint2(5);
    vector<char> vchar2(5);
    vector<string> vstring2(5);

    //第三种：参数一 n个元素，每个元素的初值 开辟数组并进行初始化
    vector<int> vint3(5,0);
    vector<char> vchar3(5,'a');
    vector<string> vstring3(5,"a");

    //第四种：传一段迭代器区间
    vector<int> vint4(vint3.begin(),vint3.end());
    vector<char> vchar4(vchar3.begin(),vchar3.end());
    vector<string> vstring4(vstring3.begin(),vstring3.end());


    //第五种：传一个对象，既拷贝函数
    vector<int> vint5(vint3);
    vector<char> vchar5(vchar3);
    vector<string> vstring5(vstring3);

    //第六种：赋值运算符的重载
    vector<int> vint6;
    vector<char> vchar6;
    vector<string> vstring6;
    vint6=vint5;
    vchar6=vchar5;
    vstring6=vstring5;

    //迭代器定义
    //begin() end() rbegin() rend() 正向和反向迭代器
    std::vector<int>::iterator itint=vint6.begin();
    std::vector<char>::iterator itchar=vchar6.begin();
    std::vector<string>::iterator itstring=vstring.end();
    itint =vint6.end();
    itchar = vchar.end();
    itstring=vstring.end();
    std::vector<int>::reverse_iterator ritint =vint6.rbegin();
    std::vector<char>::reverse_iterator ritchar = vchar.rbegin();
    std::vector<string>::reverse_iterator ritstring=vstring.rbegin();
    ritint = vint6.rend();
    ritchar = vchar6.rend();
    ritstring=vstring.rend();

    //cbegin() cend() crbegin() crend() const正向和反向迭代器
    std::vector<int>::const_iterator citint=vint6.cbegin();
    std::vector<char>::const_iterator citchar=vchar6.cbegin();
    std::vector<string>::const_iterator citstring=vstring6.cbegin();
    citint=vint6.cend();
    citchar=vchar6.cend();
    citstring=vstring.cend();

    std::vector<int>::const_reverse_iterator critint;
    std::vector<char>::const_reverse_iterator critchar;
    std::vector<string>::const_reverse_iterator critstring;
    critint=vint6.crbegin();
    critchar=vchar6.crbegin();
    critstring=vstring6.crbegin();
    critint=vint6.crend();
    critchar=vchar6.crend();
    critstring=vstring6.crend();

    //用来描述大小的一系列函数
    vector<int> test(5,1);
    cout<<test.size()<<endl;//表示顺序表的元素个数
    cout<<test.capacity()<<endl;//表示顺序表的容量
    cout<<test.max_size()<<endl;//表示容器的最大存储，但实际到不了
    test.resize(1);//设置大小，可以开辟出更多的空间，当参数小于时就销毁空间
    test.resize(10,2);//当大于时就开辟并初始化
    cout<<test.size()<<endl;
    test.empty();//用来检查是否为空
    test.reserve(10);//用来设置容器大小但是并不初始化，元素个数也没变，变化不可见
    test.shrink_to_fit();//将容器的大小收缩至于元素个数相同的大小

    //关于元素存取的函数
    //operator[] 既重载[]使其类似于数组元素的操纵，实现随机访问
    cout<<test[1]<<endl;
    cout<<test.at(1)<<endl;//类似于[]的作用，只是是一个函数行形式
    cout<<test.front()<<endl;//显示存在的第一个元素
    cout<<test.back()<<endl;//显示存在的最后一个元素
    int* p = test.data();//取到了一个指向顺序表的一个指针
    *p =10; 
    cout<<test.front()<<endl;//显示存在的第一个元素

    //修改动作函数
    cout<<"==============================="<<endl;
    test.assign(vint6.begin(),vint6.end()-1);
    printvetor(test);
    int arr[]={1,2,3};
    test.assign(arr,arr+3);//assign替换函数可以替换一个对象的区间或者一个同类型的数组
    printvetor(test);
    test.push_back(4);//尾插，并没有头插
    printvetor(test);
    test.pop_back();//尾删
    printvetor(test);
    vector<int>::iterator it = test.begin();
    it++;
    test.insert(it,5);//插入指定位置
    printvetor(test);
    test.erase(it);//删除指定位置
    printvetor(test);
    vector<int> test1(5,200);
    cout<<"===============交换============"<<endl;
    printvetor(test);
    printvetor(test1);
    test.swap(test1);
    printvetor(test);
    printvetor(test1);
    cout<<"===============交换结束========"<<endl;
    printvetor(test);
    test.clear();//清空整个顺序表
    printvetor(test);

    return 0;
}
