#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace {

/**
 * @brief Stores one node in a binary tree.
 *
 * Role:
 * - Represent binary-tree and BST structure for traversal and search demos.
 */
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

/**
 * @brief Prints an integer vector with a label.
 *
 * Role:
 * - Display traversal and heap results in a readable format.
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
 * @brief Prints a matrix of integer levels with a label.
 *
 * Role:
 * - Display level-order traversal output row by row.
 *
 * Input:
 * - `label`: Text printed before the matrix rows.
 * - `levels`: Nested integer levels to print.
 *
 * Output:
 * - No return value.
 * - Writes one line per level to standard output.
 */
void PrintLevels(const std::string& label, const std::vector<std::vector<int>>& levels) {
    // Print the overall heading for the level-order result.
    std::cout << label << ":\n";

    // Print each level as one vector row.
    for (const std::vector<int>& level : levels) {
        PrintVector("  level", level);
    }
}

/**
 * @brief Deletes every node in a binary tree.
 *
 * Role:
 * - Release demo memory after tree examples finish.
 *
 * Input:
 * - `root`: Root pointer of the tree to delete.
 *
 * Output:
 * - No return value.
 * - Frees every node reachable from `root`.
 */
void DeleteTree(TreeNode* root) {
    // Stop once the recursion reaches an empty subtree.
    if (root == nullptr) {
        return;
    }

    // Delete both subtrees before deleting the current node.
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

/**
 * @brief Builds a fixed binary tree for traversal demonstrations.
 *
 * Role:
 * - Create a small non-BST-shaped example so traversal orders are easy to compare.
 *
 * Input:
 * - No external input.
 *
 * Output:
 * - Returns the root pointer of a newly allocated binary tree.
 */
TreeNode* BuildTraversalDemoTree() {
    // Create a tree with multiple levels and both left/right branches.
    TreeNode* root = new TreeNode{1, nullptr, nullptr};
    root->left = new TreeNode{2, nullptr, nullptr};
    root->right = new TreeNode{3, nullptr, nullptr};
    root->left->left = new TreeNode{4, nullptr, nullptr};
    root->left->right = new TreeNode{5, nullptr, nullptr};
    root->right->right = new TreeNode{6, nullptr, nullptr};

    // Return the completed demo tree.
    return root;
}

/**
 * @brief Builds a BST by inserting fixed values.
 *
 * Role:
 * - Create a demo BST for search, insert, and inorder traversal examples.
 *
 * Input:
 * - No external input.
 *
 * Output:
 * - Returns the root pointer of a newly allocated BST.
 */
TreeNode* BuildBstDemoTree();

/**
 * @brief Inserts one value into a BST.
 *
 * Role:
 * - Demonstrate how BST ordering guides recursive insertion.
 *
 * Input:
 * - `root`: Root of the BST or subtree.
 * - `value`: Value to insert.
 *
 * Output:
 * - Returns the root pointer of the BST after insertion.
 */
TreeNode* InsertIntoBst(TreeNode* root, int value) {
    // Create a new node when the insertion point is reached.
    if (root == nullptr) {
        return new TreeNode{value, nullptr, nullptr};
    }

    // Follow BST ordering to the left or right subtree.
    if (value < root->value) {
        root->left = InsertIntoBst(root->left, value);
    } else if (value > root->value) {
        root->right = InsertIntoBst(root->right, value);
    }

    // Return the unchanged root pointer of this subtree.
    return root;
}

/**
 * @brief Searches for a value inside a BST.
 *
 * Role:
 * - Demonstrate comparison-guided BST lookup.
 *
 * Input:
 * - `root`: Root of the BST or subtree.
 * - `target`: Value to search for.
 *
 * Output:
 * - Returns the node pointer containing `target`.
 * - Returns `nullptr` if the target does not exist.
 */
TreeNode* SearchBst(TreeNode* root, int target) {
    // Walk downward until the target is found or the search falls off the tree.
    TreeNode* current = root;
    while (current != nullptr) {
        if (target == current->value) {
            return current;
        }
        if (target < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Report failure when the value is absent.
    return nullptr;
}

/**
 * @brief Appends preorder traversal values recursively.
 *
 * Role:
 * - Visit node, then left subtree, then right subtree.
 *
 * Input:
 * - `root`: Current subtree root.
 * - `result`: Output vector receiving traversal values.
 *
 * Output:
 * - No return value.
 * - Appends preorder values into `result`.
 */
void CollectPreorder(const TreeNode* root, std::vector<int>* result) {
    // Stop once the recursion reaches an empty subtree.
    if (root == nullptr) {
        return;
    }

    // Visit the current node before both children.
    result->push_back(root->value);
    CollectPreorder(root->left, result);
    CollectPreorder(root->right, result);
}

/**
 * @brief Appends inorder traversal values recursively.
 *
 * Role:
 * - Visit left subtree, then node, then right subtree.
 *
 * Input:
 * - `root`: Current subtree root.
 * - `result`: Output vector receiving traversal values.
 *
 * Output:
 * - No return value.
 * - Appends inorder values into `result`.
 */
void CollectInorder(const TreeNode* root, std::vector<int>* result) {
    // Stop once the recursion reaches an empty subtree.
    if (root == nullptr) {
        return;
    }

    // Visit left subtree, current node, then right subtree.
    CollectInorder(root->left, result);
    result->push_back(root->value);
    CollectInorder(root->right, result);
}

/**
 * @brief Appends postorder traversal values recursively.
 *
 * Role:
 * - Visit left subtree, then right subtree, then node.
 *
 * Input:
 * - `root`: Current subtree root.
 * - `result`: Output vector receiving traversal values.
 *
 * Output:
 * - No return value.
 * - Appends postorder values into `result`.
 */
void CollectPostorder(const TreeNode* root, std::vector<int>* result) {
    // Stop once the recursion reaches an empty subtree.
    if (root == nullptr) {
        return;
    }

    // Visit both children before the current node.
    CollectPostorder(root->left, result);
    CollectPostorder(root->right, result);
    result->push_back(root->value);
}

/**
 * @brief Returns preorder traversal of a binary tree.
 *
 * Role:
 * - Package recursive preorder traversal into a convenient value-returning function.
 *
 * Input:
 * - `root`: Root of the binary tree.
 *
 * Output:
 * - Returns the preorder traversal values.
 */
std::vector<int> PreorderTraversal(const TreeNode* root) {
    // Collect preorder values into a result vector.
    std::vector<int> result;
    CollectPreorder(root, &result);
    return result;
}

/**
 * @brief Returns inorder traversal of a binary tree.
 *
 * Role:
 * - Package recursive inorder traversal into a convenient value-returning function.
 *
 * Input:
 * - `root`: Root of the binary tree.
 *
 * Output:
 * - Returns the inorder traversal values.
 */
std::vector<int> InorderTraversal(const TreeNode* root) {
    // Collect inorder values into a result vector.
    std::vector<int> result;
    CollectInorder(root, &result);
    return result;
}

/**
 * @brief Returns postorder traversal of a binary tree.
 *
 * Role:
 * - Package recursive postorder traversal into a convenient value-returning function.
 *
 * Input:
 * - `root`: Root of the binary tree.
 *
 * Output:
 * - Returns the postorder traversal values.
 */
std::vector<int> PostorderTraversal(const TreeNode* root) {
    // Collect postorder values into a result vector.
    std::vector<int> result;
    CollectPostorder(root, &result);
    return result;
}

/**
 * @brief Returns level-order traversal of a binary tree.
 *
 * Role:
 * - Demonstrate iterative BFS traversal with a queue.
 *
 * Input:
 * - `root`: Root of the binary tree.
 *
 * Output:
 * - Returns one vector per level from top to bottom.
 */
std::vector<std::vector<int>> LevelOrderTraversal(const TreeNode* root) {
    // Handle the empty-tree case early.
    if (root == nullptr) {
        return {};
    }

    // Initialize the BFS queue with the root node.
    std::queue<const TreeNode*> pending;
    pending.push(root);
    std::vector<std::vector<int>> levels;

    // Process one full level at a time.
    while (!pending.empty()) {
        const int level_size = static_cast<int>(pending.size());
        std::vector<int> level;
        level.reserve(static_cast<std::size_t>(level_size));

        // Pop every node currently in the queue and enqueue its children.
        for (int i = 0; i < level_size; ++i) {
            const TreeNode* current = pending.front();
            pending.pop();
            level.push_back(current->value);

            if (current->left != nullptr) {
                pending.push(current->left);
            }
            if (current->right != nullptr) {
                pending.push(current->right);
            }
        }

        // Save the completed level before moving deeper.
        levels.push_back(std::move(level));
    }

    // Return the full level-order traversal result.
    return levels;
}

/**
 * @brief Drains a max-heap into pop order.
 *
 * Role:
 * - Show the order in which a max-heap returns the current largest element.
 *
 * Input:
 * - `heap`: Max-heap copied by value so the demo object stays unchanged.
 *
 * Output:
 * - Returns the values in max-heap pop order.
 */
std::vector<int> DrainMaxHeap(std::priority_queue<int> heap) {
    // Pop every element from the heap from largest to smallest.
    std::vector<int> order;
    while (!heap.empty()) {
        order.push_back(heap.top());
        heap.pop();
    }

    // Return the max-first pop order.
    return order;
}

/**
 * @brief Drains a min-heap into pop order.
 *
 * Role:
 * - Show the order in which a min-heap returns the current smallest element.
 *
 * Input:
 * - `heap`: Min-heap copied by value so the demo object stays unchanged.
 *
 * Output:
 * - Returns the values in min-heap pop order.
 */
std::vector<int> DrainMinHeap(std::priority_queue<int, std::vector<int>, std::greater<int>> heap) {
    // Pop every element from the heap from smallest to largest.
    std::vector<int> order;
    while (!heap.empty()) {
        order.push_back(heap.top());
        heap.pop();
    }

    // Return the min-first pop order.
    return order;
}

/**
 * @brief Builds the fixed BST used in search and insert demonstrations.
 *
 * Role:
 * - Reuse `InsertIntoBst` so the BST demo matches the taught operation.
 *
 * Input:
 * - No external input.
 *
 * Output:
 * - Returns the root pointer of a newly allocated BST.
 */
TreeNode* BuildBstDemoTree() {
    // Insert values one by one so BST structure follows the ordering rule.
    TreeNode* root = nullptr;
    for (int value : {5, 3, 7, 2, 4, 6, 8}) {
        root = InsertIntoBst(root, value);
    }
    return root;
}

/**
 * @brief Demonstrates recursive DFS and iterative BFS traversals.
 *
 * Role:
 * - Show preorder, inorder, postorder, and level-order on the same tree.
 *
 * Input:
 * - No external input. Uses a fixed demo tree.
 *
 * Output:
 * - No return value.
 * - Prints all four traversal orders.
 */
void DemoTreeTraversals() {
    // Build one demo tree whose traversal orders are easy to compare.
    TreeNode* root = BuildTraversalDemoTree();

    // Print the recursive DFS traversal orders.
    PrintVector("preorder", PreorderTraversal(root));
    PrintVector("inorder", InorderTraversal(root));
    PrintVector("postorder", PostorderTraversal(root));

    // Print the iterative BFS level-order traversal.
    PrintLevels("level order", LevelOrderTraversal(root));

    // Release the demo tree memory.
    DeleteTree(root);
}

/**
 * @brief Demonstrates BST search and insertion.
 *
 * Role:
 * - Show how ordering guides search and how inorder traversal stays sorted.
 *
 * Input:
 * - No external input. Uses a fixed BST and two inserted values.
 *
 * Output:
 * - No return value.
 * - Prints BST inorder order and search/insert results.
 */
void DemoBstOperations() {
    // Build one demo BST from fixed insertion order.
    TreeNode* root = BuildBstDemoTree();
    PrintVector("BST inorder before insert", InorderTraversal(root));

    // Search for one present value and one absent value.
    std::cout << "search 6: " << (SearchBst(root, 6) != nullptr ? "found" : "not found") << "\n";
    std::cout << "search 10: " << (SearchBst(root, 10) != nullptr ? "found" : "not found") << "\n";

    // Insert two new values and show the sorted inorder order again.
    root = InsertIntoBst(root, 1);
    root = InsertIntoBst(root, 9);
    PrintVector("BST inorder after insert", InorderTraversal(root));

    // Release the demo BST memory.
    DeleteTree(root);
}

/**
 * @brief Demonstrates max-heap and min-heap behavior.
 *
 * Role:
 * - Show repeated best-element extraction with `priority_queue`.
 *
 * Input:
 * - No external input. Uses fixed heap values.
 *
 * Output:
 * - No return value.
 * - Prints pop order for a max-heap and a min-heap built from the same values.
 */
void DemoHeaps() {
    // Push the same values into a max-heap and a min-heap.
    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (int value : {7, 2, 9, 1, 5}) {
        max_heap.push(value);
        min_heap.push(value);
    }

    // Drain both heaps to show their extraction order.
    PrintVector("max-heap pop order", DrainMaxHeap(max_heap));
    PrintVector("min-heap pop order", DrainMinHeap(min_heap));
}

} // namespace

/**
 * @brief Runs all demonstrations for trees, BSTs, and heaps.
 *
 * Role:
 * - Serve as the executable entrypoint for this topic's examples.
 *
 * Input:
 * - No command-line input is required.
 *
 * Output:
 * - Returns `0` on successful completion.
 * - Prints traversal, BST, and heap demos.
 */
int main() {
    // Print the topic heading.
    std::cout << "Topic 8: Trees, BST, and Heap\n\n";

    // Run the traversal demonstration.
    DemoTreeTraversals();
    std::cout << '\n';

    // Run the BST operation demonstration.
    DemoBstOperations();
    std::cout << '\n';

    // Run the heap demonstration.
    DemoHeaps();
    return 0;
}
