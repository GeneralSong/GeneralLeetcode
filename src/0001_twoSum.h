/*
 *https://leetcode-cn.com/problems/two-sum/
 *https://github.com/grandyang/leetcode/issues/1
*/

/*
 *Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]


Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 *
*/

/*
 *啦啦啦,欢迎开启LeetCode刷题的旅程,这将是一段漫长而又艰辛的旅程,这是一条攀登珠穆朗玛峰的皑皑雪山路，这是通向One Piece宝藏的伟大航路，这是成为火影的无比残酷的修罗场，这是打破屌丝与高富帅之间界限的崩玉。但请不要害怕，在老船长GeneralSong博主的带领下，必将一路披荆斩棘，将各位带到成功的彼岸，不过一定要牢记的是，不要下船，不要中途放弃，要坚持，要自我修炼，不断成长！那么，起航吧~这道Two Sum的题目作为LeetCode的开篇之题，乃是经典中的经典，正所谓“平生不识TwoSum，刷尽LeetCode也枉然”，就像英语单词书的第一个单词总是Abandon一样，很多没有毅力坚持的人就只能记住这一个单词，所以通常情况下单词书就前几页有翻动的痕迹，后面都是攒心如初，道理不需要多讲，鸡汤不必多灌，明白的人自然明白。
 *
 * 这道题给了我们一个数组，还有一个目标数target，让找到两个数字，使其和为target，乍一看就感觉可以使用暴力搜索，这个算法的时间复杂度是O(n^2)。那只能像个O(n)的算法来实现，由于暴力搜索的方法是遍历所有的两个数字的组合，然后算其和，这样虽然节省了空间，但是时间复杂度高。一般来说，为了提高时间的复杂度，需要用空间来换，这算是一个trade off吧，但这里只想用线性的时间复杂度,就是说只能遍历一个数字，那么另一个数字呢，可以事先将其存储起来，使用一个HashMap，来建立数字和其坐标位置之间的映射，由于HashMap是常数级的查找效率，这样在遍历数组的时候，用target减去遍历到的数字，就是另一个需要的数字了，直接在HashMap中朝招其是否存在即可，注意要判断查找到的数字是不是第一个数字，比如target是4，遍历到了一个2，那么另一个2不能是之前那个2，整个实现步骤为:先遍历一遍数组，建立HashMap映射，然后再遍历一遍，开始查找，找到则记录index。
 *
 *
 *
 *
 *
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
/*C++解法一*/
class Solution11
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> m;
        vector<int> res;
        for(int i = 0; i < nums.size(); ++i)
        {
            m[nums[i]] = i;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            int t = target-nums[i];
            if(m.count(t) && m[t] != i)
            {
                res.push_back(i);
                res.push_back(m[t]);
                break;
            }
        }
        return res;
    }
};

/*C++解法二*/
class Solution12
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> m;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(m.count(target - nums[i]))
            {
                return {i, m[target - nums[i]]};
            }
            m[nums[i]] = i;
        }
    }
};
































