#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {

using NamedValue = std::pair<std::string, int>;

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display a sequence in a readable `[a, b, c]` format for demonstrations.
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

    // Print each element and insert commas between neighbors.
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
 * @brief Prints `(name, value)` pairs with a label.
 *
 * Role:
 * - Show the ordering of named values before and after custom sorting.
 *
 * Input:
 * - `label`: Text printed before the pair list.
 * - `items`: Pair sequence to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintPairs(const std::string& label, const std::vector<NamedValue>& items) {
    // Print the label and start the bracketed pair list.
    std::cout << label << ": [";

    // Print each pair and keep the output comma-separated.
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::cout << "(" << items[i].first << ", " << items[i].second << ")";
        if (i + 1 != items.size()) {
            std::cout << ", ";
        }
    }

    // Close the pair list and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Builds the prefix maximum array of an integer sequence.
 *
 * Role:
 * - Precompute, for every index `i`, the maximum value seen from `0` to `i`.
 *
 * Input:
 * - `nums`: Source integer sequence.
 *
 * Output:
 * - Returns a vector where `result[i]` equals `max(nums[0..i])`.
 * - Returns an empty vector when the input is empty.
 */
std::vector<int> BuildPrefixMax(const std::vector<int>& nums) {
    // Allocate the result with the same size as the input.
    std::vector<int> prefix_max(nums.size());

    // Handle the empty-input case early.
    if (nums.empty()) {
        return prefix_max;
    }

    // Seed the first prefix value with the first input element.
    prefix_max[0] = nums[0];

    // Extend the running maximum from left to right.
    for (std::size_t i = 1; i < nums.size(); ++i) {
        prefix_max[i] = std::max(prefix_max[i - 1], nums[i]);
    }

    // Return the completed prefix maximum array.
    return prefix_max;
}

/**
 * @brief Demonstrates array traversal and prefix maximum preprocessing.
 *
 * Role:
 * - Show a basic array example, compute its prefix maximum array, and print a
 *   left-to-right traversal.
 *
 * Input:
 * - No external input. Uses a fixed demo array.
 *
 * Output:
 * - No return value.
 * - Prints the original array, prefix maximum array, and traversal order.
 */
void DemoTraversalAndPrefixMax() {
    // Prepare a small sample array for the demo.
    const std::vector<int> nums = {3, 1, 5, 2, 4};
    PrintVector("original", nums);

    // Build and display the prefix maximum preprocessing result.
    const std::vector<int> prefix_max = BuildPrefixMax(nums);
    PrintVector("prefix_max", prefix_max);

    // Show the simplest left-to-right traversal pattern.
    std::cout << "left-to-right traversal:";
    for (int value : nums) {
        std::cout << ' ' << value;
    }
    std::cout << "\n";
}

/**
 * @brief Demonstrates default sorting and reversing on integers.
 *
 * Role:
 * - Show how `sort` produces ascending order and `reverse` flips the order.
 *
 * Input:
 * - No external input. Uses a fixed demo array.
 *
 * Output:
 * - No return value.
 * - Prints the array before sorting, after sorting, and after reversing.
 */
void DemoSortAndReverse() {
    // Prepare an unsorted integer array.
    std::vector<int> nums = {4, 1, 7, 3, 9, 2};
    PrintVector("before sort", nums);

    // Apply the default ascending sort.
    std::sort(nums.begin(), nums.end());
    PrintVector("after ascending sort", nums);

    // Reverse the sorted range to show descending order quickly.
    std::reverse(nums.begin(), nums.end());
    PrintVector("after reverse", nums);
}

/**
 * @brief Demonstrates sorting with a custom comparator.
 *
 * Role:
 * - Sort `(name, score)` pairs by score descending, then by name ascending.
 *
 * Input:
 * - No external input. Uses a fixed demo vector of pairs.
 *
 * Output:
 * - No return value.
 * - Prints the pairs before and after the custom ordering.
 */
void DemoCustomComparator() {
    // Prepare named values to sort with custom rules.
    std::vector<NamedValue> items = {
        {"pear", 2},
        {"apple", 5},
        {"banana", 5},
        {"grape", 1},
    };
    PrintPairs("before custom sort", items);

    // Sort by higher score first, then by lexicographically smaller name.
    std::sort(items.begin(), items.end(), [](const NamedValue& left, const NamedValue& right) {
        if (left.second != right.second) {
            return left.second > right.second;
        }
        return left.first < right.first;
    });

    // Show the final custom-ordered sequence.
    PrintPairs("after custom sort", items);
}

} // namespace

/**
 * @brief Runs all demonstrations for the first algorithm topic.
 *
 * Role:
 * - Serve as the executable entrypoint for the foundations and arrays examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints three small demonstrations to standard output.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 1: Foundations, Arrays, and STL\n\n";

    // Run the traversal and prefix maximum example.
    DemoTraversalAndPrefixMax();
    std::cout << '\n';

    // Run the sorting and reverse example.
    DemoSortAndReverse();
    std::cout << '\n';

    // Run the custom comparator example.
    DemoCustomComparator();
    return 0;
}
