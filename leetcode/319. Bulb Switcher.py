class Solution(object):
    def bulbSwitch(self, n):
        """
        :type n: int
        :rtype: int
        """
        result = 0
        i = 1
        while i <= math.sqrt(n):
            if i*i<=n:
                result+=1
            i+=1
        
        return result