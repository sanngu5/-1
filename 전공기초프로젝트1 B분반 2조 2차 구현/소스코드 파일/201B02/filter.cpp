//여기에 문법 검사하는 함수 정의하세요.
//이름은 filter_grammar_asdf() 혹은 filter_meaning_asdf()

#include "filter.h"

int filter_grammar_student_id_length(char* str) {

	int checker_korean = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (strlen(str) - checker_korean / 2 != 9) {						//길이 검사
		return 0;
	}
	return 1;
}

int filter_grammar_student_id_number(char* str) {
	for (int i = 0; i < strlen(str); i++) {		//숫자 검사
		if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

int filter_meaning_student_id_register(char* str) {
	ifstream readFile;							//중복 검사
	readFile.open("account_list.txt");
	if (readFile.is_open()) {
		for (int i = 0; !readFile.eof(); i++) {
			char temp_line[100];		//메모장 한 줄 수 최대 68자 (학번9 + 비번15 + 이름8 + 과목수1 + 과목번호24 + 공백10 + 널값1)
			readFile.getline(temp_line, 100);
			if (temp_line[0] != NULL) {
				char* compare = strtok(temp_line, " ");
				//컴페어 자르기
				if (!strcmp(compare, str)) {
					readFile.close();
					return i;				//리스트에 같은 학번 있으면 라인 넘버 반환
				}
			}
		}
		readFile.close();
		return -1;					//리스트에 없으면 0반환
	}
	return -1;
}

int filter_grammar_password_length(char* str) {

	int checker_korean = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (strlen(str) - checker_korean / 2 < 5 || strlen(str) - checker_korean / 2 > 15) {		//길이 검사
		return 0;
	}
	return 1;
}

int filter_grammar_password_comb(char* str) {
	bool checker_num = false;						//숫자+알파벳 검사
	bool checker_char = false;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= '0' && str[i] <= '9')
			checker_num = true;
		else if (str[i] >= 'a' && str[i] <= 'z')
			checker_char = true;
		else
			return 0;
	}
	if (checker_num && checker_char)				//같이 있는지 검사
		return 1;

	return 0;
}

int filter_meaning_password_match(char* str, int line_num) {

	ifstream readFile;							//중복 검사
	readFile.open("account_list.txt");
	if (readFile.is_open()) {
		char temp_line[100];		//메모장 한 줄 수 최대 100자 (학번9 + 비번15 + 이름8 + 과목수1 + 과목번호24 + 공백10 + 널값1)
		for (int i = 0; i <= line_num; i++) {
			readFile.getline(temp_line, 100);
			strtok(temp_line, " ");
			char* compare = strtok(NULL, " ");
			if (!strcmp(compare, str)) {
				readFile.close();
				return 1;
			}
		}
	}
	readFile.close();
	return 0;
}
int filter_grammar_student_id_length(string str) {
	int checker_korean = 0;

	for (int i = 0; i < str.length(); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (str.length() - checker_korean / 2 != 9) {						//길이 검사
		return 0;
	}
	return 1;
}


int filter_grammar_student_id_number(string str) {
	for (int i = 0; i < str.length(); i++) {		//숫자 검사
		if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

int filter_grammar_password_length(string str) {

	int checker_korean = 0;

	for (int i = 0; i < str.length(); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (str.length() - checker_korean / 2 < 5 || str.length() - checker_korean / 2 > 15) {		//길이 검사
		return 0;
	}

	return 1;
}

int filter_grammar_password_comb(string str) {
	bool checker_num = false;						//숫자+알파벳 검사
	bool checker_char = false;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= '0' && str[i] <= '9')
			checker_num = true;
		else if (str[i] >= 'a' && str[i] <= 'z')
			checker_char = true;
		else
			return 0;
	}
	if (checker_num && checker_char)				//같이 있는지 검사
		return 1;

	return 0;
}

int filter_meaning_student_id_overlap(string str) {
	ifstream inFile;
	string temp = ""; // 문자열 임시 저장

	inFile.open("account_list.txt"); // account_list.txt : 계정정보 저장 텍스트 파일
	while (!inFile.eof()) {
		getline(inFile, temp);
		temp = temp.substr(0, temp.find(" "));
		if (temp == str) {
			return 0;
		}
	}
	inFile.close();

	return 1;
}

int filter_meaning_password_check(string str1, string str2) {
	if (str1 != str2) {
		return 0;
	}
	return 1;
}

int filter_grammar_name_length(string str) {
	int checker_korean = 0;

	for (int i = 0; i < str.length(); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (str.length() - checker_korean / 2 < 2 || str.length() - checker_korean / 2 > 5) {		//길이 검사
		return 0;
	}
	return 1;
}

int filter_meaning_name_korean(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (((str[i] & 0x80) == 0)) {
			return 0;
		}
	}
	return 1;
}

int f_smenu(string num) {	//강의조회 메뉴 예외처리
	if (num == "1") return 1;
	else if (num == "2") return 2;
	else if (num == "3") return 3;
	else if (num == "q") return 4;
	else return 0;
}

int f_num(string s_num) {	//강의번호로 검색 예외처리
	if (s_num.size() == 4) {
		if (s_num == "0000") return 2;	//조건 (0001~9999)과 다른 입력값
		char s_array[5];
		strcpy(s_array, s_num.c_str());
		if (48 <= s_array[0] && s_array[0] <= 57 && 48 <= s_array[1] && s_array[1] <= 57 && 48 <= s_array[2] && s_array[2] <= 57 && 48 <= s_array[3] && s_array[3] <= 57)
			return 0;	//조건과 일치하는 입력값
		else return 2;
	}
	else {
		if (s_num == "q") return 3;	//강의조회 메뉴로 돌아가기
		return 1;	//4byte가 아닌 입력값
	}
}

int f_name(string s_name) {	//강의명으로 검색 예외처리
	if (s_name.size() >= 2 && s_name.size() <= 40) return 0;	//조건(한글 2자리, 영어/숫자/특수문자(키보드로 입력 가능한 값만)은 1자리로 계산할 때 2자리 이상)과 일치하는 입력값
	else {	//예외처리
		if (s_name == "q") return 2;	//강의조회 메뉴로 돌아가기
		return 1;	//조건과 다른 입력값
	}
}

int f_all(string back) {
	if (back == "q")
		return 0;
	else return 1;
}