# Hash Table, Strings, and Sorting

This topic focuses on lookup-based thinking. Hash tables let you remember
information from earlier elements so you do not repeatedly scan the same data.
Sorting lets you transform data into an order where grouping, comparison, or
greedy decisions become easier.

This topic has four main patterns:

- frequency counting
- deduplication and membership lookup
- grouping by a derived key
- sorting with a custom comparator

## Goals

After this topic, you should be able to:

- use `unordered_map` for counting and key-value lookup
- use `unordered_set` for membership and deduplication
- build stable grouping keys for string problems
- write custom comparators for `sort`
- choose between hash counting and sorting based on the problem shape

## Hash Map Counting

Use `unordered_map` when you need to count or remember information by key.

Common examples:

- character frequency
- number frequency
- first index of a value
- mapping a sorted string key to an anagram group

Typical pattern:

```cpp
unordered_map<char, int> count;
for (char c : text) {
    ++count[c];
}
```

For anagram checks, compare character counts. For grouping anagrams, sort each
word to build a key:

```cpp
string key = word;
sort(key.begin(), key.end());
groups[key].push_back(word);
```

## Hash Set Membership

Use `unordered_set` when you only care whether a value exists.

Common examples:

- remove duplicates
- detect repeated values
- test whether a sequence start exists
- avoid revisiting values

Example: in `Longest Consecutive Sequence`, store every value in a set. Only
start counting from a value `x` when `x - 1` does not exist. That guarantees each
sequence is counted from its first value.

## Sorting

Sorting is useful when:

- order reveals structure
- equal keys become adjacent
- you want the smallest, largest, or top values
- you need deterministic output

Default sort is ascending:

```cpp
sort(nums.begin(), nums.end());
```

Custom comparator example:

```cpp
sort(words.begin(), words.end(), [](const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
});
```

Comparator rule:

- return `true` only when the left value should come before the right value
- handle ties consistently
- do not write contradictory ordering rules

## Hashing vs Sorting

Use hashing when:

- you need fast average lookup
- order does not matter
- counting or membership is the main operation

Use sorting when:

- order matters
- adjacent equal/grouped values help
- you need deterministic ordered output
- a comparator naturally expresses the problem rule

Practical complexity:

- hash table operations are average `O(1)`
- sorting is usually `O(n log n)`
- hash tables can degrade in rare worst cases, but for LeetCode-style practice,
  focus first on average-case reasoning

## Common Bugs

- using `map[key]` when you only wanted to test existence, because it inserts a
  default value
- forgetting to decrement or erase counts when a window or state changes
- using an unordered container and expecting deterministic iteration order
- writing an invalid comparator that does not handle equal cases
- sorting a string key but accidentally grouping by the original string
- choosing sorting when a single hash pass would be simpler

## How To Recognize This Topic

Ask these questions:

1. Do I need to know whether a value appeared before?
2. Do I need counts by value or character?
3. Can I build a key that makes equivalent items share one bucket?
4. Would sorting make related items adjacent or easier to compare?

If yes, consider hash tables, string keys, or custom sorting.

## Practice Problems

Suggested order:

1. `Valid Anagram` (242) [[link]](https://leetcode.com/submissions/detail/1987503618/)
2. `Contains Duplicate` (217) [[link]](https://leetcode.com/submissions/detail/1987508113/)
3. `Group Anagrams` (49) [[link]](https://leetcode.com/submissions/detail/1987518933/)
4. `Longest Consecutive Sequence` (128) [[link]](https://leetcode.com/submissions/detail/1987525561/)
5. `Top K Frequent Elements` (347) [[link]](https://leetcode.com/submissions/detail/1987534158/)
6. `Custom Sort String` (791) [[link]](https://leetcode.com/submissions/detail/1987559277/)

## Completion Checklist

You are ready for the next topic when:

- you can choose between `unordered_map`, `unordered_set`, and sorting
- you can build a frequency table without mixing up keys and values
- you can group strings by a derived key
- you can write a custom comparator with clear tie-breaking

## Mistake Log

Fill this section after solving problems.

- 
