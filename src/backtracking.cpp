#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

using IntMatrix = std::vector<std::vector<int>>;

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display one-dimensional backtracking paths or source data.
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
 * @brief Prints a nested integer vector with a label.
 *
 * Role:
 * - Display the list of generated backtracking answers row by row.
 *
 * Input:
 * - `label`: Text printed before the rows.
 * - `rows`: Nested integer vectors to print.
 *
 * Output:
 * - No return value.
 * - Writes one line per row to standard output.
 */
void PrintMatrix(const std::string& label, const IntMatrix& rows) {
    // Print the heading for the nested result.
    std::cout << label << ":\n";

    // Print each row using the vector printer.
    for (const std::vector<int>& row : rows) {
        PrintVector("  row", row);
    }
}

/**
 * @brief Collects all subsets recursively.
 *
 * Role:
 * - Demonstrate subset backtracking where every partial path is already valid.
 *
 * Input:
 * - `nums`: Source values.
 * - `index`: Current position in the source array.
 * - `path`: Current subset being built.
 * - `result`: Output matrix receiving all subsets.
 *
 * Output:
 * - No return value.
 * - Appends subsets into `result`.
 */
void CollectSubsets(const std::vector<int>& nums, int index, std::vector<int>* path,
                    IntMatrix* result) {
    // Save the current path because every recursion state is a valid subset.
    result->push_back(*path);

    // Try including each remaining value as the next subset element.
    for (int i = index; i < static_cast<int>(nums.size()); ++i) {
        path->push_back(nums[static_cast<std::size_t>(i)]);
        CollectSubsets(nums, i + 1, path, result);
        path->pop_back();
    }
}

/**
 * @brief Returns all subsets of a value list.
 *
 * Role:
 * - Package the subset backtracking template into one helper function.
 *
 * Input:
 * - `nums`: Source values.
 *
 * Output:
 * - Returns every subset of `nums`.
 */
IntMatrix GenerateSubsets(const std::vector<int>& nums) {
    // Prepare the current path and final result container.
    std::vector<int> path;
    IntMatrix result;

    // Start recursive subset generation from the first index.
    CollectSubsets(nums, 0, &path, &result);
    return result;
}

/**
 * @brief Collects all permutations recursively.
 *
 * Role:
 * - Demonstrate permutation backtracking with a used-array state.
 *
 * Input:
 * - `nums`: Source values.
 * - `used`: Flags for values already chosen in the current path.
 * - `path`: Current permutation prefix.
 * - `result`: Output matrix receiving permutations.
 *
 * Output:
 * - No return value.
 * - Appends complete permutations into `result`.
 */
void CollectPermutations(const std::vector<int>& nums, std::vector<bool>* used,
                         std::vector<int>* path, IntMatrix* result) {
    // Save one answer once the path uses every value exactly once.
    if (path->size() == nums.size()) {
        result->push_back(*path);
        return;
    }

    // Try each currently unused value in the next permutation position.
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if ((*used)[static_cast<std::size_t>(i)]) {
            continue;
        }

        (*used)[static_cast<std::size_t>(i)] = true;
        path->push_back(nums[static_cast<std::size_t>(i)]);
        CollectPermutations(nums, used, path, result);
        path->pop_back();
        (*used)[static_cast<std::size_t>(i)] = false;
    }
}

/**
 * @brief Returns all permutations of a value list.
 *
 * Role:
 * - Package the permutation backtracking template into one helper function.
 *
 * Input:
 * - `nums`: Source values.
 *
 * Output:
 * - Returns every permutation of `nums`.
 */
IntMatrix GeneratePermutations(const std::vector<int>& nums) {
    // Prepare state for used flags, current path, and final answers.
    std::vector<bool> used(nums.size(), false);
    std::vector<int> path;
    IntMatrix result;

    // Start recursive permutation generation.
    CollectPermutations(nums, &used, &path, &result);
    return result;
}

