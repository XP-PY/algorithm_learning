#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

/**
 * @brief Stores one node in a singly linked list.
 *
 * Role:
 * - Represent linked-list structure for traversal, reversal, and merge demos.
 */
struct ListNode {
    int value;
    ListNode* next;
};

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display array-style results for divide-and-conquer demonstrations.
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
 * @brief Prints a linked list with a label.
 *
 * Role:
 * - Display linked-list node order in a readable form for demonstrations.
 *
 * Input:
 * - `label`: Text printed before the linked-list contents.
 * - `head`: Head pointer of the linked list to print.
 *
 * Output:
 * - No return value.
 * - Writes one formatted line to standard output.
 */
void PrintList(const std::string& label, const ListNode* head) {
    // Print the label and start the bracketed sequence.
    std::cout << label << ": [";

    // Traverse the list from head to tail and print each node value.
    const ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next != nullptr) {
            std::cout << ", ";
        }
        current = current->next;
    }

    // Close the sequence and finish the line.
    std::cout << "]\n";
}

/**
 * @brief Builds a singly linked list from an integer vector.
 *
 * Role:
 * - Create demo linked lists without manual node wiring in each example.
 *
 * Input:
 * - `values`: Node values in head-to-tail order.
 *
 * Output:
 * - Returns the head pointer of a newly allocated linked list.
 * - Returns `nullptr` when the input vector is empty.
 */
ListNode* BuildList(const std::vector<int>& values) {
    // Handle the empty-input case early.
    if (values.empty()) {
        return nullptr;
    }

    // Create the head node and grow the list one node at a time.
    ListNode* head = new ListNode{values[0], nullptr};
    ListNode* tail = head;
    for (std::size_t i = 1; i < values.size(); ++i) {
        tail->next = new ListNode{values[i], nullptr};
        tail = tail->next;
    }

    // Return the head of the completed list.
    return head;
}

/**
 * @brief Deletes every node in a singly linked list.
 *
 * Role:
 * - Release demo memory after linked-list examples finish.
 *
 * Input:
 * - `head`: Head pointer of the list to delete.
 *
 * Output:
 * - No return value.
 * - Frees every node reachable from `head`.
 */
void DeleteList(ListNode* head) {
    // Walk through the list and delete one node at a time.
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next_node = current->next;
        delete current;
        current = next_node;
    }
}

/**
 * @brief Reverses a singly linked list iteratively.
 *
 * Role:
 * - Demonstrate careful pointer rewiring with `previous`, `current`, and `next`.
 *
 * Input:
 * - `head`: Head pointer of the list to reverse.
 *
 * Output:
 * - Returns the new head pointer of the reversed list.
 */
ListNode* ReverseList(ListNode* head) {
    // Track the reversed prefix and the current node being processed.
    ListNode* previous = nullptr;
    ListNode* current = head;

    // Rewire each node to point backward instead of forward.
    while (current != nullptr) {
        ListNode* next_node = current->next;
        current->next = previous;
        previous = current;
        current = next_node;
    }

    // The previous pointer becomes the new head.
    return previous;
}

/**
 * @brief Merges two sorted linked lists recursively.
 *
 * Role:
 * - Demonstrate recursive merge structure on linked-list nodes.
 *
 * Input:
 * - `left`: Head of the first sorted linked list.
 * - `right`: Head of the second sorted linked list.
 *
 * Output:
 * - Returns the head of one sorted merged linked list using the original nodes.
 */
ListNode* MergeSortedLists(ListNode* left, ListNode* right) {
    // Stop when either list is empty.
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    // Choose the smaller head node and merge the remaining suffix recursively.
    if (left->value <= right->value) {
        left->next = MergeSortedLists(left->next, right);
        return left;
    }
    right->next = MergeSortedLists(left, right->next);
    return right;
}

/**
 * @brief Computes `base^exponent` with recursive binary exponentiation.
 *
 * Role:
 * - Demonstrate recursion that reduces problem size by halving the exponent.
 *
 * Input:
 * - `base`: Base value.
 * - `exponent`: Non-negative integer exponent.
 *
 * Output:
 * - Returns `base` raised to `exponent`.
 */
double Power(double base, int exponent) {
    // Stop at the smallest subproblem where the answer is known directly.
    if (exponent == 0) {
        return 1.0;
    }

    // Solve the half-size subproblem recursively.
    const double half = Power(base, exponent / 2);
    const double squared = half * half;

    // Multiply by one more base when the exponent is odd.
    if (exponent % 2 == 1) {
        return squared * base;
    }
    return squared;
}

/**
 * @brief Merges two sorted integer vectors into one sorted vector.
 *
 * Role:
 * - Provide the merge step for merge-sort style divide and conquer.
 *
 * Input:
 * - `left`: First sorted half.
 * - `right`: Second sorted half.
 *
 * Output:
 * - Returns one sorted vector containing all elements from both halves.
 */
