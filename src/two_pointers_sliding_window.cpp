#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display a sequence in a readable format for two-pointer demonstrations.
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
 * @brief Checks whether a string is a palindrome with two pointers.
 *
 * Role:
 * - Demonstrate opposite-direction pointers while skipping non-alphanumeric
 *   characters and ignoring case.
 *
 * Input:
 * - `text`: Source string to test.
 *
 * Output:
 * - Returns `true` if the normalized string is a palindrome.
 * - Returns `false` otherwise.
 */
bool IsPalindromeIgnoringNonAlnum(const std::string& text) {
    // Initialize the two pointers at both ends of the string.
    int left = 0;
    int right = static_cast<int>(text.size()) - 1;

    // Move inward until the pointers cross or a mismatch appears.
    while (left < right) {
        while (left < right && !std::isalnum(static_cast<unsigned char>(text[left]))) {
            ++left;
        }
        while (left < right && !std::isalnum(static_cast<unsigned char>(text[right]))) {
            --right;
        }

        const char left_char =
            static_cast<char>(std::tolower(static_cast<unsigned char>(text[left])));
        const char right_char =
            static_cast<char>(std::tolower(static_cast<unsigned char>(text[right])));
        if (left_char != right_char) {
            return false;
        }

        ++left;
        --right;
    }

    // Report success after every mirrored pair matches.
    return true;
}

/**
 * @brief Moves all zeroes to the end while preserving non-zero order.
 *
 * Role:
 * - Demonstrate the fast-slow pointer pattern for in-place stable compaction.
 *
 * Input:
 * - `nums`: Integer sequence modified in place.
 *
 * Output:
 * - No return value.
 * - Reorders `nums` so non-zero values appear first and zeroes move to the end.
 */
void MoveZeroes(std::vector<int>* nums) {
    // Track the next position where a non-zero value should be written.
    int slow = 0;

    // Copy each non-zero value forward in original order.
    for (int fast = 0; fast < static_cast<int>(nums->size()); ++fast) {
        if ((*nums)[fast] != 0) {
            (*nums)[slow] = (*nums)[fast];
            ++slow;
        }
    }

    // Fill the remaining suffix with zeroes.
    while (slow < static_cast<int>(nums->size())) {
        (*nums)[slow] = 0;
        ++slow;
    }
}

/**
 * @brief Finds the minimum length of a subarray with sum at least `target`.
 *
 * Role:
 * - Demonstrate a variable-size sliding window on positive integers.
 *
 * Input:
 * - `target`: Required minimum subarray sum.
 * - `nums`: Positive integer array.
 *
 * Output:
 * - Returns the minimum valid window length.
 * - Returns `0` if no subarray reaches the target sum.
 */
int MinSubarrayLenAtLeastTarget(int target, const std::vector<int>& nums) {
    // Initialize the sliding window state and fallback answer.
    int left = 0;
    int current_sum = 0;
    int answer = static_cast<int>(nums.size()) + 1;

    // Expand the right boundary one step at a time.
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        current_sum += nums[right];

        // Shrink the left boundary while the window already satisfies the goal.
        while (current_sum >= target) {
            answer = std::min(answer, right - left + 1);
            current_sum -= nums[left];
            ++left;
        }
    }

    // Convert the sentinel answer into the standard "not found" result.
    if (answer == static_cast<int>(nums.size()) + 1) {
        return 0;
    }
    return answer;
}

/**
 * @brief Finds the length of the longest substring without repeated characters.
 *
 * Role:
 * - Demonstrate sliding window with frequency tracking on a string.
 *
 * Input:
 * - `text`: Source string to analyze.
 *
 * Output:
 * - Returns the maximum length of a substring with all distinct characters.
 */
