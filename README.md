# Algorithm Learning Plan

This repository is for learning and practicing algorithms in a consistent order.

The working rule for every topic is:

1. Learn the idea and write knowledge notes in `docs/`.
2. Implement the core template and basic examples in `src/` with C++.
3. Practice representative LeetCode problems until the pattern feels natural.

At a steady pace, this roadmap is designed for roughly 12 to 16 weeks.

## Build And Tooling

This repository uses a lightweight C++ setup based on CMake and Ninja.

- Build system: `CMake`
- Presets: `CMakePresets.json`
- Formatting: `.clang-format`
- Linting: `.clang-tidy`
- Language standard: `C++17`
- Source layout: each `src/<topic>.cpp` file becomes its own executable target automatically

Common commands:

```bash
cmake --preset debug
cmake --build --preset debug
cmake --preset release
cmake --build --preset release
cmake --preset debug-tidy
cmake --build --preset debug-tidy
```

Notes:

- `compile_commands.json` is generated in the preset build directory for editor integration.
- If `src/` is empty, configure still succeeds and no executables are created yet.

## Standard Workflow For Every Topic

For each part of the roadmap, follow the same sequence:

1. `Knowledge`
   - Create or update one Markdown note under `docs/`.
   - Summarize definitions, core ideas, invariants, complexity, common bugs, and when to use the technique.
2. `Implementation`
   - Create one C++ file under `src/`.
   - Write the clean template first.
   - Add 1 to 2 small examples that show the technique in isolation.
3. `Practice`
   - Solve the suggested LeetCode problems.
   - Start with the easier pattern-recognition problems, then move to medium problems.
   - Record mistakes and insights back into the corresponding note in `docs/`.
4. `Completion`
   - Only move on when you can explain the pattern, write the template without searching, and solve at least one fresh problem independently.

## Study Rules

- Keep note files and code files aligned by topic name.
- Prefer short, clear templates over large personal libraries.
- Revisit earlier topics while studying later ones.
- If one topic still feels unstable, solve 2 more medium problems before moving on.
- Every 3 to 4 topics, spend one review session on mixed problems only.

## Roadmap Overview

| Part | Topic | Suggested Pace | Planned Note | Planned Code |
| --- | --- | --- | --- | --- |
| 1 | Foundations, complexity, arrays, STL | 1.5 weeks | `docs/foundations_arrays.md` | `src/foundations_arrays.cpp` |
| 2 | Binary search | 1 week | `docs/binary_search.md` | `src/binary_search.cpp` |
| 3 | Two pointers and sliding window | 1 week | `docs/two_pointers_sliding_window.md` | `src/two_pointers_sliding_window.cpp` |
| 4 | Prefix sums and difference arrays | 0.5 week | `docs/prefix_sum_difference.md` | `src/prefix_sum_difference.cpp` |
| 5 | Hash table, strings, sorting | 1 week | `docs/hash_string_sort.md` | `src/hash_string_sort.cpp` |
| 6 | Stack, queue, monotonic structures | 1 week | `docs/stack_queue_monotonic.md` | `src/stack_queue_monotonic.cpp` |
| 7 | Linked list, recursion, divide and conquer | 1 week | `docs/linked_list_recursion.md` | `src/linked_list_recursion.cpp` |
| 8 | Trees, BST, heap | 1.5 weeks | `docs/tree_bst_heap.md` | `src/tree_bst_heap.cpp` |
| 9 | Backtracking | 1 week | `docs/backtracking.md` | `src/backtracking.cpp` |
| 10 | Greedy | 1 week | `docs/greedy.md` | `src/greedy.cpp` |
| 11 | Graph traversal, topological sort, union-find | 1.5 weeks | `docs/graph_traversal_union_find.md` | `src/graph_traversal_union_find.cpp` |
| 12 | Shortest path algorithms | 1 week | `docs/shortest_path.md` | `src/shortest_path.cpp` |
| 13 | Dynamic programming foundations | 2 weeks | `docs/dynamic_programming_basic.md` | `src/dynamic_programming_basic.cpp` |
| 14 | Advanced dynamic programming | 1.5 weeks | `docs/dynamic_programming_advanced.md` | `src/dynamic_programming_advanced.cpp` |
| 15 | Advanced structures and bit techniques | 1.5 weeks | `docs/advanced_structures.md` | `src/advanced_structures.cpp` |

## 1. Foundations, Complexity, Arrays, STL

