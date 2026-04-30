#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display a sequence in a readable format for binary search examples.
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

    // Print each element and separate neighbors with commas.
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
 * @brief Prints an index result with a label.
 *
 * Role:
 * - Show the output of a search routine in a consistent format.
 *
 * Input:
 * - `label`: Text printed before the index value.
 * - `index`: Search result index, or `-1` when not found.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintIndex(const std::string& label, int index) {
    // Print the label and the associated search result.
    std::cout << label << ": " << index << "\n";
}

/**
 * @brief Finds one exact occurrence of `target` in a sorted array.
 *
 * Role:
 * - Perform classic exact-match binary search on a sorted integer array.
 *
 * Input:
 * - `nums`: Sorted integer sequence.
 * - `target`: Value to search for.
 *
 * Output:
 * - Returns an index where `nums[index] == target`.
 * - Returns `-1` if the target is absent.
 */
int BinarySearchExact(const std::vector<int>& nums, int target) {
    // Handle the empty-input case early.
    if (nums.empty()) {
        return -1;
    }

    // Initialize the closed search interval [left, right].
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    // Shrink the range until the target is found or the interval is exhausted.
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Report failure after the interval becomes empty.
    return -1;
}

/**
 * @brief Finds the first index whose value is at least `target`.
 *
 * Role:
 * - Implement the lower-bound pattern using binary search on a sorted array.
 *
 * Input:
 * - `nums`: Sorted integer sequence.
 * - `target`: Threshold value.
 *
 * Output:
 * - Returns the first index `i` such that `nums[i] >= target`.
 * - Returns `nums.size()` if no such index exists.
 */
int LowerBoundIndex(const std::vector<int>& nums, int target) {
    // Initialize the closed search interval and the fallback answer.
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = static_cast<int>(nums.size());

    // Search for the earliest index satisfying the lower-bound condition.
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (nums[mid] >= target) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // Return the first valid position or the insertion position at the end.
    return answer;
}

/**
 * @brief Finds the first index whose value is greater than `target`.
 *
 * Role:
 * - Implement the upper-bound pattern using binary search on a sorted array.
 *
 * Input:
 * - `nums`: Sorted integer sequence.
 * - `target`: Threshold value.
 *
 * Output:
 * - Returns the first index `i` such that `nums[i] > target`.
 * - Returns `nums.size()` if no such index exists.
 */
int UpperBoundIndex(const std::vector<int>& nums, int target) {
    // Initialize the closed search interval and the fallback answer.
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = static_cast<int>(nums.size());

    // Search for the earliest index satisfying the upper-bound condition.
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // Return the first strictly greater position or the end position.
    return answer;
}

/**
 * @brief Finds the last occurrence of `target` in a sorted array.
 *
 * Role:
 * - Derive the last exact position from the upper-bound result.
 *
 * Input:
 * - `nums`: Sorted integer sequence.
 * - `target`: Value to search for.
 *
 * Output:
 * - Returns the last index where `nums[index] == target`.
 * - Returns `-1` if the target does not appear.
 */
int FindLastPosition(const std::vector<int>& nums, int target) {
    // Locate the first element greater than the target.
    const int first_greater = UpperBoundIndex(nums, target);
    const int candidate = first_greater - 1;

    // Validate that the candidate exists and matches the target exactly.
    if (candidate >= 0 && nums[candidate] == target) {
        return candidate;
    }

    // Report failure when the target does not occur.
    return -1;
}

/**
 * @brief Computes the total hours needed to eat all piles at a fixed speed.
 *
 * Role:
 * - Support answer-space binary search by evaluating whether a candidate speed
 *   is fast enough.
 *
 * Input:
 * - `piles`: Banana piles.
 * - `speed`: Bananas eaten per hour.
 *
 * Output:
 * - Returns the total number of hours required at the given speed.
 */
std::int64_t RequiredHoursForSpeed(const std::vector<int>& piles, int speed) {
    // Accumulate the time needed for each pile independently.
    std::int64_t total_hours = 0;

    // Use ceiling division because partial hours count as a full hour.
    for (int pile : piles) {
        total_hours += (pile + speed - 1) / speed;
    }

    // Return the full schedule cost for this speed.
    return total_hours;
}

