# Trees, BST, and Heap

This topic is the first larger data-structure block in the roadmap. Trees add a
branching structure instead of the linear structure used in arrays, linked
lists, stacks, and queues. Binary search trees add ordered search behavior, and
heaps add efficient repeated access to the current best element.

This topic has five main parts:

- recursive DFS traversals
- iterative BFS traversal
- tree recursion patterns
- BST search and insert
- min-heap and max-heap usage

## Goals

After this topic, you should be able to:

- tell preorder, inorder, postorder, and level-order traversal apart
- write recursive tree functions with clear subtree meaning
- explain why BFS uses a queue
- use BST ordering to search or insert efficiently
- recognize when `priority_queue` is the right tool

## Tree Basics

A binary tree node usually stores:

- a value
- a pointer to the left child
- a pointer to the right child

Key difference from linked lists:

- a linked list has one natural next step
- a tree splits into multiple recursive subproblems

Common tree tasks:

- traversal
- search
- depth or height computation
- path reasoning
- subtree combination

## DFS Traversals

Depth-first traversal explores down one branch before switching branches.

The three standard recursive DFS orders are:

- preorder: node, left, right
- inorder: left, node, right
- postorder: left, right, node

Meaning:

- preorder is useful when you want to process the current node before its children
- inorder is important for BSTs because it visits values in sorted order
- postorder is useful when you need child results before processing the current node

## BFS Traversal

Breadth-first traversal processes the tree level by level.

Use a queue:

1. push the root
2. pop nodes in FIFO order
3. push their children

This naturally matches level order because earlier nodes on the current level
enter the queue before nodes on the next level.

Common uses:

- level order traversal
- shortest path in an unweighted graph or tree
- per-level aggregation

## Tree Recursion Pattern

A recursive tree function should answer:

1. what does the function return for one subtree?
2. what is the base case for `nullptr`?
3. how are the left and right subtree results combined?

Examples:

- maximum depth
- subtree sum
- validate BST
- lowest common ancestor

If the return meaning is unclear, tree recursion becomes hard to debug.

## Binary Search Tree

BST rule:

- every value in the left subtree is smaller than the node value
- every value in the right subtree is larger than the node value

As a result:

- search goes left or right by comparison
- insertion follows the same rule
- inorder traversal of a BST is sorted

This topic focuses on the basic operations:

- search for a value
- insert a value
- verify the sorted inorder result

## Heap

A heap is often used through `priority_queue`.

Max-heap:

- largest element comes out first
- default `priority_queue<int>`

Min-heap:

- smallest element comes out first
- use `priority_queue<int, vector<int>, greater<int>>`

Use a heap when:

- you repeatedly need the current largest or smallest element
- you want top-`k`
- sorting everything would be unnecessary or too expensive

## Traversal Summary

Preorder:

- node first
- often used for "process current node before children"

Inorder:

- left, node, right
- sorted order for BSTs

Postorder:

- children first
- useful when parent work depends on child results

Level order:

- level by level
- queue-based BFS

## Common Bugs

- forgetting the `nullptr` base case in recursion
- mixing traversal order and getting the wrong result shape
- treating tree recursion like linear iteration
- forgetting that BST logic depends on ordering, not just traversal
- using a heap when a sorted array or direct scan would be simpler
- expecting heap output to be fully sorted without repeated pops

## How To Recognize This Topic

Ask these questions:

1. Does each state branch into left and right child problems?
2. Does level-by-level processing matter?
3. Can ordering properties guide search or insertion?
4. Do I repeatedly need the largest or smallest available element?

If yes, think about trees, BSTs, BFS, or heaps.

## Practice Problems

Suggested order:

1. `Binary Tree Inorder Traversal` (94)
2. `Maximum Depth of Binary Tree` (104)
3. `Invert Binary Tree` (226)
4. `Binary Tree Level Order Traversal` (102)
5. `Validate Binary Search Tree` (98)
6. `Lowest Common Ancestor of a Binary Tree` (236)
7. `Kth Largest Element in an Array` (215)

## Completion Checklist

You are ready for the next topic when:

- you can switch correctly between preorder, inorder, postorder, and level order
- you can explain what a recursive tree function returns for each subtree
- you understand why BST inorder traversal is sorted
- you can choose between direct sorting and heap extraction for repeated best-element problems

## Mistake Log

Fill this section after solving problems.

- Example: I wrote the recursive calls in the wrong order and thought I was doing
  inorder traversal while actually doing preorder; I fixed it by writing the
  intended visit order in words before coding.