Build the base vocabulary and coding habits used by every later topic.

### Knowledge

- Planned note: `docs/foundations_arrays.md`
- Learn Big-O, common STL containers, array traversal patterns, indexing discipline, iterator basics, and sorting fundamentals.
- Focus on the cost of reading, writing, inserting, deleting, and sorting.
- Write down common off-by-one mistakes and how to avoid them.

### Implementation

- Planned code: `src/foundations_arrays.cpp`
- Implement:
  - array traversal patterns
  - prefix maximum or minimum example
  - sorting with default comparator and custom comparator
  - 1 to 2 tiny examples using `vector`, `sort`, and `reverse`

### Practice

- Target: 3 easy + 2 medium
- Suggested problems:
  - `Two Sum` (1)
  - `Remove Duplicates from Sorted Array` (26)
  - `Merge Sorted Array` (88)
  - `Sort Colors` (75)
  - `Squares of a Sorted Array` (977)

### Completion Standard

- You can explain time and space complexity for simple loops and nested loops.
- You can use `vector`, `pair`, `sort`, and basic STL utilities comfortably.
- You can write clean array code without index confusion.

## 2. Binary Search

This is the first classic algorithm pattern that should feel mechanical after practice.

### Knowledge

- Planned note: `docs/binary_search.md`
- Learn exact-match binary search, left boundary search, right boundary search, and answer-space binary search.
- Write down loop invariants, interval conventions, and why binary search works only under monotonic conditions.
- Record the most common bugs: wrong interval, wrong mid update, infinite loop.

### Implementation

- Planned code: `src/binary_search.cpp`
- Implement:
  - exact-match template
  - lower-bound style template
  - upper-bound or last-position template
  - search-on-answer template
  - 1 to 2 small examples

### Practice

- Target: 2 easy + 3 medium
- Suggested problems:
  - `Binary Search` (704)
  - `Search Insert Position` (35)
  - `Sqrt(x)` (69)
  - `Find First and Last Position of Element in Sorted Array` (34)
  - `Koko Eating Bananas` (875)

### Completion Standard

- You can write at least 3 binary search variants from memory.
- You can identify whether a problem is "search in array" or "search in answer space".
- You no longer debug binary search by trial and error.

## 3. Two Pointers And Sliding Window

This part teaches how to reduce brute-force scans into linear-time passes.

### Knowledge

- Planned note: `docs/two_pointers_sliding_window.md`
- Learn opposite-direction pointers, same-direction fast-slow pointers, and variable-size sliding windows.
- Understand when a window can expand and shrink monotonically.
- Summarize how sorted arrays and frequency tables often enable these patterns.

### Implementation

- Planned code: `src/two_pointers_sliding_window.cpp`
- Implement:
  - opposite-direction two-pointer template
  - fast-slow pointer template
  - variable-size sliding window template
  - 1 to 2 examples with string or array windows

### Practice

- Target: 2 easy + 4 medium
- Suggested problems:
  - `Valid Palindrome` (125)
  - `Move Zeroes` (283)
  - `Container With Most Water` (11)
  - `Longest Substring Without Repeating Characters` (3)
  - `Minimum Size Subarray Sum` (209)
  - `Longest Repeating Character Replacement` (424)

### Completion Standard

- You can tell whether a problem needs fixed-window or variable-window logic.
- You can maintain the window state without rescanning the whole interval.
- You can explain why the algorithm is linear.

## 4. Prefix Sums And Difference Arrays

This topic turns repeated range work into constant-time queries or efficient updates.

### Knowledge

- Planned note: `docs/prefix_sum_difference.md`
- Learn 1D prefix sums, 2D prefix sums, and difference arrays for batched range updates.
- Write down the standard formula for range sum queries and reconstruction from a difference array.
- Note the difference between preprocessing cost and query cost.

### Implementation

- Planned code: `src/prefix_sum_difference.cpp`
- Implement:
  - 1D prefix sum template
  - 2D prefix sum template
  - difference array template
  - 1 to 2 small examples with range query and range update

### Practice

- Target: 1 easy + 4 medium
- Suggested problems:
  - `Range Sum Query - Immutable` (303)
  - `Pivot Index` (724)
  - `Subarray Sum Equals K` (560)
  - `Corporate Flight Bookings` (1109)
  - `Car Pooling` (1094)

### Completion Standard

- You can derive the query formula instead of memorizing it blindly.
- You can recognize when repeated range operations should trigger a prefix-sum idea.
- You can separate query problems from update problems.

