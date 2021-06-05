#include <iostream>
#include <vector>
using namespace std;

/*
 *leetcode 网址:https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
 *参考文章:  https://github.com/grandyang/leetcode/issues/4
*/

/*
 *Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000


Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
 *
*/

/*
 *这道题让我们求两个有序数组中的中位数，而且限制了时间复杂度为O(log(m+n)), 看到这个时间复杂度,
 *自然而然的想到了应该使用二分查找发来求解。但是这道题被定义为Hard也是有其原因的，难就难在要在
 * 两个未合并的有序数组之间使用二分法，如果这道题只有个一个有序数组，让求中位数的话，估计就是个
 * Easy题。对于这道题来说，可以将两个有序数组混合起来成为一个有序数组再做吗，图样图森破，这个时间
 * 复杂度限制的就是告诉你尽可能别想啦。还是要用二分法，而且是在两个数组之间使用，感觉很高端啊。
 * 回顾一下中位数的定义，如果某个有序数组长度是奇数，那么其中中位数就是最中间那个，如果是偶数，
 * 那么就是最中间两个数字的平均值。这里对于两个有序数组也是一样的，假设两个有序数组的长度分别为
 * m和n，由于两个数组长度之和m+n的奇偶不确定，因此需要分情况来讨论，对于奇数的情况，直接找到最
 * 中间的数即可，偶数的话需要求最中间两个数的平均值，为了简化代码，不分情况讨论，使用一个小trick，
 * 分别找第(m+n+1)/2个，和(m+n+2)/2个，然后求其平均值即可，这对奇偶数均适用。若m+n为奇数的话，
 * 那么其实(m+n+1)/2 和 (m+n+2)/2的值相等，相当于两个相同的数字相加再除以2，还是其本身。
 *
 * 好，这里需要定义一个函数来在两个有序数组中找到第k个元素，下面重点来看如何实现找到第k个元素。
 * 首先，为了避免拷贝产生新的数组从而增加时间复杂度，使用两个变量i和j分别来标记数组nums1和nus2
 * 的起始位置。然后来处理一些corner cases，比如当某一个数组的起始位置大于等于其数组长度时，说明
 * 其所有数字均已经被淘汰了，相当于一个空数组了，那么实际上就变成了在另一个数组中找数字，直接就可
 * 以找出来了。还有就是如果k=1的话，直接比较nums1和nums2的起始位置i和j上的数字就可以了。难点
 * 就在于一般的情况怎么处理？因为需要在两个有序数组中找到第k个元素，为了加快搜索的速度，可以使用
 * 二分法，那么对谁二分呢，数组么？其实要对K二分，意思是需要分别在nums1和nums2中查找k/2个元素，
 * 注意这里由于两个数组的长度不定，所以有可能某个数组没有第k/2个数字，所以需要先check一下，数组
 * 中到底存不存在第k/2个数字，如果存在就取出来，否则就复制上一个整形最大值(目的是要在nums1和
 * nums2中先淘汰k/2个较小的数字，判断的依据就是看midVal1和midVal2谁更小，但如果某个数组的
 * 个数都不到k/2个，自然无法淘汰，所以将其对应的的midVal值设为整型最大值，以保证不会被淘汰)，若
 * 某个数组没有第k/2个数字，则淘汰另一个数组的前k/2数字即可。举个例子来说吧，比如nums1={3},
 * nums2={2,4,5,6,7}, k = 4,要找两个数组混合中第四个数字，则分别在nums1和nums2中找第2个
 * 数字,而nums1中只有一个数字，不存在第二个数字，则nums2中的前两个数字可以直接跳过，为啥呢，
 * 因为要求的是整个混合数组中的第4个数字，不管nums1中的那个数字是大是小，第四个数字绝对不会出
 * 现在nums2的前两个数字中，所以可以直接跳过。
 *
 * 有没有可能两个数组都不存在第k/2个数字呢，这道题里是不可能的，因为k不是随意给的，而是给的m+
 * n的中间值，所以必定至少会有一个数组是存在第k/2个数字的。最后就是二分法的核心啦，比较这两个
 * 数组的第k/2小的数字midVal1和midVal2的大小，如果第一个数组的第k/2个数字小的话，那么说明要
 * 找的数字肯定不在nums1中的前k/2个数字，可以将其淘汰，将nums1的其实位置向后移动k/2个，并且
 * 此时的k也自减取k/2，调用递归，举个例子吧，比如nums1={1,3},nums2={2,4,5},k=4,要找两个
 * 数组混合中第4个数字，那么分别在nums1和nums2中找第2个数字，nums1中的第2个数字是3，nums2中
 * 的第2个数字是4，由于3小于4，所以混合数组中第4个数字肯定在nums2中，可以将nums1的其实位置向后
 * 移动k/2个。反之，淘汰nums2中的前k/2个数字，并将nums2的起始位置向后移动k/2个，并且此时的k
 * 也自减去k/2,调用递归即可。
*/


