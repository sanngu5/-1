//���� ����¿� �ʿ��� �Լ��� �����ϼ���.
//�Լ� �̸��� read_asdf() Ȥ�� write_asdf()

#include"file.h"
#include"data.h"

int line_num;

int login() {
	while (1) {
		char temp_student_id[100];
		string tempid;
		cout << "�й�: ";
		getline(cin, tempid);
		strcpy_s(temp_student_id, tempid.c_str());
		if (tempid.size()==1&&temp_student_id[0]=='q') {			//qŻ��
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
		cout << "��й�ȣ: ";
		getline(cin, temppw);
		strcpy_s(temp_pw, temppw.c_str());
		if (temppw.size() == 1 && temp_pw[0] == 'q') {					//qŻ��
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

	string total_info = ""; // ��ü ������ ����Ǵ� ��
	string student_id; // �й�
	string password; // ��й�ȣ
	string password_check; // ��й�ȣ Ȯ��
	string name; // �̸�

	bool not_compliant; // �й� �ߺ�����üũ

//	cout << "=====ȸ������=====" << endl << endl;

	// �й����� ������
	do {
		not_compliant = false;

		cout << "�й�: ";
		getline(cin, student_id);

		// q �Է½� ���
		if (student_id == "q") {
			//			cout << "-�ʱ� ����ȭ������ �̵��մϴ�." << endl << endl;
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
	} while (not_compliant); // ���ǿ� �������� ���ϸ� �����
	cout << endl;
	total_info = total_info + student_id + " ";

	// ��й�ȣ���� ������	
	do {
		not_compliant = false;
		cout << "��й�ȣ: ";
		getline(cin, password);

		// q �Է½� ���
		if (password == "q") {
			//			cout << "-�ʱ� ����ȭ������ �̵��մϴ�." << endl << endl;
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
	} while (not_compliant); // ���ǿ� �������� ���ϸ� �����

	do {
		not_compliant = false;
		cout << "��й�ȣ Ȯ��: ";
		getline(cin, password_check);

		// q �Է½� ���
		if (password_check == "q") {
			//			cout << "-�ʱ� ����ȭ������ �̵��մϴ�." << endl << endl;
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
	} while (not_compliant); // ���ǿ� �������� ���ϸ� �����
	cout << endl;
	total_info = total_info + password + " ";

	// �̸����� ������
	do {
		not_compliant = false;
		cout << "�̸�: ";
		getline(cin, name);

		// q �Է½� ���
		if (name == "q") {
			//			cout << "-�ʱ� ����ȭ������ �̵��մϴ�." << endl << endl;
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
	} while (not_compliant); // ���ǿ� �������� ���ϸ� �����
	cout << endl;
	total_info = total_info + name + " ";

	// ���񰹼�, �����ڵ� (default) ������
	total_info = total_info + "0";

	// �����Է� ������
	outFile.open("account_list.txt", ios::app);
	outFile << total_info << endl;
	outFile.close();
	cout << "���Կ� �����߽��ϴ�" << endl;
	return true;
}