/**
* Definition for an interval.
* struct Interval {
*     int start;
*     int end;
*     Interval() : start(0), end(0) {}
*     Interval(int s, int e) : start(s), end(e) {}
* };
*/
class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		vector<Interval> result(0);
		if (intervals.size() == 0) return result;
		sort(intervals.begin(), intervals.end(), cmp);//先排序
		int start = intervals[0].start, end = intervals[0].end;

		for (int i = 1; i<intervals.size(); ++i)
		{
			//如果后面一个区间的开始在现在合并区间内，则合并
			if (intervals[i].start <= end)
			{
				end = max(end, intervals[i].end);
			}
			else
			{
				result.push_back(Interval(start, end));
				start = intervals[i].start;
				end = intervals[i].end;
			}
		}
		result.push_back(Interval(start, end));
		return result;
	}
	static bool cmp(const Interval&a, const Interval&b)
	{
		if (a.start<b.start)
			return true;
		else if (a.start == b.start)
		{
			if (a.end<b.end) return true;
			else return false;
		}
		else
			return false;
	}
};