class Solution41
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        int left = (m+n+1)/2, right = (m+n+2)/2;
        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right))/2.0;
    }

    int findKth(vector<int> &nums1, int i, vector<int> &nums2, int j, int k)
    {
        if(i >= nums1.size()) return nums2[j+k-1];
        if(j >= nums2.size()) return nums1[i+k-1];
        if(k == 1) return min(nums1[i], nums2[j]);
        int midVal1 = (i+k/2-1 < nums1.size()) ? nums1[i+k/2-1] : INT32_MAX;
        int midVal2 = (j+k/2-1 < nums2.size()) ? nums2[j+k/2-1] : INT32_MAX;
        if(midVal1 < midVal2)
        {
            return findKth(nums1, i+k/2, nums2, j, i - k/2);
        }
        else
        {
            return findKth(nums1, i, nums2, j+k/2, j-k/2);
        }
    }
};


/*
 *上面的解法一直使用的是原数组，同时用了两个变量来分别标记当前的起始位置。我们也可以直接生成新的
 * 数组，这样就不要用起始位置变量了，不过拷贝数组的操作可能会增加时间复杂度，也许会超出限制，不过
 * 就算当个思路拓展也是好的。首先要判断数组是否为空，为空的话，直接在另一个数组找第k个即可，还有
 * 一种情况是当k=1时，表示要找第一个元素，只要比较两个数组的第一个元素，返回较小的那个即可。这里
 * 分别取出两个数组的第k/2个数字的位置坐标i和j，为了避免数组没有第k/2个数组的情况，每次都和数组
 * 长度做比较，取出较小值。这里跟上面的解法有些许不同，上面解法直接取出的是值，而这里取出的是位置
 * 坐标，但是思想都是很类似的。不同在于，上面解法中每次固定淘汰k/2个数字，而这里由于取出了合法的
 * i和j，所以每次淘汰i或j个。评论区有网友提出，可以让j=k-i，这样也是对的，可能还更好一些，收敛
 * 速度可能会更快一些，参考代码如下:
 *
*/

class Solution42
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        return (findKth(nums1, nums2, (m+n+1)/2) + findKth(nums1, nums2, (m+n+2)/2))/2.0;
    }
    int findKth(vector<int> nums1, vector<int> nums2, int k)
    {
        if(nums1.empty()) return nums2[k-1];
        if(nums2.empty()) return nums1[k-1];
        if(k == 1) return min(nums1[0], nums2[0]);
        int i = min((int)nums1.size(), k/2);
        int j = min((int)nums2.size(), k/2);
        if(nums1[i-1] > nums2[j-1])
        {
            return findKth(nums1, vector<int>(nums2.begin()+j, nums2.end()), k-j);
        }
        else
        {
            return findKth(vector<int>(nums1.begin()+i, nums1.end()), nums2, k-i);
        }
        return 0;
    }
};