std::vector<int> MergeSortedVectors(const std::vector<int>& left, const std::vector<int>& right) {
    // Walk both halves and append the smaller front value each time.
    std::vector<int> merged;
    merged.reserve(left.size() + right.size());

    std::size_t i = 0;
    std::size_t j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i]);
            ++i;
        } else {
            merged.push_back(right[j]);
            ++j;
        }
    }

    // Append any remaining values from the unfinished half.
    while (i < left.size()) {
        merged.push_back(left[i]);
        ++i;
    }
    while (j < right.size()) {
        merged.push_back(right[j]);
        ++j;
    }

    // Return the merged sorted result.
    return merged;
}

/**
 * @brief Sorts an integer vector with recursive merge sort.
 *
 * Role:
 * - Demonstrate divide and conquer by split, solve, and merge.
 *
 * Input:
 * - `nums`: Integer vector to sort.
 *
 * Output:
 * - Returns a new sorted vector.
 */
std::vector<int> MergeSort(const std::vector<int>& nums) {
    // Stop when the vector is already of size zero or one.
    if (nums.size() <= 1) {
        return nums;
    }

    // Split the vector into left and right halves.
    const std::size_t middle = nums.size() / 2;
    const std::vector<int> left(nums.begin(), nums.begin() + static_cast<std::ptrdiff_t>(middle));
    const std::vector<int> right(nums.begin() + static_cast<std::ptrdiff_t>(middle), nums.end());

    // Recursively sort both halves.
    const std::vector<int> sorted_left = MergeSort(left);
    const std::vector<int> sorted_right = MergeSort(right);

    // Merge the sorted halves into one sorted result.
    return MergeSortedVectors(sorted_left, sorted_right);
}

/**
 * @brief Demonstrates linked-list traversal and reversal.
 *
 * Role:
 * - Show the original linked-list order and the reversed order after pointer updates.
 *
 * Input:
 * - No external input. Uses a fixed demo linked list.
 *
 * Output:
 * - No return value.
 * - Prints the original and reversed linked lists.
 */
void DemoLinkedListTraversalAndReverse() {
    // Build a small linked list for traversal and reversal.
    ListNode* head = BuildList({1, 2, 3, 4, 5});
    PrintList("original list", head);

    // Reverse the list and print the new node order.
    head = ReverseList(head);
    PrintList("reversed list", head);

    // Release the demo list memory.
    DeleteList(head);
}

/**
 * @brief Demonstrates recursive merge of two sorted linked lists.
 *
 * Role:
 * - Show how sorted linked-list heads are chosen and merged recursively.
 *
 * Input:
 * - No external input. Uses two fixed sorted linked lists.
 *
 * Output:
 * - No return value.
 * - Prints both input lists and the merged sorted result.
 */
void DemoMergeSortedLists() {
    // Build two sorted linked lists.
    ListNode* left = BuildList({1, 3, 5});
    ListNode* right = BuildList({2, 4, 6, 8});
    PrintList("left sorted list", left);
    PrintList("right sorted list", right);

    // Merge the two lists into one sorted linked list.
    ListNode* merged = MergeSortedLists(left, right);
    PrintList("merged sorted list", merged);

    // Release the merged list memory.
    DeleteList(merged);
}

/**
 * @brief Demonstrates recursive binary exponentiation.
 *
 * Role:
 * - Show how recursion reduces exponentiation to half-size subproblems.
 *
 * Input:
 * - No external input. Uses fixed base-exponent examples.
 *
 * Output:
 * - No return value.
 * - Prints a few power results.
 */
void DemoRecursivePower() {
    // Evaluate two fixed exponentiation examples.
    std::cout << "2^10: " << Power(2.0, 10) << "\n";
    std::cout << "3^5: " << Power(3.0, 5) << "\n";
}

/**
 * @brief Demonstrates merge-sort style divide and conquer.
 *
 * Role:
 * - Show the split-solve-merge structure on an integer vector.
 *
 * Input:
 * - No external input. Uses a fixed unsorted vector.
 *
 * Output:
 * - No return value.
 * - Prints the original vector and the sorted merge-sort result.
 */
void DemoMergeSort() {
    // Prepare an unsorted vector for divide-and-conquer sorting.
    const std::vector<int> nums = {7, 2, 9, 1, 5, 3};
    PrintVector("before merge sort", nums);

    // Sort the vector recursively and print the result.
    PrintVector("after merge sort", MergeSort(nums));
}

} // namespace

/**
 * @brief Runs all demonstrations for linked lists, recursion, and divide and conquer.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints linked-list, recursion, and divide-and-conquer demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 7: Linked List, Recursion, and Divide and Conquer\n\n";

    // Run the linked-list traversal and reverse demonstration.
    DemoLinkedListTraversalAndReverse();
    std::cout << '\n';

    // Run the linked-list merge demonstration.
    DemoMergeSortedLists();
    std::cout << '\n';

    // Run the recursive power demonstration.
    DemoRecursivePower();
    std::cout << '\n';

    // Run the merge-sort divide-and-conquer demonstration.
    DemoMergeSort();
    return 0;
}
