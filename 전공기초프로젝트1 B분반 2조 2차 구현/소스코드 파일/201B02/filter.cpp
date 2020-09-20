//���⿡ ���� �˻��ϴ� �Լ� �����ϼ���.
//�̸��� filter_grammar_asdf() Ȥ�� filter_meaning_asdf()

#include "filter.h"

int filter_grammar_student_id_length(char* str) {

	int checker_korean = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (((str[i] & 0x80) != 0)) {
			checker_korean++;
		}
	}

	if (strlen(str) - checker_korean / 2 != 9) {						//���� �˻�
		return 0;
	}
	return 1;
}

int filter_grammar_student_id_number(char* str) {
	for (int i = 0; i < strlen(str); i++) {		//���� �˻�
		if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

int filter_meaning_student_id_register(char* str) {
	ifstream readFile;							//�ߺ� �˻�
	readFile.open("account_list.txt");
	if (readFile.is_open()) {
		for (int i = 0; !readFile.eof(); i++) {
			char temp_line[100];		//�޸��� �� �� �� �ִ� 68�� (�й�9 + ���15 + �̸�8 + �����1 + �����ȣ24 + ����10 + �ΰ�1)
			readFile.getline(temp_line, 100);
			if (temp_line[0] != NULL) {
				char* compare = strtok(temp_line, " ");
				//����� �ڸ���
				if (!strcmp(compare, str)) {
					readFile.close();
					return i;				//����Ʈ�� ���� �й� ������ ���� �ѹ� ��ȯ
				}
			}
		}
		readFile.close();
		return -1;					//����Ʈ�� ������ 0��ȯ
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

	if (strlen(str) - checker_korean / 2 < 5 || strlen(str) - checker_korean / 2 > 15) {		//���� �˻�
		return 0;
	}
	return 1;
}

int filter_grammar_password_comb(char* str) {
	bool checker_num = false;						//����+���ĺ� �˻�
	bool checker_char = false;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= '0' && str[i] <= '9')
			checker_num = true;
		else if (str[i] >= 'a' && str[i] <= 'z')
			checker_char = true;
		else
			return 0;
	}
	if (checker_num && checker_char)				//���� �ִ��� �˻�
		return 1;

	return 0;
}

int filter_meaning_password_match(char* str, int line_num) {

	ifstream readFile;							//�ߺ� �˻�
	readFile.open("account_list.txt");
	if (readFile.is_open()) {
		char temp_line[100];		//�޸��� �� �� �� �ִ� 100�� (�й�9 + ���15 + �̸�8 + �����1 + �����ȣ24 + ����10 + �ΰ�1)
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

	if (str.length() - checker_korean / 2 != 9) {						//���� �˻�
		return 0;
	}
	return 1;
}


int filter_grammar_student_id_number(string str) {
	for (int i = 0; i < str.length(); i++) {		//���� �˻�
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

	if (str.length() - checker_korean / 2 < 5 || str.length() - checker_korean / 2 > 15) {		//���� �˻�
		return 0;
	}

	return 1;
}

int filter_grammar_password_comb(string str) {
	bool checker_num = false;						//����+���ĺ� �˻�
	bool checker_char = false;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= '0' && str[i] <= '9')
			checker_num = true;
		else if (str[i] >= 'a' && str[i] <= 'z')
			checker_char = true;
		else
			return 0;
	}
	if (checker_num && checker_char)				//���� �ִ��� �˻�
		return 1;

	return 0;
}

int filter_meaning_student_id_overlap(string str) {
	ifstream inFile;
	string temp = ""; // ���ڿ� �ӽ� ����

	inFile.open("account_list.txt"); // account_list.txt : �������� ���� �ؽ�Ʈ ����
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

	if (str.length() - checker_korean / 2 < 2 || str.length() - checker_korean / 2 > 5) {		//���� �˻�
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

int f_smenu(string num) {	//������ȸ �޴� ����ó��
	if (num == "1") return 1;
	else if (num == "2") return 2;
	else if (num == "3") return 3;
	else if (num == "q") return 4;
	else return 0;
}

int f_num(string s_num) {	//���ǹ�ȣ�� �˻� ����ó��
	if (s_num.size() == 4) {
		if (s_num == "0000") return 2;	//���� (0001~9999)�� �ٸ� �Է°�
		char s_array[5];
		strcpy(s_array, s_num.c_str());
		if (48 <= s_array[0] && s_array[0] <= 57 && 48 <= s_array[1] && s_array[1] <= 57 && 48 <= s_array[2] && s_array[2] <= 57 && 48 <= s_array[3] && s_array[3] <= 57)
			return 0;	//���ǰ� ��ġ�ϴ� �Է°�
		else return 2;
	}
	else {
		if (s_num == "q") return 3;	//������ȸ �޴��� ���ư���
		return 1;	//4byte�� �ƴ� �Է°�
	}
}

int f_name(string s_name) {	//���Ǹ����� �˻� ����ó��
	if (s_name.size() >= 2 && s_name.size() <= 40) return 0;	//����(�ѱ� 2�ڸ�, ����/����/Ư������(Ű����� �Է� ������ ����)�� 1�ڸ��� ����� �� 2�ڸ� �̻�)�� ��ġ�ϴ� �Է°�
	else {	//����ó��
		if (s_name == "q") return 2;	//������ȸ �޴��� ���ư���
		return 1;	//���ǰ� �ٸ� �Է°�
	}
}

int f_all(string back) {
	if (back == "q")
		return 0;
	else return 1;
}