## 5. Hash Table, Strings, Sorting

This part strengthens lookup-based thinking and string processing basics.

### Knowledge

- Planned note: `docs/hash_string_sort.md`
- Learn `unordered_map`, `unordered_set`, counting, deduplication, grouping, and common string processing patterns.
- Review sorting by key, stable ordering, and custom comparator design.
- Record collision-related caveats only at a practical level; focus on problem-solving usage first.

### Implementation

- Planned code: `src/hash_string_sort.cpp`
- Implement:
  - frequency counting template
  - grouping-by-key example
  - custom sorting example
  - 1 to 2 string-processing examples

### Practice

- Target: 2 easy + 4 medium
- Suggested problems:
  - `Valid Anagram` (242)
  - `Contains Duplicate` (217)
  - `Group Anagrams` (49)
  - `Longest Consecutive Sequence` (128)
  - `Top K Frequent Elements` (347)
  - `Custom Sort String` (791)

### Completion Standard

- You can quickly choose between array counting, hash map counting, and sorting.
- You can use hash tables without mixing up keys, values, and update logic.
- You can solve common string counting problems in one pass.

## 6. Stack, Queue, Monotonic Structures

This part trains you to model order, next greater relationships, and window maxima.

### Knowledge

- Planned note: `docs/stack_queue_monotonic.md`
- Learn stack usage, queue usage, monotonic stack, and monotonic queue.
- Understand why monotonic structures preserve useful candidate states.
- Write down the "push once, pop once" amortized-time argument.

### Implementation

- Planned code: `src/stack_queue_monotonic.cpp`
- Implement:
  - basic stack and queue examples
  - monotonic increasing stack template
  - monotonic decreasing queue template
  - 1 to 2 examples such as next-greater and window maximum

### Practice

- Target: 2 easy + 4 medium
- Suggested problems:
  - `Valid Parentheses` (20)
  - `Min Stack` (155)
  - `Daily Temperatures` (739)
  - `Next Greater Element II` (503)
  - `Decode String` (394)
  - `Sliding Window Maximum` (239)

### Completion Standard

- You can explain why a monotonic stack solves "nearest greater/smaller" problems.
- You can identify when a queue is preserving order versus preserving candidates.
- You can implement these templates without mixing up indices and values.

## 7. Linked List, Recursion, Divide And Conquer

This topic focuses on pointer discipline and recursive problem decomposition.

### Knowledge

- Planned note: `docs/linked_list_recursion.md`
- Learn linked list traversal, reversal, merge patterns, recursive thinking, and divide-and-conquer structure.
- Summarize base case design, recurrence structure, and how to trust recursive subproblems.
- Write down the pointer mistakes that frequently break linked list code.

### Implementation

- Planned code: `src/linked_list_recursion.cpp`
- Implement:
  - reverse linked list
  - merge two sorted linked lists
  - recursive binary exponentiation
  - merge-sort style divide-and-conquer example

### Practice

- Target: 2 easy + 4 medium
- Suggested problems:
  - `Reverse Linked List` (206)
  - `Linked List Cycle` (141)
  - `Merge Two Sorted Lists` (21)
  - `Sort List` (148)
  - `Pow(x, n)` (50)
  - `Merge k Sorted Lists` (23)

### Completion Standard

- You can draw pointer movement before coding.
- You can write recursion with a clear base case and return value meaning.
- You can explain why divide and conquer reduces the problem correctly.

## 8. Trees, BST, Heap

This is the first large data-structure block and deserves extra time.

### Knowledge

- Planned note: `docs/tree_bst_heap.md`
- Learn DFS traversals, BFS traversals, binary search tree properties, heap usage, and tree recursion patterns.
- Understand preorder, inorder, postorder, level order, and the difference between tree recursion and graph traversal.
- Write down when a priority queue is the right tool.

### Implementation

- Planned code: `src/tree_bst_heap.cpp`
- Implement:
  - recursive DFS traversals
  - iterative BFS traversal
  - BST search and insert basics
  - min-heap and max-heap examples with `priority_queue`
  - 1 to 2 small tree examples

### Practice

- Target: 2 easy + 5 medium
- Suggested problems:
  - `Binary Tree Inorder Traversal` (94)
  - `Maximum Depth of Binary Tree` (104)
  - `Invert Binary Tree` (226)
  - `Validate Binary Search Tree` (98)
  - `Binary Tree Level Order Traversal` (102)
  - `Lowest Common Ancestor of a Binary Tree` (236)
  - `Kth Largest Element in an Array` (215)

