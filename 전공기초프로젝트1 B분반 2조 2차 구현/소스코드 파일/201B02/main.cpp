#include "menu3.h"
#include "file.h"
#include "modify.h"
extern int line_num;
int menu2() {
	string menu_input;
	while (1) {
//		cout << "[" << logname() << "�� ȯ���մϴ�]" << endl;
		cout << "[�޴�2]" << endl;
		cout << "1. ������ȸ" << endl;
		cout << "2. ������û" << endl;
		cout << "3. �ð�ǥ" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ���: ";
		getline(cin, menu_input);
		if (menu_input == "1") {
			menu3(); // ������ȸ
		}
		else if (menu_input == "2") {
			modify();
			// ������û
		}
		else if (menu_input == "3") {
			table(); //�ð�ǥ
		}
		else if (menu_input == "4") {
			// ����
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
		cout << "[�޴�1]" << endl;
		cout << "1. �α���" << endl;
		cout << "2. ȸ������" << endl;
		cout << "3. ����" << endl;
		cout << "�޴��� �����ϼ���: ";
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

