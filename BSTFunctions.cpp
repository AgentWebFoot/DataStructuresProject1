#include <iostream>
using namespace std;
class Node {
  public:
    int data;
    Node *left;
    Node *right;
    int height;
    Node(){
      data = 0;
      left = NULL;
      right = NULL; 
    }
    Node(int val){
      data = val;
      left = NULL;
      right = NULL;
    }
};
void inorder(Node *currentPtr);
Node* insert(Node *root,
                         Node *element);
int add(Node *currentPtr);
int find(Node *currentPtr, int val);
Node* parent(Node *root, Node *node);
Node* minVal(Node *root);
Node* maxVal(Node *root);
int isLeaf(Node *node);
int hasOnlyLeftChild(Node *node);
int hasOnlyRightChild(Node *node);
Node* findNode(Node *currentPtr, int value);
Node* deleteNode(Node* root, int value);
int menu();

Node* Next(Node *root, Node *node);
void AVLInsert(int k, Node* R);
int ComputeHeight(Node *node);
void RotateRight(Node* node);
void RotateLeft(Node* node);
void ComputerBF(Node* node);
void Rebalance(Node *root, Node *node);
void AdjustHeight(Node* node);
void RebalanceRight(Node* node);
void RebalanceLeft(Node* node);
Node* LeftDescendant(Node* node);
Node* RightAncestor(Node* root, Node* node);
Node* FindSearch(int k, Node* node);
bool IsUnbalance(Node* node);
void AVLDelete(Node *root, Node* node);

void inorder(Node *currentPtr) {
  // Only traverse the node if it's not null.
  if (currentPtr != NULL) {
    inorder(currentPtr->left); // Go Left.
    cout<<" "<<currentPtr->data; // Print the root.
    inorder(currentPtr->right); // Go Right.
  }
}
Node* insert(Node *root,
                         Node *element) {
  // Inserting into an empty tree.
  if (root == NULL){
    return element;
  }
  else {
    // element should be inserted to the right.
    if (element->data > root->data) {
      // There is a right subtree to insert the node.
      if (root->right != NULL)
        root->right = insert(root->right, element);
      // Place the node directly to the right of root.
      else
        root->right = element;
    }
    // element should be inserted to the left.
    else {
      // There is a left subtree to insert the node.
      if (root->left != NULL)
        root->left = insert(root->left, element);
      // Place the node directly to the left of root.
      else
        root->left = element;
    }
    // Return the root pointer of the updated tree.
    return root;
  }
}
int find(Node *currentPtr, int val) {
  // Check if there are nodes in the tree.
  if (currentPtr != NULL) {
    // Found the value at the root.
    if (currentPtr->data == val)
      return 1;
    // Search to the left.
    if (val < currentPtr->data)
      return find(currentPtr->left, val);
    // Or search to the right.
    else
      return find(currentPtr->right, val);
  }
  else
    return 0;
}
int add(Node *currentPtr) {
  if (currentPtr != NULL)
    return currentPtr->data+add(currentPtr->left)+
           add(currentPtr->right);
  else
    return 0;
}
// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
Node* parent(Node *root, Node *node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (node->data < root->data)
    return parent(root->left, node);
  // Look for node's parent in the right side of the tree.
  else if (node->data > root->data)
    return parent(root->right, node);
  return NULL; // For any other cases.
}
// Returns a pointer to the node storing the minimum value in the tree
Node* minVal(Node *root) {
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;
  // The left subtree of the root stores the minimal value.
  else
    return minVal(root->left);
}
// Returns a pointer to the node storing the maximum value in the tree
Node* maxVal(Node *root) {
  // Root stores the maximal value.
  if (root->right == NULL)
    return root;
  // The right subtree of the root stores the maximal value.
  else
    return maxVal(root->right);
}
// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(Node *node) {
  return (node->left == NULL && node->right == NULL);
}
// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(Node *node) {
  return (node->left!= NULL && node->right == NULL);
}
// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(Node *node) {
  return (node->left== NULL && node->right != NULL);
}
// Returns a pointer to a node that stores value in it in the subtree
Node* findNode(Node *currentPtr, int value) {
  // Check if there are nodes in the tree.
  if (currentPtr != NULL) {
    // Found the value at the root.
    if (currentPtr->data == value)
      return currentPtr;
    // Search to the left.
    if (value < currentPtr->data)
      return findNode(currentPtr->left, value);
    // Or search to the right.
    else
      return findNode(currentPtr->right, value);
  }
  else
    return NULL; // No node found.
}
// Will delete the node storing value in the tree rooted at root. The
// value must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
Node* deleteNode(Node* root, int value) {
  Node *delnode, *newDelNode, *saveNode;
  Node *par;
  int saveVal;
  delnode = findNode(root, value); // Get a pointer to the node to delete.
  par = parent(root, delnode); // Get the parent of this node.
  // Take care of the case where the node to delete is a leaf node.
  if (isLeaf(delnode)) {// case 1
    // Deleting the only node in the tree.
    if (par == NULL) {
      delete root; // free the memory for the node.
      return NULL;
    }
    // Deletes the node if it's a left child.
    if (value < par->data) {
      delete par->left; // Free the memory for the node.
    }
    // Deletes the node if it's a right child.
    else {
      delete par->right; // Free the memory for the node.
      par->right = NULL;
    }
    return root; // Return the root of the new tree.
  }
  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChild(delnode)) {
    // Deleting the root node of the tree.
    if (par == NULL) {
      saveNode = delnode->left;
      delete delnode; // Free the node to delete.
      return saveNode; // Return the new root node of the resulting tree.
    }
    // Deletes the node if it's a left child.
    if (value < par->data) {
      saveNode = par->left; // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      delete saveNode; // Free the memory for the deleted node.
    }
    // Deletes the node if it's a right child.
    else {
      saveNode = par->right; // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      delete saveNode; // Free the memory for the deleted node.
    }
    return root; // Return the root of the tree after the deletion.
  }
  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChild(delnode)) {
    // Node to delete is the root node.
    if (par == NULL) {
      saveNode = delnode->right;
      delete delnode;
      return saveNode;
    }
    // Delete's the node if it is a left child.
    if (value < par->data) {
      saveNode = par->left;
      par->left = par->left->right;
      delete saveNode;
    }
    // Delete's the node if it is a right child.
    else {
      saveNode = par->right;
      par->right = par->right->right;
      delete saveNode;
    }
    return root;
  }
