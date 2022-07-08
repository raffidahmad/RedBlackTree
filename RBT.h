#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class RBT {
protected:
	Node<T>* root;
	Node<T>*& createNode(const T& value) {
		Node<T>* tempNode = new Node<T>;
		tempNode->color = 'R'; //new nodes are inserted as red color
		tempNode->data = value;
		tempNode->left = nullptr;
		tempNode->right = nullptr;
		tempNode->count = 1;
		return tempNode;
	}
	void INSERT(Node<T>*& ptr, T val) {
		//if ptr empty
		if (ptr != nullptr && ptr->data == val) {
			ptr->count++;
		}
		else if (ptr == nullptr) {
			ptr = createNode(val);
			return;
		}
		else if (val < ptr->data) {
			INSERT(ptr->left, val);
		}
		else {
			INSERT(ptr->right, val);
		}
		bool red = false;
		Node<T>* VAR = nullptr;
		if (ptr->color == 'R') {
			if (ptr->right!=nullptr && ptr->right->color == 'R') {
				val = ptr->right->data;
				VAR = ptr->right;
				red = true;
			}
			else if (ptr->left != nullptr && ptr->left->color == 'R') {
				val = ptr->left->data;
				VAR = ptr->left;
				red = true;
			}
			if (red == true) {
				//find ptr(parent) ka bhai
				Node<T>* grandParent = findParent(ptr->data);
				Node<T>* uncle = findUncle(grandParent, ptr);
				//if uncle (temp) = R then recolor else rotate
				// 
				//RECOLORING
				if (uncle != nullptr && uncle->color == 'R')
				{
					switchColor(ptr);  //parent
					switchColor(uncle);
					switchColor(grandParent);
					if (root->color == 'R') { switchColor(root); }
				}
				else {
					Node<T>* tempParent = ptr;
					Node<T>* tempGrandpa = grandParent;
					//rotate here
					//right right case
											// parent is on right of grandparent				//					// child is on right of parent
					if (grandParent->right != nullptr && ptr->data == grandParent->right->data && ptr->right != nullptr && VAR->data == ptr->right->data) { // masla is here -> val is at leaf
						//rotate left grandparent
						leftRotation(grandParent);
						switchColor(tempParent); //parent
						switchColor(tempGrandpa);
					}
					//left left case
											// parent is on left of grandparent					//			// child is on left of parent
					else if (grandParent->left != nullptr && ptr->data == grandParent->left->data && ptr->left != nullptr && VAR->data == ptr->left->data) {
						//rotate right grandparent
						rightRotation(grandParent);
						switchColor(tempParent); //parent
						switchColor(tempGrandpa);
					}

					//right left case
											// parent is on right of grandparent					//	      // child is on left of parent
					else if (grandParent->right != nullptr && ptr->data == grandParent->right->data && ptr->left != nullptr && VAR->data == ptr->left->data) {
						//rotate right parent
						rightRotation(ptr);
						//rotate left grandparent
						leftRotation(grandParent);
						switchColor(tempParent); //parent
						switchColor(tempGrandpa);
					}

					//left right case
											// parent is on left of grandparent					//				// child is on right of parent
					else if (grandParent->left != nullptr && ptr->data == grandParent->left->data && ptr->right != nullptr && VAR->data == ptr->right->data) {
						//rotate left parent
						leftRotation(ptr);
						//rotate right grandparent
						rightRotation(grandParent);
						switchColor(tempParent); //parent
						switchColor(tempGrandpa);
					}
					if (root->color == 'R') { switchColor(root); }
				}
			}
		}
	}
	
	Node<T>* findUncle(const Node<T>* grandParent, const Node<T>* parent) {
		if (grandParent->right != nullptr && grandParent->right == parent) {
				return grandParent->left;
		}
		else if (grandParent->left != nullptr) {
				return grandParent->right;
		}
	}
	void INORDER(Node<T>* ptr) {
		if (ptr != nullptr) {
			INORDER(ptr->left);
			cout << ptr->data << ptr->color << "  ";
			INORDER(ptr->right);
		}
	}
	void PREORDER(Node<T>* ptr)
	{
		if (ptr != nullptr){
			cout << ptr->data << ptr->color << "  ";
			PREORDER(ptr->left);
			PREORDER(ptr->right);
		}
	}
	void delTree(Node<T>* ptr)
	{
		if (ptr != nullptr){
			delTree(ptr->left);
			delTree(ptr->right);
			delete ptr;
			ptr = nullptr;
		}
	}
	void POSTORDER(Node<T>* ptr)
	{
		if (ptr != nullptr){
			POSTORDER(ptr->left);
			POSTORDER(ptr->right);
			cout << ptr->data << ptr->color << "  ";
		}
	}
	void PREORDER2(Node<T>* ptr)
	{
		if (ptr != nullptr){
			cout << ptr->data << ptr->color << "  ";
			PREORDER2(ptr->right);
			PREORDER2(ptr->left);

		}
	}
	void INORDER2(Node<T>* ptr)
	{
		if (ptr != nullptr){
			INORDER2(ptr->right);
			cout << ptr->data << ptr->color << "  ";
			INORDER2(ptr->left);

		}
	}
	void POSTORDER2(Node<T>* ptr) {
		if (ptr != nullptr){
			POSTORDER2(ptr->right);
			POSTORDER2(ptr->left);
			cout << ptr->data << ptr->color << "  ";
		}
	}
	void switchColor(Node<T>*& nodePtr) // & by reference = change in original
	{
		if (nodePtr->color == 'R'){
			nodePtr->color = 'B';
		}
		else if (nodePtr->color == 'B'){
			nodePtr->color = 'R';
		}
	}
	Node<T>* findParent(T data) {
		return FINDPARENT(root, data);
	}
	Node<T>* FINDPARENT(Node<T>* r, T& val){
		if (r == nullptr || r->left!=nullptr && r->left->data == val || r->right!=nullptr &&  r->right->data == val) {
			return r;
		}
		else if (r->data < val) {
			FINDPARENT(r->right, val);
		}
		else if (r->data > val) {
			FINDPARENT(r->left, val);
		}
	}

	void rightRotation(Node<T>*& grandpa) {
		Node<T>* parent = grandpa->left;
		grandpa->left = parent->right;
		parent->right = grandpa;

		if (grandpa != root) {
			Node<T>* t = findParent(grandpa->data);
			if (t->right == grandpa) {
				t->right = parent;
			}
			else {
				t->left = parent;
			}
		}
		else {
			root = parent;
		}
	}
	void leftRotation(Node<T>*& grandpa) {
		Node<T>* parent = grandpa->right;
		grandpa->right = parent->left;
		parent->left = grandpa;
		if (grandpa != root) {
			Node<T>* t = findParent(grandpa->data);
			if (t->right == grandpa) {
				t->right = parent;
			}
			else {
				t->left = parent;
			}
		}
		else {
			root = parent;
		}
	}
	Node<T>*& SEARCH(Node<T>* r, T val) {
		if (r == nullptr || r->data == val) {
			return r;
		}
		else if (r->data < val) {
			SEARCH(r->right, val);
		}
		else if (r->data > val) {
			SEARCH(r->left, val);
		}
	}

	Node<T>*& maxLeft(Node<T>* n) {
		Node<T>* nn = n;
		if (n -> left != nullptr) {
			nn = n->left;
			while (nn->right != nullptr){
				nn = nn->right;
			}
		}
		return nn;
	}

