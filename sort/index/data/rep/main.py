#!/usr/bin/python
#coding:utf-8

import urllib3
import re
from bs4 import BeautifulSoup

#打开页面
def OpenPage(url):
    http = urllib3.PoolManager()
    r = http.request('GET',url)
    return r.data


def run():
    page = OpenPage("https://www.boost.org/doc/libs/1_68_0/")

def Test1():
    page = OpenPage("https://www.boost.org/doc/libs/1_68_0/")
    print page

#主函数
if __name__ == "__main__":
    #run()
    Test1()
