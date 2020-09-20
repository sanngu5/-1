#include "menu3.h"

void menu3() {
	string num;
	int e_code;

	while (1) {
		//system("cls");
		while (1) {
			cout << "[메뉴3]" << endl;
			cout << "1. 과목번호로 조회" << endl << "2. 과목명으로 조회" << endl << "3. 전체조회" << endl << "메뉴를 선택하세요: ";
			getline(cin, num);
			e_code = f_smenu(num);
			if (e_code == 0) {
				cout << "메뉴3의 규칙 중 '메뉴존재 조건' 오류입니다" << endl; //1,2,3,q를 제외한 예외처리
			}
			else {
				if (e_code == 1) search_num();	//강의명으로 검색
				else if (e_code == 2) search_name();	//강의번호로 검색
				else if (e_code == 3) search_all();	//전체보기
				else if (e_code == 4) {
					//system("cls");
					return;	//메인메뉴로
				}
				break;
			}
		}
	}
}