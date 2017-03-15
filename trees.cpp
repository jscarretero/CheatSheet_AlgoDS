#include <iostream>
#include <vector>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent; // Normally unused, just in case
};

Node* newNode (int data) {
    Node* n = new Node;
    n->data = data;
    n->left = n->right = n->parent = NULL;
    return n;
}

Node* insert (Node* root, int data) {
    if (root == NULL)  return newNode(data);
    if (data > root->data) {
        Node* newRightTree = insert(root->right, data);
        root->right = newRightTree;
        newRightTree->parent = root;
    } else {
        Node* newLeftTree = insert(root->left, data);
        root->left = newLeftTree;
        newLeftTree->parent = root;
    }
    return root;
}

void deleteTree (Node* root) {
    if (root == NULL)  return;
    if (root->left)    deleteTree(root->left);
    if (root->right)   deleteTree(root->right);
    delete root;
}

void printPreOrder (Node* root) {
    if (root == NULL)  return;
    cout << root->data << " ";
    printPreOrder (root->left);
    printPreOrder (root->right);
}

void printPostOrder (Node* root) {
    if (root == NULL)  return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->data << " ";
}

void printInOrder (Node* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

/* ============================== Sorted Array to Balanced BST ===================================*/
// http://www.geeksforgeeks.org/sorted-array-to-balanced-bst/

Node* arrayToTree (vector<int>& v, int l, int r) {
    if (l  > r)   return NULL;
    if (l == r)   return newNode(v[l]);

    int h = (l + r) / 2;  //l + ((r - l) / 2)
    Node* root  = newNode(v[h]);
    root->left  = arrayToTree(v, l, h-1);
    root->right = arrayToTree(v, h+1, r);
    return root;
}

void arrayToTree_example () {
    vector<int> v {1,2,3,4,5,6,7}; // -std=c++11
    cout << "Tree is: ";
    printPreOrder ( arrayToTree(v, 0, v.size() - 1) );
    cout << endl;
}

/*================================= Check if tree is BST ========================================*/
// htp://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

Node* lastNode = NULL;

bool isBST (Node* root) {
    if (root == NULL)        return true;
    if (!isBST(root->left))  return false;

    if ((lastNode != NULL) && (lastNode->data >= root->data)) return false;

    lastNode = root;
    return isBST(root->right);
}

void isBST_example() {
    Node* root        = newNode(4);
    root->left        = newNode(2);
    root->right       = newNode(5);
    root->left->left  = newNode(1);
    root->left->right = newNode(3);
    cout << "Tree is BST: " << isBST(root) << endl;
}

/* =============================== Inorder successor in BST ======================================*/
// http://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/

Node* inorderSuccessor(Node* root, Node* n) {
    if (root == NULL)  return NULL;

    Node* tmp = root;
    Node* succ = NULL;
    while (tmp != NULL) {
        if (n->data > tmp->data) {
            tmp = tmp->right;
        } else if (n->data < tmp->data) {
            succ = tmp;
            tmp = tmp->left;
        } else if (n->data == tmp->data) {
            break;
        }
    }
    return succ;
}

void inorderSuccessor_example() {
    Node* root = NULL, *temp;

    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 22);
    root = insert(root, 4);
    root = insert(root, 12);
    root = insert(root, 10);
    root = insert(root, 14);
    temp = root->left->right->right;

    Node* succ =  inorderSuccessor(root, temp); //tmp is 14
    if (succ !=  NULL)
        printf("Inorder Successor of %d is %d \n", temp->data, succ->data);
    else
        printf("Inorder Successor doesn't exit\n");

}

/* ===============================  Is a Tree Symmetric (Mirror Image) ===========================*/
// http://www.geeksforgeeks.org/symmetric-tree-tree-which-is-mirror-image-of-itself/

bool isSymmetric (Node* t1, Node* t2) {
    if ((t1 == NULL) && (t2 == NULL))  return true;
    else if (t1 && t2 && (t1->data == t2->data)) {
        return isSymmetric(t1->left, t2->right) && isSymmetric(t1->right, t2->left);
    }
    else return false;
}

bool isSymmetric_main (Node* root) {
    if (root != NULL)  return isSymmetric(root->left, root->right);
    else               return true;
}

