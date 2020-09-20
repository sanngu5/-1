//파일 입출력에 필요한 함수들 정의하세요.
//함수 이름은 read_asdf() 혹은 write_asdf()

#include"file.h"
#include"data.h"

int line_num;

int login() {
	while (1) {
		char temp_student_id[100];
		string tempid;
		cout << "학번: ";
		getline(cin, tempid);
		strcpy_s(temp_student_id, tempid.c_str());
		if (tempid.size()==1&&temp_student_id[0]=='q') {			//q탈출
			return 0;
		}
		if (!filter_grammar_student_id_length(temp_student_id)) {
			set_error_flag(ERROR_GRAMMAR_STUDENT_ID_LENGTH);
			continue;
		}
		if (!filter_grammar_student_id_number(temp_student_id)) {
			set_error_flag(ERROR_GRAMMAR_STUDENT_ID_NUMBER);
			continue;
		}
		if ((line_num = filter_meaning_student_id_register(temp_student_id)) == -1) {
			set_error_flag(ERROR_MEANING_STUDENT_ID_REGISTER);
			continue;
		}
		break;
	}
	while (1) {
		char temp_pw[100];
		string temppw;
		cout << "비밀번호: ";
		getline(cin, temppw);
		strcpy_s(temp_pw, temppw.c_str());
		if (temppw.size() == 1 && temp_pw[0] == 'q') {					//q탈출
			return 0;
		}
		if (!filter_grammar_password_length(temp_pw)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_LENGTH);
			continue;
		}
		if (!filter_grammar_password_comb(temp_pw)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_COMB);
			continue;
		}
		if (!filter_meaning_password_match(temp_pw, line_num)) {
			set_error_flag(ERROR_MEANING_PASSWORD_MATCH);
			continue;
		}
		return 1;
	}
}

bool Register() {
	ifstream inFile;
	ofstream outFile;

	string total_info = ""; // 전체 정보가 저장되는 곳
	string student_id; // 학번
	string password; // 비밀번호
	string password_check; // 비밀번호 확인
	string name; // 이름

	bool not_compliant; // 학번 중복여부체크

//	cout << "=====회원가입=====" << endl << endl;

	// 학번저장 구현부
	do {
		not_compliant = false;

		cout << "학번: ";
		getline(cin, student_id);

		// q 입력시 취소
		if (student_id == "q") {
			//			cout << "-초기 선택화면으로 이동합니다." << endl << endl;
			return false;
		}

		if (not_compliant = !filter_grammar_student_id_length(student_id)) {
			set_error_flag(ERROR_GRAMMAR_STUDENT_ID_LENGTH);
			continue;
		}

		if (not_compliant = !filter_grammar_student_id_number(student_id)) {
			set_error_flag(ERROR_GRAMMAR_STUDENT_ID_NUMBER);
			continue;
		}

		if (not_compliant = !filter_meaning_student_id_overlap(student_id)) {
			set_error_flag(ERROR_GRAMMAR_STUDENT_ID_OVERLAP);
			continue;
		}
	} while (not_compliant); // 조건에 부합하지 못하면 재실행
	cout << endl;
	total_info = total_info + student_id + " ";

	// 비밀번호저장 구현부	
	do {
		not_compliant = false;
		cout << "비밀번호: ";
		getline(cin, password);

		// q 입력시 취소
		if (password == "q") {
			//			cout << "-초기 선택화면으로 이동합니다." << endl << endl;
			return false;
		}

		if (not_compliant = !filter_grammar_password_length(password)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_LENGTH);
			continue;
		}

		if (not_compliant = !filter_grammar_password_comb(password)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_COMB);
			continue;
		}
	} while (not_compliant); // 조건에 부합하지 못하면 재실행

	do {
		not_compliant = false;
		cout << "비밀번호 확인: ";
		getline(cin, password_check);

		// q 입력시 취소
		if (password_check == "q") {
			//			cout << "-초기 선택화면으로 이동합니다." << endl << endl;
			return false;
		}

		if (not_compliant = !filter_grammar_password_length(password_check)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_LENGTH);
			continue;
		}

		if (not_compliant = !filter_grammar_password_comb(password_check)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_COMB);
			continue;
		}

		if (not_compliant = !filter_meaning_password_check(password, password_check)) {
			set_error_flag(ERROR_GRAMMAR_PASSWORD_CHECK);
			continue;
		}
	} while (not_compliant); // 조건에 부합하지 못하면 재실행
	cout << endl;
	total_info = total_info + password + " ";

	// 이름저장 구현부
	do {
		not_compliant = false;
		cout << "이름: ";
		getline(cin, name);

		// q 입력시 취소
		if (name == "q") {
			//			cout << "-초기 선택화면으로 이동합니다." << endl << endl;
			return false;
		}

		if (not_compliant = !filter_grammar_name_length(name)) {
			set_error_flag(ERROR_GRAMMAR_NAME_LENGTH);
			continue;
		}

		if (not_compliant = !filter_meaning_name_korean(name)) {
			set_error_flag(ERROR_MEANING_NAME_KOREAN);
			continue;
		}
	} while (not_compliant); // 조건에 부합하지 못하면 재실행
	cout << endl;
	total_info = total_info + name + " ";

	// 과목갯수, 과목코드 (default) 구현부
	total_info = total_info + "0";

	// 최종입력 구현부
	outFile.open("account_list.txt", ios::app);
	outFile << total_info << endl;
	outFile.close();
	cout << "가입에 성공했습니다" << endl;
	return true;
}