### Completion Standard

- You can switch between traversal styles depending on the question.
- You can identify tree recursion states clearly.
- You can use heaps for repeated best-element extraction problems.

## 9. Backtracking

This part teaches systematic search over combinations, permutations, and constrained choices.

### Knowledge

- Planned note: `docs/backtracking.md`
- Learn the decision tree model, path state, choice list, pruning, and undo operations.
- Write down the difference between combination, permutation, subset, and constrained-search problems.
- Record how to avoid duplicates.

### Implementation

- Planned code: `src/backtracking.cpp`
- Implement:
  - subset template
  - permutation template
  - combination-sum style template
  - 1 example with pruning

### Practice

- Target: 1 easy + 5 medium/hard
- Suggested problems:
  - `Letter Combinations of a Phone Number` (17)
  - `Subsets` (78)
  - `Permutations` (46)
  - `Combination Sum` (39)
  - `Palindrome Partitioning` (131)
  - `N-Queens` (51)

### Completion Standard

- You can describe path, choices, and termination conditions before coding.
- You can add pruning without breaking correctness.
- You can tell whether duplicates should be skipped on the tree level or branch level.

## 10. Greedy

This topic trains proof-oriented thinking: local choice must support a global optimum.

### Knowledge

- Planned note: `docs/greedy.md`
- Learn common greedy forms: interval choice, local optimum, sorting-first greedy, and exchange arguments.
- Write down that greedy is not just "pick the biggest or smallest"; it needs a reason.
- Practice explaining the proof in plain language.

### Implementation

- Planned code: `src/greedy.cpp`
- Implement:
  - interval scheduling style example
  - sorting-first greedy example
  - jump-style reachability example
  - 1 to 2 minimal demonstrations

### Practice

- Target: 2 easy + 4 medium
- Suggested problems:
  - `Assign Cookies` (455)
  - `Best Time to Buy and Sell Stock II` (122)
  - `Jump Game` (55)
  - `Jump Game II` (45)
  - `Partition Labels` (763)
  - `Gas Station` (134)

### Completion Standard

- You can justify the greedy choice instead of relying on intuition alone.
- You can recognize when sorting enables a greedy decision.
- You can distinguish greedy problems from DP problems that only look greedy.

## 11. Graph Traversal, Topological Sort, Union-Find

This section introduces graph thinking without shortest-path complexity yet.

### Knowledge

- Planned note: `docs/graph_traversal_union_find.md`
- Learn graph representations, DFS, BFS, connected components, topological sorting, and disjoint set union.
- Summarize adjacency list representation and visited-state management.
- Write down when union-find is simpler than graph traversal.

### Implementation

- Planned code: `src/graph_traversal_union_find.cpp`
- Implement:
  - adjacency-list graph template
  - DFS and BFS traversal
  - topological sort with indegree
  - union-find with path compression and union by rank or size

### Practice

- Target: 1 easy + 5 medium
- Suggested problems:
  - `Find if Path Exists in Graph` (1971)
  - `Number of Islands` (200)
  - `Number of Provinces` (547)
  - `Course Schedule` (207)
  - `Clone Graph` (133)
  - `Redundant Connection` (684)

### Completion Standard

- You can model a problem as a graph instead of forcing an array pattern onto it.
- You can switch correctly between DFS, BFS, topological sort, and union-find.
- You can reason about visited states and component boundaries.

## 12. Shortest Path Algorithms

This part should come only after basic graph traversal is comfortable.

### Knowledge

- Planned note: `docs/shortest_path.md`
- Learn single-source shortest path ideas, BFS on unweighted graphs, Dijkstra on non-negative edges, and when Bellman-Ford style thinking is needed conceptually.
- Focus on priority-queue driven state expansion and distance relaxation.
- Record the assumptions each algorithm requires.

### Implementation

- Planned code: `src/shortest_path.cpp`
- Implement:
  - unweighted shortest path with BFS
  - Dijkstra template with priority queue
  - 1 weighted example
  - optional Bellman-Ford template as an extension note

### Practice

- Target: 4 medium
- Suggested problems:
  - `Network Delay Time` (743)
  - `Path With Minimum Effort` (1631)
  - `Cheapest Flights Within K Stops` (787)
  - `The Maze II` (505)

