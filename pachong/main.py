#!/usr/bin/python
#coding:utf-8

import urllib3
import re
from bs4 import BeautifulSoup

#发送url请求
def OpenPage(url):
    http = urllib3.PoolManager()
    r = http.request('GET',url)
    return r.data.decode("GBK",errors="ignore").encode("utf-8")

#从小说获取各个章节的url
def ParseMainPage(page):
    #解析服务器端响应内容，格式化
    soup = BeautifulSoup(page,"html.parser")
    ListCharts = soup.find_all(href=re.compile("read"))
    UrlList = []
    #item的类型是Besutiful的一个类型，可以根据属性的到属性值
    for item in ListCharts:
        url="http://www.shengxu6.com" + item["href"]
        UrlList.append(url)

    return UrlList

#根据url获取url和正文
def ParseDetailPage(page):
    soup=BeautifulSoup(page,"html.parser")
    title = soup.find_all(class_="panel-heading")[0].get_text()
    content = soup.find_all(class_="content-body")[0].get_text()
    return title, content[:-12]

#把数据写入一个txt文件
def WriteDataToFile(data):
    #f = open("output.txt","a+")
    #f.write(data)
    #f.close()
    #上下文管理器
    with open("output.txt","a+") as f:
        f.write(data)



def Test3():
    page= OpenPage("http://www.shengxu6.com/read/2967_2008192.html")
    title,content=ParseDetailPage(page)
    print title
    print content

def Test1():
    d = OpenPage("http://www.shengxu6.com/book/2967.html")
    print d

def Test2():
    page = OpenPage("http://www.shengxu6.com/book/2967.html")
    print ParseMainPage(page)

if __name__ == "__main__":
    Get = raw_input("请输入要爬取的小说：")
    #打开主页 
    MainPage = OpenPage(Get)
    #解析主页
    GetUrl = ParseMainPage(MainPage)
    for item in GetUrl:
        #打开章节页面
        page = OpenPage(item)
        #获取章节标题和文件
        title,content = ParseDetailPage(page)
        print "Clone" + title
        data = "\n\n\n" + title + "\n\n\n" + content
        data = data.encode("utf-8")
        WriteDataToFile(data)

