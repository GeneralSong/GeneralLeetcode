/*
 *leetcode 网址:https://leetcode-cn.com/problems/add-two-numbers/
 *参考文章: https://github.com/grandyang/leetcode/issues/2
*/


/*
 *
 *You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.



Example 1:


Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]
Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]


Constraints:

The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 *这道并不算什么难题，算法很简单，链表的数据类型也不难，就是建立一个新链表，然后把输入的两个链表
 * 从头往后撸，每两个相加，添加一个新节点到链表后面，为了避免两个输入链表同时为空，我们建立一个
 * dummpy节点，将两个节点相加生成的新节点按照顺序街道dummy节点之后，由于dummy节点本身不能变，
 * 所以用一个指针cur来指向新链表的最后一个节点。好，可以开始让两个链表相加了，这道题好就好在在
 * 最低位在链表的开头，所以可以在遍历链表的同时按从低到高的顺序直接相加。while循环的条件两个链表
 * 中只要有一个不为空行，由于链表可能为空，所以在取当前节点值的时候，先判断一下，若为空则取0，否则
 * 取节点值。然后把两个节点值相加，同时还要加上进位carry。然后更新carry，直接sum/10即可，然后
 * 以swm%10为值建立一个新节点，连到cur后面，然后cur移动到下一个节点。之后再更新两个节点，若存在，
 * 则指向下一个位置。while循环退出之后，最高位的进位问题要最后特殊处理一下，若carry为1，则再建立
 * 一个值为1的节点。
*/

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution21
{
public:
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2){
        if(!l1 && !l2) return nullptr;
        ListNode *dummy = new ListNode(-1), *cur = dummy;
        int carry = 0;
        while(l1 || l2)
        {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum%10);
            cur = cur->next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry) cur->next = new ListNode(1);
        cur = dummy->next;
        if(dummy) delete dummy;
        return cur;
    }
};













