//urls.cpp

#include<algorithm>//find find_if()
#include <cctype>// isalnum()
#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool not_url_char(char c) {
	static const string url_ch = "~;/?:@=&-_.+!*'(),";
	return !(
		isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end()
		);

}
string::const_iterator url_beg(string::const_iterator b,
	string::const_iterator e) {
	static const string sep = "://";
	typedef string::const_iterator iter;
	//i는 구분 기호를 발견한 위치를 표시
	iter i = b;
	while ((i = search(i, e, sep.begin(), sep.end())) != e) {
		//구분 기호가 현재 탐색 범위의 처음 또는 마지막에 있는지 확인
		if (i != b && i + sep.size() != e) {
			//beg는 프로토콜 이름의 시작 위치를 표시
			iter beg = i;
			while (beg != b && isalpha(beg[-1])) {
				--beg;
			}
			if (beg != i && !not_url_char(i[sep.size()])) //구분 기호 앞뒤로 URL의 일부에서 유효한 문자가 하나라도 있는지 확인
				return beg;
		}

		//발견한 구분 기호는 URL 일부가 아니므로 
		//해당 구분기호 이후를 표시하도록 i를 증가시킴
		i += sep.size();
	}
	return e;
}
string::const_iterator url_end(string::const_iterator b,
	string::const_iterator e) {
	return find_if(b, e, not_url_char);
}

vector<string> find_urls(const string& s) {
	vector<string> urls;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();
	//인수로 전달받은 문자열 전체를 탐색
	while (b != e) {
		//://의 앞쪽에서 하나 이상의 문자를 탐색
		b = url_beg(b, e); //프로토콜 이름 찾기 
		if (b != e) {
			//해당 문자를 찾았다면 URL의 나머지 부분을 탐색
			iter after = url_end(b, e);//프로토콜 이름 
			urls.push_back(string(b, after));
			//URL을 저장
			b = after;
		}
	}
	return urls;
}
int main() {
	string s;
	while (getline(cin, s)) {
		vector<string> v = find_urls(s);
		for (vector<string>::const_iterator i = v.begin(); i != v.end(); i++){
			cout<<*i<<endl;
		}
	}
}