#include <mysql++.h>
#include<vector>
#include<iostream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
using namespace mysqlpp;
const char* user_insert = "insert into message value(\"%s\", \"%s\");";
const char* user_selectname = "select * from message where username=\"%s\";";
const char* user_selectpass = "select password  from message where username=\"%s\";";
const char* user_update = "update message set password = \"%s\" where username = \"%s\";";
const char* resume_create="create table %s(title varchar(30) primary key,url varchar(100) not null,message varchar(100), data TimeStamp) charset=utf8 collate utf8_bin;";
const char* resume_insert="insert into %s(title,url,message) values(\"%s\",\"%s\",\"%s\");";
const char* resume_delete = "delete from %s where title = \"%s\";";
const char* resume_select = "select * from %s;";
const char* resume_selectfile = "select * from %s where title=%s;";
const char* resume_update = "update %s set message=\"%s\" where title=\"%s\";";
const char* note_create="create table %s(title varchar(30) primary key,url varchar(100) not null,message varchar(100),class varchar(10) not null, data TimeStamp) charset=utf8 collate utf8_bin;";
const char* note_insert="insert into %s(title,url,message,class) values(\"%s\",\"%s\",\"%s\",\"%s\");";
const char* note_delete = "delete from %s where title = \"%s\";";
const char* note_select = "select * from %s order by class;";
const char* project_create="create table %s(title varchar(50) primary key,message text,env varchar(50),func text,flow text,url text) charset=utf8 collate=utf8_bin;";
const char* project_insert="insert into %s value(\"%s\",\"%s\",\"%s\",'无','无','无');";
const char* project_delete = "delete from %s where title = \"%s\";";
const char* project_select = "select * from %s;";
const char* project_update4 = "update %s set func=\"%s\" where title=\"%s\";";
const char* project_update5 = "update %s set flow=\"%s\" where title=\"%s\";";
const char* project_update6 = "update %s set url=\"%s\" where title=\"%s\";";
const char* set_create="create table %s(title varchar(50) ,class varchar(50)) charset=utf8 collate=utf8_bin;";
const char* set_insertx="insert into %s value(\"%s\",\"%s\");";
const char* set_delete = "drop table %s;";
const char* set_select = "select * from %s;";
const char* cookie_insert = "insert into cookie(name,sessid) value(\"%s\", \"%s\");";
const char* cookie_select = "select * from cookie where sessid=\"%s\";";
const char* cookie_update = "update cookie set flag = 0  where name = \"%s\";";


#define DATEBASE_NAME1 "user"
#define DATEBASE_NAME2 "resume"
#define DATEBASE_NAME3 "note"
#define DATEBASE_NAME4 "project"
#define DATEBASE_NAME5 "set"
#define DATEBASE_NAME6 "cookie"
#define DATEBASE_IP "127.0.0.1"
#define DATEBASE_USERNAME "root"
#define DATEBASE_PWD "fuxingde"

#define DATA_BUF_SIZE 1024
#define DATA_BUF_SIZE_MAX 4096
//创建表
bool resumecreate(const char* tablename)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_create,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool notecreate(const char* tablename)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME3, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,note_create,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectcreate(const char* tablename)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,project_create,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool setcreate(const char* tablename)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME5, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,set_create,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//增用户
bool userinsert(const char* value1,const char* value2)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME1, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,user_insert,value1,value2);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool resumeinsert(const char* value1,const char* value2,const char* value3,const char* value4)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_insert,value1,value2,value3,value4);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool noteinsert(const char* value1,const char* value2,const char* value3,const char* value4,const char* value5)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME3, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,note_insert,value1,value2,value3,value4,value5);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectinsert(const char* value1,const char* value2,const char* value3,const char* value4)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE_MAX] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE_MAX);
    sprintf((char*)str_Insert,project_insert,value1,value2,value3,value4);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool setinsert(const char* value1,const char* value2,const char* value3)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME5, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,set_insertx,value1,value2,value3);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool cookieinsert(const char* value1,const char* value2)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME6, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,cookie_insert,value1,value2);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//删
