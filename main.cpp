using namespace std;
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <regex>

struct Node {
	Node* left; // stores the left child of the node
	Node* right; // stores the right child of the node
	~Node(); // node destructor
	string name;
	int height;
	int ID;
	int balanceFactor;
	Node(string, int); // constructor for node
	void setBalanceFactor(); // calculates and sets the balance factor for each node
	int getHeight(); // calculates and returns the height of each node
	int getBalanceFactor(); // returns the balance factor for each node
	Node* rotateRight(); // rotates for left left case
	Node* rotateLeft(); // rotates for right right case
	Node* rotateLeftRight(); // rotates for left right case
	Node* rotateRightLeft(); // rotates for right left case
};
Node::~Node() {}
Node::Node(string _name, int _ID) {
	height = 1;
	name = _name;
	ID = _ID;
	left = nullptr;
	right = nullptr;
}
int getDigits(int x) { // helper function to calculate the amount of digits in a node
	int digits = 0;
	while (x != 0) {
		x /= 10;
		digits++;
	}
	return digits;
}
int maxInt(int x, int y) { // helper function to find the maximum of 2 ints
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}
void Node::setBalanceFactor() {
	if (this != nullptr) {
		if (this->left == nullptr && this->right == nullptr) {
			this->balanceFactor = 0;
		}
		if (this->left != nullptr && this->right != nullptr) {
			this->balanceFactor = this->left->getHeight() - this->right->getHeight();
		}
		if (this->left == nullptr && this->right != nullptr) {
			this->balanceFactor = 0 - this->right->getHeight();
		}
		if (this->left != nullptr && this->right == nullptr) {
			this->balanceFactor = this->left->getHeight() - 0;
		}
	}
	else {
		this->balanceFactor = 0;
	}
}
int Node::getHeight() {
	if (this == nullptr) {
		return 0;
	}
	else {
		if (this->left != nullptr && this->right != nullptr) {
			return 1 + maxInt(this->left->getHeight(), this->right->getHeight());
		}
		if (this->left == nullptr && this->right == nullptr) {
			return 1;
		}
		if (this->left != nullptr && this->right == nullptr) {
			return 1 + this->left->getHeight();
		}
		if (this->left == nullptr && this->right != nullptr) {
			return 1 + this->right->getHeight();
		}
	}
}
int Node::getBalanceFactor() {
	return this->balanceFactor;
}
Node* Node::rotateRight() {
	Node* grandChild;
	Node* newParent;
	grandChild = this->left->right;
	newParent = this->left;
	newParent->right = this;
	this->left = grandChild;
	newParent->setBalanceFactor(); // recalculates the balance factors of the affected nodes
	this->setBalanceFactor();
	return newParent;
}
Node* Node::rotateLeft() {
	Node* grandChild;
	Node* newParent;
	grandChild = this->right->left;
	newParent = this->right;
	newParent->left = this;
	this->right = grandChild;
	newParent->setBalanceFactor(); // recalculates the balance factors of the affected nodes
	this->setBalanceFactor();
	return newParent;
}
Node* Node::rotateLeftRight()
{
	this->left = this->left->rotateLeft();
	Node* n = this->rotateRight();
	return n;
}
Node* Node::rotateRightLeft()
{
	this->right = this->right->rotateRight();
	Node* n = this->rotateLeft();
	return n;
}
struct AVLTree {
private:
	Node* root;
public:
	int size;
	AVLTree(); // constructor for AVL tree
	void setRoot(Node* n); // sets the root of the AVL tree
	Node* getRoot(); // returns the root of the tree
	void levelByLevel(Node* root); // visualization function to print the tree level by level 
	void printInorder(Node* node, int& count); // inorder traversal of tree
	void printPostorder(Node* node, int& count); // postorder traversal
	void printPreorder(Node* node, int& count); // preorder traversal
	Node* insertNode(Node* root, string name, int ID); // inserts new node into tree
	Node* getParent(Node* root, int ID, int height); // helper function to return the parent of node
	Node* deleteNode(Node* root, int ID); // deletes node 
	Node* getRightMost(Node* root); // helper function to get the rightmost node of given node
	void setBalanceFactors(Node* root); // recalculates and resets the tree balance factors
	Node* searchID(Node* root, int ID); // searches tree for ID
	void printLevelCount(Node* root); // prints level count of tree
	void removeInorder(Node* root, int n, int& count); // removes node at n of in order traversal
	bool searchName(Node* root, string name, int& count, bool& exists); // searches for name in tree
};
bool AVLTree::searchName(Node* root, string name, int& count, bool& exists) {
	if (count == 0) {
		exists = false;
	}
	if (root != nullptr) {
		if (root->name == name) { // if the name was found
			string idString = to_string(root->ID);
			if (idString.length() != 8) {
				string fixedID = "";
				for (int i = 0; i < 8 - idString.length(); i++) {
					fixedID.append("0");
				}
				idString = fixedID + idString;
			}
			cout << idString << endl;
			exists = true;
		}
		count++;
		searchName(root->left, name, count, exists);
		searchName(root->right, name, count, exists);
	}
	if (count == this->size) { // if the entire tree has been traversed
		if (exists) { // if the name was found in the tree
			return true;
		}
		if (!exists) { // if name never found
			return false;
		}
	}
}
Node* AVLTree::searchID(Node* root, int ID) {
	if (root != nullptr) {
		if (ID > root->ID) {
			return searchID(root->right, ID);
		}
		if (ID < root->ID) {
			return searchID(root->left, ID);
		}
		if (ID == root->ID) {
			cout << root->name << endl;
			return nullptr; // ends the recursion when the name is found
		}
	}
	cout << "unsuccessful" << endl; // prints if the name was never found
}
void AVLTree::printLevelCount(Node* root) { // prints amount of levels based on root's height
	if (this->getRoot() == nullptr) {
		cout << 0 << endl;
		return;
	}
	cout << this->getRoot()->getHeight() << endl;

}
AVLTree::AVLTree() {
	root = nullptr;
	size = 0;
}
void AVLTree::setRoot(Node* n) {
	this->root = n;
}
Node* AVLTree::getRoot() {
	return this->root;
}
void AVLTree::levelByLevel(Node* root) { // helper function to print tree level by level (taken and modified from my stepik 4.1.1 solution)
		queue<Node*> q1;
		queue<Node*> q2;
		int level = 0;
		if (root != nullptr) {
			q1.push(root);
		}
		while (!q1.empty() || !q2.empty()) {
			level++;
			cout << "Level: " << level << endl;
			while (!q1.empty()) {
				if (q1.front()->left != nullptr) {
					q2.push(q1.front()->left);
				}
				if (q1.front()->right != nullptr) {
					q2.push(q1.front()->right);
				}
				cout << q1.front()->ID << " ";
				cout << ", " << q1.front()->getBalanceFactor() << " ";
				q1.pop();
			}
			if (!q2.empty()) {
				cout << endl;
				level++;
				cout << "Level: " << level << endl;
			}
			while (!q2.empty()) {
				if (q2.front()->left != nullptr) {
					q1.push(q2.front()->left);
				}
				if (q2.front()->right != nullptr) {
					q1.push(q2.front()->right);
				}
				cout << q2.front()->ID << " ";
				cout <<  ", " << q2.front()->getBalanceFactor() << " ";
				q2.pop();
			}
			cout << endl;
		}
}
// All 3 printing traversals very similar to their normal traversal counterparts
// The count is used to make sure a comma is not printed when it is at the last node
void AVLTree::printInorder(Node* node, int& count) {
	if (this->size == 1) {
		cout << node->name;
		return;
	}
	if (node != nullptr) {
		printInorder(node->left, count);
		cout << node->name;
		count++;
		if (count != this->size) {
			cout << ", ";
		}
		printInorder(node->right, count);
	}
}
void AVLTree::printPostorder(Node* node, int& count) {
	if (this->size == 1) {
		cout << node->name;
		return;
	}
	if (node != nullptr) {
		printPostorder(node->left, count);
		printPostorder(node->right, count);
		cout << node->name;
		count++;
		if (count != this->size) {
			cout << ", ";
		}
	}
}
void AVLTree::printPreorder(Node* node, int& count) {
	if (this->size == 1) {
		cout << node->name;
		return;
	}
	if (node != nullptr) {
		cout << node->name;
		count++;
		if (count != this->size) {
			cout << ", ";
		}
		printPreorder(node->left, count);
		printPreorder(node->right, count);
	}
}
// Insert function influenced by Professor Kapoor's AVL tree insertion lecture video
Node* AVLTree::insertNode(Node* root, string name, int ID) { 
	if (root == nullptr) { // if we are at null node, create new node
		Node* n = new Node(name, ID);
		n->setBalanceFactor();
		this->size++;
		cout << "successful" << endl;
		return n;
	}
	if (ID < root->ID) {
		root->left = insertNode(root->left, name, ID);
		root->setBalanceFactor(); // rebalances the node whenever a new node is "passing" it
	}
	if (ID > root->ID) {
		root->right = insertNode(root->right, name, ID);
		root->setBalanceFactor(); // rebalances node
	}
	if (ID == root->ID) { // if node already exists in tree
		cout << "unsuccessful" << endl;
		return this->getRoot();
	}
	// the next four if statements check if balance factors are incorrect
	// as the recursion unwinds up the tree, it checks each node
	if (root->getBalanceFactor() > 1 && root->left->getBalanceFactor() >= 1) { // left left case
		Node* n = root->rotateRight();
		return n;
	}
	if (root->getBalanceFactor() < -1 && root->right->getBalanceFactor() <= -1) { // right right case
		Node* n = root->rotateLeft();
		return n;
	}
	if (root->getBalanceFactor() > 1 && root->left->getBalanceFactor() <= -1) { // left right case
		Node* n = root->rotateLeftRight();
		return n;
	}
	if (root->getBalanceFactor() < -1 && root->right->getBalanceFactor() >= 1) { // right left case
		Node* n = root->rotateRightLeft();
		return n;
	}
	return root; // always returns the current root of the tree
}
//Delete function influenced by psuedocode provided in "BST Delete" lecture video by Professor Kapoor
Node* AVLTree::deleteNode(Node* root, int ID) { 
	if (root == this->getRoot() && this->size == 1) {
		this->setRoot(nullptr);
		delete root;
		this->size--;
		cout << "successful" << endl;
		return nullptr;
	}
	if (root == nullptr) { // if the node is never found
		cout << "unsuccessful" << endl;
		return nullptr;
	}
	// tree is searched until node is found to delete
	if (ID < root->ID) { 
		return deleteNode(root->left, ID);
	}
	else if (ID > root->ID) {
		return deleteNode(root->right, ID);
	}
	else if (ID == root->ID) { // once node is found
		int rootData = root->ID;
		int height = root->getHeight();
		if (root->left == nullptr && root->right == nullptr) { // if node has no children
			Node* p = getParent(this->getRoot(), ID, height); // returns the parent of the node
			if (p->right != nullptr && p->right->ID == ID) { // if the node is the right child of the parent
				delete p->right; // node gets deleted, parent points to nullptr
				p->right = nullptr; 
			}
			if (p->left != nullptr && p->left->ID == ID) { // if the node is the left child of the parent
				delete p->left; // node gets deleted, parent points to nullptr
				p->left = nullptr;
			}
		}
		else if (root->left != nullptr && root->right == nullptr) { // if node has one left child
			if (root == this->getRoot()) {
				Node* n = root;
				this->setRoot(n->left);
				delete n;
				this->size--;
				cout << "successful" << endl;
				return nullptr;
			}
			Node* p = getParent(this->getRoot(), ID, height);
			if (p->right != nullptr && p->right->ID == ID) { // if the root is on right side of parent
				Node* n = root;
				p->right = n->left; // the parent's right child points to the node's left child 
				delete n; // node gets deleted
			}
			if (p->left != nullptr && p->left->ID == ID) { // if the node is on left side of parent
				Node* n = root;
				p->left = n->left; // the parent's left child points to the node's left child
				delete n; // node gets deleted
			}
		}
		else if (root->left == nullptr && root->right != nullptr) { // if the node has one right child
			if (root == this->getRoot()) {
				Node* n = root;
				this->setRoot(n->right);
				delete n;
				this->size--;
				cout << "successful" << endl;
				return nullptr;
			}
			Node* p = getParent(this->getRoot(), ID, height);
			if (p->right != nullptr && p->right->ID == ID) { // if the node on right side of parent
				Node* n = root;
				p->right = n->right; // the parent's right child points to the node's right child
				delete n; // node deleted
			}
			if (p->left != nullptr && p->left->ID == ID) { // if the node is on left side of parent
				Node* n = root;
				p->left = n->right; // the parent's left child points to the node's right child
				delete n; // node gets deleted
			}
		}
		else if (root->left != nullptr && root->right != nullptr) { // if the node has 2 children
			// Now finds the inorder predecessor
			if (root->left->right == nullptr) { // if node's left child no right child, it is predecessor
				root->ID = root->left->ID; // gives the node the predecessor's data
				root->name = root->left->name;
				return deleteNode(root->left, root->left->ID); // deletes the predecessor recursively
			}
			else {
				Node* n = this->getRightMost(root->left); // used to find the inorder predecessor if it has right children
				root->ID = n->ID; // gives the node the predecessor's data
				root->name = n->name;
				return deleteNode(n, n->ID); // recursively deletes predecessor's data
			}
		}
	}
	this->size--; // adjusts size as node is removed
	cout << "successful" << endl;
	setBalanceFactors(this->getRoot()); // recalculates the balance factors of the tree
}
Node* AVLTree::getRightMost(Node* root) {
	if (root->right != nullptr) {
		return getRightMost(root->right);
	}
	return root;
}
Node* AVLTree::getParent(Node* root, int ID, int height) { // finds parent of node, uses height due to temporary duplicate values when deleting
	if (root != nullptr) {
		// evaluates when either the node's left of right child meets all the requirements of the input node
		if ((root->right != nullptr && root->right->ID == ID && root->right->getHeight() == height) || (root->left != nullptr && root->left->ID == ID && root->left->getHeight() == height)) {
			return root; // returns the parent
		}
		if (ID > root->ID) {
			return getParent(root->right, ID, height);
		}
		if (ID < root->ID) {
			return getParent(root->left, ID, height);
		}
		if (ID == root->ID && height != root->getHeight()) { // if the ID is equal but the height is different (happens during deletion)
			if (getParent(root->right, ID, height)->ID != 0) { // if the parent is somewhere on the right side
				return getParent(root->right, ID, height);
			}
			if (getParent(root->left, ID, height)->ID != 0) { // if the parent is somewhere on the left side
				return getParent(root->left, ID, height);
			}
		}
	}
}
void AVLTree::setBalanceFactors(Node* root) { // preorder traversal that resets the balance factors of the nodes
	if (root != nullptr) {
		root->setBalanceFactor();
		setBalanceFactors(root->right);
		setBalanceFactors(root->left);
	}
}
void AVLTree::removeInorder(Node* root, int n, int& count) {
	if (n > this->size) { // if the input value is greater than the amount of nodes in the tree
		cout << "unsuccessful" << endl;
		return;
	}
	if (root != nullptr) { // whenever we reach the root, increment the count
		removeInorder(root->left, n, count);
		if (count == n) { // evaluates when we reach the desired node
			deleteNode(this->getRoot(), root->ID);
			return;
		}
		count++;
		removeInorder(root->right, n, count);
	}
}
int main() {
	AVLTree gatorAVL;
	int numInputs = 0;
	cin >> numInputs; // number of inputs user wants to enter
	for (int i = 0; i <= numInputs; i++) { // allows user to input as many inputs as numInputs
		string command;
		getline(cin, command);
		if (command.substr(0, 6) == "search") {
			if (command.at(7) == '\"') {
				int temp2 = command.find_last_of("\"");
				int temp = command.find_first_of("\"");
				int length = temp2 - temp;
				string name = command.substr(temp + 1, length - 1);
				int count = 0;
				bool exists = false;
				if (!gatorAVL.searchName(gatorAVL.getRoot(), name, count, exists)) {
					cout << "unsuccessful" << endl;
				}
			}
			else {
				int back = command.length() - 7;
				int id  = 0;
				try {
					string s = command.substr(7, back);
					int id = stoi(s);
					gatorAVL.searchID(gatorAVL.getRoot(), id);
				}
				catch (exception e) {
					cout << "unsuccessful" << endl;
				}
				
			}
		}
		if (command.substr(0, 6) == "insert") {
			try {
				int temp2 = command.find_last_of("\"");
				int temp = command.find_first_of("\"");
				int length = temp2 - temp;
				string name = command.substr(temp + 1, length - 1);
				string idString = command.substr(temp2 + 2, command.length() - 7);
				regex regx("[]1234567890!@#$%^&*()_+=|}{\~`/?><:;'/.,'");
				if (regex_search(name, regx) == 0) {
					cout << "unsuccessful";
				}
				//cout << id.length() << endl;
				if (idString.length() == 8) {
					int idInt = stoi(idString);
					//cout << id;
					gatorAVL.setRoot(gatorAVL.insertNode(gatorAVL.getRoot(), name, idInt));
				}
				else {
					cout << "unsuccessful" << endl;
				}
				
			}
			catch (exception e) {
				cout << "unsuccessful" << endl;
			}
		}
		if (command.substr(0, 13) == "removeInorder") {
			try {
				int n = stoi(command.substr(14, command.length() - 14));
				int count = 0;
				gatorAVL.removeInorder(gatorAVL.getRoot(), n, count);
				
			}
			catch (exception e) {
				cout << "unsuccessful" << endl;
			}
		}
		else if (command.substr(0, 6) == "remove") {
			try {
				string idString = command.substr(7, command.length() - 7);
				if (idString.length() == 8) {
					int idInt = stoi(idString);
					gatorAVL.deleteNode(gatorAVL.getRoot(), idInt);
				}
				else {
					cout << "unsuccessful" << endl;
				}
			}
			catch (exception e) {
				cout << "unsuccessful" << endl;
			}
		}
		if (command.substr(0, 12) == "printInorder") {
			int count = 0;
			gatorAVL.printInorder(gatorAVL.getRoot(), count);
			cout << endl;
		}
		if (command.substr(0, 13) == "printPreorder") {
			int count = 0;
			gatorAVL.printPreorder(gatorAVL.getRoot(), count);
			cout << endl;
		}
		if (command.substr(0, 14) == "printPostorder") {
			int count = 0;
			gatorAVL.printPostorder(gatorAVL.getRoot(), count);
			cout << endl;
		}
		if (command.substr(0, 15) == "printLevelCount") {
			gatorAVL.printLevelCount(gatorAVL.getRoot());
		}

	}
	return 0;
}