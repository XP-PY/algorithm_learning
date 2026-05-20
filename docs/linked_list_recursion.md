# Linked List, Recursion, and Divide and Conquer

This topic combines three closely related ideas:

- linked lists require careful pointer updates
- recursion solves a problem by trusting smaller subproblems
- divide and conquer splits a problem, solves each part, and merges the results

These patterns often appear together. For example, linked-list merge sort uses
pointer handling, recursion, and divide-and-conquer structure at the same time.

## Goals

After this topic, you should be able to:

- traverse and modify a singly linked list safely
- reverse a linked list without losing nodes
- merge two sorted linked lists
- write recursion with a clear base case and return meaning
- explain why merge sort is a divide-and-conquer algorithm

## Linked List Basics

A linked list node stores:

- a value
- a pointer to the next node

Unlike arrays:

- nodes are not contiguous in memory
- you cannot jump directly to the `k`-th element in `O(1)`
- pointer updates are more important than index arithmetic

Common linked-list tasks:

- traversal
- reversal
- merging
- finding the middle
- detecting cycles

## Traversal

The basic pattern is:

```cpp
ListNode* current = head;
while (current != nullptr) {
    // use current->value
    current = current->next;
}
```

Important rule:

- save any pointer you still need before changing links

## Reversal

The standard iterative reverse keeps three ideas:

- `previous`: already reversed part
- `current`: node being processed now
- `next_node`: saved pointer to the remaining unreversed part

Pattern:

```cpp
ListNode* previous = nullptr;
ListNode* current = head;
while (current != nullptr) {
    ListNode* next_node = current->next;
    current->next = previous;
    previous = current;
    current = next_node;
}
```

At the end, `previous` is the new head.

## Merge Two Sorted Lists

When two linked lists are already sorted, always connect the smaller current
node first.

Two common approaches:

- iterative merge with a dummy head
- recursive merge

This topic uses recursive merge as a good recursion example:

- base case: one list is empty
- recursive step: connect the smaller head to the merged remainder

## Recursion

A recursive function should answer three questions clearly:

1. What is the function trying to return?
2. What is the smallest subproblem, the base case?
3. How does the current case reduce to a smaller case?

Example: binary exponentiation for `x^n`

- if `n == 0`, return `1`
- recursively compute `x^(n/2)`
- square the half result
- multiply by one more `x` when `n` is odd

This reduces the problem size from `n` to `n / 2`, so the recursion depth is
`O(log n)`.

## Divide and Conquer

Divide and conquer has three parts:

1. divide the problem into smaller subproblems
2. solve each subproblem
3. combine the answers

Merge sort is the classic example:

- split the array into two halves
- sort each half recursively
- merge the two sorted halves

Why it works:

- each half becomes easier to solve
- the merge step restores the full sorted order

## Common Bugs

- losing the rest of a linked list because `next` was overwritten too early
- forgetting the base case in recursion
- not knowing what the recursive function is supposed to return
- using recursion where the subproblem size does not actually shrink
- merging two sorted structures but forgetting tie handling
- splitting a divide-and-conquer range incorrectly and causing infinite recursion

## How To Recognize This Topic

Ask these questions:

1. Does the structure naturally point from one node to the next?
2. Can the problem be described as "solve a smaller version of the same task"?
3. Can I split the input into smaller pieces and combine the answers?

If yes, linked-list, recursion, or divide-and-conquer thinking is probably needed.

## Practice Problems

Suggested order:

1. `Reverse Linked List` (206) [[link]](https://leetcode.com/submissions/detail/2006860173/)
2. `Linked List Cycle` (141) [[link]](https://leetcode.com/submissions/detail/2006865581/)
3. `Merge Two Sorted Lists` (21) [[link]](https://leetcode.com/submissions/detail/2006871785/)
4. `Pow(x, n)` (50) [[link]](https://leetcode.com/submissions/detail/2006879030/)
5. `Sort List` (148) [[link]](https://leetcode.com/submissions/detail/2006889706/)
6. `Merge k Sorted Lists` (23) [[link]]()

## Completion Checklist

You are ready for the next topic when:

- you can draw pointer movement before coding a linked-list edit
- you can state the base case and return meaning of a recursive function
- you can explain why binary exponentiation is `O(log n)`
- you can explain the split-solve-merge structure of divide and conquer

## Mistake Log

Fill this section after solving problems.

- `Pow(x, n)` (50): Using the binary search approach greatly reduces the number of recursive calls.
- `Sort List` (148): Merge sort, O(n log n), instead of bubble sort, O(n²), for single linked list sotring.
