#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    bool isThreaded;
    TreeNode(int x) {
        val = x;
        left = right = NULL;
        isThreaded = false;
    }
};

class ThreadedBinaryTree {
public:
    TreeNode *root;
    ThreadedBinaryTree() {
        root = NULL;
        prevNode = NULL;
    }

    /* ---------- 1. Normal BST Insert ---------- */
    TreeNode* insertBST(TreeNode *node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->val)
            node->left = insertBST(node->left, val);
        else
            node->right = insertBST(node->right, val);
        return node;
    }
    void insert(int val) {
        root = insertBST(root, val);
    }

    /* ---------- 2. Convert into Threaded Tree ---------- */
    TreeNode *prevNode;
    TreeNode* createThreaded(TreeNode *node) {
        if (!node) return NULL;

        createThreaded(node->left);

        if (prevNode && prevNode->right == NULL) {
            prevNode->right = node;
            prevNode->isThreaded = true;
        }
        prevNode = node;

        createThreaded(node->right);
        return node;
    }

    /* ---------- 3. Insert in Already Threaded Tree ---------- */
    TreeNode* insertThreaded(TreeNode *root, int val) {
        TreeNode *parent = NULL, *curr = root;

        // Find the parent under inorder-threaded structure
        while (curr) {
            parent = curr;
            if (val < curr->val) {
                if (!curr->left) break;
                curr = curr->left;
            } else {
                if (curr->isThreaded) break;
                curr = curr->right;
            }
        }

        TreeNode *newNode = new TreeNode(val);
        if (!parent) return newNode;

        if (val < parent->val) {
            newNode->left = NULL;
            newNode->right = parent;
            newNode->isThreaded = true;
            parent->left = newNode;
        }
        else {
            if (parent->isThreaded) {
                newNode->right = parent->right;
                newNode->isThreaded = true;
            }
            parent->right = newNode;
            parent->isThreaded = false;
        }
        return root;
    }

    /* ---------- 4. Inorder Traversal (Without Recursion/Stack) ---------- */
    TreeNode* leftmost(TreeNode *node) {
        while (node && node->left) node = node->left;
        return node;
    }
    void inorder(TreeNode *root) {
        TreeNode* curr = leftmost(root);
        while (curr) {
            cout << curr->val << " ";
            if (curr->isThreaded) curr = curr->right;
            else curr = leftmost(curr->right);
        }
    }
};

int main() {
    ThreadedBinaryTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(2);
    t.insert(7);

    // Convert to threaded
    t.prevNode = NULL;
    t.createThreaded(t.root);

    cout << "Inorder before threaded insertion: ";
    t.inorder(t.root);  // 2 5 7 10 15
    cout << endl;

    // Insert into threaded tree
    t.root = t.insertThreaded(t.root, 6);
    t.root = t.insertThreaded(t.root, 12);

    cout << "Inorder after threaded insertion: ";
    t.inorder(t.root);  // 2 5 6 7 10 12 15
    cout << endl;
}
