#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {

using CharCount = std::pair<char, int>;
using StringGroups = std::vector<std::vector<std::string>>;

/**
 * @brief Prints a string vector with a label.
 *
 * Role:
 * - Display words or string results in a readable format for demonstrations.
 *
 * Input:
 * - `label`: Text printed before the vector contents.
 * - `values`: String sequence to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintStringVector(const std::string& label, const std::vector<std::string>& values) {
    // Print the label and start the bracketed sequence.
    std::cout << label << ": [";

    // Print each string with quotes and comma separators.
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << '"' << values[i] << '"';
        if (i + 1 != values.size()) {
            std::cout << ", ";
        }
    }

    // Close the sequence and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Prints character counts with a label.
 *
 * Role:
 * - Display frequency-count results in deterministic character order.
 *
 * Input:
 * - `label`: Text printed before the count list.
 * - `counts`: Character-count pairs sorted by character.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintCharCounts(const std::string& label, const std::vector<CharCount>& counts) {
    // Print the label and start the bracketed count list.
    std::cout << label << ": [";

    // Print each character-count pair in display order.
    for (std::size_t i = 0; i < counts.size(); ++i) {
        std::cout << "('" << counts[i].first << "', " << counts[i].second << ")";
        if (i + 1 != counts.size()) {
            std::cout << ", ";
        }
    }

    // Close the count list and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Prints grouped strings with a label.
 *
 * Role:
 * - Display anagram groups or other string buckets in deterministic order.
 *
 * Input:
 * - `label`: Text printed before the groups.
 * - `groups`: Nested string groups to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line per group to standard output.
 */
void PrintStringGroups(const std::string& label, const StringGroups& groups) {
    // Print the group heading.
    std::cout << label << ":\n";

    // Print each group as one string vector.
    for (const std::vector<std::string>& group : groups) {
        PrintStringVector("  group", group);
    }
}

/**
 * @brief Builds sorted character-frequency pairs from a string.
 *
 * Role:
 * - Demonstrate `unordered_map` counting while producing deterministic output.
 *
 * Input:
 * - `text`: Source string whose characters are counted.
 *
 * Output:
 * - Returns `(character, count)` pairs sorted by character.
 */
std::vector<CharCount> BuildSortedCharacterCounts(const std::string& text) {
    // Count each character with an unordered hash table.
    std::unordered_map<char, int> frequency;
    for (char character : text) {
        ++frequency[character];
    }

    // Copy hash-table entries into a vector so they can be sorted for display.
    std::vector<CharCount> counts;
    counts.reserve(frequency.size());
    for (const auto& entry : frequency) {
        counts.push_back(entry);
    }

    // Sort by character to avoid relying on unordered_map iteration order.
    std::sort(counts.begin(), counts.end(), [](const CharCount& left, const CharCount& right) {
        return left.first < right.first;
    });

    // Return the deterministic frequency list.
    return counts;
}

/**
 * @brief Checks whether two strings are anagrams.
 *
 * Role:
 * - Demonstrate frequency balancing with a hash map.
 *
 * Input:
 * - `left`: First string.
 * - `right`: Second string.
 *
 * Output:
 * - Returns `true` if both strings contain the same characters with the same counts.
 * - Returns `false` otherwise.
 */
bool AreAnagrams(const std::string& left, const std::string& right) {
    // Reject strings with different lengths before building counts.
    if (left.size() != right.size()) {
        return false;
    }

    // Count all characters from the first string.
    std::unordered_map<char, int> balance;
    for (char character : left) {
        ++balance[character];
    }

    // Subtract characters from the second string and fail on overuse.
    for (char character : right) {
        auto found = balance.find(character);
        if (found == balance.end() || found->second == 0) {
            return false;
        }
        --found->second;
    }

    // Equal lengths plus no overuse means every count returned to zero.
    return true;
}

/**
 * @brief Builds a sorted-character key for an anagram group.
 *
 * Role:
 * - Convert words with the same letters into the same hash-map key.
 *
 * Input:
 * - `word`: Source word.
 *
 * Output:
 * - Returns a sorted copy of the word.
 */
std::string BuildAnagramKey(const std::string& word) {
    // Copy the original word so the caller's value is not modified.
    std::string key = word;

    // Sort the copied characters to make anagrams share a key.
    std::sort(key.begin(), key.end());

    // Return the derived grouping key.
    return key;
}

/**
 * @brief Groups words that are anagrams of each other.
 *
 * Role:
 * - Demonstrate grouping by a derived string key with `unordered_map`.
 *
 * Input:
 * - `words`: Source words to group.
 *
 * Output:
 * - Returns anagram groups with each group and the group list sorted for stable display.
 */
StringGroups GroupAnagrams(const std::vector<std::string>& words) {
    // Bucket each word by its sorted-character key.
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    for (const std::string& word : words) {
        buckets[BuildAnagramKey(word)].push_back(word);
    }

    // Move buckets into a vector and sort inside each group.
    StringGroups groups;
    groups.reserve(buckets.size());
    for (auto& entry : buckets) {
        std::sort(entry.second.begin(), entry.second.end());
        groups.push_back(entry.second);
    }

    // Sort the groups by their first element for deterministic demo output.
    std::sort(groups.begin(), groups.end(),
              [](const auto& left, const auto& right) { return left.front() < right.front(); });

    // Return the stable group list.
    return groups;
}