/**
 * @brief Collects all combination-sum answers recursively.
 *
 * Role:
 * - Demonstrate backtracking with a start index and sorted-order pruning.
 *
 * Input:
 * - `candidates`: Sorted candidate values.
 * - `start`: First candidate index allowed in this recursion state.
 * - `remaining`: Remaining target sum.
 * - `path`: Current combination being built.
 * - `result`: Output matrix receiving valid combinations.
 *
 * Output:
 * - No return value.
 * - Appends valid combinations into `result`.
 */
void CollectCombinationSums(const std::vector<int>& candidates, int start, int remaining,
                            std::vector<int>* path, IntMatrix* result) {
    // Save one answer once the remaining target becomes exactly zero.
    if (remaining == 0) {
        result->push_back(*path);
        return;
    }

    // Try each allowed candidate and stop early once values are too large.
    for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
        const int candidate = candidates[static_cast<std::size_t>(i)];
        if (candidate > remaining) {
            break;
        }

        path->push_back(candidate);
        CollectCombinationSums(candidates, i, remaining - candidate, path, result);
        path->pop_back();
    }
}

/**
 * @brief Returns all combinations whose sum equals a target.
 *
 * Role:
 * - Package combination-sum backtracking with sorted pruning.
 *
 * Input:
 * - `candidates`: Candidate values.
 * - `target`: Required target sum.
 *
 * Output:
 * - Returns every valid combination whose sum equals `target`.
 */
IntMatrix GenerateCombinationSum(std::vector<int> candidates, int target) {
    // Sort candidates so pruning by remaining target becomes valid.
    std::sort(candidates.begin(), candidates.end());

    // Prepare state for the current path and final answers.
    std::vector<int> path;
    IntMatrix result;

    // Start recursive search from the first candidate.
    CollectCombinationSums(candidates, 0, target, &path, &result);
    return result;
}

/**
 * @brief Demonstrates subset generation.
 *
 * Role:
 * - Show the subset decision-tree pattern where every partial path is valid.
 *
 * Input:
 * - No external input. Uses a fixed source vector.
 *
 * Output:
 * - No return value.
 * - Prints the source vector and all generated subsets.
 */
void DemoSubsets() {
    // Prepare a small source vector for subset generation.
    const std::vector<int> nums = {1, 2, 3};
    PrintVector("subset source", nums);

    // Generate and print all subsets.
    PrintMatrix("subsets", GenerateSubsets(nums));
}

/**
 * @brief Demonstrates permutation generation.
 *
 * Role:
 * - Show the permutation decision-tree pattern with a used-array state.
 *
 * Input:
 * - No external input. Uses a fixed source vector.
 *
 * Output:
 * - No return value.
 * - Prints the source vector and all generated permutations.
 */
void DemoPermutations() {
    // Prepare a small source vector for permutation generation.
    const std::vector<int> nums = {1, 2, 3};
    PrintVector("permutation source", nums);

    // Generate and print all permutations.
    PrintMatrix("permutations", GeneratePermutations(nums));
}

/**
 * @brief Demonstrates combination-sum generation with pruning.
 *
 * Role:
 * - Show start-index control, candidate reuse, and sorted-order pruning.
 *
 * Input:
 * - No external input. Uses fixed candidates and target.
 *
 * Output:
 * - No return value.
 * - Prints the source candidates and all valid combinations.
 */
void DemoCombinationSum() {
    // Prepare fixed candidates and target for the backtracking search.
    const std::vector<int> candidates = {2, 3, 6, 7};
    const int target = 7;
    PrintVector("combination-sum candidates", candidates);
    std::cout << "target: " << target << "\n";

    // Generate and print all combinations whose sum equals the target.
    PrintMatrix("combination-sum answers", GenerateCombinationSum(candidates, target));
}

} // namespace

/**
 * @brief Runs all demonstrations for backtracking.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints subset, permutation, and combination-sum demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 9: Backtracking\n\n";

    // Run the subset-generation demonstration.
    DemoSubsets();
    std::cout << '\n';

    // Run the permutation-generation demonstration.
    DemoPermutations();
    std::cout << '\n';

    // Run the combination-sum demonstration.
    DemoCombinationSum();
    return 0;
}
