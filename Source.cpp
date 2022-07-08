#include<iostream>
#include <fstream>
using namespace std;
#include "RBT.h"

int main() {
	RBT<int> tree;
	int option=0;
	
	while (1)
	{
		cout << "Press 1 to insert values in the tree." << endl;
		cout << "Press 2 for searching a value from the tree." << endl;
		cout << "Press 3 for pre-order traversal." << endl;
		cout << "Press 4 for in-order traversal." << endl;
		cout << "Press 5 for post-order traversal." << endl;
		cout << "Press 6 for pre-order traversal 2." << endl;
		cout << "Press 7 for in-order traversal 2." << endl;
		cout << "Press 8 for post-order traversal 2." << endl;
		cout << "Press 9 for displaying parent of a node present in Tree." << endl;
		cout << "Press 10 to read integer values from the file to create a red - black tree." << endl;
		cout << "Press 11 to delete." << endl;
		cout << "Press 12 to destroy the complete tree." << endl;
		cout << "Press 13 to EXIT." << endl;

		cin >> option;
		if (option == 1){
			int val = 0;
			cout << "Please enter a value to insert: ";
			cin >> val;
			tree.insert(val);
		}
		else if (option == 2)
		{
			int val = 0;
			cout << "Please enter the value to search from the tree: ";
			cin >> val;
			cout << tree.search(val)<<endl;
			
		}
		else if (option == 3)
		{
			cout << "Pre-Order Traversal: ";
			tree.preOrder();
			cout << endl;
		}
		else if (option == 4)
		{
			cout << "In-Order Traversal: ";
			tree.inOrder();
			cout << endl;
		}
		else if (option == 5)
		{
			cout << "Post-Order Traversal: ";
			tree.postOrder();
			cout << endl;
		}
		else if (option == 6)
		{
			cout << "Pre-Order Traversal 2: ";
			tree.preOrder2();
			cout << endl;
		}
		else if (option == 7)
		{
			cout << "In-Order Traversal 2: ";
			tree.inOrder2();
			cout << endl;
		}
		else if (option == 8)
		{
			cout << "Post-Order Traversal 2: ";
			tree.postOrder2();
			cout << endl;
		}
		else if (option == 9)
		{
			int val;
			cout << "Enter node value to display its parent: ";
			cin >> val;

			tree.displayParent(val);
			cout << endl;
		}
		else if (option == 11) {
			tree.snapShot(std::cout, tree.getRoot());
			cout << endl;
			int val;
			cout << "Enter node value to del ";
			cin >> val;
			tree.del(val);
			tree.snapShot(std::cout, tree.getRoot());
			cout << endl;
		}
		else if (option == 10)
		{
			ifstream fin;
			fin.open("input.txt");
			int val;
			cout << "Reading from file: \n";
			while (!fin.eof()) {
				fin >> val;
				tree.insert(val);
			}
		}
		else if (option == 12)
		{
			tree.~RBT();
		}
		else if (option == 13)
		{
			break;
		}
		else {
			cout << "Please enter valid option." << endl;
		}
	}
	return 0;
}