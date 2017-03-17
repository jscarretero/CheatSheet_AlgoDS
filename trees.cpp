#include <iostream>
#include <vector>
#include <list>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode (int data) {
    Node* n = new Node;
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

Node* insert (Node* root, int data) {
    if (root == NULL)  return newNode(data);
    if (data > root->data) {
        Node* newRightTree = insert(root->right, data);
        root->right = newRightTree;
    } else {
        Node* newLeftTree = insert(root->left, data);
        root->left = newLeftTree;
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

/* ====================================Minimum Depth of a Tree====================================*/
// http://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
int minDepth(Node* root) {
    if (root == NULL) return 0;
    if (!root->left)  return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    return 1 + min ( minDepth(root->left), minDepth(root->right) );
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

/* ===========================Height of a Tree (max Depth) =======================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
int height (Node* root) {
    if (root == NULL) return 0;
    return 1 + max ( height(root->left), height(root->right) );
}

/* ==================================== Size of a Tree ===========================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/
int size(Node* root) {
    if (root == NULL) return 0;
    return 1 + size(root->left) + size(root->right);
}

/* ===============================Identical Trees?================================================*/
// http://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
bool identical (Node* t1, Node* t2) {
    if (!t1) return !t2;
    if (!t2) return !t1;
    return (t1->data == t2->data) && identical(t1->left, t2->left) &&
                                     identical(t1->right, t2->right);
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

/* =========================================Count Leaves==========================================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/

int leaves (Node* root) {
    if (root == NULL) return 0;
    if (!root->left && !root->right) return 1;
    return leaves(root->left) + leaves(root->right);
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

/* ======================================== Path Sum==============================================*/
// http://www.geeksforgeeks.org/root-to-leaf-path-sum-equal-to-a-given-number/

bool hasPathSum (Node* root, int s, int acc) {
    if (root == NULL) return false;
    if (!root->left && !root->right) return (s == acc + root->data);
    return hasPathSum(root->left, s, acc + root->data) ||
           hasPathSum(root->right, s, acc + root->data) ;
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

/* ================Construct Tree from given Inorder and Preorder traversals =====================*/
// http://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/
// Assuming not repeated elements

Node* toTreeFromInorderPreorder(vector<int>& inorder, vector<int>& preorder, int s, int e, int& p)
{
    if (s > e) return NULL;

    Node* root = newNode(preorder[p]);
    p++;

    // Find element in in-order traversal
    int i;
    for (i = s; i <= e; i++) {
        if (inorder[i] == root->data) break;
    }

    root->left  = toTreeFromInorderPreorder (inorder, preorder, s, i - 1, p);
    root->right = toTreeFromInorderPreorder (inorder, preorder, i + 1, e, p);
    return root;
}

/* ===========================Print Left View of a Binary Tree====================================*/
// http://www.geeksforgeeks.org/print-left-view-binary-tree/
// TIP: The left view contains all nodes that are first nodes in their levels

void leftView(Node* root, int& max_lev, int level) {
    if (!root) return;
    if (level > max_lev) {
        max_lev = level;
        cout << root->data << " ";
    }
    leftView(root->left,  max_lev, level+1);
    leftView(root->right, max_lev, level+1);
}

/* =========================Diameter of a Binary Tree=============================================*/
// http://www.geeksforgeeks.org/diameter-of-a-binary-tree/
// The diameter of a tree T is the largest of the following quantities:
//   * the diameter of T’s left subtree
//   * the diameter of T’s right subtree
//   * the longest path between leaves that goes through the root of T (this can be computed from
//     the heights of the subtrees of T)

int diameter (Node* root) { // Time Complexity: O(N^2) because height is calculated many times
    if (!root) return 0;
    int dl = diameter(root->left);
    int dr = diameter(root->right);
    int hl = height(root->left);
    int hr = height(root->right);
    return max(dl, max (dr, hl+hr+1));
}

int diameterFast (Node* root, int& h) {
    if (!root) { h = 0; return 0; }

    int hr = 0; int hl = 0;
    int dl = diameterFast(root->left,  hl);
    int dr = diameterFast(root->right, hr);
    h = max(hl, hr) + 1;
    return max(hl+hr+1, max(dl,dr));
}

/* =========================Convert a given tree to its Sum Tree==================================*/
// http://www.geeksforgeeks.org/convert-a-given-tree-to-sum-tree/
int sumTree(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) {
        int sum = root->data;
        root->data = 0;
        return sum;
    }
    int sl = sumTree(root->left);
    int sr = sumTree(root->right);
    int sum = root->data + sl + sr;
    root->data =  sl + sr;
    return sum;
}

/* ============================== Find k-th smallest element in BST ==============================*/
// http://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/
// Tip: do in-order traversal and track current visited node

Node* kSmallestNode (Node* root, int k, int& curr) {  //curr starts at 0
    if (!root) return NULL;
    Node* res = kSmallestNode(root->left, k, curr);
    if (res) return res;
    curr++;
    if (curr == k) return root;
    return kSmallestNode(root->right, k, curr);
}

/* ==========================Lowest Common Ancestor in a Binary Tree==============================*/
// http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

bool inTree(Node* root, int v) {
    if (!root) return false;
    if (root->data == v) return true;
    return inTree(root->left, v) || inTree(root->right, v);
}

Node* lca (Node* root, int n1, int n2) {
    if (!root) return NULL;

    if ((root->data == n1) || (root->data == n2)) {
        // Check the other node exists
        if (!inTree(root, n1) || !inTree(root, n2)) return NULL;
        return root;
    }

    bool in1 = inTree(root->left, n1);
    bool in2 = inTree(root->left, n2);
    if (in1  &&  in2) return lca(root->left, n1, n2);
    if (!in1 && !in2) return lca(root->right, n1, n2);
    return root;
}

/* ================================Lowest Common Ancestor in a BST================================*/
// http://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/

Node* lca_bst (Node* root, int n1, int n2) {
    if (!root) return NULL;

    if (root->data == n1) {
        // Check the other node exists
        if (n2 > n1) {
            if (inTree(root->right, n2)) return root;
            else                         return NULL;
        } else if (n2 < n1) {
            if (inTree(root->left, n2))  return root;
            else                         return NULL;
        } else                           return root;
    } else if (root->data == n2) {
        // Check the other node exists
        if (n1 > n2) {
            if (inTree(root->right, n1)) return root;
            else                         return NULL;
        } else if (n1 < n2) {
            if (inTree(root->left, n1))  return root;
            else                         return NULL;
        } else                           return root;

    }

    if ((n1 < root->data) && (n2 < root->data))   return lca_bst(root->left,  n1, n2);
    if ((n1 > root->data) && (n2 > root->data))   return lca_bst(root->right, n1, n2);
    return root;
}

/* =======================================Is Subtree==============================================*/
// http://www.geeksforgeeks.org/check-if-a-binary-tree-is-subtree-of-another-binary-tree/
// http://www.geeksforgeeks.org/check-binary-tree-subtree-another-binary-tree-set-2/
bool isSubtree(Node* t1, Node* t2) { //t2 subtree,  // TIme Complexity: O(t1*t2)
    if (!t2) return true;
    if (!t1) return !t2;

    if (identical(t1, t2)) return true;
    else                   return isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
}

/*
 We have discussed a O(ST) solution for this problem. In this post a O(T) solution is discussed.
 The idea is based on the fact that inorder and preorder/postorder uniquely identify a binary tree.
 Tree S is a subtree of T if both inorder and preorder traversals of S arw substrings of
 inorder and preorder traversals of T respectively. :)
 SPACE COMPLEXITY O(S+T) = O(T)

Following are detailed steps.
  1) Find inorder and preorder traversals of T, store them in two auxiliary arrays inT[] and preT[].
  2) Find inorder and preorder traversals of S, store them in two auxiliary arrays inS[] and preS[].
  3) If inS[] is a subarray of inT[] and preS[] is a subarray preT[], then S is a subtree of T. Else
     not.
     For step 3, use pattern matching algorithm. Specifically KMP algorithm for O(T) complexity
     rather than O(S*T) of naive ones
*/

/* ======================= Remove BST keys outside the given range ===============================*/
// http://www.geeksforgeeks.org/remove-bst-keys-outside-the-given-range/

Node* removeOutsideRange (Node* root, int min, int max) {
    if (!root) return NULL;

    root->left  = removeOutsideRange(root->left, min, max);
    root->right = removeOutsideRange(root->right, min, max);

    if (root->data < min) {
        Node* tmp = root->right;
        delete root;
        return tmp;
    } else if (root->data > max) {
        Node* tmp = root->left;
        delete root;
        return tmp;
    }
    return root;
}

/* =========================Boundary Traversal of binary tree=====================================*/
// http://www.geeksforgeeks.org/boundary-traversal-of-binary-tree/
// Decompose problem in: 1) print left side without last leave
//                       2) print leaves left-to-right
//                       3) print right side bottom-up (stack) without root

void printLeaves (Node* root) {
    if (!root) return;
    if (!root->left && !root->right) cout << root->data << " ";
    printLeaves(root->left);
    printLeaves(root->right);
}

void printLeft (Node* root) {
    if (!root) return;
    if (!root->left && !root->right) return;
    cout << root->data << " ";
    printLeft(root->left);
}

void printRight (Node* root) {
    if (!root) return;
    if (!root->left && !root->right) return;
    printRight(root->right);
    cout << root->data << " ";
}

void boundary (Node* root) {
    if (root == NULL);
    printLeft(root);
    printLeaves(root);
    printRight(root->right); //to avoid printing root again
}

/* ==========================Largest BST subtree of Normal Tree==================================*/
// http://www.geeksforgeeks.org/find-the-largest-subtree-in-a-tree-that-is-also-a-bst/
Node* largestBST (Node* root, int& max_size) {
    lastNode = NULL; //reinitialize var from isBST
    if (!root)       { max_size = 0;        return NULL; }
    if (isBST(root)) { max_size=size(root); return root; }
    int sl, sr;
    Node* ll = largestBST(root->left,  sl);
    Node* lr = largestBST(root->right, sr);
    max_size = max(sl, sr);
    if (sl > sr) return ll;
    else         return lr;
}

/* ========================Level order traversal in spiral form===================================*/
// http://www.geeksforgeeks.org/level-order-traversal-in-spiral-form/
// TIP: print a level in a given direction
void printLevel (Node* root, int l, bool left_to_right) {
    if (!root) return;
    if (l == 1) { cout << root->data << " "; return; }
    if (left_to_right) {
        printLevel(root->left,  l-1, left_to_right);
        printLevel(root->right, l-1, left_to_right);
    } else {
        printLevel(root->right, l-1, left_to_right);
        printLevel(root->left,  l-1, left_to_right);
    }
}

void spiral (Node* root) {
    int levels = height(root);
    bool left_to_right = false;
    for (int i = 1; i <= levels; i++) {
        printLevel(root, i, left_to_right);
        left_to_right = !left_to_right;
    }
}

/* ===========================Tree to Double-Linked List==========================================*/
// http://www.geeksforgeeks.org/in-place-convert-a-given-binary-tree-to-doubly-linked-list/
void tree2List(Node* root, Node*& head, Node*& last_visited) {
    if (!root) return;

//    if (!root->left && !root->right) {
//        if (!head)        head = root;
//        if (last_visited) last_visited->right = root;
//        root->left   = last_visited;
//        last_visited = root;
//    } else {
        tree2List(root->left, head, last_visited);
        if (!head)        head = root;
        if (last_visited) last_visited->right = root;
        root->left = last_visited;
        last_visited = root;
        tree2List(root->right, head, last_visited);
//    }
}

/* ===============================Balance BST=====================================================*/
// NOTE:  O(N log N) with O(1) space
//        O(N)       with O(N) space if we were using arrays (direct access)

Node* DLLToBalancedBST (Node* root, int s) {
    if (!root  || !s) return NULL;
    if (s == 1)       return root; // remove?

    // Split list in half based on size 's', element at the middle does not go to any list! O(N)
    Node* l2   = root;
    Node* prev = NULL;
    for (int h = (s/2)-1; h >= 0; h--) {
        prev = l2;
        l2 = l2 ->right;
    }

    Node* tmp = l2->right;
    prev->right = NULL;
    l2->left    = NULL;
    l2->right   = NULL;
    tmp->left   = NULL;

    l2->left  = DLLToBalancedBST(root, s/2);
    l2->right = DLLToBalancedBST(tmp,  (s%2?s/2:(s/2)-1));
    return l2;
}

int sizeDLL (Node* root) {
    Node* tmp = root;
    int   res = 0;
    while (tmp != NULL) {
        res++;
        tmp = tmp->right;
    }
    return res;
}

Node* balanceBST (Node* root) {
    // Convert tree to DLL list
    Node* head = NULL;
    Node* last_visited = NULL;
    tree2List(root, head, last_visited);

    // Compute size
    int s = sizeDLL(head);

    //Call function
    return DLLToBalancedBST(head, s);
}

/* ==========================List of Nodes at Each Depth==========================================*/
// From 'Cracking the Coding Interview'
void listNodesPerDepth (Node* root, vector<list<Node*> >& res , int h) {
    if (!root) return;
    if (res.size() < h) res.push_back(list<Node*>());
    res[h-1].push_back(root);
    listNodesPerDepth(root->left,  res, h+1);
    listNodesPerDepth(root->right, res, h+1);
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void arrayToTree_example () {
    vector<int> v {1,2,3,4,5,6,7}; // -std=c++11
    cout << "Tree is: ";
    printPreOrder ( arrayToTree(v, 0, v.size() - 1) );
    cout << endl;
}
void isBST_example() {
    Node* root        = newNode(4);
    root->left        = newNode(2);
    root->right       = newNode(5);
    root->left->left  = newNode(1);
    root->left->right = newNode(3);
    cout << "Tree is BST: " << isBST(root) << endl;
    deleteTree(root);
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
    deleteTree(root);
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
    deleteTree(root);
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
    deleteTree(root);
}
void minDepth_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Minimum tree depth is: " << minDepth(root) << endl;
    deleteTree(root);
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
    deleteTree(root);
    deleteTree(root2);
}
void height_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Height of tree is: " << height(root) << endl;
    deleteTree(root);
}
void size_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Size of tree is: " << size(root) << endl;
    deleteTree(root);
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
    deleteTree(root1);
    deleteTree(root2);
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
    deleteTree(root);
}
void leaves_example() {
    Node *root             = newNode(1);
    root->left             = newNode(2);
    root->right            = newNode(3);
    root->left->left       = newNode(4);
    root->left->right      = newNode(5);
    root->right->left      = newNode(6);
    root->left->left->left = newNode(7);
    cout << "Number of leaves is: " << leaves(root) << endl;
    deleteTree(root);
}
void printDistanceK_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(8);

    cout << "Nodes at distance 2 are: ";
    printDistanceK(root,2,0);
    cout << endl;
    deleteTree(root);
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
    deleteTree(root);
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
    deleteTree(root);
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
    deleteTree(root);
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
    deleteTree(T);
}
void toTreeFromInorderPreorder_example() {
    vector<int> in  = {3,4,5,7,8,10};
    vector<int> pre = {5,3,4,10,8,7};
    int ptr = 0;
    Node *root = toTreeFromInorderPreorder(in, pre, 0, in.size() - 1, ptr);
    cout << "Tree from inorder and preorder is (postorder traversal): ";
    printPostOrder(root);
    cout << endl;
}
void leftView_example() {
    Node *root         = newNode(12);
    root->left         = newNode(10);
    root->right        = newNode(30);
    root->right->left  = newNode(25);
    root->right->right = newNode(40);
    int maxLevel = -1;
    cout << "Left view is: ";
    leftView(root, maxLevel, 0);
    cout << endl;
    deleteTree(root);
}
void diameter_example() {
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    int h = 0;
    cout << "Diameter is: " << diameterFast(root, h) << endl;
    deleteTree(root);
}
void sumTree_example() {
    Node* root         = newNode(10);
    root->left         = newNode(-2);
    root->right        = newNode(6);
    root->left->left   = newNode(8);
    root->left->right  = newNode(-4);
    root->right->left  = newNode(7);
    root->right->right = newNode(5);

    sumTree(root);
    cout << "SumTree is: ";
    printPreOrder(root);
    cout << endl;
    deleteTree(root);
}
void kSmallestNode_example() {
    Node* root               = newNode(10);
    root->left               = newNode(8);
    root->left->left         = newNode(1);
    root->left->right        = newNode(7);
    root->right              = newNode(15);
    root->right->left        = newNode(13);
    root->right->left->left  = newNode(12);
    root->right->left->right = newNode(14);
    root->right->right       = newNode(20);

    int curr_node = 0;
    Node* res = kSmallestNode(root, 6, curr_node);
    cout << "K smallest node (6th) is: " << res->data << endl;
    deleteTree(root);
}
void lca_example() {
    Node * root        = newNode(1);
    root->left         = newNode(2);
    root->right        = newNode(3);
    root->left->left   = newNode(4);
    root->left->right  = newNode(5);
    root->right->left  = newNode(6);
    root->right->right = newNode(7);
    //cout << "LCA(4, 5) of tree is: " << lca(root, 4, 5)->data << endl;
    //cout << "LCA(4, 6) of tree is: " << lca(root, 4, 6)->data << endl;
    //cout << "LCA(3, 4) of tree is: " << lca(root, 3, 4)->data << endl;
    //cout << "LCA(2, 4) of tree is: " << lca(root, 2, 4)->data << endl;
    cout << "LCA(6, 7)  of tree is: " << lca(root, 6, 7)->data << endl;
    deleteTree(root);
}

void lca_bst_example() {
    Node *root               = newNode(20);
    root->left               = newNode(8);
    root->right              = newNode(22);
    root->left->left         = newNode(4);
    root->left->right        = newNode(12);
    root->left->right->left  = newNode(10);
    root->left->right->right = newNode(14);

    Node* res = NULL;
    int n1 = 10, n2 = 14;
    res= lca_bst(root, n1, n2);
    cout << "LCA(10,14) of BST is: " << res->data << endl;


    n1 = 14, n2 = 8;
    res = lca_bst(root, n1, n2);
    cout << "LCA(14,8)  of BST is: " << res->data << endl;

    n1 = 10, n2 = 22;
    res = lca_bst(root, n1, n2);
    cout << "LCA(10,22) of BST is: " << res->data << endl;
    deleteTree(root);
}
void isSubtree_example() {
    Node *T               = newNode(26);
    T->right              = newNode(3);
    T->right->right       = newNode(3);
    T->left               = newNode(10);
    T->left->left         = newNode(4);
    T->left->left->right  = newNode(30);
    T->left->right        = newNode(6);

    Node *S           = newNode(10);
    S->right          = newNode(6);
    S->left           = newNode(4);
    S->left->right    = newNode(30);

    cout << "S is subtree of T: " << isSubtree(T,S) << endl;
    deleteTree(T);
    deleteTree(S);
}
void removeOutsideRange_example() {
    Node* root = NULL;
    root = insert(root, 6);
    root = insert(root, -13);
    root = insert(root, 14);
    root = insert(root, -8);
    root = insert(root, 15);
    root = insert(root, 13);
    root = insert(root, 7);

    cout << "After removing nodes outside range: ";
    printInOrder(removeOutsideRange(root, -10, 13));
    cout << endl;
    deleteTree(root);
}
void boundary_example() {
    Node *root                = newNode(20);
    root->left                = newNode(8);
    root->left->left          = newNode(4);
    root->left->right         = newNode(12);
    root->left->right->left   = newNode(10);
    root->left->right->right  = newNode(14);
    root->right               = newNode(22);
    root->right->right        = newNode(25);

    cout << "Boundary of tree is: ";
    boundary(root);
    cout << endl;
    deleteTree(root);
}
void  largestBST_example() {
    Node *root                = newNode(50);
    root->left                = newNode(10);
    root->right               = newNode(60);
    root->left->left          = newNode(5);
    root->left->right         = newNode(20);
    root->right->left         = newNode(55);
    root->right->left->left   = newNode(45);
    root->right->right        = newNode(70);
    root->right->right->left  = newNode(65);
    root->right->right->right = newNode(80);

    int max_size;
    Node* res = largestBST(root, max_size);
    cout << "Largest BST size is " << max_size << " and subtree is: ";
    printPreOrder(res);
    cout << endl;
    deleteTree(root);
}
void spiral_example() {
    Node *root         = newNode(1);
    root->left         = newNode(2);
    root->right        = newNode(3);
    root->left->left   = newNode(7);
    root->left->right  = newNode(6);
    root->right->left  = newNode(5);
    root->right->right = newNode(4);
    cout << "Spiral Order traversal of binary tree is: ";
    spiral(root);
    cout << endl;
    deleteTree(root);
}
void tree2List_example() {
    Node *root        = newNode(10);
    root->left        = newNode(12);
    root->right       = newNode(15);
    root->left->left  = newNode(25);
    root->left->right = newNode(30);
    root->right->left = newNode(36);

    Node* head = NULL; Node* last_visited = NULL;
    tree2List(root, head, last_visited );
    cout << "List of BST is: ";
    Node* tmp = head;
    while (tmp != NULL){
        cout << tmp->data << " ";
        Node* todelete = tmp;
        tmp = tmp->right;
        delete todelete;
    } cout << endl;
}
void balanceBST_example() {
    Node* root = NULL;
    root = insert(root, 6);
    root = insert(root, -13);
    root = insert(root, 14);
    root = insert(root, -8);
    root = insert(root, 15);
    root = insert(root, 13);
    root = insert(root, 7);

    Node* res = balanceBST(root);
    cout << "Balanced BST is: ";
    printPreOrder(res);
    cout << endl;;
    deleteTree(root);
}
void listNodesPerDepth_example() {
    Node* root = NULL;
    root = insert(root, 6);
    root = insert(root, -13);
    root = insert(root, 14);
    root = insert(root, -8);
    root = insert(root, 15);
    root = insert(root, 13);
    root = insert(root, 7);

    vector<list<Node*> > res;
    listNodesPerDepth(root, res , 1);
    cout << "Lists of nodes per level are: " << endl;
    for (auto& l: res ) {
        cout << "\t";
        for (auto& e: l) {
            cout << e->data << " ";
        }
        cout << endl;
    }
    deleteTree(root);

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
    toTreeFromInorderPreorder_example();
    leftView_example();
    diameter_example();
    sumTree_example();
    kSmallestNode_example();
    lca_example();
    lca_bst_example();
    isSubtree_example();
    removeOutsideRange_example();
    boundary_example();
    largestBST_example();
    spiral_example();
    tree2List_example();
    balanceBST_example();
    listNodesPerDepth_example();
}

/* =======================================TODO====================================================*/
// http://www.geeksforgeeks.org/binary-tree-to-binary-search-tree-conversion/
// http://www.geeksforgeeks.org/find-if-there-is-a-triplet-in-bst-that-adds-to-0/
// http://www.geeksforgeeks.org/merge-two-bsts-with-limited-extra-space/
// http://www.geeksforgeeks.org/fix-two-swapped-nodes-of-bst/
// http://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
// http://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-
//        linked-representation/