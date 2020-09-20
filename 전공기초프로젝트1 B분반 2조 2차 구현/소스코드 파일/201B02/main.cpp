#include "menu3.h"
#include "file.h"
#include "modify.h"
extern int line_num;
int menu2() {
	string menu_input;
	while (1) {
//		cout << "[" << logname() << "님 환영합니다]" << endl;
		cout << "[메뉴2]" << endl;
		cout << "1. 과목조회" << endl;
		cout << "2. 수강신청" << endl;
		cout << "3. 시간표" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요: ";
		getline(cin, menu_input);
		if (menu_input == "1") {
			menu3(); // 과목조회
		}
		else if (menu_input == "2") {
			modify();
			// 수강신청
		}
		else if (menu_input == "3") {
			table(); //시간표
		}
		else if (menu_input == "4") {
			// 종료
			break;
		}
	}
	return 1;
}

int main() {
	system("mode con cols=140 lines=30");
	bool wh = filecheck();
	string menu_input;
	while (wh) {
		cout << "[메뉴1]" << endl;
		cout << "1. 로그인" << endl;
		cout << "2. 회원가입" << endl;
		cout << "3. 종료" << endl;
		cout << "메뉴를 선택하세요: ";
		getline(cin, menu_input);
		if (menu_input == "1") {
			if (login()) {
				menu2();
				break;
			}
		}
		else if (menu_input == "2") {
			if (Register())registersuccess();
		}
		else if (menu_input == "3") {
			break;
		}
	}
	if (!wh)system("pause > nul");
	return 1;
}