public:
	Node<T>* getRoot() {
		return root;
	}
	void del(T value) {
		Node<T>* TBD = SEARCH(root, value);
		if (TBD != nullptr) {
			if (TBD->count == 1) {
				if (TBD->right == nullptr && TBD->left == nullptr) {
					Node<T>* parent = findParent(TBD->data);
					if (parent->right != nullptr && parent->right == TBD) {
						parent->right = nullptr;
					}
					else {
						parent->left = nullptr;
					}
					delete TBD;
					return;
				}
				else {
					Node<T>* max = maxLeft(TBD);
					T data = max->data;
					del(max->data);
					TBD->data = data;
				}
			}
			else if (TBD->count > 1) {
				TBD->count = 1;
			}
		}
		else {
			cout << "Value doesnt exist\n";
		}
	}
	void snapShot(std::ostream& out, Node<T>* p) {
		out << '\"' << p->data  << p->color << '\"';
		if (p->left != nullptr || p->right != nullptr) {
			out << '[';
			if (p->left == nullptr)
				out << "\"\"";
			else
				snapShot(out, p->left);
			out << ',';
			if (p->right == nullptr)
				out << "\"\"";
			else
				snapShot(out, p->right);
			out << ']';
		}
	}
	~RBT() {
		if (root != nullptr){
			delTree(root);
			root = nullptr;
		}
	}
	bool search(T value) {
		if (root != nullptr) {
			if (SEARCH(root, value) != nullptr) {
				return true;
			}
		}
		return false;
	}

	RBT() {
		root = nullptr;
	}
	void insert(T val) {
		if (root == nullptr) {
			root = createNode(val);
			if (root->color == 'R') { switchColor(root); }
		}
		else if (root->data == val) {
			root->count++;
		}
		else if (val > root->data) {
			//insert right since value is greater
			INSERT(root->right, val);
		}
		else if (val < root->data) {
			//insert left since value is smaller
			INSERT(root->left, val);
		}
	}
	void preOrder2(){
		if (root != nullptr){
			PREORDER2(root);
		}
	}
	void inOrder2() {
		if (root != nullptr) {
			INORDER2(root);
		}
	}
	void postOrder2(){
		if (root != nullptr){
			POSTORDER2(root);
		}
	}
	void inOrder() {
		if (root != nullptr) {
			INORDER(root);
		}
	}
	void preOrder(){
		if (root != nullptr){
			PREORDER(root);
		}
	}
	void postOrder(){
		if (root != nullptr){
			POSTORDER(root);
		}
	}
	void displayParent(T data){
		if (root == nullptr || root->data == data){
			cout << "Root node has no parent / is empty" << endl;
		}
		else {
			Node<T>* parent = findParent(data);
			if (parent != nullptr) {
				cout << "Parent: " << parent->data<<endl;
			}
			else {
				cout << "Node not found\n" << endl;
			}
		}
	}
};