bool isSymmetric_example () {
    Node *root         = newNode(1);
    root->left         = newNode(2);
    root->right        = newNode(2);
    root->left->left   = newNode(3);
    root->left->right  = newNode(4);
    root->right->left  = newNode(4);
    root->right->right = newNode(3);

    cout << "Tree is symmetric: " << isSymmetric_main(root) << endl;;
}


/* ============================================ Mirror a Tree ====================================*/
//http://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/

Node* mirrorTree(Node* root) {
    if (root == NULL)  return NULL;
    Node* tmpLeft  = mirrorTree(root->left);
    Node* tmpRight = mirrorTree(root->right);
    root->left = tmpRight;
    root->right = tmpLeft;
    return root;
}

void mirrorTree_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Mirrored tree is: ";
    printPreOrder(mirrorTree(root));
    cout << endl;
}

/* ====================================Minimum Depth of a Tree====================================*/
// http://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
int minDepth(Node* root) {
    if (root == NULL) return 0;
    if (!root->left)  return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    return 1 + min ( minDepth(root->left), minDepth(root->right) );
}

void minDepth_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Minimum tree depth is: " << minDepth(root) << endl;
}

/* =========================Print Common Nodes in Two BST=========================================*/
// http://www.geeksforgeeks.org/print-common-nodes-in-two-binary-search-trees/

/* Method 1 (Simple Solution)
 *   A simple way is to one by once search every node of first tree in second tree. Time complexity
 *   of this solution is O(m * h) where m is number of nodes in first tree and
 *   h is height of second tree.
 *
 * Method 2 (Linear Time) We can find common elements in O(n) time.
 *   1) Do inorder traversal of first tree and store the traversal in an auxiliary array ar1[].
 *   2) Do inorder traversal of second tree and store the traversal in an auxiliary array ar2[]
 *   3) Find intersection of ar1[] and ar2[]. See this for details.
 *
 * Time complexity of this method is O(m+n) where m and n are number of nodes in first and second
 * tree respectively.
 * This solution requires O(m+n) extra space
*/

void treeToArray(Node* root, vector<Node*>& v) {
    if (root == NULL) return;
    treeToArray(root->left, v);
    v.push_back(root);
    treeToArray(root->right, v);
}

vector<Node*> intersectArrays(vector<Node*>& a1, vector<Node*>& a2) {
    // Pre-condition: a1 and a2 are sorted
    int i1 = 0; int i2 = 0;
    vector<Node*> result;

    while (i1 < a1.size() && i2 < a2.size()) {
        if ( a1[i1]->data > a2[i2]->data) {
            i2++;
        } else if (a1[i1]->data < a2[i2]->data ) {
            i1++;
        } else {
            result.push_back(a1[i1]);
            i1++; i2++;
        }
    }
    return result;
}

vector<Node*> commonNodes (Node* t1, Node* t2) {
    vector<Node*> a1, a2;

    treeToArray(t1, a1);
    treeToArray(t2, a2);

    return intersectArrays(a1, a2);
}

void commonNodes_example() {
    Node *root = insert(NULL, 8);
          root = insert(root, 6);
          root = insert(root, 2);
          root = insert(root, 7);
          root = insert(root, 4);


    Node* root2 = insert(NULL, 5);
                  insert(root2, 9);
                  insert(root2, 7);
                  insert(root2, 4);

    vector<Node*> res = commonNodes (root, root2);
    cout << "Common nodes are: ";
    for (auto& e : res)
        cout << e->data << " ";
    cout << endl;

}

/* ===========================Height of a Tree (max Depth) =======================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
int height (Node* root) {
    if (root == NULL) return 0;
    return 1 + max ( height(root->left), height(root->right) );
}

void height_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Height of tree is: " << height(root) << endl;
}

/* ==================================== Size of a Tree ===========================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/
int size(Node* root) {
    if (root == NULL) return 0;
    return 1 + size(root->left) + size(root->right);
}

void size_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Size of tree is: " << size(root) << endl;
}

/* ===============================Identical Trees?================================================*/
// http://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
bool identical (Node* t1, Node* t2) {
    if (!t1) return !t2;
    if (!t2) return !t1;
    return (t1->data == t2->data) && identical(t1->left, t2->left) &&
                                     identical(t1->right, t2->right);
}

