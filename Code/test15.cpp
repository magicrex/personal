#include <iostream>
#include <cstdio>
#include<stack>
using namespace std;

int main(){
    int n;
    char ch;
    int m;
    stack<int> s;
    while(1){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin>>ch;
            switch(ch){
            case 'P':
                cin>>m;
                s.push(m);
                break;
            case 'A':
                if(s.empty())
                    cout<<'E'<<endl;
                else
                    cout<<s.top()<<endl;
                break;
            case 'O':
                if(!s.empty())
                    s.pop();
                break;
            default:
                break;
            }       
        }
        cout << endl;
        while(!s.empty()){
            s.pop();
        }
    }
    return 0;
}
