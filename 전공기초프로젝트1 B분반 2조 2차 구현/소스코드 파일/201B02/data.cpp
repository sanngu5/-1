#include"data.h"

class Account {
private:
	char* student_number;
	char* name;
	char* id;
	char* pw;
	int timetable[5][20] = { 0 };	//�ð�ǥ ��� �迭
};

void set_error_flag(int setError) {
	ERROR_FLAG = setError;
	show_error(ERROR_FLAG);
	ERROR_FLAG = NOERROR;
}

void show_error(int flag) {
	switch (flag) {
	case -2:
		cout << "�й��� ������Ģ �� '����' �����Դϴ�" << endl;
		break;
	case -3:
		cout << "�й��� ������Ģ �� '���ڰ� �ƴ� ����' �����Դϴ�" << endl;
		break;
	case -4:
		cout << "�й��� �ṉ̀�Ģ �� '�̵��'�� �����Դϴ�" << endl;
		break;
	case -5:
		cout << "��й�ȣ�� ������Ģ �� '����' �����Դϴ�" << endl;
		break;
	case -6:
		cout << "��й�ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl;
		break;
	case -7:
		cout << "��й�ȣ�� �ṉ̀�Ģ �� '����ġ'�� �����Դϴ�" << endl;
		break;
	case -8:
		cout << "�й��� �ṉ̀�Ģ �� '�ߺ�'�� �����Դϴ�" << endl;
		break;
	case -9:
		cout << "��й�ȣ Ȯ���� �ṉ̀�Ģ �� '��й�ȣ Ȯ�ΰ� ��й�ȣ ����ġ'�� �����Դϴ�" << endl;
		break;
	case -10:
		cout << "�̸��� ������Ģ �� '����' �����Դϴ�" << endl;
		break;
	case -11:
		cout << "�̸��� ������Ģ �� '�ѱ��� �ƴ� ����' �����Դϴ�" << endl;
		break;
	default:
		break;
	}
}