/*
 * 此题还能用迭代形式的二分搜索发来解，是一种相当巧妙的应用，这里就参照 stellari大神的帖子来
 * 讲解吧。所谓的中位数，换一种角度去看，其实就是把一个有序数组分为长度相等的两段，中位数就是前
 * 半段的最大值和后半段的最小值的平均数，也就是离分割点相邻的两个数字的平均值。比如说对于偶数个
 * 数组[1357],那么分割开来就是[13/57],其中'/'表示分割点，中位数就是3和5的平均值，对于奇数个
 * 数组[13457],可以分割为[134/457],可以发现左右两边都有两个4，则中位数是两个4的平均数，还是
 * 4。这里使用L表示分割点左边的数字，R表示分割点右边的数字，对于[1357]来说，L=3,R=5。对于[134
 * 57]来说，L=4,R=4。那么对于长度为N的数组来说，可以分别得到L和R的位置，如下所示:
 *
 *      N   Index of L      Index of R
 *      1        0               0
 *      2        0               1
 *      3        1               1
 *      4        1               2
 *      5        2               2
 *      6        2               3
 *      7        3               3
 *      8        3               4
 *
 * 观察上表，可以得到规律，idx(L)= (N-1)/2, idx(R) = N/2,所以中位数可以用下式表示:
 * (L+R)/2=(A[(N-1)/2] + A[N/2]) / 2;
 *
 * 为了统一数组长度为奇数和偶数的情况，可以使用一个小tricky,即在每个数字的两边都加上一个特殊
 * 字符，比如#号，这个tricky其实在马拉车算法中也使用过，可以参见博主之前的帖子Manacher's
 * Algorithm 马拉车算法。这样做的好处是不管奇数或者偶数，加#号后数组的长度都是奇数，并且切割
 * 点的位置也是确定的，比如:
 ×
 * [1 3 5 7] -> [# 1 # 3 # 5 # 7 #]     N1 = 5
 * index         0 1 2 3 4 5 6 7 8     newN1 = 11
 ×
 * [1 3 4 5 7] -> [# 1 # 3 # 4 # 5 # 7 #]     N1 = 5
 * index           0 1 2 3 4 5 6 7 8 9 10     newN1 = 11
 *
 * 这里的N是原数组的长度，newN是新添加#号后新数组的长度，可以发现newN = 2N+1,而且切割点永远
 * 都在新数组中坐标为N的位置，且 idx(L) = (N-1)/2, idx(R) = N/2, 这里的N就可以换成分割点
 * 的位置，岂不美哉(注意这里的idx(L) 和 idx(R) 表示的是在未填充#号的坐标位置)！现在假设有两
 * 个数组：
 *
 * [1 3 4 5 7] -> [# 1 # 3 # 4 # 5 # 7 #]     N1 = 5
 * index           0 1 2 3 4 5 6 7 8 9 10     newN1 = 11
 *
 * [1 2 2 2] -> [# 1 # 2 # 2 # 2 #]     N2 = 4
 * index         0 1 2 3 4 5 6 7 8      newN2 = 9
 *
 * 跟只有一个数组的情况类似，这里需要找到一个切割点，使得其分别可以将两个数组分成左右两部分，需要
 * 满足的是两个左半边中的任意一个数字都要小于两个右半边数组的数字，注意这里可能有的左半边或右半边
 * 为空，但是两个左半边数字的个数和应该等于两个右半边的个数和。这里还可以观察出一些规律:
 * 1.总共有 2N1+2N2+2个位置，那么出去两个分割点，两个左右半边应该各有N1+N2个数字。
 * 2.因此，对于一个在A2数组中的分割点位置C2=K，在A1数组中的位置应该为C1=N1+N2-K，比如假如
 * 在A2中的分割点位置为C2=2，那么在A1中的位置为C1= 4+5-C2 = 7。
 *
 * [# 1 # 3 # 4 # (5/5) # 7 #]
 * [# 1 / 2 # 2 # 2 #]
 *
 * 3.加入连个数组都被分割了，那么就应该会有两个L和R，分别是:
 * L1 = A1[(C1-1)/2]
 * R1 = A1[C1/2]
 *
 * L2 = A2[(C2-1)/2]
 * R2 = A2[C2/2]
 *
 * 对于上面的例子就有:
 * L1 = A1[(7-1)/2] = A1[3] = 5
 * R1 = A1[7/2] = A1[3] = 5
 *
 * L2 = A2[(2-1)/2] = A2[0] = 1
 * R2 = A1[2/2] = A2[1] = 2
 *
 * 现在需要检测这个切割点是否是正确的中位数的切割点，那么根据之前的分析，任意的左半边的数字都需要
 * 小鱼等于右半边的数字，L1和L2是左半边的最大的数字，R1和R2是右半边的最小的数字，所以需要满足
 * 下列关系:
 * L1 <= R1 && L1 << R2 && L2 <= R1 && L2 <= R2
 *
 * you由于两个数组都是有序的，所以L1<=R1 和 L2<=R2都是满足的，那么就只需要满足下列的不等式即
 * 可：
 * L1 <= R2 && L2 <= R1
 *
 * 这样的话就可以利用二分搜索了，假如L1>R2的话，说明数组A1的左半边的数字过大了，需要把切割点C1
 * 往左移动。假如L2>R1，说明数组A2的左半边数字过大，需要把分割点C2左移。若满足上面的条件，说明
 * 当前切割点就是正确的，那么中位数就可以求出来了，即为：
 * (max(L1,L2) + min(R1,R2))/2
 *
 * 最后还有两点注意事项:
 * 1.由于C1和C2是可以相互计算而得，即一个确定了，另一个就可以计算出来了。所以尽量去移动较短的
 * 那个数组，这样得到的时间复杂度为O(lg(min(N1, N2)))。
 * 2.对于corner case的处理，当切割点在0或者2n的位置时，将L或R的值分别赋值为整形最小值和最大值，
 * 这不会改变正确的切割点的位置，会使得代码实现更加方便。
 *
 *
 *
*/


class Solution43
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        if(m < n) return findMedianSortedArrays(nums2, nums1);
        if(n == 0) return ((double)nums1[(m-1)/2] + (double)nums1[m/2]) / 2.0;
        int left = 0, right = n*2;
        while(left <= right)
        {
            int mid2 = (left + right) / 2;
            int mid1 = m + n - mid2;
            double L1 = mid1 == 0 ? INT32_MIN : nums1[(mid1-1)/2];
            double L2 = mid2 == 0 ? INT32_MIN : nums2[(mid2-1)/2];
            double R1 = mid1 == m * 2 ? INT32_MAX : nums1[mid1/2];
            double R2 = mid2 == n * 2 ? INT32_MAX : nums2[mid2/2];
            if (L1 > R2) left = mid2+1;
            else if(L2 > R1) right = mid2 -1;
            else return (max(L1, L2) + min(R1, R2)) / 2;
        }
        return -1;
    }
};


class Test
{
public:
    void goTest()
    {
        vector<int> nums1 = {6,8,10,12,14};
        vector<int> nums2 = {2,4,20};
        double res = 0.0;
        Solution43 solution;
        res = solution.findMedianSortedArrays(nums1, nums2);
        std::cout << "goTest() endl" << std::endl;
    }
};