void identical_example() {
    Node *root1        = newNode(1);
    Node *root2        = newNode(1);
    root1->left        = newNode(2);
    root1->right       = newNode(3);
    root1->left->left  = newNode(4);
    root1->left->right = newNode(5);

    root2->left        = newNode(2);
    root2->right       = newNode(3);
    root2->left->left  = newNode(4);
    root2->left->right = newNode(5);
    cout << "Trees are identical: " << identical(root1, root2) << endl;
}

/* ==============================Is tree balanced? ===============================================*/
// http://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
bool isBalanced (Node* root) {
    if (!root) return true;
    int h1 = height(root->left);
    int h2 = height(root->right);
    if ( (h1 == h2) || (h1 + 1 == h2) || (h1 == h2 + 1)) {
        return isBalanced(root->left) && isBalanced(root->right);
    }
    return false;
}

bool isBalancedFast (Node* root, int& h) {
    if (!root) { h= 0; return true; }
    int h1 = 0; int h2 = 0;
    bool is1 = isBalancedFast(root->left,  h1);
    bool is2 = isBalancedFast(root->right, h2);
    h = 1 + max (h1, h2);
    return (is1 && is2 && ((h1 == h2) || (h1 + 1 == h2) || (h1 == h2 + 1)));
}

void isBalanced_example() {
    Node *root             = newNode(1);
    root->left             = newNode(2);
    root->right            = newNode(3);
    root->left->left       = newNode(4);
    root->left->right      = newNode(5);
    root->right->left      = newNode(6);
    root->left->left->left = newNode(7);
    //cout << "Tree is balanced: " << isBalanced(root) << endl;
    int tmp;
    cout << "Tree is balanced: " << isBalancedFast(root, tmp) << endl;
}

/* =========================================Count Leaves==========================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/

int leaves (Node* root) {
    if (root == NULL) return 0;
    if (!root->left && !root->right) return 1;
    return leaves(root->left) + leaves(root->right);
}

void leaves_example() {
    Node *root              = newNode(1);
    root->left             = newNode(2);
    root->right            = newNode(3);
    root->left->left       = newNode(4);
    root->left->right      = newNode(5);
    root->right->left      = newNode(6);
    root->left->left->left = newNode(7);
    cout << "Number of leaves is: " << leaves(root) << endl;
}
/* ========================Print nodes at k distance from root====================================*/
// http://www.geeksforgeeks.org/print-nodes-at-k-distance-from-root/

void printDistanceK (Node* root, int h, int c) {
    if (!root) return;
    if (c == h) cout << root->data << " ";
    else {
        printDistanceK(root->left, h, c+1);
        printDistanceK(root->right, h, c+1);
    }
}

void printDistanceK_example() {
    Node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(8);

    cout << "Nodes at distance 2 are: ";
    printDistanceK(root,2,0);
    cout << endl;
}

/* =============================Root-To-Leaf Paths================================================*/
// http://www.geeksforgeeks.org/given-a-binary-tree-print-all-root-to-leaf-paths/
// http://www.geeksforgeeks.org/sum-numbers-formed-root-leaf-paths/s

void rootToLeafs (Node* root, vector<int>& curr_path) {
    if (root == NULL) return;
    curr_path.push_back(root->data);
    if (!root->left && !root->right) {
        // Print path
        cout << '\t';
        for (auto& e: curr_path)
            cout << e << " ";
        cout << endl;
    }
    else {
        rootToLeafs(root->left, curr_path);
        curr_path.pop_back();
        rootToLeafs(root->right, curr_path);
        curr_path.pop_back();
    }
}

void rootToLeafs_example() {
    Node *root         = newNode(10);
    root->left         = newNode(8);
    root->right        = newNode(2);
    root->left->left   = newNode(3);
    root->left->right  = newNode(5);
    root->right->left  = newNode(12);
    root->right->right = newNode(20);

    vector<int> current_sol;
    cout << "Root to leaf paths are: " << endl;
    rootToLeafs(root, current_sol);
}

/* ======================================== Path Sum==============================================*/
// http://www.geeksforgeeks.org/root-to-leaf-path-sum-equal-to-a-given-number/

