# Binary Search

Binary search is one of the most important algorithm patterns. It works when the
search space has a monotonic property, which means that once some condition
becomes true, it stays true, or once it becomes false, it stays false.

This topic has four parts:

- exact-match binary search
- left boundary search
- right boundary or last-position search
- answer-space binary search

## Goals

After this topic, you should be able to:

- write exact-match binary search from memory
- find the first position that satisfies a condition
- find the last position that satisfies a condition
- recognize when the real search target is not an array index, but an answer value

## Core Idea

Binary search reduces the search space by half each round.

For a sorted array:

- if `nums[mid]` is too small, the answer must be on the right
- if `nums[mid]` is large enough for the condition, the answer may be at `mid`
  or on the left

This is why loop invariants matter more than memorizing one exact code block.

## Interval Convention

In this repository, the binary search templates use the closed interval:

- search range is `[left, right]`
- loop condition is `left <= right`

Why this is useful:

- exact-match search is very direct
- left-boundary and right-boundary search can reuse the same shape
- the update rules stay consistent:
  - move right: `left = mid + 1`
  - move left: `right = mid - 1`

Always compute the middle safely:

```cpp
int mid = left + (right - left) / 2;
```

## Exact-Match Search

Use this when you want:

- the index of one target value
- `-1` if the target does not exist

Template idea:

```cpp
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
        return mid;
    }
    if (nums[mid] < target) {
        left = mid + 1;
    } else {
        right = mid - 1;
    }
}
```

## Left Boundary Search

Use this when you want the first index satisfying a condition.

For example:

- first index where `nums[i] >= target`
- insertion position for `target`

Important idea:

- when `nums[mid] >= target`, `mid` may still be the answer, so do not throw it
  away too early
- record it and continue left

## Right Boundary Search

Use this when you want:

- the first index where `nums[i] > target`
- the last occurrence of `target`
- the last index satisfying some monotonic condition

One common trick:

- first find the first index `> target`
- then step one position left

If the resulting index is invalid or not equal to `target`, the target was not
present.

## Answer-Space Binary Search

This is the most important step beyond basic array search.

Sometimes you are not searching for an index. Instead, you are searching for
the smallest or largest answer that makes a predicate true.

Example:

- in `Koko Eating Bananas`, search the minimum eating speed
- if speed `k` works, then every larger speed also works
- that is a monotonic condition, so binary search applies

General pattern:

- define the answer range, such as `[1, max_value]`
- write a `Check(mid)` function
- if `Check(mid)` is true, record `mid` and continue left
- otherwise continue right

## Common Bugs

- using binary search on data that is not sorted or not monotonic
- mixing interval conventions, such as `[left, right]` updates with a
  `[left, right)` loop condition
- writing `right = mid` in a closed-interval template and causing an infinite
  loop
- using `(left + right) / 2` without thinking about overflow
- not deciding clearly whether the condition is:
  - exact match
  - first `>= target`
  - first `> target`
  - smallest valid answer

## How To Recognize Binary Search

Ask these questions:

1. Is the input already sorted?
2. Is there a monotonic yes/no condition?
3. Can I safely discard half of the current search space each round?

If the answer is yes, binary search is likely the right tool.

## Practice Problems

Suggested order:

1. `Binary Search` (704) [[link]](https://leetcode.com/submissions/detail/1983182790/)
2. `Search Insert Position` (35) [[link]](https://leetcode.com/submissions/detail/1983194865/)
3. `Sqrt(x)` (69) [[link]](https://leetcode.com/submissions/detail/1983211245/)
4. `Find First and Last Position of Element in Sorted Array` (34) [[link]](https://leetcode.com/submissions/detail/1983226004/)
5. `Koko Eating Bananas` (875) [[link]](https://leetcode.com/submissions/detail/1983288055/)

## Completion Checklist

You are ready for the next topic when:

- you can write exact-match binary search without checking old code
- you understand the difference between `first >= target` and `first > target`
- you can explain why the search range shrinks correctly every round
- you can identify answer-space binary search problems

## Mistake Log

Fill this section after solving problems.

- `Binary Search` (704): 
  - use `left <= right` for the closed interval template,
  not `left < right`, or you can miss the last candidate. 
  - Also avoid using `size_t` for `left/right/mid` in this template 
  because `mid - 1` can underflow
  when `mid == 0`; signed `int` is safer for this style of binary search.
