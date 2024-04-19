// split.cpp
#include <cctype>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
static bool space(char c) {
	return isspace(c);
}
static bool not_space(char c) {
	return !isspace(c);
}

vector<string>split(const string& s) {
	typedef string::const_iterator iter;

	vector<string> ret;
	iter i = s.begin();
	

	//불변성 :지금까지 원래의 i,현재의 i 범위에 있는 
	//문자들을 처리
	while (i != s.end()) {
		
		i = find_if(i, s.end(), not_space);
		iter  j = find_if(i, s.end(), space);
		if (i != s.end())
			ret.push_back(string(i, j));
		i = j;
	}

	return ret;
}

int main() {
	string s;

	while (getline(cin, s)) {
		vector<string> v = split(s);
		for (vector<string>::size_type i = 0; i != v.size(); ++i) {
			cout << v[i] << endl;
		}
	}
	return 0;
}
