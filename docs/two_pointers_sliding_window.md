# Two Pointers and Sliding Window

This topic turns many brute-force scans into linear-time algorithms. The core
idea is to move one or two boundaries through the array or string without
restarting work from the beginning every time.

This topic has three main patterns:

- opposite-direction two pointers
- same-direction fast-slow pointers
- variable-size sliding window

## Goals

After this topic, you should be able to:

- recognize when a sorted array can be processed from both ends
- use fast-slow pointers to compact or filter data in place
- expand and shrink a window while maintaining state incrementally
- explain why these solutions are often `O(n)` instead of `O(n^2)`

## Opposite-Direction Two Pointers

Use this pattern when one pointer starts at the left side and the other starts
at the right side.

Common situations:

- sorted arrays
- palindrome checking
- pair problems where the sum is too small or too large
- container or interval problems where both ends matter

Typical reasoning:

- if the current state is too small, move the left pointer
- if the current state is too large, move the right pointer
- each move discards impossible answers

Examples:

- `Valid Palindrome` (125)
- `Container With Most Water` (11)

## Same-Direction Fast-Slow Pointers

Use this when both pointers move left to right, but they play different roles.

Typical roles:

- `fast` scans every element
- `slow` marks the next write position or the start of a useful range

Common situations:

- removing duplicates
- moving zeroes
- partitioning values in place
- tracking the current valid segment

Examples:

- `Move Zeroes` (283)
- `Remove Duplicates from Sorted Array` (26)

## Sliding Window

Sliding window is usually a special same-direction two-pointer technique.

The window is often written as `[left, right]` or `[left, right)`, and it grows
and shrinks while maintaining some summary information.

Common maintained state:

- current sum
- character frequency
- count of distinct values
- number of invalid or over-limit elements

Use sliding window when:

- the window expands to include new information
- the left side can move forward without ever needing to move backward
- the window condition is monotonic enough to support shrinking

Examples:

- `Minimum Size Subarray Sum` (209)
- `Longest Substring Without Repeating Characters` (3)
- `Longest Repeating Character Replacement` (424)

## Core Templates

### Opposite-direction

```cpp
int left = 0;
int right = n - 1;
while (left < right) {
    // inspect current pair
    // move left or right based on the condition
}
```

### Fast-slow

```cpp
int slow = 0;
for (int fast = 0; fast < n; ++fast) {
    if (keep(nums[fast])) {
        nums[slow] = nums[fast];
        ++slow;
    }
}
```

### Variable-size sliding window

```cpp
int left = 0;
for (int right = 0; right < n; ++right) {
    // add nums[right] or s[right]
    while (window_is_invalid()) {
        // remove nums[left] or s[left]
        ++left;
    }
    // update answer from the current valid window
}
```

## Common Bugs

- moving the wrong pointer in an opposite-direction problem
- forgetting whether `left < right` or `left <= right` is correct
- updating the answer before the window becomes valid
- shrinking the window only once when it should shrink in a `while` loop
- forgetting to remove the effect of `left` before incrementing it
- mixing the meaning of the `slow` pointer: write position vs. logical length

## How To Recognize This Topic

Ask these questions:

1. Am I repeatedly scanning overlapping ranges?
2. Can the left boundary move only forward?
3. Can I maintain the needed information incrementally instead of recomputing
   it from scratch?

If the answer is yes, two pointers or sliding window is often the right tool.

## Practice Problems

Suggested order:

1. `Valid Palindrome` (125) [[link]](https://leetcode.com/submissions/detail/1984105193/)
2. `Move Zeroes` (283) [[link]](https://leetcode.com/submissions/detail/1984115234/)
3. `Container With Most Water` (11) [[link]](https://leetcode.com/submissions/detail/1984142087/)
4. `Longest Substring Without Repeating Characters` (3) [[link]](https://leetcode.com/submissions/detail/1984169464/)
5. `Minimum Size Subarray Sum` (209) [[link]](https://leetcode.com/submissions/detail/1984187217/)
6. `Longest Repeating Character Replacement` (424) [[link]](https://leetcode.com/submissions/detail/1984970793/)

## Completion Checklist

You are ready for the next topic when:

- you can distinguish opposite-direction and same-direction pointer problems
- you can maintain window state without rescanning the whole interval
- you know when the shrink step must be a `while` loop
- you can explain why each pointer moves at most `n` times in linear solutions

## Mistake Log

Fill this section after solving problems.

- Questions in `Practice Problems`, including `11`, `209` and `424`, are all good questions that I didn't make it.
