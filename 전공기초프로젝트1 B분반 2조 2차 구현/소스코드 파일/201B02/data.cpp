#include"data.h"

class Account {
private:
	char* student_number;
	char* name;
	char* id;
	char* pw;
	int timetable[5][20] = { 0 };	//시간표 담는 배열
};

void set_error_flag(int setError) {
	ERROR_FLAG = setError;
	show_error(ERROR_FLAG);
	ERROR_FLAG = NOERROR;
}

void show_error(int flag) {
	switch (flag) {
	case -2:
		cout << "학번의 문법규칙 중 '길이' 오류입니다" << endl;
		break;
	case -3:
		cout << "학번의 문법규칙 중 '숫자가 아닌 문자' 오류입니다" << endl;
		break;
	case -4:
		cout << "학번의 의미규칙 중 '미등록'의 오류입니다" << endl;
		break;
	case -5:
		cout << "비밀번호의 문법규칙 중 '길이' 오류입니다" << endl;
		break;
	case -6:
		cout << "비밀번호의 문법규칙 중 '인자 조합' 오류입니다" << endl;
		break;
	case -7:
		cout << "비밀번호의 의미규칙 중 '불일치'의 오류입니다" << endl;
		break;
	case -8:
		cout << "학번의 의미규칙 중 '중복'의 오류입니다" << endl;
		break;
	case -9:
		cout << "비밀번호 확인의 의미규칙 중 '비밀번호 확인과 비밀번호 불일치'의 오류입니다" << endl;
		break;
	case -10:
		cout << "이름의 문법규칙 중 '길이' 오류입니다" << endl;
		break;
	case -11:
		cout << "이름의 문법규칙 중 '한글이 아닌 문자' 오류입니다" << endl;
		break;
	default:
		break;
	}
}