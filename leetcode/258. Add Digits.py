class Solution(object):
    def addDigits(self, num):
        """
        :type num: int
        :rtype: int
        """
        result=num
        while num/10!=0:
            result=0
            while num!=0:
                result+=num%10
                num/=10
            num=result
        return result