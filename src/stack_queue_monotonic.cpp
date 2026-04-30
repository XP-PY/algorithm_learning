#include <climits>
#include <cstddef>
#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace {

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display array-based results for stack and queue demonstrations.
 *
 * Input:
 * - `label`: Text printed before the vector contents.
 * - `nums`: Integer sequence to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintVector(const std::string& label, const std::vector<int>& nums) {
    // Print the label and start the bracketed sequence.
    std::cout << label << ": [";

    // Print each value with comma separators.
    for (std::size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i];
        if (i + 1 != nums.size()) {
            std::cout << ", ";
        }
    }

    // Close the sequence and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Drains a stack into a vector in pop order.
 *
 * Role:
 * - Show the Last-In-First-Out behavior of a stack.
 *
 * Input:
 * - `values`: Stack copied by value so the original demo object stays unchanged.
 *
 * Output:
 * - Returns the popped values in the order they leave the stack.
 */
std::vector<int> DrainStack(std::stack<int> values) {
    // Pop every element from top to bottom.
    std::vector<int> popped;
    while (!values.empty()) {
        popped.push_back(values.top());
        values.pop();
    }

    // Return the LIFO pop order.
    return popped;
}

/**
 * @brief Drains a queue into a vector in pop order.
 *
 * Role:
 * - Show the First-In-First-Out behavior of a queue.
 *
 * Input:
 * - `values`: Queue copied by value so the original demo object stays unchanged.
 *
 * Output:
 * - Returns the popped values in the order they leave the queue.
 */
std::vector<int> DrainQueue(std::queue<int> values) {
    // Pop every element from front to back.
    std::vector<int> popped;
    while (!values.empty()) {
        popped.push_back(values.front());
        values.pop();
    }

    // Return the FIFO pop order.
    return popped;
}

/**
 * @brief Checks whether a bracket string is valid.
 *
 * Role:
 * - Demonstrate stack-based matching for nested symbols.
 *
 * Input:
 * - `text`: String containing only bracket-like characters.
 *
 * Output:
 * - Returns `true` if every opening bracket is matched in the correct order.
 * - Returns `false` otherwise.
 */
bool IsValidParentheses(const std::string& text) {
    // Track unmatched opening brackets.
    std::stack<char> openings;

    // Process each character and match closing brackets immediately.
    for (char c : text) {
        if (c == '(' || c == '[' || c == '{') {
            openings.push(c);
            continue;
        }

        if (openings.empty()) {
            return false;
        }

        const char top = openings.top();
        if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
            return false;
        }
        openings.pop();
    }

    // A valid string leaves no unmatched openings behind.
    return openings.empty();
}

/**
 * @brief Computes waiting days for a warmer temperature.
 *
 * Role:
 * - Demonstrate a monotonic decreasing stack of indices.
 *
 * Input:
 * - `temperatures`: Daily temperatures.
 *
 * Output:
 * - Returns a vector where each position stores how many days until a warmer temperature.
 * - Returns `0` for days with no warmer future temperature.
 */
std::vector<int> DailyTemperatures(const std::vector<int>& temperatures) {
    // Prepare the answer array and a stack of unresolved day indices.
    std::vector<int> wait_days(temperatures.size(), 0);
    std::stack<int> indices;

    // Resolve previous colder days whenever the current day is warmer.
    for (int i = 0; i < static_cast<int>(temperatures.size()); ++i) {
        while (!indices.empty() && temperatures[i] > temperatures[indices.top()]) {
            const int previous = indices.top();
            indices.pop();
            wait_days[static_cast<std::size_t>(previous)] = i - previous;
        }

        // Push the current unresolved day.
        indices.push(i);
    }

    // Unresolved days keep the default answer of zero.
    return wait_days;
}

