class Solution(object):
    def climbStairs(self, n):
	    """
		:type n: int
		:rtype: int
		"""
		if n<=1:
			return 1
		map={}	
		map[0]=1														
		map[1]=1
		for i in range(2, n+1):
			map[i]=map[i-1]+map[i-2]									
		return map[n] 
