#!/usr/bin/python
#coding:utf-8

import urllib3
import re
from bs4 import BeautifulSoup

def OpenPage(url):
    http=urllib3.PoolManager()
    r= http.request('GET',url)
    return r.data
def ParseMainPage(page):
    data = json.loads(page)
    rows = data["rows"]
    return rows

def Test1():
    print OpenPage("jy.51uns.com:8022/Pro_StudentEmploy/StudentJobFair/Zhaoping.aspx?WorkType=0")

if __name__ == "__main__":
    Test1()