//when delnode has two children
  // Find the new physical node to delete.
  newDelNode = minVal(delnode->right);
  saveVal = newDelNode->data;
  deleteNode(root, saveVal);  // Now, delete the proper value.
  // Restore the data to the original node to be deleted.
  delnode->data = saveVal;
  return root;
}
// Prints out the menu of choices for the user and returns their choice.
int menu() {
  int ans;
  cout<<"Here are your choices.\n";
  cout<<"1. Insert an item into your tree.\n";
  cout<<"2. Delete an item from your tree.\n";
  cout<<"3. Search for an item in your tree.\n";
  cout<<"4. Print the sum of the nodes. \n";
  cout<<"5. Print the next element of the node with key x. \n";
  cout<<"6. Print the elements between x, and y. \n";
  cout<<"7. Print the height of the tree with root x. \n";
  cout<<"8. Print the sum of the list of elements between x, and y. \n";
  cout<<"9. Print out an inorder traversal.\n";
  cout<<"10. Exit.\n";
  cin>> ans;
  return ans;
}

Node* Next(Node *root, Node *node){
  if (node->right == NULL) return LeftDescendant(node->right);
  else return RightAncestor(root, node);
}

void AVLInsert(int k, Node* root, Node* node){
  Node *N, *temp;
  temp = new Node(k);
  insert(temp, node);
  N = FindSearch(k, node);
  Rebalance(root, N);
}
int ComputeHeight(Node *node){
  return node->height;
}
void RotateRight(Node* node){
  Node *L, *R;
  L = node->left;
  R = node->right;
  L->right = node;
  node->left = R;
}
void RotateLeft(Node* node){
  Node *L, *R;
  L = node->left;
  R = node->right;
  R->left = node;
  node->right = L;
}
void ComputerBF(Node* node){
  
}
void Rebalance(Node *root, Node *node){
  Node *P;
  P = parent(root, node);
  if (node->left->height > (node->right->height+1)) RebalanceRight(node);
  if (node->right->height > (node->left->height+1)) RebalanceLeft(node);
  AdjustHeight(node);
  if (!(P == NULL)) Rebalance(root, node);
}
void AdjustHeight(Node* node){
  node->height = 1+ max(node->left->height, node->right->height);
}
void RebalanceRight(Node* node){
  Node *M;
  M = node->left;
  if (M->right->height > M->left->height) RotateLeft(node);
  RotateRight(node);
  AdjustHeight(node);
}
void RebalanceLeft(Node* node){
  Node *M;
  M = node->right;
  if (M->left->height > M->right->height) RotateRight(node);
  RotateLeft(node);
  AdjustHeight(node);
}
Node* LeftDescendant(Node* node){
  if (node->left == NULL) return node;
  else return LeftDescendant(node->left);
}
Node* RightAncestor(Node* root, Node* node){
  if (node->data < parent(root, node)->data) return parent(root, node);
  else return RightAncestor(root, parent(root, node));
}
Node* FindSearch(int k, Node* node){
  if ((node->data = k)) return node;
  else if (node->data > k) return FindSearch(k, node->left);
  else if (node->data < k) return FindSearch(k, node->right);
}
bool IsUnbalance(Node* node){
  if (node->left->height == node->right->height) return true;
  else return false;
}
void AVLDelete(Node *root, Node* node){
  Node *M;
  delete(node);
  M = parent(root, node);
  Rebalance(root, node);
}

int main() {
  Node *myRoot=NULL, *tempNode;
  int done = 0,ans=1, val, q6data;
  ans = menu();
  while (ans<8) {
    if (ans == 1) {
      // Get value to insert.
      cout<<"What value would you like to insert?";
      cin>>val;
      tempNode = new Node(val); // Create the node.
      // Insert the value.
      myRoot = insert(myRoot, tempNode);
    }
    if (ans == 2) {
      cout<<"What value would you like to delete?\n";
      cin>>val;
      if (!find(myRoot, val))
        cout<<"Sorry that value isn't in the tree to delete.\n";
      else {
        myRoot = deleteNode(myRoot, val);
      }
    }
    if (ans == 3) {
      cout<<"What value would you like to search for?\n";
      cin>>val;
      if (find(myRoot, val))
        cout<<" Found"<<val<<"in the tree.\n";
      else
        cout<<" Did not find %d in the tree.\n";
    }
    if (ans == 4)
      cout<<"The sum of the nodes in your tree is"<<add(myRoot)<<"\n";
    if (ans == 5) {
      
    }
    if (ans == 6){
      
    }
    if (ans == 7){
      
    }
    if (ans == 8){
      
    }
    if (ans == 9) {
      // Print the resulting tree.
      cout<<"Here is an inorder traversal of your tree: ";
      inorder(myRoot);
      cout<<"\n";
    }
    
    // See if they want to insert more nodes.
    ans = menu();
  }
  return 0;
}
