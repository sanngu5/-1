#include "search_menu.h"

//���ǹ�ȣ�� �˻�
void search_num() {
	ifstream c_file;
	string s_num;
	int e_code;

	//system("cls");
	while (1) {
		cout << "�����ȣ: ";
		getline(cin, s_num);
		e_code = f_num(s_num);	//����ó��
		if (e_code == 0) {
			char s_array[5];
			strcpy(s_array, s_num.c_str());
			c_file.open("class_list.txt");
			string line;
			while (1) {
				getline(c_file, line);
				if (line[0] == s_array[0] && line[1] == s_array[1] && line[2] == s_array[2] && line[3] == s_array[3]) {	//���� ��
					cout << endl;
					class_style(line);
					cout << endl << endl;
					c_file.close();
					break;
				}
				if (c_file.eof()) {	//���� ��
					cout << endl << "�����ȣ�� �ṉ̀�Ģ �� '�������� ����' �����Դϴ�" << endl << endl;
					c_file.close();
					break;
				}
			}
		}
		else if (e_code == 1) {
			cout << endl << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl << endl;
		}
		else if (e_code == 2) {
			cout << endl << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl << endl;
		}
		else if (e_code == 3) return;
	}
}

//���Ǹ����� �˻�
void search_name() {
	ifstream c_file;
	string s_name;
	int e_code;

	//system("cls");
	while (1) {
		cout << "�����: ";
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
					if (name == s_name) {	//���� ��
						cout << endl;
						class_style(line);
						cout << endl << endl;
						c_file.close();
						break;
					}
				}
				if (c_file.eof()) {	//���� ��
					cout << endl << "������� �ṉ̀�Ģ �� '�������� ����' �����Դϴ�" << endl << endl;
					c_file.close();
					break;
				}
			}
		}
		else if (e_code == 1) {
			cout << endl << "������� ������Ģ �� '���� ����' �����Դϴ�" << endl << endl;
		}
		else if (e_code == 2)
			return;
	}
}

//��ü����
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
		cout << "���ư����� q�� �Է��ϼ���: ";
		getline(cin, back);
		e_code = f_all(back);
		if (e_code == 0)
			return;
		else if (e_code == 1) {
			cout << endl << "��ü��ȸ�� ��Ģ �� '�ڷΰ��� ����' �����Դϴ�" << endl << endl;
		}
	}
}