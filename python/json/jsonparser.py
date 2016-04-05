#encoding: utf-8
import sys  
reload(sys)   
sys.setdefaultencoding('utf8')  

import json

def txt2str(file='jsondata.txt'):
	fp=open(file)
	allLines = fp.readlines()
	fp.close()
	str=""
	for eachLine in allLines:
		eachLine=ConvertCN(eachLine)

		#转换成字符串
		for i in range(0,len(eachLine)):
			#if eachLine[i]!= ' ' and eachLine[i]!= '	' and eachLine[i]!='\n': #删除空格和换行符，但是json双引号中的内容空格不能删除
			str+=eachLine[i]
	return str


#main函数
if __name__ == '__main__':

