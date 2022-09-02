#include <iostream>
using namespace std;

class TreeChunk {
 public:
  int value;
  TreeChunk *left;
  TreeChunk *right;

  TreeChunk() {
    value = 0;
    left = right = NULL;
  }
};

class BST {
 public:
  TreeChunk *root;

  BST() { root = NULL; }

  // 1. Add values
  void addValue(int key) {
    if (root == NULL) {
      root = new TreeChunk;
      root->value = key;
      return;
    }

    TreeChunk *fast, *slow;
    fast = slow = root;

    while (fast != NULL) {
      slow = fast;  

      if (fast->value == key) {
  
        cout << "Sorry, not adding duplicates" << endl;
        return;
      }
      else if (key < fast->value) {
        fast = fast->left;
      }
      else {
        fast = fast->right;
      }
    }

    if (fast == NULL) {
      TreeChunk *temp = new TreeChunk;
      temp->value = key;

      if (key < slow->value)
        slow->left = temp;
      else
        slow->right = temp;
    }
  }

  // 2. Search for a value (key)
  void searchBST(int key, TreeChunk *start) {
    if (start == NULL) {
      cout << "Value not found in this tree" << endl;
    }
    else {
      if (key == start->value) {
        cout << "Found it!!" << endl;
      }
      else if (key > start->value) {
        searchBST(key, start->right);
      }
      else {
        searchBST(key, start->left);
      }
    }
  }
  
  TreeChunk *delete_min(TreeChunk **proot) {
    if((*proot)->left == NULL){
      TreeChunk *temp = *proot;
      *proot = (*proot)->right;
        return temp;
    }
    else {
      return delete_min(&(*proot)->left);
    }
}
  // 3. delete a key
  void  deleteNode(TreeChunk **proot, int key) {
    if(*proot == NULL) {
      cout << "cannot find this value" << endl;
      return;
      
    }
    //Case 1
    if((*proot)->value == key) {
      if((*proot)->left == NULL && (*proot)->right == NULL) {
	cout << "Case 1 Delete" << endl;
	cout << "About To Delete: " << (*proot)->value << endl;
            delete *proot;
            *proot = NULL;
            return;
        }
        //Case 2
      if((*proot)->left != NULL && (*proot)->right == NULL) {
	cout << "Case 2 Delete" << endl;
	cout << "About To Delete: " << (*proot)->value << endl;
            TreeChunk *temp = *proot;
            *proot = (*proot)->left;
            delete temp;
            return;
        }
        
      if((*proot)->left == NULL && (*proot)->right != NULL) {
	cout << "Case 2 Delete" << endl;
	cout << "About To Delete: " << (*proot)->value << endl;
            TreeChunk *temp = *proot;
            *proot = (*proot)->right;
            delete temp;
            return;
        }
        //Case3
      if((*proot)->left != NULL && (*proot)->right != NULL) {
	cout << "Case 3 Delete" << endl;
	cout << "About To Delete: " << (*proot)->value << endl;
	  TreeChunk *min = delete_min(&(*proot)->right);
            TreeChunk *temp = *proot;
            min->left = (*proot)->left;
            min->right = (*proot)->right;
            *proot = min;
            delete temp;
            return;
        }

    }
    if ((*proot)->value < key) {
      return deleteNode(&(*proot)->right, key);
    }
    else{
      return deleteNode(&(*proot)->left, key);
    }
}

  // 4. Display contents: (a) in--, (b) pre--, (c) post-- order
  void inorder(TreeChunk *start) {
    if (start == NULL) {
      return;
    }
    else {
    
      inorder(start->left);
      cout << start->value << "  " << endl;
      inorder(start->right);
    }
  }

  void preorder(TreeChunk *start) {
    if (start == NULL)
      return;
    else {
      cout << start->value << " " << endl;
      preorder(start->left);
      preorder(start->right);
    }
  }

  void postorder(TreeChunk *start) {
    if (start == NULL)
      return;
    else {
      postorder(start->left);
      postorder(start->right);
      cout << start->value << "  " << endl;
    }
  }

  //FOR TEST 2
  //8. Delete a tree
  void deleteTree(TreeChunk *root) {
    if(root == NULL) {
      return; 
    }
    else {
      deleteTree(root->left);
      deleteTree(root->right);
      cout << "Deleting: " << root->value << endl;
      delete root;
    }
  }

  //9. Check if tree is balanced
  bool isBalanced(TreeChunk *start){
    int LH;
    int RH;

    if (start == NULL) {
      return true;
    }

    LH = height(start->left);
    RH = height(start->right);

    if (abs(LH-RH) <= true && isBalanced(start->right)) {
      return true;
    }
    else {
      return false;
    }
  }
  int height(TreeChunk *start){
    if (start == NULL){
      return 0;
    }
    else {
      return 1 + max(height(start->left),height(start->right));
    }
  }
    

  //10. Find first common parent
  int firstCommonParent(TreeChunk *root, int value1, int value2) {
    if (root == NULL) {
      return NULL;
    }
    if (root->value > value1 && root->value > value2){
      return firstCommonParent(root->left, value1, value2);
    }
    if (root->value < value1 && root->value < value2){
      return firstCommonParent(root->right, value1, value2);
    }
    return root->value;
    }
};

int main() {
  BST tree;
  int choice, value, value1, value2;

  while (1) {
    cout << "Press 1 to add a new value" << endl;
    cout << "Press 2 to search" << endl;
    cout << "Press 3 for in-order" << endl;
    cout << "Press 4 for pre-order" << endl;
    cout << "Press 5 for post-order" << endl;
    cout << "Press 6 for deleting a node" << endl;
    cout << "Press 7 for deleting a tree" << endl;
    cout << "Press 8 to check if tree is balanced" << endl;
    cout << "Press 9 to find first common parent" << endl;
    cin >> choice;

    switch (choice) {
      case 1:
        cout << "What value did you want to add?" << endl;
        cin >> value;
        tree.addValue(value);
        break;

      case 2:
        cout << "Search for what?" << endl;
        cin >> value;
        tree.searchBST(value, tree.root);
        break;

      case 3:
        tree.inorder(tree.root);
        break;

      case 4:
        tree.preorder(tree.root);
        break;
	
     case 5:
        tree.postorder(tree.root);
        break;

      case 6:
	cout << "delete what?" << endl;
	cin >> value;
        tree.deleteNode(&(tree.root), value);
        break;

    case 7:
      tree.deleteTree(tree.root);
      break;

    case 8:
      if(tree.isBalanced(tree.root) == true){
	cout << "True: Tree is balanced" << endl;
      }
      else {
	cout << "False: Tree is not balanced" << endl;
      }
      break;
      
      case 9:
	cout << "enter node #1" << endl;
	cin >> value1;
	cout << "enter node #2" << endl; 
	cin >> value2;
	cout << "The first common parent function is: " << tree.firstCommonParent(tree.root, value1, value2) <<  endl;
      break;

      default:
        cout << "Goodbye!" << endl;
        exit(1);
    }
  }
}
