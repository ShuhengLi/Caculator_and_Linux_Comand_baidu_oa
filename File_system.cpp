#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


struct TreeNode
{
	string Key;
	string content;
	vector<TreeNode* > children;
};

class Tree
{
public:
	Tree();
	bool find(string);
	void fromroot();
	void insert(string);
	void addcontent(string);
	vector<string> showchild();
	string showcontent();
	string getKey();

private:
	TreeNode *root;
	TreeNode *target;
	bool preorder(string, TreeNode *T);
};

Tree::Tree()
{
	TreeNode* newnode = new TreeNode();
	newnode->Key = "";
	root = newnode;
	return;
}
string Tree::getKey() {
	return target->Key;
}
bool Tree::find(string s) {
	TreeNode *temp = root;
	return preorder(s, temp);
}
void Tree::fromroot() {
	target = root;
}

bool Tree::preorder(string s, TreeNode* node) {
	if (node == NULL) return false;
	if (node->Key == s) {
		target = node;
		return true;
	}
	bool res = 0;
	for (int j = 0; j < node->children.size(); j++) {
		res = res || preorder(s, node->children[j]);
	}
	return  res;
}

void Tree::insert(string s) {
	TreeNode* newNode = new TreeNode();
	newNode->Key = s;
	target->children.push_back(newNode);
}
void Tree::addcontent(string s) {
	target->content = s;
}
vector<string> Tree::showchild() {
	vector<string> res;
	for (size_t i = 0; i < target->children.size(); i++) {
		res.push_back(target->children[i]->Key);
	}
	return res;
}

string Tree::showcontent() {
	string res;
	res = target->content;
	return res;
}


vector<string> split(const string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

string join(const vector<string>& input) {
	string output = "";
	bool has_data = false;
	for (size_t i = 0; i < input.size(); ++i) {
		has_data = true;
		output += input[i];
		output += ", ";
	}
	if (has_data) {
		output = output.substr(0, output.length() - 2);
	}
	return output;
}

class FileSystem {
public:
	vector<string> Ls(const string& path, Tree* T) {
		// IMPLEMENT ME
		vector<string> output;
		vector<string> nodes = split(path, '/');
		int last = nodes.size() - 1;
		T->find(nodes[last]);
		output = T->showchild();
		if (output.size() == 0) output.push_back(T->getKey());
		return output;
	}

	void MkdirP(const string& dir_path, Tree *T) {
		// IMPLEMENT ME
		vector<string> nodes = split(dir_path, '/');

		for (size_t i = 0; i < nodes.size(); i++) {
			if (T->find(nodes[i])) continue;
			else {
				T->find(nodes[i - 1]);
				T->insert(nodes[i]);
			}
		}
	}

void AddFileWithContent(const string& file_path, const string& content, Tree *T) {
	// IMPLEMENT ME
	// IMPLEMENT ME
	MkdirP(file_path, T);
	vector<string> nodes = split(file_path, '/');
	int last = nodes.size() - 1;
	T->find(nodes[last]);
	T->addcontent(content);
}

string GetFileContent(const string& file_path, Tree *T) {
	// IMPLEMENT ME
	string res;
	vector<string> nodes = split(file_path, '/');
	int last = nodes.size() - 1;
	T->find(nodes[last]);
	res = T->showcontent();
	return res;
}
};


#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
	FileSystem fs;
	Tree *theTree = new Tree();
	// should print ""
	cout << join(fs.Ls("/", theTree)) << endl;
	fs.MkdirP("/a/b/c", theTree);
	fs.AddFileWithContent("/a/b/c/d", "hello world", theTree);
	// should print a
	cout << join(fs.Ls("/", theTree)) << endl;
	// should print d
	cout << join(fs.Ls("/a/b/c", theTree)) << endl;
	// should print d
	cout << join(fs.Ls("/a/b/c/d", theTree)) << endl;
	// should print hello world
	cout << fs.GetFileContent("/a/b/c/d", theTree) << endl;
	getchar();
}

#endif


