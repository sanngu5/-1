#include "search_menu.h"

//강의번호로 검색
void search_num() {
	ifstream c_file;
	string s_num;
	int e_code;

	//system("cls");
	while (1) {
		cout << "과목번호: ";
		getline(cin, s_num);
		e_code = f_num(s_num);	//예외처리
		if (e_code == 0) {
			char s_array[5];
			strcpy(s_array, s_num.c_str());
			c_file.open("class_list.txt");
			string line;
			while (1) {
				getline(c_file, line);
				if (line[0] == s_array[0] && line[1] == s_array[1] && line[2] == s_array[2] && line[3] == s_array[3]) {	//있을 시
					cout << endl;
					class_style(line);
					cout << endl << endl;
					c_file.close();
					break;
				}
				if (c_file.eof()) {	//없을 시
					cout << endl << "과목번호의 의미규칙 중 '강의존재 조건' 오류입니다" << endl << endl;
					c_file.close();
					break;
				}
			}
		}
		else if (e_code == 1) {
			cout << endl << "과목번호의 문법규칙 중 '길이 조건' 오류입니다" << endl << endl;
		}
		else if (e_code == 2) {
			cout << endl << "과목번호의 문법규칙 중 '범위 조건' 오류입니다" << endl << endl;
		}
		else if (e_code == 3) return;
	}
}

//강의명으로 검색
void search_name() {
	ifstream c_file;
	string s_name;
	int e_code;

	//system("cls");
	while (1) {
		cout << "과목명: ";
		getline(cin, s_name);
		e_code = f_name(s_name);
		if (e_code == 0) {
			c_file.open("class_list.txt");
			while (1) {
				string line;
				getline(c_file, line);
				if (line.size() != 0) {
					char s_array[100];
					strcpy(s_array, line.c_str());
					char* ptr = strtok(s_array, " ");
					ptr = strtok(NULL, " ");
					string name = ptr;
					if (name == s_name) {	//있을 시
						cout << endl;
						class_style(line);
						cout << endl << endl;
						c_file.close();
						break;
					}
				}
				if (c_file.eof()) {	//없을 시
					cout << endl << "과목명의 의미규칙 중 '강의존재 조건' 오류입니다" << endl << endl;
					c_file.close();
					break;
				}
			}
		}
		else if (e_code == 1) {
			cout << endl << "과목명의 문법규칙 중 '길이 조건' 오류입니다" << endl << endl;
		}
		else if (e_code == 2)
			return;
	}
}

//전체보기
void search_all() {
	ifstream c_file;
	string back;
	int e_code;

	//system("cls");
	c_file.open("class_list.txt");
	while (1) {
		string line;
		getline(c_file, line);
		if(line.size()!=0)class_style(line);
		if (c_file.eof()) {
			break;
		}
	}
	while (1) {
		cout << "돌아가려면 q를 입력하세요: ";
		getline(cin, back);
		e_code = f_all(back);
		if (e_code == 0)
			return;
		else if (e_code == 1) {
			cout << endl << "전체조회의 규칙 중 '뒤로가기 조건' 오류입니다" << endl << endl;
		}
	}
}