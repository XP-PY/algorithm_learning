# Foundations, Complexity, Arrays, and STL

This is the preparation topic for the rest of the repository. Before learning
specific algorithm patterns such as binary search or dynamic programming, you
should be comfortable with complexity analysis, arrays, and the most common C++
STL containers and algorithms.

## Goals

After this topic, you should be able to:

- read and write simple array code without index mistakes
- explain the time and space complexity of basic loops
- use `vector`, `pair`, `sort`, and `reverse` comfortably
- recognize when preprocessing can simplify later work

## Big-O Basics

Big-O describes how running time or memory usage grows as input size `n` grows.

Common examples:

- `O(1)`: direct access such as `a[i]`
- `O(log n)`: repeated halving, such as binary search
- `O(n)`: one full pass through an array
- `O(n log n)`: efficient comparison sorting
- `O(n^2)`: double loop over all pairs

When analyzing a solution:

1. count how many times the main loop runs
2. check whether there is nested work inside it
3. ignore constants and lower-order terms

Examples:

- one loop from `0` to `n - 1` is usually `O(n)`
- two independent loops of size `n` are still `O(n)`
- a loop inside a loop is often `O(n^2)`

## Arrays and Indexing

Arrays and `vector` are the most common containers in algorithm problems.

Important habits:

- use `0`-based indexing consistently
- always check whether the range is `[0, n)` or `[1, n]`
- when iterating neighbors, verify boundary conditions first
- prefer clear variable names such as `left`, `right`, `i`, `j`, `n`

Typical traversal patterns:

```cpp
for (int i = 0; i < n; ++i) {
    // left to right
}

for (int i = n - 1; i >= 0; --i) {
    // right to left
}
```

## Useful STL Pieces

These are enough for the first several topics:

- `vector<T>`: dynamic array
- `pair<T1, T2>`: store two related values
- `sort(begin, end)`: sort ascending by default
- `reverse(begin, end)`: reverse a range
- `min`, `max`: compare two values

Examples:

```cpp
vector<int> nums = {4, 1, 3};
sort(nums.begin(), nums.end());
reverse(nums.begin(), nums.end());
```

Custom comparator example:

```cpp
sort(items.begin(), items.end(), [](const pair<int, int>& a,
                                    const pair<int, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
});
```

## Prefix Maximum

Prefix preprocessing is an important algorithm habit.

For an array `a`, the prefix maximum array `pref_max` stores:

- `pref_max[i] = max(a[0], a[1], ..., a[i])`

Why it matters:

- later queries become easier
- preprocessing often changes repeated work into a simple lookup
- this idea appears again in prefix sums, dynamic programming, and greedy scans

Example:

- original: `[3, 1, 5, 2, 4]`
- prefix max: `[3, 3, 5, 5, 5]`

## Common Mistakes

- off-by-one errors in loop boundaries
- using `<= n` when the valid index range is only `< n`
- forgetting that `sort` is ascending by default
- writing a comparator that does not define a consistent order
- accessing `nums[i + 1]` or `nums[i - 1]` without checking boundaries

## Practice Problems

Start with these:

- `Two Sum` (1) [[link]](https://leetcode.com/submissions/detail/1982387600/)
- `Remove Duplicates from Sorted Array` (26) [[link]](https://leetcode.com/submissions/detail/1982414707/)
- `Merge Sorted Array` (88) [[link]](https://leetcode.com/submissions/detail/1982399028/)
- `Sort Colors` (75) [[link]](https://leetcode.com/submissions/detail/1982424396/)
- `Squares of a Sorted Array` (977) [[link]](https://leetcode.com/submissions/detail/1982431050/)

Suggested order:

1. `Two Sum`
2. `Merge Sorted Array`
3. `Remove Duplicates from Sorted Array`
4. `Squares of a Sorted Array`
5. `Sort Colors`

## Completion Checklist

You are ready for the next topic when:

- you can explain why a loop is `O(n)` or `O(n^2)`
- you can write clean `vector` traversal without boundary bugs
- you can sort integers and pairs confidently
- you understand what a prefix preprocessing array is doing

## Mistake Log

Fill this section after solving problems.

- 
