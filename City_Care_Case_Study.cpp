/*
 City Care Hospital � Recursive BST Prototype
 Student Name: Obadiah Goodnews Chukwu
 School Project

 PURPOSE:
 - Store integer patient IDs in a Binary Search Tree (BST).
 - Support INSERT, SEARCH, and PRINT-SORTED via INORDER traversal.
 - Use RECURSION for core operations.
 - Provide XAI comments (base/recursive cases, invariants, complexity).

 RESPONSIBLE AI NOTES:
 - Demo with synthetic IDs only; do not log real patient data.
 - No file persistence here; memory-only prototype for classroom use.
*/

#include <iostream>
#include <limits>
using namespace std;

// --------- Node definition ----------
struct Node {
    int patientID;
    Node* left;
    Node* right;
    explicit Node(int id) : patientID(id), left(nullptr), right(nullptr) {}
};

/*
 INVARIANT (BST property):
 For any node N:
   - All keys in N->left  < N->patientID
   - All keys in N->right > N->patientID
 This invariant is preserved by insert/search and used by inorder for sorted output.
*/

class BST {
    Node* root = nullptr;

    // --- destroy (postorder) ---
    // XAI: Base: null subtree -> nothing to free
    //      Recursive: delete left, then right, then current node (postorder).
    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    // --- insert (recursive) ---
    // XAI: Base case: reached null -> create new leaf node.
    //      Recursive case: branch left if id < key; branch right if id > key.
    //      Duplicate rule: ignore equal id (keeps unique IDs).
    // Complexity: average O(log n) if balanced; worst O(n) if skewed.
    Node* insertRec(Node* n, int id) {
        if (!n) return new Node(id);
        if (id < n->patientID) {
            n->left = insertRec(n->left, id);
        }
        else if (id > n->patientID) {
            n->right = insertRec(n->right, id);
        } // else equal -> ignore
        return n;
    }

    // --- search (recursive) ---
    // XAI: Base cases:
    //        - n == nullptr -> not found
    //        - n->patientID == id -> found
    //      Recursive case: choose left or right subtree based on comparison.
    // Complexity: O(height) -> average O(log n), worst O(n).
    bool containsRec(Node* n, int id) const {
        if (!n) return false;
        if (id == n->patientID) return true;
        return id < n->patientID
            ? containsRec(n->left, id)
            : containsRec(n->right, id);
    }

    // --- inorder traversal (L, N, R) ---
    // XAI: For BSTs, Left subtree holds smaller keys, Right holds larger.
    //      Visiting Left -> Node -> Right prints in ascending order.
    // Base: null -> do nothing. Recursive: visit left, then self, then right.
    void inorderRec(Node* n) const {
        if (!n) return;
        inorderRec(n->left);
        cout << n->patientID << " ";
        inorderRec(n->right);
    }

    // (Optional) utility: size (node count) � helpful for sanity checks/tests.
    int sizeRec(Node* n) const {
        if (!n) return 0;
        return 1 + sizeRec(n->left) + sizeRec(n->right);
    }

public:
    ~BST() { destroy(root); }

    void insert(int id) { root = insertRec(root, id); }
    bool contains(int id) const { return containsRec(root, id); }
    void printInorder()   const { inorderRec(root); cout << "\n"; }
    int  size()           const { return sizeRec(root); }
};

// --------- small console UI for the prototype ----------
static void flushLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    BST tree;

    // Seed with synthetic sample data (feel free to remove/change):
    for (int id : { 1005, 1001, 1012, 1000, 1003, 1008, 1015 }) {
        tree.insert(id);
    }

    cout << "City Care Hospital � Patient ID BST (prototype)\n";
    cout << "Operations: INSERT, SEARCH, PRINT-SORTED (Inorder), EXIT\n";
    cout << "(Demo seeded with a few synthetic IDs.)\n\n";

    while (true) {
        cout << "1) Insert ID  2) Search ID  3) Print sorted  4) Size  5) Exit\n";
        cout << "Choose: ";
        int choice;
        if (!(cin >> choice)) { flushLine(); cout << "Invalid input.\n"; continue; }

        if (choice == 1) {
            cout << "Enter patient ID (integer): ";
            int id;
            if (!(cin >> id)) { flushLine(); cout << "Invalid ID.\n"; continue; }
            tree.insert(id);
            cout << "Inserted (duplicates ignored).\n";
        }
        else if (choice == 2) {
            cout << "Enter patient ID to search: ";
            int id;
            if (!(cin >> id)) { flushLine(); cout << "Invalid ID.\n"; continue; }
            cout << (tree.contains(id) ? "FOUND\n" : "NOT FOUND\n");
        }
        else if (choice == 3) {
            cout << "Patient IDs (ascending): ";
            tree.printInorder();
        }
        else if (choice == 4) {
            cout << "Node count: " << tree.size() << "\n";
        }
        else if (choice == 5) {
            cout << "Goodbye.\n";
            break;
        }
        else {
            cout << "Unknown choice.\n";
        }
        cout << "\n";
    }
    return 0;
}
