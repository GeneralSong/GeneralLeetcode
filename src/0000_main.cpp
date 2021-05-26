#include <iostream>
#include "0001_twoSum.h"
using namespace std;

int main(int argc, char *argv[])
{

    std::cout << "hello world" << std::endl;

    /*0001 twoSum*/
    vector<int> nums = {2, 4, 8, 3};
    int target = 10;
    vector<int> res;
    Solution11 sl;
    res = sl.twoSum(nums, target);
    for(auto p : res)
    {
        std::cout << p << std::endl;
    }


    return 0;
}









