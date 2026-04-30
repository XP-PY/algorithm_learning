#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

/**
 * @brief Describes one inclusive range update for a difference array.
 *
 * Role:
 * - Store `delta` to add over the inclusive range `[left, right]`.
 */
struct RangeUpdate {
    int left;
    int right;
    int delta;
};

/**
 * @brief Prints a vector with a label.
 *
 * Role:
 * - Display a one-dimensional sequence in a readable format for demos.
 *
 * Input:
 * - `label`: Text printed before the vector contents.
 * - `values`: Sequence to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
template <typename T> void PrintVector(const std::string& label, const std::vector<T>& values) {
    // Print the label and start the bracketed sequence.
    std::cout << label << ": [";

    // Print each value with comma separators.
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 != values.size()) {
            std::cout << ", ";
        }
    }

    // Close the sequence and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Prints a matrix with a label.
 *
 * Role:
 * - Display a two-dimensional sequence for prefix-sum demonstrations.
 *
 * Input:
 * - `label`: Text printed before the matrix rows.
 * - `matrix`: Matrix to print row by row.
 *
 * Output:
 * - No return value.
 * - Writes the label and one formatted line per matrix row.
 */
template <typename T>
void PrintMatrix(const std::string& label, const std::vector<std::vector<T>>& matrix) {
    // Print the matrix heading.
    std::cout << label << ":\n";

    // Print each row using the vector printer.
    for (const std::vector<T>& row : matrix) {
        PrintVector("  row", row);
    }
}

/**
 * @brief Builds a 1D prefix sum array with a leading zero.
 *
 * Role:
 * - Precompute cumulative sums so inclusive range queries become `O(1)`.
 *
 * Input:
 * - `nums`: Source integer sequence.
 *
 * Output:
 * - Returns `prefix` where `prefix[i + 1]` stores the sum of `nums[0..i]`.
 */