/**
 * @brief Finds the minimum eating speed that finishes all piles in time.
 *
 * Role:
 * - Demonstrate answer-space binary search on a monotonic predicate.
 *
 * Input:
 * - `piles`: Banana piles.
 * - `hours`: Maximum number of hours allowed.
 *
 * Output:
 * - Returns the smallest integer speed that allows finishing within `hours`.
 */
int MinEatingSpeed(const std::vector<int>& piles, int hours) {
    // Define the answer range from the slowest to the fastest useful speed.
    int left = 1;
    int right = *std::max_element(piles.begin(), piles.end());
    int answer = right;

    // Search for the smallest speed whose required hours fit the budget.
    while (left <= right) {
        const int mid = left + (right - left) / 2;
        if (RequiredHoursForSpeed(piles, mid) <= hours) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // Return the smallest valid speed discovered during the search.
    return answer;
}

/**
 * @brief Demonstrates exact-match binary search.
 *
 * Role:
 * - Show how exact search returns a valid index or `-1`.
 *
 * Input:
 * - No external input. Uses a fixed sorted array and fixed targets.
 *
 * Output:
 * - No return value.
 * - Prints the array and two exact-search results.
 */
void DemoExactSearch() {
    // Prepare a sorted array for exact-match searching.
    const std::vector<int> nums = {1, 3, 5, 7, 9, 11};
    PrintVector("exact-search array", nums);

    // Search for one present target and one missing target.
    PrintIndex("index of 7", BinarySearchExact(nums, 7));
    PrintIndex("index of 6", BinarySearchExact(nums, 6));
}

/**
 * @brief Demonstrates left-boundary and right-boundary binary search.
 *
 * Role:
 * - Show how lower bound, upper bound, and last-position search differ.
 *
 * Input:
 * - No external input. Uses a fixed sorted array with duplicates.
 *
 * Output:
 * - No return value.
 * - Prints the array and several boundary-search results.
 */
void DemoBoundarySearch() {
    // Prepare a sorted array containing duplicate values.
    const std::vector<int> nums = {1, 2, 2, 2, 4, 6};
    PrintVector("boundary-search array", nums);

    // Show the first >= target, first > target, and last exact position.
    PrintIndex("first index >= 2", LowerBoundIndex(nums, 2));
    PrintIndex("first index > 2", UpperBoundIndex(nums, 2));
    PrintIndex("last index of 2", FindLastPosition(nums, 2));
    PrintIndex("insertion index for 3", LowerBoundIndex(nums, 3));
}

/**
 * @brief Demonstrates answer-space binary search with the Koko pattern.
 *
 * Role:
 * - Show how binary search can operate on candidate answers instead of indices.
 *
 * Input:
 * - No external input. Uses a fixed pile set and hour limit.
 *
 * Output:
 * - No return value.
 * - Prints the piles, time limit, and minimum valid speed.
 */
void DemoSearchOnAnswer() {
    // Prepare the example from the classic banana-eating problem.
    const std::vector<int> piles = {3, 6, 7, 11};
    const int hours = 8;
    PrintVector("banana piles", piles);

    // Search for the smallest speed that satisfies the hour constraint.
    std::cout << "hours limit: " << hours << "\n";
    std::cout << "minimum eating speed: " << MinEatingSpeed(piles, hours) << "\n";
}

} // namespace

/**
 * @brief Runs all demonstrations for the binary search topic.
 *
 * Role:
 * - Serve as the executable entrypoint for binary search examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints exact-search, boundary-search, and answer-search demonstrations.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 2: Binary Search\n\n";

    // Run the exact-match binary search demonstration.
    DemoExactSearch();
    std::cout << '\n';

    // Run the boundary-search demonstration.
    DemoBoundarySearch();
    std::cout << '\n';

    // Run the answer-space binary search demonstration.
    DemoSearchOnAnswer();
    return 0;
}
