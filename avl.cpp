#include <iostream>

using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    int height;
    Node(int x) : val(x), left(NULL), right(NULL), height(1) {}
};

class AVL
{
public:
    Node *root = NULL;

    int height(Node *n)
    {
        return n ? n->height : 0;
    }

    int getBalance(Node *n)
    {
        if (!n)
            return 0;
        return height(n->left) - height(n->right);
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node *rotateRight(Node *x)
    {
        Node *y = x->left;
        Node *T = y->right;

        y->right = x;
        x->left = T;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return y;
    }

    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);

        if (key < node->val)
            node->left = insert(node->left, key);
        else if (key > node->val)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int bf = getBalance(node);

        if (bf > 1 && key < node->left->val)
            return rotateRight(node);
        if (bf > 1 && key > node->left->val)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && key < node->right->val)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (bf < -1 && key > node->right->val)
            return rotateLeft(node);

        return node;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (!root)
            return root;

        if (key < root->val)
            root->left = deleteNode(root->left, key);
        else if (key > root->val)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left || !root->right)
            {
                Node *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp; 
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(root->right);
                root->val = temp->val;
                root->right = deleteNode(root->right, temp->val);
            }
        }

        if (!root)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int bf = getBalance(root);


        if (bf > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (bf > 1 && getBalance(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (bf < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (bf < -1 && getBalance(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    Node *minValueNode(Node *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }
};
