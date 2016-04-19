#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include<stack>
#include <algorithm> 

using namespace std;

bool is_number(const string& s) {
	string::const_iterator it = s.begin();
	while (it != s.end() && *it == ' ') {
		++it;
	}
	if (*it == '-') {
		++it;
	}
	while (it != s.end() && *it == ' ') {
		++it;
	}
	if (it == s.end()) {
		return false;
	}
	while (it != s.end() && (isdigit(*it) || (*it == '.'))) {
		++it;
	}
	while (it != s.end()&&*it == ' ') {
		++it;
	}
	return !s.empty() && it == s.end();
}

double to_number(const string& s) {
	return atof(s.c_str());
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
bool mycom(string i, string j) { return (i.size() > j.size() ); }
string infix2postfix(const string& s) {
	string res;
	stack<char> ops;
	map<char, int> prior;
	prior['+'] = 0;
	prior['-'] = 0;
	prior['/'] = 1;
	prior['*'] = 1;
	int i = 0;
	while(i < s.size()){
		if (s[i] == ' ') {
			i++;
		}
		if (isdigit(s[i])) {
			string num;
			while (isdigit(s[i]) || s[i] == '.') {
				num.push_back(s[i]);
				i++;
			}
			res = res + num + '$';
			continue;
		}
		else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')) {
			if (ops.empty()) ops.push(s[i]);
			else {
				char temp = ops.top();
				while (prior[temp] >= prior[s[i]] && temp != '(') {
					res += temp;
					ops.pop();
					if (ops.empty()) break;
					temp = ops.top();
				}
				ops.push(s[i]);
			}
		}
		else if (s[i] == '(') ops.push(s[i]);
		else if (s[i] == ')') {
			char temp = ops.top();
			while (temp != '(') {
				res += temp;
				ops.pop();
				temp = ops.top();
			}
			ops.pop();
		}
		i++;
	}
	while (!ops.empty()) {
		res += ops.top();
		ops.pop();
	}
//	cout << "The RPE is " << res << endl;
	return res;

}

string& trim(string &s){
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

class Calculator {
public:
	double Calc(const string& s) const {

		string postfix = infix2postfix(s);
		// IMPLEMENT ME
		double res = 0;
		int i = 0;
		stack<string> stack1;
		string num;
		while (i< postfix.size())
		{
			if (isdigit(postfix[i])) {
				num.clear();
				while (postfix[i] != '$') {
					num.push_back(postfix[i]);
					i++;
				}
				stack1.push(num);
				i++;//skip '$'
				continue;
			}
			else {
				double num2 = to_number(stack1.top());
				stack1.pop();
				double num1 = to_number(stack1.top());
				stack1.pop();
				double temp = 0;
				if (postfix[i] == '+') {
					temp = num1 + num2;
				}
				else if (postfix[i] == '-') {
					temp = num1 - num2;
				}
				else if (postfix[i] == '*') {
					temp = num1 * num2;
				}
				else if(postfix[i] == '/') {
					temp = num1 / num2;
				}
				stack1.push(to_string(temp));
			}
			i++;
		}
		res = to_number(stack1.top());
		stack1.pop();
		return res;
		
	}

	vector<double> CalcWithVars(const vector<string>& inputs) const {
		// IMPLEMENT ME
		map<string, double> table;
		vector<string> lefts;
		vector<double> output;
		for (int i = 0; i < inputs.size(); i++) {
			vector<string> split_equal = split(inputs[i], '=');
			string left = trim(split_equal[0]);
			string right = trim(split_equal[1]); 
			for (int j = 0; j < lefts.size(); j++) {
				string temp = lefts[j];
				string repl  = to_string(table[temp]);
				while (right.find(temp) != string::npos) {
					right.replace(right.find(temp), temp.size(), repl);
				}
			}
			double right_val = Calc(right);
			lefts.push_back(left);
			sort(lefts.begin(), lefts.end(), mycom);
			table[left] = right_val;
			output.push_back(right_val);
		}
		return output;
	}
};


#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
	Calculator calculator;
	cout << "First Step" << endl;
	// should print 5.85714
	cout << calculator.Calc(" 3 + 4 * 5 ") << endl;

	cout << "\nSecond Step" << endl;
	// should print a 5
	cout << calculator.Calc("( 3 + 4 ) * 5 / 7") << endl;

	cout << "\nThird Step" << endl;
	// should print 3 and 243. 3 for "pi" and 243 for "9 * 9 * 3".
	vector<double> output = calculator.CalcWithVars(
	{ "   a  = 3", "ab = 2 * 3+a-4","abc = ab*( a + 1)+a*(ab+3)" });
	for (size_t i = 0; i < output.size(); ++i) {
		cout << output[i] << endl;
	}
	getchar();
}

#endif
