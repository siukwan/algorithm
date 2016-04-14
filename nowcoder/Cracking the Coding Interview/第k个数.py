# -*- coding:utf-8 -*-
class KthNumber:
    def findKth(self, k):
        # write code here
        result=[1]
        idx=[0,0,0]
        for i in range(0,k,1):
            a=result[idx[0]]*3
            b=result[idx[1]]*5
            c=result[idx[2]]*7
            
            tmp=min(min(a,b),c)
            result.append(tmp)
            if tmp == a:
                idx[0]+=1
            if tmp == b:
                idx[1]+=1
            if tmp == c:
                idx[2]+=1
        return result[k]