/**
 * @brief Computes the maximum value for every sliding window of size `k`.
 *
 * Role:
 * - Demonstrate a monotonic decreasing queue of indices.
 *
 * Input:
 * - `nums`: Source integer array.
 * - `k`: Sliding window size.
 *
 * Output:
 * - Returns the maximum value in each consecutive window of length `k`.
 */
std::vector<int> SlidingWindowMaximum(const std::vector<int>& nums, int k) {
    // Maintain candidate indices in decreasing-value order.
    std::deque<int> candidates;
    std::vector<int> maxima;

    // Expand the right boundary one step at a time.
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        // Remove indices that already left the window.
        while (!candidates.empty() && candidates.front() <= right - k) {
            candidates.pop_front();
        }

        // Remove smaller values that can never become the maximum again.
        while (!candidates.empty() && nums[candidates.back()] <= nums[right]) {
            candidates.pop_back();
        }

        // Add the current index as a new candidate.
        candidates.push_back(right);

        // Record the maximum once the first full window is formed.
        if (right >= k - 1) {
            maxima.push_back(nums[candidates.front()]);
        }
    }

    // Return the maximum for each window.
    return maxima;
}

/**
 * @brief Demonstrates basic stack and queue behavior.
 *
 * Role:
 * - Show the difference between LIFO and FIFO processing order.
 *
 * Input:
 * - No external input. Uses fixed demo values.
 *
 * Output:
 * - No return value.
 * - Prints the pop order of a stack and a queue built from the same values.
 */
void DemoBasicStackAndQueue() {
    // Push the same values into a stack and a queue.
    std::stack<int> stack_values;
    std::queue<int> queue_values;
    for (int value : {1, 2, 3, 4}) {
        stack_values.push(value);
        queue_values.push(value);
    }

    // Drain both containers to reveal their processing order.
    PrintVector("stack pop order", DrainStack(stack_values));
    PrintVector("queue pop order", DrainQueue(queue_values));

    // Show a bracket-matching example that naturally uses a stack.
    std::cout << "\"([]{})\" is valid: " << (IsValidParentheses("([]{})") ? "true" : "false")
              << "\n";
    std::cout << "\"([)]\" is valid: " << (IsValidParentheses("([)]") ? "true" : "false") << "\n";
}

/**
 * @brief Demonstrates a monotonic stack with daily temperatures.
 *
 * Role:
 * - Show how unresolved indices wait for the next greater value.
 *
 * Input:
 * - No external input. Uses a fixed temperature array.
 *
 * Output:
 * - No return value.
 * - Prints the temperatures and the waiting-day answer array.
 */
void DemoMonotonicStack() {
    // Prepare the classic daily temperatures example.
    const std::vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    PrintVector("temperatures", temperatures);

    // Compute how many days each index waits for a warmer day.
    PrintVector("warmer-day waits", DailyTemperatures(temperatures));
}

/**
 * @brief Demonstrates a monotonic queue with sliding window maximum.
 *
 * Role:
 * - Show how a deque preserves only useful maximum candidates.
 *
 * Input:
 * - No external input. Uses a fixed integer array and window size.
 *
 * Output:
 * - No return value.
 * - Prints the source array and each sliding-window maximum.
 */
void DemoMonotonicQueue() {
    // Prepare a standard sliding-window maximum example.
    const std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    const int k = 3;
    PrintVector("window array", nums);
    std::cout << "window size: " << k << "\n";

    // Compute the maximum value for every window.
    PrintVector("window maxima", SlidingWindowMaximum(nums, k));
}

} // namespace

/**
 * @brief Runs all demonstrations for stack, queue, and monotonic structures.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints stack, queue, monotonic-stack, and monotonic-queue demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 6: Stack, Queue, and Monotonic Structures\n\n";

    // Run the basic stack and queue demonstration.
    DemoBasicStackAndQueue();
    std::cout << '\n';

    // Run the monotonic stack demonstration.
    DemoMonotonicStack();
    std::cout << '\n';

    // Run the monotonic queue demonstration.
    DemoMonotonicQueue();
    return 0;
}
