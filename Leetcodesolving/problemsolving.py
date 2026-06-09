# // Question

# // Given an array nums and a target, return indices of two numbers that add up to the target.

# nums = [2,7,11,15]
# target = 9

# def twoSum(nums, target):
#     hashmap = {}

#     for i, num in enumerate(nums):
#         diff = target - num

#         if diff in hashmap:
#             return [hashmap[diff], i]

#         hashmap[num] = i

# # 2. Valid Anagram
# s = "anagram"
# t = "nagaram"
# def isAnagram(s, t):
#     return sorted(s) == sorted(t)

# 3. Contains Duplicate

# nums = [1,2,3,1]
# def containsDuplicate(nums):
#     return len(nums) != len(set(nums))


# 4. Valid Parentheses
# s = "()[]{}"
# def isValid(s):
#     stack = []

#     mapping = {
#         ')': '(',
#         ']': '[',
#         '}': '{'
#     }

#     for ch in s:
#         if ch in mapping:
#             if not stack or stack.pop() != mapping[ch]:
#                 return False
#         else:
#             stack.append(ch)

#     return len(stack) == 0