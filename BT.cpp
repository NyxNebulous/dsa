#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    Node *left, *right;
    int data;
    Node(int x) : data(x), left(NULL), right(NULL) {}
};

class BST
{
public:
    Node *root;

    BST() { root = NULL; }

    void insert(int val)
    {
        root = insertRec(root, val);
    }

    Node *insertRec(Node *node, int val)
    {
        if (!node)
            return new Node(val);
        if (val < node->data)
            node->left = insertRec(node->left, val);
        else
            node->right = insertRec(node->right, val);
        return node;
    }

    void insertIterative(int val)
    {
        Node *newNode = new Node(val);
        if (!root)
        {
            root = newNode;
            return;
        }

        Node *curr = root;
        while (true)
        {
            if (val < curr->data)
            {
                if (!curr->left)
                {
                    curr->left = newNode;
                    break;
                }
                curr = curr->left;
            }
            else
            {
                if (!curr->right)
                {
                    curr->right = newNode;
                    break;
                }
                curr = curr->right;
            }
        }
    }

    Node *buildTreeLevelOrder()
    {
        int x;
        cout << "Enter root (-1 for NULL): ";
        cin >> x;
        if (x == -1)
            return NULL;

        Node *root = new Node(x);
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();

            int leftVal, rightVal;
            cout << "Left of " << temp->data << " (-1 for NULL): ";
            cin >> leftVal;
            if (leftVal != -1)
            {
                temp->left = new Node(leftVal);
                q.push(temp->left);
            }

            cout << "Right of " << temp->data << " (-1 for NULL): ";
            cin >> rightVal;
            if (rightVal != -1)
            {
                temp->right = new Node(rightVal);
                q.push(temp->right);
            }
        }
        return root;
    }

    Node *buildFromPreIn(vector<int> &pre, vector<int> &in)
    {
        int preIndex = 0;
        return buildTreeRec(pre, in, preIndex, 0, in.size() - 1);
    }

private:
    Node *buildTreeRec(vector<int> &pre, vector<int> &in, int &idx, int inStart, int inEnd)
    {
        if (inStart > inEnd)
            return NULL;

        Node *node = new Node(pre[idx++]);

        if (inStart == inEnd)
            return node;

        int pos = inStart;
        while (pos <= inEnd && in[pos] != node->data)
            pos++;

        node->left = buildTreeRec(pre, in, idx, inStart, pos - 1);
        node->right = buildTreeRec(pre, in, idx, pos + 1, inEnd);
        return node;
    }

public:
    void inorder(Node *node)
    {
        if (!node)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void preorder(Node *node)
    {
        if (!node)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void levelorder(Node *node)
    {
        if (!node)
            return;
        queue<Node *> q;
        q.push(node);
        while (!q.empty())
        {
            Node *t = q.front();
            q.pop();
            cout << t->data << " ";
            if (t->left)
                q.push(t->left);
            if (t->right)
                q.push(t->right);
        }
    }

    bool isBST(Node *root, int minVal, int maxVal)
    {
        if (root == NULL)
            return true;

        if (root->data <= minVal || root->data >= maxVal)
            return false;

        return isBST(root->left, minVal, root->data) &&
               isBST(root->right, root->data, maxVal);
    }

    bool isValidBST(Node *root)
    {
        return isBST(root, -1000000000, 1000000000);
    }
};

int main()
{
    BST tree;

    // === Example 1: Insert values like a normal BST ===
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insertIterative(12);
    tree.insertIterative(20);

    cout << "Inorder Traversal: ";
    tree.inorder(tree.root); // 5 10 12 15 20
    cout << "\n";

    // === Example 2: Build using Preorder + Inorder ===
    vector<int> pre = {10, 5, 2, 7, 15, 12, 20};
    vector<int> in = {2, 5, 7, 10, 12, 15, 20};
    tree.root = tree.buildFromPreIn(pre, in);
    cout << "Tree Built from Traversals (Inorder): ";
    tree.inorder(tree.root); // Sorted output
    cout << "\n";

    // === Example 3: Level Order Build ===
    // tree.root = tree.buildTreeLevelOrder();
    // cout << "Level order after input: ";
    // tree.levelorder(tree.root); cout << "\n";

    return 0;
}