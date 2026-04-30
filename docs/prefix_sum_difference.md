# Prefix Sums and Difference Arrays

Prefix sums and difference arrays are preprocessing techniques for range
problems.

Use prefix sums when you need many range queries. Use difference arrays when
you need many range updates and only need the final array later.

## Goals

After this topic, you should be able to:

- build a 1D prefix sum array
- answer range sum queries in `O(1)`
- build and query a 2D prefix sum matrix
- apply many range increment updates with a difference array
- distinguish query-heavy problems from update-heavy problems

## 1D Prefix Sum

For an array `nums`, define:

```cpp
prefix[0] = 0
prefix[i + 1] = prefix[i] + nums[i]
```

Then the sum of the inclusive range `[left, right]` is:

```cpp
prefix[right + 1] - prefix[left]
```

This convention is useful because `prefix[0]` represents the empty prefix, so
queries starting at index `0` work without special cases.

Example:

- `nums = [2, 4, 1, 7, 3]`
- `prefix = [0, 2, 6, 7, 14, 17]`
- sum of `[1, 3]` is `prefix[4] - prefix[1] = 14 - 2 = 12`

## 2D Prefix Sum

For a matrix, build a prefix matrix with one extra row and one extra column.

For cell `(row, col)` in the original matrix:

```cpp
prefix[row + 1][col + 1] =
    matrix[row][col]
    + prefix[row][col + 1]
    + prefix[row + 1][col]
    - prefix[row][col]
```

The subtraction removes the top-left overlap that was counted twice.

For rectangle `(top, left)` to `(bottom, right)`, inclusive:

```cpp
prefix[bottom + 1][right + 1]
- prefix[top][right + 1]
- prefix[bottom + 1][left]
+ prefix[top][left]
```

## Difference Array

A difference array represents changes between neighboring values.

For range update `[left, right] += delta`:

```cpp
diff[left] += delta
diff[right + 1] -= delta
```

Then rebuild the final array by taking the running sum of `diff`.

Why it works:

- adding at `left` starts the effect
- subtracting after `right` stops the effect
- the running sum carries active updates forward

Use this when:

- there are many range updates
- you do not need to know every intermediate array state
- you only need the final values or a final feasibility check

## Prefix Sum vs Difference Array

Prefix sum:

- many range queries
- original data is mostly fixed
- query result is needed immediately

Difference array:

- many range updates
- final state matters
- individual update simulation would be too slow

## Common Bugs

- forgetting that `prefix` usually has length `n + 1`
- using `prefix[right] - prefix[left]` instead of `prefix[right + 1] - prefix[left]`
- mixing inclusive and exclusive range boundaries
- forgetting the overlap subtraction in 2D prefix sums
- forgetting to stop a range update at `right + 1`
- writing `diff[right + 1]` when `right + 1 == n` without allocating or checking

## How To Recognize This Topic

Ask these questions:

1. Do I repeatedly ask for sums over ranges?
2. Do I repeatedly add values over ranges?
3. Can preprocessing turn repeated work into a direct lookup or one final scan?

If yes, consider prefix sums or difference arrays.

## Practice Problems

Suggested order:

1. `Range Sum Query - Immutable` (303) [[link]](https://leetcode.com/submissions/detail/1985010691/)
2. `Pivot Index` (724) [[link]](https://leetcode.com/submissions/detail/1985016854/)
3. `Subarray Sum Equals K` (560) [[link]](https://leetcode.com/submissions/detail/1985824863/)
4. `Corporate Flight Bookings` (1109) [[link]](https://leetcode.com/submissions/detail/1985835110/)
5. `Car Pooling` (1094) [[link]](https://leetcode.com/submissions/detail/1985845346/)

## Completion Checklist

You are ready for the next topic when:

- you can derive the 1D range sum formula from the prefix definition
- you can explain the 2D overlap correction
- you can apply range updates without touching every element in the range
- you can identify whether a problem is query-heavy or update-heavy

## Mistake Log

Fill this section after solving problems.

- `Subarray Sum Equals K` (560): Find subarray sum equal `k` -> $sum[r]−sum[l−1]=k$ -> $sum[l−1]=sum[r]−k$ -> Using `hashmap` record exsiting $sum[l−1]$ count.
