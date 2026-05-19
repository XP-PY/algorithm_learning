# Stack, Queue, and Monotonic Structures

This topic is about ordered processing. A stack processes the most recent item
first, while a queue processes the earliest item first. Monotonic stacks and
queues add an extra rule: they keep only candidates that are still useful for
future answers.

This topic has four main parts:

- basic stack usage
- basic queue usage
- monotonic stack
- monotonic queue

## Goals

After this topic, you should be able to:

- choose between stack and queue based on processing order
- use a stack for matching, undoing, or nearest-greater/smaller problems
- use a queue for FIFO processing
- understand why monotonic structures often run in linear time
- distinguish between preserving full order and preserving only useful candidates

## Stack

A stack is Last In, First Out.

Common uses:

- bracket matching
- expression parsing
- recursive-state simulation
- nearest greater or smaller element problems

Basic operations:

```cpp
stack<int> st;
st.push(x);
st.top();
st.pop();
st.empty();
```

Example:

- `Valid Parentheses` (20)

## Queue

A queue is First In, First Out.

Common uses:

- task processing
- level-order traversal
- breadth-first search
- maintaining elements in arrival order

Basic operations:

```cpp
queue<int> q;
q.push(x);
q.front();
q.pop();
q.empty();
```

## Monotonic Stack

A monotonic stack keeps elements in increasing or decreasing order.

Use it for problems such as:

- next greater element
- next smaller element
- previous greater/smaller element
- daily temperatures

Typical decreasing-stack idea for "next greater":

- while the current value is greater than the stack top's value, the current
  value answers the stack top
- pop answered indices
- push the current index

Important detail:

- store indices when you need both values and positions

Why it is `O(n)`:

- each index is pushed once
- each index is popped once

## Monotonic Queue

A monotonic queue is usually implemented with `deque`.

Use it for problems such as:

- sliding window maximum
- sliding window minimum
- window candidate maintenance

Typical decreasing-queue idea for window maximum:

1. remove indices that are outside the window
2. remove smaller values from the back because they can never become the maximum
3. push the current index
4. the front is the maximum candidate

This structure preserves useful candidates, not every element in strict arrival
order.

## Stack vs Queue vs Monotonic Structures

Stack:

- most recent item first
- nested structure
- nearest previous unresolved item

Queue:

- earliest item first
- processing by arrival order

Monotonic stack:

- unresolved candidates with an order constraint
- often answers nearest greater/smaller questions

Monotonic queue:

- window candidates with an order constraint
- often answers max/min over a moving window

## Common Bugs

- pushing values when the problem needs indices
- forgetting to check `empty()` before `top()` or `front()`
- using a stack when the problem is really FIFO
- forgetting to remove expired indices from a monotonic queue
- maintaining the wrong monotonic direction
- mixing up "preserve order" and "preserve only useful candidates"

## How To Recognize This Topic

Ask these questions:

1. Do I need the newest unresolved item first?
2. Do I need the oldest waiting item first?
3. Am I looking for nearest greater/smaller relationships?
4. Do I need the max/min over every sliding window?

If yes, stack, queue, monotonic stack, or monotonic queue is likely involved.

## Practice Problems

Suggested order:

1. `Valid Parentheses` (20) [[link]](https://leetcode.com/submissions/detail/1989083149/)
2. `Min Stack` (155) [[link]](https://leetcode.com/submissions/detail/1989109370/)
3. `Daily Temperatures` (739) [[link]](https://leetcode.com/submissions/detail/1989131112/)
4. `Next Greater Element II` (503) [[link]](https://leetcode.com/submissions/detail/1989885312/)
5. `Decode String` (394) [[link]](https://leetcode.com/submissions/detail/1989915714/)
6. `Sliding Window Maximum` (239) [[link]](https://leetcode.com/submissions/detail/1989941954/)

## Completion Checklist

You are ready for the next topic when:

- you can explain why a monotonic stack solves nearest greater/smaller problems
- you can explain why a monotonic queue solves sliding window max/min problems
- you know when to store indices instead of values
- you can justify the linear-time push-once, pop-once argument

## Mistake Log

Fill this section after solving problems.

- 