### Completion Standard

- You can identify whether the graph is weighted and whether edges are non-negative.
- You can explain what "relaxing an edge" means.
- You can write Dijkstra without mixing stale states and final distances.

## 13. Dynamic Programming Foundations

This is the most important long block in the roadmap and should not be rushed.

### Knowledge

- Planned note: `docs/dynamic_programming_basic.md`
- Learn how to define state, transition, base case, traversal order, and space optimization.
- Start with linear DP, staircase DP, house-robber style DP, grid DP, and 0/1 knapsack basics.
- Record the difference between recursion plus memoization and bottom-up DP.

### Implementation

- Planned code: `src/dynamic_programming_basic.cpp`
- Implement:
  - Fibonacci-style DP
  - house-robber style DP
  - grid DP
  - 0/1 knapsack template
  - example of rolling-array optimization

### Practice

- Target: 2 easy + 5 medium
- Suggested problems:
  - `Climbing Stairs` (70)
  - `Min Cost Climbing Stairs` (746)
  - `House Robber` (198)
  - `Unique Paths` (62)
  - `Partition Equal Subset Sum` (416)
  - `Coin Change` (322)
  - `Target Sum` (494)

### Completion Standard

- You can define the state before writing code.
- You can explain why the transition covers all cases without overlap mistakes.
- You can convert a memoized solution into a bottom-up table when needed.

## 14. Advanced Dynamic Programming

Study this only after the DP foundations start to feel repeatable.

### Knowledge

- Planned note: `docs/dynamic_programming_advanced.md`
- Learn sequence DP, LIS, LCS, interval DP, palindrome DP, and state-machine style DP.
- Focus on recognizing DP dimensions and iteration order.
- Write down why advanced DP still starts from state and transition, not from memorized formulas.

### Implementation

- Planned code: `src/dynamic_programming_advanced.cpp`
- Implement:
  - LIS template
  - LCS template
  - interval DP example
  - state-machine DP example

### Practice

- Target: 4 medium + 2 hard
- Suggested problems:
  - `Longest Increasing Subsequence` (300)
  - `Longest Common Subsequence` (1143)
  - `Edit Distance` (72)
  - `Longest Palindromic Subsequence` (516)
  - `Best Time to Buy and Sell Stock III` (123)
  - `Burst Balloons` (312)

### Completion Standard

- You can spot sequence DP and interval DP patterns from the problem structure.
- You can justify traversal order instead of copying it mechanically.
- You can keep state definitions simple and precise.

## 15. Advanced Structures And Bit Techniques

Finish the roadmap with tools that often appear in harder interview or contest-style problems.

### Knowledge

- Planned note: `docs/advanced_structures.md`
- Learn trie basics, Fenwick tree, segment tree intuition, bit manipulation tricks, and optional string-pattern tools such as KMP.
- Focus on the use cases first: prefix counts, dynamic range query/update, compact state representation, and fast pattern reuse.
- Record which techniques are core interview tools and which are optional extensions.

### Implementation

- Planned code: `src/advanced_structures.cpp`
- Implement:
  - basic trie
  - Fenwick tree
  - segment tree for range sum
  - several common bit tricks
  - optional KMP prefix-function example

### Practice

- Target: 3 medium + 2 hard
- Suggested problems:
  - `Implement Trie (Prefix Tree)` (208)
  - `Design Add and Search Words Data Structure` (211)
  - `Range Sum Query - Mutable` (307)
  - `Count of Smaller Numbers After Self` (315)
  - `Single Number III` (260)

### Completion Standard

- You can explain the problem type that requires each structure.
- You can implement the basic version before optimizing details.
- You know which of these tools are optional for now and which deserve repetition.

## Review And Progress Tracking

Use these rules while moving through the roadmap:

- After every topic, add a short "mistake log" section to the note in `docs/`.
- After every 3 topics, solve 3 mixed problems without looking at old code.
- After every 5 topics, rewrite one earlier template from scratch.
- If a topic took more than two full practice rounds to stabilize, mark it for a second pass later.

## Definition Of "Finished"

A topic is finished only when all of the following are true:

- The note in `docs/` explains the idea in your own words.
- The C++ file in `src/` contains the clean template and basic examples.
- You solved the target set of problems or an equivalent set.
- You can explain the common failure cases and how to debug them.

If you follow this plan from top to bottom, the repository will gradually grow into a complete personal algorithm handbook plus C++ template library.
