// This Sqeaky's solution to the problem and can be found at: https://github.com/Sqeaky/LeetCodeAnswers

// Copied from leet code as a description of this problem
// https://leetcode.com/problems/two-sum/
//
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// Example: Given nums = [2, 7, 11, 15], target = 9,
// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].


// This takes 4~12 ms to execute onc leetcode which outputperforms 99.71% and 64.35% which is
// pretty good as the linear scan alone takes 130ms+ and the hash table alone takes 12ms+.
//
// This uses between 10.1mb and 10.3mb which is better than 45.5% and 34.88% which is fine in
// most cases, consider that linear scanning version of this that beat out 100% of other on
// memory use consumed 9mb.


#include <algorithm>
#include <map>
#include <unordered_map>

// Leet code provided this class and I presume it uses this to create a new instance of the
// class to match other languages. To see where the algorithm starts look for the function
// vector<int> Solution::twoSum(vector<int>& nums, int target)
class Solution {
public:
    using max_type = std::vector<int>::size_type;

    // Maps offer O*log(n) or O(1) lookup times in terms of computational complexity at
    // the cost of some space.
    //
    // Unorder_maps are usually hash tables. These can be thought of as taking the same
    // time to lookup any item at the cost of cache misses because they need to use much
    // more memory than the useful data they store requires. This memory is most often
    // one big block that the hash table internally and unlikely to play well with
    // whatever hardware is filling the cache. This makes them great for data sets that
    // already don't fit into memory because it means that it mimimizes caches misses to
    // one at the cost of force that one cache miss on even the smallest data sets. So
    // this should be used with the largest data sets.
    //
    // Maps are using implement as some kind of tree, most often a binary red-black tree.
    // These offer logarithm lookup of items because it often requires multiple
    // comparisons and pointer dereference. This requires a multiple of space 2 to 4
    // larger than the data being operated on. This produces "wasted" space in the form
    // of multiple pointers on each node in the treee. This is fairly cache friendly
    // because most hardware that fills cache can read pointers. This is always cheaper
    // computationally than a linear scan and on smaller data sets cheaper than hash
    // tables. The space complexity is on the same order as hash tables, but likely to
    // play more nicely with caches because the nodes of the tree and pointers in them
    // can be placed in cache more intelligently.
    template<typename map_type>
    vector<int> twoSumMap(vector<int>& nums, int target, const max_type max) const
    {
        map_type value_to_index;
        for(int index{0}; index<max; index++)
        {
            int compliment = target-nums[index];
            typename map_type::const_iterator lookup = value_to_index.find(compliment);
            if(lookup != value_to_index.end())
            {
                return {index, lookup->second};
            }
            value_to_index.emplace(nums[index], index);
        }

        return {-1, -1};
    }

    // This simply advances on one index then checking each other index for a compliment
    // starting just after the first index. This means if takes quadratic time to complete
    // but only constant memory. This is good when the entire set fits in cache because
    // scan over a few dozen numbers is likely to be faster even a single hash table
    // lookup because it is likely to miss cache and force a lookup to main memory.
    vector<int> twoSumScan(vector<int>& nums, int target, const max_type max) const
    {
        for(int index_a{0}; index_a<max; index_a++)
        {
            for(int index_b{index_a+1}; index_b<max; index_b++)
            {
                if(nums[index_a]+nums[index_b] == target)
                    { return {index_a,index_b}; }
            }
        }

        return {-1, -1};
    }

    // The entry point provided by leetcode
    vector<int> twoSum(vector<int>& nums, int target)
    {
        // This is normally a waste of code, but leetcode turns off all optimizations
        // but each function call has a cost even -O1 or /O1 would prevent.
        const max_type max{nums.size()};

        // Estimate size of cache to be enough for 256 ints and left some room for
        // whatever the function needs. Set this extremely large to reduce memory use.
        const max_type linear_cache_cutoff{250};

        // What is the size where a tree stops behaving well and a hash table
        // outperforms it.
        const max_type tree_cache_cutoff{500};

        if(max < linear_cache_cutoff)
            { return twoSumScan(nums, target, max); }

        if(max < tree_cache_cutoff)
            { return twoSumMap<std::map<int,int>>(nums, target, max); }

        return twoSumMap<std::unordered_map<int,int>>(nums, target, max);
    }
};

// For more solutions see: https://github.com/Sqeaky/LeetCodeAnswers
