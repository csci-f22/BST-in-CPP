#include <iostream>
using namespace std;

struct node{
	int data;
	struct node* left;
	struct node* right;
};

struct node* newNode(int data){
	struct node* node = new struct node;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}
/*
 * 1. If the tree is empty, set rootRef to the address of newly created node
 * 2. Otherwise, recur down the tree
 */
void insert(struct node** rootRef, int data){
	if(*rootRef == NULL) {
		*rootRef = newNode(data);
	}

	else{
		if( data <= (*rootRef)->data ){
			insert(&((*rootRef)->left), data);
		}else{
			insert(&((*rootRef)->right), data);
		}
	}


}

int size(struct node* node){

	if(node == NULL) return 0;
	return(size(node->left) + size(node->right) + 1);

}

void printTreeInOrder(struct node* root){

	if(root == NULL){
		return;
	}
	//left-root-right
	printTreeInOrder(root->left);
	cout << root->data << " ";
	printTreeInOrder(root->right);
}

void printTreePreOrder(struct node* root){

	if(root == NULL){
			return;
		}
	//root-left-right
	cout << root->data << " ";
	printTreePreOrder(root->left);
	printTreePreOrder(root->right);
}

void printTreePostOrder(struct node* root){

	if(root == NULL){
			return;
		}
	//left-right-root
	printTreePostOrder(root->left);
	printTreePostOrder(root->right);
	cout << root->data << " ";
}

int maxDepth(struct node* root){

	if(root==NULL) return 0;
	else{
		int lheight = maxDepth(root->left);
		int rheight = maxDepth(root->right);

		if(lheight > rheight){
			return (lheight+1);
		}else
			return (rheight+1);

	}


}

//Added a findMinValue for helping with deletion
struct node* findMinValue(struct node* root){
	struct node* current = root;

	while(current && current->left != NULL)
		current = current->left;

	return current;
}

struct node* findMaxValue(struct node* root){
	//no recursion
	struct node* temp = root;

	while(temp->right!=NULL){
		temp = temp->right;
	}
	return temp;

}

bool lookup(struct node* node, int target){

	if(node == NULL) return false;

	if(target == node->data) return true;
	if(target < node->data){
		return lookup(node->left, target);
	}else
		return lookup(node->right, target);


}

//Write a recursive method that checks whether a given binary 
//tree is a BST or not. 
bool isBST(struct node* node, int min, int max){
	if(node == NULL) return true;

	if(node->data < min || node->data > max) return false;

	return isBST(node->left, min, node->data) && isBST(node->right, node->data, max);
}

void isBST(struct node* root){
	if(isBST(root, INT8_MIN, INT8_MAX)){
		cout << "Given binary tree is a BST" << endl;
	}
	else{
		cout << "Given binary tree is not a BST" << endl;
	}
}

//Write a method that finds the kth biggest element in a BST.
void kthLargestHelper(struct node* root, int k, int &c){
	if(root == NULL || c >= k)
		return;
	kthLargestHelper(root->right, k, c);
	c++;
	if(c == k)
	{
		cout << "Kth largest element is: " << root->data << endl;
		return;
	}

	kthLargestHelper(root->left, k, c);
}

void kthLargest(struct node* root, int k){
	int c = 0;
	kthLargestHelper(root, k, c);
}

//Write a method that takes an integer target value as a 
//parameter and deletes the node. Make sure there is no 
//memory leak when the program exits.
struct node* deleteTarget(struct node* root, int data){
	if(root == NULL)
		return root;
	
	if(data < root->data)
		root->left = deleteTarget(root->left, data);

	else if(data > root->data)
		root->right = deleteTarget(root->right, data);
	
	else{
		if(root->left == NULL && root->right == NULL)
			return NULL;
		else if(root->left == NULL){
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL){
			struct node* temp = root->left;
			free(root);
			return temp;
		}
	struct node* temp = findMinValue(root->right);
	root->data = temp->data;
	root->right = deleteTarget(root->right, temp->data);
	}
	return root;
}

int main() {
	struct node* root = NULL;

	insert(&root, 41);
	insert(&root, 20);
	insert(&root, 11);
	insert(&root, 29);
	insert(&root, 32);
	insert(&root, 65);
	insert(&root, 50);
	insert(&root, 91);
	insert(&root, 72);
	insert(&root, 99);

	cout << size(root) << endl;
	printTreePreOrder(root);
	cout << endl;
	printTreePreOrder(root);
	cout << endl;
	printTreePostOrder(root);
	cout << endl;
	cout << maxDepth(root) << endl;
	cout << findMinValue(root)->data << endl;
	cout << findMaxValue(root)->data << endl;
	isBST(root);
	int c = 0;
	for(int k = 1; k <= 10; k++)
		kthLargest(root, k);
	printTreeInOrder(root);
	cout << endl;
	root = deleteTarget(root, 20);
	printTreeInOrder(root);
	cout << endl;
	return 0;
}
