import json
 
json_input = '{ "one": 1, "two": { "list": [ {"item":"A"},{"item":"B"} ] } }'
 
try:
    decoded = json.loads(json_input)
 
    # pretty printing of json-formatted string
    print json.dumps(decoded, sort_keys=True, indent=4)
 
    print "JSON parsing example: ", decoded['one']
    print "Complex JSON parsing example: ", decoded['two']['list'][1]['item']
 
except (ValueError, KeyError, TypeError):
    print "JSON format error"