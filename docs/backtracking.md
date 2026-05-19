# Backtracking

Backtracking is structured search over a decision tree. At each step, you make
a choice, continue exploring, and then undo that choice before trying the next
option.

This topic has four main ideas:

- path
- choice list
- termination condition
- pruning

## Goals

After this topic, you should be able to:

- describe a problem as a search tree
- distinguish subsets, permutations, and combinations
- write recursive search with choose-explore-undo structure
- add pruning without breaking correctness
- reason about when duplicate handling is needed

## Core Model

Backtracking usually tracks:

- `path`: the partial answer built so far
- `choices`: what can be chosen next
- `end condition`: when one complete answer is ready

Typical skeleton:

```cpp
void Dfs(...) {
    if (end_condition) {
        save_answer(path);
        return;
    }

    for (choice in choices) {
        make_choice(choice);
        Dfs(...);
        undo_choice(choice);
    }
}
```

The undo step is what makes backtracking different from just building one path.

## Subsets

Subset problems ask:

- for every element, take it or skip it

Common pattern:

- move by index from left to right
- save the current `path` at each recursion level

This works because every partial path is already a valid subset.

Example:

- `Subsets` (78)

## Permutations

Permutation problems ask:

- arrange all elements in different orders

Common pattern:

- the `path` length tells how many positions are filled
- a `used` array marks which elements are already chosen

Example:

- `Permutations` (46)

## Combination Sum Style Search

Combination-style search usually means:

- choose values in nondecreasing index order
- reuse or skip candidates based on the problem rule

For `Combination Sum`:

- candidates are often sorted first
- if `candidate > remaining_target`, stop the loop early
- staying at the same index allows reuse of the current candidate

That early stop is a pruning rule.

## Pruning

Pruning means stopping branches that cannot lead to a valid answer.

Good pruning examples:

- remaining target is already negative
- the sorted candidate is larger than the remaining target
- a duplicate choice at the same tree level would repeat work

Important rule:

- prune only when you can justify that the entire branch is impossible or redundant

## Subset vs Permutation vs Combination

Subset:

- order does not matter
- every recursion level often decides include or exclude

Permutation:

- order matters
- each recursion level chooses the next position value

Combination:

- order does not matter
- often use a start index so earlier choices are not reused in a different order

## Common Bugs

- forgetting the undo step after recursion returns
- saving the same mutable `path` object instead of a copy
- using the wrong start index and generating duplicate combinations
- forgetting the `used` array in permutation problems
- pruning too aggressively and missing valid answers
- not sorting candidates before using sorted-order pruning

## How To Recognize This Topic

Ask these questions:

1. Am I trying many possible choices rather than following one deterministic path?
2. Does the problem naturally form a tree of decisions?
3. Do I need to enumerate all valid answers or search all feasible possibilities?

If yes, backtracking is likely the right tool.

## Practice Problems

Suggested order:

1. `Letter Combinations of a Phone Number` (17)
2. `Subsets` (78)
3. `Permutations` (46)
4. `Combination Sum` (39)
5. `Palindrome Partitioning` (131)
6. `N-Queens` (51)

## Completion Checklist

You are ready for the next topic when:

- you can explain path, choices, and termination before coding
- you can choose between start-index control and used-array control
- you can justify a pruning rule clearly
- you can tell whether duplicates should be removed by tree-level skipping or by state design

## Mistake Log

Fill this section after solving problems.

- 