bool resumedelete(const char* tablename,const char* value1)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_delete,tablename,value1);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool notedelete(const char* tablename,const char* value1)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME3, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,note_delete,tablename,value1);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectdelete(const char* tablename,const char* value1)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,project_delete,tablename,value1);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool setdelete(const char* tablename)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME5, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,set_delete,tablename);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//改
bool userupdate(const char* username,const char* password)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME1, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,user_update,password,username);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool resumeupdate(const char* username,const char* title,const char* message)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_update,username,message, title);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectupdate4(const char* username,const char* title,const char* message)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE_MAX] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE_MAX);
    sprintf((char*)str_Insert,project_update4,username,message, title);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectupdate5(const char* username,const char* title,const char* message)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE_MAX] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE_MAX);
    sprintf((char*)str_Insert,project_update5,username,message, title);
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool projectupdate6(const char* username,const char* title,const char* message)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE_MAX] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE_MAX);
    sprintf((char*)str_Insert,project_update6,username,message, title);
    Log(DEBUG)<<*message<<"\n";
    Query query = conn.query(str_Insert);
    return  query.exec();
}
bool cookieupdate(const char* username)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME6, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE_MAX] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE_MAX);
    sprintf((char*)str_Insert,cookie_update,username);
    Query query = conn.query(str_Insert);
    return  query.exec();
}

//查
//查用户名验证用户是否存在
bool userselect(const char* username)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME1, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,user_selectname,username);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[0];
    }
    std::string s=ss.str();
    if(s.empty()){
        return false;
    }else{
        return true;
    }
}

//查wenjian是否存在shujuku
bool resumselectfile(const char* username,const char* title)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_selectfile,username,title);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[0];
    }
    std::string s=ss.str();
    if(s.empty()){
        return false;
    }else{
        return true;
    }
}

//查密码密码是否正确
bool userselectpass(const char* username,const char* password)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME1, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,user_selectpass,username);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::string pass(password);
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[0];
    }
    std::string s;
    s=ss.str();
    if(s.empty()){
        return false;
    }else{
        if(s==password){
            return true;
        }else{
            return false;
        }
    }
}

//查用sessid查用户名
std::string cookieselect(const char* sessid)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME6, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,cookie_select,sessid);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[0];
    }
    std::string s;
    s=ss.str();
    return s;
}

//查cookie状态
bool cookieselectstatus(const char* sessid)
{
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME6, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,cookie_select,sessid);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::stringstream ss;
    for (it = res.begin(); it != res.end(); ++it) 
    {
            mysqlpp::Row row = *it;
            ss << row[3];
    }
    std::string s;
    s=ss.str();
    if(s=="1")
        return true;
    else
        return false;
}
//查简历内容
std::vector<std::vector<std::string> > resumeselect(const char* tablename){
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME2, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,resume_select,tablename);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::vector<std::vector<std::string> > v;
    for(it=res.begin();it !=res.end();++it){
        std::vector<std::string> tmp;
        for(int i=0;i<4;++i){
            mysqlpp::Row row= *it;
            std::stringstream ss;
            ss<<row[i];
            tmp.push_back(ss.str());
        }
        v.push_back(tmp);
    }
    return v;
}

//查笔记内容
std::vector<std::vector<std::string> > noteselect(const char* tablename){
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME3, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,note_select,tablename);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::vector<std::vector<std::string> > v;
    for(it=res.begin();it !=res.end();++it){
        std::vector<std::string> tmp;
        for(int i=0;i<5;++i){
            mysqlpp::Row row= *it;
            std::stringstream ss;
            ss<<row[i];
            tmp.push_back(ss.str());
        }
        v.push_back(tmp);
    }
    return v;
}
//查项目内容
std::vector<std::vector<std::string> > projectselect(const char* tablename){
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME4, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,project_select,tablename);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::vector<std::vector<std::string> > v;
    for(it=res.begin();it !=res.end();++it){
        std::vector<std::string> tmp;
        for(int i=0;i<6;++i){
            mysqlpp::Row row= *it;
            std::stringstream ss;
            ss<<row[i];
            tmp.push_back(ss.str());
        }
        v.push_back(tmp);
    }
    return v;
}
//查设置内容
std::vector<std::vector<std::string> > setselect(const char* tablename){
    Connection conn(false);
    conn.set_option(new mysqlpp::SetCharsetNameOption("UTF8"));
    conn.connect(DATEBASE_NAME5, DATEBASE_IP, DATEBASE_USERNAME, DATEBASE_PWD);
    char str_Insert[DATA_BUF_SIZE] = {0};
    memset(str_Insert, 0, DATA_BUF_SIZE);
    sprintf((char*)str_Insert,project_select,tablename);
    Query query = conn.query(str_Insert);
    StoreQueryResult res=query.store();
    mysqlpp::StoreQueryResult::const_iterator it;
    std::vector<std::vector<std::string> > v;
    for(it=res.begin();it !=res.end();++it){
        std::vector<std::string> tmp;
        for(int i=0;i<2;++i){
            mysqlpp::Row row= *it;
            std::stringstream ss;
            ss<<row[i];
            tmp.push_back(ss.str());
        }
        v.push_back(tmp);
    }
    return v;
}