int LongestUniqueSubstringLength(const std::string& text) {
    // Store character frequencies for the current window.
    std::vector<int> frequency(256, 0);
    int left = 0;
    int answer = 0;

    // Expand the right boundary and add the new character to the window.
    for (int right = 0; right < static_cast<int>(text.size()); ++right) {
        const unsigned char current = static_cast<unsigned char>(text[right]);
        ++frequency[current];

        // Shrink the window until the current character is no longer duplicated.
        while (frequency[current] > 1) {
            const unsigned char left_char = static_cast<unsigned char>(text[left]);
            --frequency[left_char];
            ++left;
        }

        // Update the best valid window length.
        answer = std::max(answer, right - left + 1);
    }

    // Return the maximum valid window length encountered.
    return answer;
}

/**
 * @brief Demonstrates opposite-direction two pointers with palindrome checking.
 *
 * Role:
 * - Show how both ends move inward while filtering irrelevant characters.
 *
 * Input:
 * - No external input. Uses one palindrome string and one non-palindrome string.
 *
 * Output:
 * - No return value.
 * - Prints the test strings and the corresponding boolean results.
 */
void DemoOppositeDirectionPointers() {
    // Prepare one positive example and one negative example.
    const std::string palindrome_text = "A man, a plan, a canal: Panama";
    const std::string non_palindrome_text = "algorithm";

    // Evaluate and print the palindrome results.
    std::cout << "palindrome test: \"" << palindrome_text << "\" -> "
              << (IsPalindromeIgnoringNonAlnum(palindrome_text) ? "true" : "false") << "\n";
    std::cout << "palindrome test: \"" << non_palindrome_text << "\" -> "
              << (IsPalindromeIgnoringNonAlnum(non_palindrome_text) ? "true" : "false") << "\n";
}

/**
 * @brief Demonstrates same-direction fast-slow pointers with move-zeroes.
 *
 * Role:
 * - Show how the fast pointer reads and the slow pointer writes compacted data.
 *
 * Input:
 * - No external input. Uses a fixed integer array.
 *
 * Output:
 * - No return value.
 * - Prints the array before and after moving zeroes.
 */
void DemoFastSlowPointers() {
    // Prepare a sequence containing zero and non-zero values.
    std::vector<int> nums = {0, 1, 0, 3, 12};
    PrintVector("before move zeroes", nums);

    // Compact non-zero values to the front and fill the suffix with zeroes.
    MoveZeroes(&nums);
    PrintVector("after move zeroes", nums);
}

/**
 * @brief Demonstrates sliding window on arrays and strings.
 *
 * Role:
 * - Show one minimum-length sum window and one longest-unique-character window.
 *
 * Input:
 * - No external input. Uses fixed examples.
 *
 * Output:
 * - No return value.
 * - Prints the test data and both sliding-window results.
 */
void DemoSlidingWindow() {
    // Prepare a positive integer array for the minimum-length window problem.
    const std::vector<int> nums = {2, 3, 1, 2, 4, 3};
    const int target = 7;
    PrintVector("sliding-window array", nums);
    std::cout << "target sum: " << target << "\n";
    std::cout << "minimum valid window length: " << MinSubarrayLenAtLeastTarget(target, nums)
              << "\n";

    // Prepare a string for the distinct-character window problem.
    const std::string text = "abcabcbb";
    std::cout << "unique-substring test: \"" << text << "\"\n";
    std::cout << "longest unique substring length: " << LongestUniqueSubstringLength(text) << "\n";
}

} // namespace

/**
 * @brief Runs all demonstrations for the two-pointer and sliding-window topic.
 *
 * Role:
 * - Serve as the executable entrypoint for the topic examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints demonstrations for opposite-direction pointers, fast-slow pointers,
 *   and sliding window.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 3: Two Pointers and Sliding Window\n\n";

    // Run the opposite-direction pointer demonstration.
    DemoOppositeDirectionPointers();
    std::cout << '\n';

    // Run the fast-slow pointer demonstration.
    DemoFastSlowPointers();
    std::cout << '\n';

    // Run the sliding-window demonstration.
    DemoSlidingWindow();
    return 0;
}
