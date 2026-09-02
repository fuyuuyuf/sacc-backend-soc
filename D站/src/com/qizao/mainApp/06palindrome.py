import re

pattern = r'^[+-]?\d+$'
inputN =input("请输入待检测整数：")
try :
    checked =re.match(pattern,inputN).group(0)  #没报错就没毛病
    isPalindrome = True
    #判断头尾
    for i in range(0,checked.__len__()//2):
        isPalindrome = True if checked[-(i+1)] ==checked[i] else False
    print("是" if isPalindrome else "不是"+"回文数")
except :
    print("非法输入")