/**
 * @brief Finds the length of the longest consecutive integer sequence.
 *
 * Role:
 * - Demonstrate `unordered_set` membership checks and deduplication.
 *
 * Input:
 * - `nums`: Integer values that may contain duplicates and gaps.
 *
 * Output:
 * - Returns the length of the longest run such as `1, 2, 3, 4`.
 */
int LongestConsecutiveLength(const std::vector<int>& nums) {
    // Store unique values for average O(1) membership checks.
    std::unordered_set<int> values(nums.begin(), nums.end());
    int best = 0;

    // Only start counting from numbers that begin a sequence.
    for (int value : values) {
        if (values.find(value - 1) != values.end()) {
            continue;
        }

        // Extend the sequence until the next value is missing.
        int current = value;
        int length = 1;
        while (values.find(current + 1) != values.end()) {
            ++current;
            ++length;
        }

        // Track the longest sequence found so far.
        best = std::max(best, length);
    }

    // Return the best sequence length.
    return best;
}

/**
 * @brief Sorts words by length, then lexicographically.
 *
 * Role:
 * - Demonstrate a custom comparator with explicit tie-breaking.
 *
 * Input:
 * - `words`: Source word list.
 *
 * Output:
 * - Returns a new list sorted by shorter length first, then alphabetically.
 */
std::vector<std::string> SortByLengthThenLexicographic(std::vector<std::string> words) {
    // Sort by the primary key first and use lexical order as the tie breaker.
    std::sort(words.begin(), words.end(), [](const std::string& left, const std::string& right) {
        if (left.size() != right.size()) {
            return left.size() < right.size();
        }
        return left < right;
    });

    // Return the sorted copy.
    return words;
}

/**
 * @brief Demonstrates frequency counting and anagram checking.
 *
 * Role:
 * - Show direct character counting and count balancing for anagrams.
 *
 * Input:
 * - No external input. Uses fixed demo strings.
 *
 * Output:
 * - No return value.
 * - Prints character counts and anagram-check results.
 */
void DemoFrequencyAndAnagram() {
    // Count characters in a sample word.
    const std::string text = "abracadabra";
    PrintCharCounts("character counts for abracadabra", BuildSortedCharacterCounts(text));

    // Check one positive and one negative anagram example.
    std::cout << "listen / silent are anagrams: "
              << (AreAnagrams("listen", "silent") ? "true" : "false") << "\n";
    std::cout << "apple / papelx are anagrams: "
              << (AreAnagrams("apple", "papelx") ? "true" : "false") << "\n";
}

/**
 * @brief Demonstrates grouping strings by a derived key.
 *
 * Role:
 * - Show how sorted-character keys group anagrams together.
 *
 * Input:
 * - No external input. Uses a fixed word list.
 *
 * Output:
 * - No return value.
 * - Prints the original words and grouped anagrams.
 */
void DemoGroupAnagrams() {
    // Prepare the classic anagram grouping example.
    const std::vector<std::string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};
    PrintStringVector("words", words);

    // Group words that share the same sorted-character key.
    const StringGroups groups = GroupAnagrams(words);
    PrintStringGroups("anagram groups", groups);
}

/**
 * @brief Demonstrates set-based consecutive sequence detection.
 *
 * Role:
 * - Show membership lookup with `unordered_set`.
 *
 * Input:
 * - No external input. Uses a fixed integer array.
 *
 * Output:
 * - No return value.
 * - Prints the longest consecutive sequence length.
 */
void DemoLongestConsecutiveSequence() {
    // Prepare values with one consecutive run from 1 to 4.
    const std::vector<int> nums = {100, 4, 200, 1, 3, 2};

    // Compute and display the longest run length.
    std::cout << "longest consecutive length in [100, 4, 200, 1, 3, 2]: "
              << LongestConsecutiveLength(nums) << "\n";
}

/**
 * @brief Demonstrates custom sorting for strings.
 *
 * Role:
 * - Show how a comparator can express a primary key and tie-breaking rule.
 *
 * Input:
 * - No external input. Uses a fixed word list.
 *
 * Output:
 * - No return value.
 * - Prints the word list before and after custom sorting.
 */
void DemoCustomSort() {
    // Prepare words with repeated lengths to show tie-breaking.
    const std::vector<std::string> words = {"pear", "fig", "apple", "plum", "kiwi", "ape"};
    PrintStringVector("before custom sort", words);

    // Sort by length and then by lexicographic order.
    const std::vector<std::string> sorted = SortByLengthThenLexicographic(words);
    PrintStringVector("after custom sort", sorted);
}

} // namespace

/**
 * @brief Runs all demonstrations for hash tables, strings, and sorting.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints frequency counting, grouping, set lookup, and custom-sort demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 5: Hash Table, Strings, and Sorting\n\n";

    // Run frequency counting and anagram examples.
    DemoFrequencyAndAnagram();
    std::cout << '\n';

    // Run grouping-by-key examples.
    DemoGroupAnagrams();
    std::cout << '\n';

    // Run set membership example.
    DemoLongestConsecutiveSequence();
    std::cout << '\n';

    // Run custom comparator example.
    DemoCustomSort();
    return 0;
}
