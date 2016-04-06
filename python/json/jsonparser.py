#encoding: utf-8
'''
Author:Siukwan
'''
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
		#eachLine=ConvertCN(eachLine)

		#转换成字符串
		for i in range(0,len(eachLine)):
			#if eachLine[i]!= ' ' and eachLine[i]!= '	' and eachLine[i]!='\n': #删除空格和换行符，但是json双引号中的内容空格不能删除
			str+=eachLine[i]
	return str


class jsonparser:

	def __init__(self, str=None):
		self._str = str
		self._index=0
	def deleteBlank(self):
		while self._index<len(self._str) and self._str[self._index] in ' \n\t\r':
			self._index=self._index+1
	def display(self):
		while self._index<len(self._str):
			self.deleteBlank()
			print self._str[self._index]
			self._index=self._index+1

#main函数
if __name__ == '__main__':
	print "test"
	jsonStr=txt2str()
	jsonInstance=jsonparser(jsonStr)
	jsonInstance.display()
