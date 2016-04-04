#encoding: utf-8
import sys  
reload(sys)   
sys.setdefaultencoding('utf8')  
import json
class json:
	def decode(self, json_input):
		print "test"

	def decode_jsonLib(self,json_input):
		try:
			decoded = json.loads(json_input)
			# pretty printing of json-formatted string
			print json.dumps(decoded, sort_keys=True, indent=4)
		except (ValueError, KeyError, TypeError):
			print "JSON format error"



def ConvertCN(s):  
	return s.encode('gb18030')  


fp=open('json.txt')
allLines = fp.readlines()
#print fp


fp.close()
str=""
for eachLine in allLines:
	eachLine=ConvertCN(eachLine)
	for i in range(0,len(eachLine)):
		if eachLine[i]!= ' ' and eachLine[i]!='\n': #删除空格和换行符，但是json双引号中的内容空格不能删除
			str+=eachLine[i]
	#print eachLine #支持输出换行符
print str