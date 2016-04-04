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
for eachLine in allLines:
	eachLine=ConvertCN(eachLine)
	print eachLine #支持输出换行符