std::vector<long long> BuildPrefixSum(const std::vector<int>& nums) {
    // Allocate one extra slot so prefix[0] represents the empty prefix.
    std::vector<long long> prefix(nums.size() + 1, 0);

    // Extend cumulative sums from left to right.
    for (std::size_t i = 0; i < nums.size(); ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    // Return the completed preprocessing array.
    return prefix;
}

/**
 * @brief Queries an inclusive 1D range sum from a prefix sum array.
 *
 * Role:
 * - Convert a repeated range sum query into two prefix lookups.
 *
 * Input:
 * - `prefix`: Prefix sum array built by `BuildPrefixSum`.
 * - `left`: Inclusive left boundary in the original array.
 * - `right`: Inclusive right boundary in the original array.
 *
 * Output:
 * - Returns the sum of the original array over `[left, right]`.
 */
long long RangeSum1D(const std::vector<long long>& prefix, int left, int right) {
    // Translate the inclusive query into the leading-zero prefix convention.
    return prefix[static_cast<std::size_t>(right) + 1] - prefix[static_cast<std::size_t>(left)];
}

/**
 * @brief Builds a 2D prefix sum matrix with an extra top row and left column.
 *
 * Role:
 * - Precompute rectangle sums so later rectangle queries become `O(1)`.
 *
 * Input:
 * - `matrix`: Source integer matrix.
 *
 * Output:
 * - Returns a prefix matrix where row `0` and column `0` represent empty areas.
 */
std::vector<std::vector<long long>> BuildPrefixSum2D(const std::vector<std::vector<int>>& matrix) {
    // Handle the empty-matrix case by returning the smallest empty prefix shape.
    if (matrix.empty() || matrix[0].empty()) {
        return {{0}};
    }

    // Allocate one extra row and one extra column for boundary-free formulas.
    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix[0].size();
    std::vector<std::vector<long long>> prefix(rows + 1, std::vector<long long>(cols + 1, 0));

    // Fill each prefix cell using top, left, and overlap correction.
    for (std::size_t row = 0; row < rows; ++row) {
        for (std::size_t col = 0; col < cols; ++col) {
            prefix[row + 1][col + 1] =
                matrix[row][col] + prefix[row][col + 1] + prefix[row + 1][col] - prefix[row][col];
        }
    }

    // Return the completed 2D preprocessing table.
    return prefix;
}

/**
 * @brief Queries an inclusive rectangle sum from a 2D prefix matrix.
 *
 * Role:
 * - Convert a rectangle sum query into four prefix lookups.
 *
 * Input:
 * - `prefix`: Prefix matrix built by `BuildPrefixSum2D`.
 * - `top`: Inclusive top row of the original matrix.
 * - `left`: Inclusive left column of the original matrix.
 * - `bottom`: Inclusive bottom row of the original matrix.
 * - `right`: Inclusive right column of the original matrix.
 *
 * Output:
 * - Returns the sum of the original matrix inside the requested rectangle.
 */
long long RangeSum2D(const std::vector<std::vector<long long>>& prefix, 
                        int top, int left, int bottom, int right) { // 
    // Shift original coordinates by one to match the prefix matrix convention.
    const std::size_t top_row = static_cast<std::size_t>(top);
    const std::size_t left_col = static_cast<std::size_t>(left);
    const std::size_t bottom_row = static_cast<std::size_t>(bottom) + 1;
    const std::size_t right_col = static_cast<std::size_t>(right) + 1;

    // Add the full bottom-right area and remove the two excluded strips.
    return prefix[bottom_row][right_col] - prefix[top_row][right_col] -
           prefix[bottom_row][left_col] + prefix[top_row][left_col];
}

/**
 * @brief Applies many inclusive range updates with a difference array.
 *
 * Role:
 * - Batch range additions in `O(number_of_updates + length)` time.
 *
 * Input:
 * - `length`: Size of the final array.
 * - `updates`: Inclusive range updates to apply.
 *
 * Output:
 * - Returns the final array after all range updates are applied.
 */
std::vector<long long> ApplyRangeUpdates(int length, const std::vector<RangeUpdate>& updates) {
    // Allocate one extra difference slot so right + 1 can stop an update safely.
    std::vector<long long> diff(static_cast<std::size_t>(length) + 1, 0);

    // Mark where each range update starts and stops.
    for (const RangeUpdate& update : updates) {
        diff[static_cast<std::size_t>(update.left)] += update.delta;
        diff[static_cast<std::size_t>(update.right) + 1] -= update.delta;
    }

    // Rebuild the final array by accumulating active updates.
    std::vector<long long> result(static_cast<std::size_t>(length), 0);
    long long running = 0;
    for (int i = 0; i < length; ++i) {
        running += diff[static_cast<std::size_t>(i)];
        result[static_cast<std::size_t>(i)] = running;
    }

    // Return the fully reconstructed array.
    return result;
}

/**
 * @brief Demonstrates 1D prefix sums and inclusive range queries.
 *
 * Role:
 * - Show how a leading-zero prefix array answers range sums directly.
 *
 * Input:
 * - No external input. Uses a fixed integer array and range.
 *
 * Output:
 * - No return value.
 * - Prints the source array, prefix array, and one range query result.
 */
void DemoOneDimensionalPrefixSum() {
    // Prepare a simple array and build its prefix sums.
    const std::vector<int> nums = {2, 4, 1, 7, 3};
    const std::vector<long long> prefix = BuildPrefixSum(nums);
    PrintVector("array", nums);
    PrintVector("prefix", prefix);

    // Query one inclusive range from the original array.
    const int left = 1;
    const int right = 3;
    std::cout << "sum [" << left << ", " << right << "]: " << RangeSum1D(prefix, left, right)
              << "\n";
}

/**
 * @brief Demonstrates 2D prefix sums and rectangle queries.
 *
 * Role:
 * - Show how the overlap-correction formula answers matrix rectangle sums.
 *
 * Input:
 * - No external input. Uses a fixed matrix and rectangle.
 *
 * Output:
 * - No return value.
 * - Prints the source matrix, prefix matrix, and one rectangle query result.
 */
void DemoTwoDimensionalPrefixSum() {
    // Prepare a small matrix and build its 2D prefix table.
    const std::vector<std::vector<int>> matrix = {
        {3, 0, 1, 4},
        {5, 6, 3, 2},
        {1, 2, 0, 1},
    };
    const std::vector<std::vector<long long>> prefix = BuildPrefixSum2D(matrix);
    PrintMatrix("matrix", matrix);
    PrintMatrix("2D prefix", prefix);

    // Query one inclusive rectangle from the original matrix.
    const int top = 0;
    const int left = 1;
    const int bottom = 1;
    const int right = 2;
    std::cout << "rectangle sum [(" << top << ", " << left << "), (" << bottom << ", " << right
              << ")]: " << RangeSum2D(prefix, top, left, bottom, right) << "\n";
}

/**
 * @brief Demonstrates difference-array range updates.
 *
 * Role:
 * - Show how many range additions can be applied through one final scan.
 *
 * Input:
 * - No external input. Uses a fixed array length and fixed updates.
 *
 * Output:
 * - No return value.
 * - Prints the final array after all range updates.
 */
void DemoDifferenceArray() {
    // Prepare range updates using inclusive 0-based boundaries.
    const int length = 6;
    const std::vector<RangeUpdate> updates = {
        {1, 3, 2},
        {2, 5, 4},
        {0, 2, -1},
    };

    // Apply all updates and show only the final reconstructed array.
    const std::vector<long long> result = ApplyRangeUpdates(length, updates);
    PrintVector("final after range updates", result);
}

} // namespace

/**
 * @brief Runs all demonstrations for prefix sums and difference arrays.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints 1D prefix sum, 2D prefix sum, and difference-array demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 4: Prefix Sums and Difference Arrays\n\n";

    // Run the 1D prefix sum demonstration.
    DemoOneDimensionalPrefixSum();
    std::cout << '\n';

    // Run the 2D prefix sum demonstration.
    DemoTwoDimensionalPrefixSum();
    std::cout << '\n';

    // Run the difference-array range update demonstration.
    DemoDifferenceArray();
    return 0;
}
