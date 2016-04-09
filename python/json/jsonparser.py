#encoding: utf-8
'''
Author:Siukwan
'''
import sys  
reload(sys)   
sys.setdefaultencoding('utf8')  

import json

def txt2str(file='jsondata2.txt'):
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

	def _skipBlank(self):  
		'''
		跳过空白、换行或tab： \n\t\r
		'''
		while self._index<len(self._str) and self._str[self._index] in ' \n\t\r':
			self._index=self._index+1
	def parse(self):
		self._skipBlank()
		if self._str[self._index]=='{':
			self._index+=1
			return self._parse_object()
	def _parse_string(self):
		'''
		找出两个双引号中的string
		'''
		begin = end =self._index
		#找到string的范围
		while self._str[end]!='"':
			end=end+1
		self._index = end+1
		return self._str[begin:end]

	def _parse_number(self):
		'''
		数值没有双引号
		'''
		begin = end = self._index
		end_str=' \n\t\r,}]' #数字结束的字符串
		while self._str[end] not in end_str:
			end += 1
		number = self._str[begin:end]

		#进行转换
		if '.' in number or 'e' in number or 'E' in number :
			res = float(number)
		else:
			res = int(number)
		self._index = end
		return res

	def _parse_value(self):
		'''
		解析值，包括string，数字
		'''
		if self._str[self._index] == '"':
			self._index = self._index+1
			self._skipBlank()
			return self._parse_string()
		else:
			self._index = self._index+1
			self._skipBlank()
			return self._parse_number()
	def _parse_object(self):
		obj={}
		self._skipBlank()
		#空object
		if self._str[self._index]=='}':
			self._index +=1
			return obj
		#elif self._str[self._index] !='"': 
			#报错
		
		self._index+=1 #跳过当前的双引号
		while True:
			key = self._parse_string() #获取key值
			self._skipBlank()

			self._index = self._index+1#跳过冒号:
			self._skipBlank()
			
			#self._index = self._index+1#跳过双引号
			#self._skipBlank()
			#获取value值,目前假设只有string的value和数字
			obj[key]= self._parse_value()
			self._skipBlank()
			print key,":",obj[key]
			#对象结束了，break
			if self._str[self._index]=='}':
				self._index +=1
				break
		 	elif self._str[self._index]==',':#还存在其他对象
				self._index +=1
				self._skipBlank()

			self._index +=1#跳过下一个对象的第一个双引号

		return obj#返回对象

	def display(self):
		displayStr=""
		self._skipBlank()
		while self._index<len(self._str):
			#print self._str[self._index],
			#print "%s"%self._str[self._index],
			displayStr=displayStr+self._str[self._index]
			self._index=self._index+1
			self._skipBlank()
			#print self._index
		print displayStr

#main函数
if __name__ == '__main__':
	print "test"
	jsonStr=txt2str()
	jsonInstance=jsonparser(jsonStr)
	dir(jsonInstance.parse())
	jsonInstance.display()
