test =[2,7,11,15,1,8]
targetN=9
testNew=[]#收集缩减结果
targetNP =[]#记录对应索引
#缩减长度
for i in range(0,len(test)):
    if test[i]< targetN :
        targetNP.append( i)
        testNew.append(test[i])
#遍历寻找
allN=0;
for i in range(0,len(testNew)-1):
    temp = testNew[i]
    for j in range(i+1,len(testNew)):
        if testNew[j]+testNew[i] ==targetN:
            print("找到了：[%d,%d]"%(targetNP[i],targetNP[j]))
            allN=allN+1
if allN==0:
    print("未找到")