bool hasPathSum (Node* root, int s, int acc) {
    if (root == NULL) return false;
    if (!root->left && !root->right) return (s == acc + root->data);
    return hasPathSum(root->left, s, acc + root->data) ||
           hasPathSum(root->right, s, acc + root->data) ;
}

void hasPathSum_example() {
    Node *root        = newNode(10);
    root->left        = newNode(8);
    root->right       = newNode(2);
    root->left->left  = newNode(3);
    root->left->right = newNode(5);
    root->right->left = newNode(2);
    cout << "Tree has a path summing 21: ";
    cout << hasPathSum(root, 21, 0) << endl;;
}

/* =================== Remove all nodes wich don't lie in any path with sum >= k =================*/
// http://www.geeksforgeeks.org/remove-all-nodes-which-lie-on-a-path-having-sum-less-than-k/

Node* removePathsSmaller(Node* root, int k, int s) {
    if (root == NULL) return NULL;
    root->left =  removePathsSmaller(root->left,  k, s + root->data);
    root->right=  removePathsSmaller(root->right, k, s + root->data);
    if ((s + root->data < k) && !root->left && !root->right) {
        delete root;
        return NULL;
    } else {
        return root;
    }
}

void removePathsSmaller_example() {
    int k = 45;
    Node *root                           = newNode(1);
    root->left                           = newNode(2);
    root->right                          = newNode(3);
    root->left->left                     = newNode(4);
    root->left->right                    = newNode(5);
    root->right->left                    = newNode(6);
    root->right->right                   = newNode(7);
    root->left->left->left               = newNode(8);
    root->left->left->right              = newNode(9);
    root->left->right->left              = newNode(12);
    root->right->right->left             = newNode(10);
    root->right->right->left->right      = newNode(11);
    root->left->left->right->left        = newNode(13);
    root->left->left->right->right       = newNode(14);
    root->left->left->right->right->left = newNode(15);

    root = removePathsSmaller(root, k, 0); // k is 45
    cout << "Tree after removing paths smaller than k: ";
    printInOrder(root);
    cout << endl;
}

/* ==============BST with + and - values, print ALL paths which sum to value v====================*/
// Note: path does not necessarily start at root and end in leaf
//Cracking the coding interview book. Problem 4.9

void pathsSumVal (Node* root, int v, vector<int>& curr_path) {
    if (root == NULL) return;

    curr_path.push_back(root->data);

    int acc = 0;
    for (int i = curr_path.size() - 1 ; i >= 0; i--) {
        acc += curr_path[i];
        if (acc == v) {
            // Print path
            cout << "\t";
            for (int l = i; l < curr_path.size(); l++) {
                cout << curr_path[l] << " ";
            }
            cout << endl;
        }
    }
    pathsSumVal(root->left,  v, curr_path);
    pathsSumVal(root->right, v, curr_path);

    curr_path.pop_back();
}

void pathsSumVal_example() {
    Node *T               = newNode(26);
    T->right              = newNode(3);
    T->right->right       = newNode(3);
    T->left               = newNode(10);
    T->left->left         = newNode(4);
    T->left->left->right  = newNode(30);
    T->left->left->left   = newNode(2);
    T->left->right        = newNode(6);
    vector<int> curr_path;
    cout << "All paths which sum to value 16: " << endl;
    pathsSumVal(T, 16, curr_path);
    cout << endl;
}

/* ===============================================================================================*/
int main () {

    arrayToTree_example();
    isBST_example();
    inorderSuccessor_example();
    isSymmetric_example();
    mirrorTree_example();
    minDepth_example();
    commonNodes_example();
    height_example();
    size_example();
    identical_example();
    isBalanced_example();
    leaves_example();
    printDistanceK_example();
    rootToLeafs_example();
    hasPathSum_example();
    removePathsSmaller_example();
    pathsSumVal_example();
}

/* =======================================TODO====================================================*/
// http://www.geeksforgeeks.org/binary-tree-to-binary-search-tree-conversion/
// http://www.geeksforgeeks.org/find-if-there-is-a-triplet-in-bst-that-adds-to-0/
// http://www.geeksforgeeks.org/merge-two-bsts-with-limited-extra-space/
// http://www.geeksforgeeks.org/fix-two-swapped-nodes-of-bst/
// http://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
// http://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-
//        linked-representation/