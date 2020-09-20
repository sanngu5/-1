#include"modify.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<Windows.h>
using namespace std;

class Lecture {
private:
	string name;
	string professor;
	string room;
public:
	Lecture() :Lecture("name", "professor", "room") {

	}
	Lecture(const string name, const string professor, const string room) : name(name), professor(professor)
	{
		this->room = room;
	}
	~Lecture() {

	}
	void printName() {
		if (name != "name")
			cout << name;
	}
	void print() {
		if (professor != "professor" && room != "room")
			cout << "(" << professor << "/" << room << ")";
	}
};

void gotoxy(int x, int y);

int table() {
	system("mode con cols=140 lines=60");
	//����� ������ �α��ν� ����ȴٰ� ����
	int total = classnumberi(); //��û�� ���񰳼�
	string* code = classnumbers(); //��û�� �����ȣ��
	Lecture** lec = new Lecture*[24];//�ð�ǥ
	for (int i = 0; i < 24; i++) {
		lec[i] = new Lecture[6];
	}

	ifstream readFile;
	readFile.open("class_list.txt");
	if (readFile.is_open()) {
		for (int i = 0; i < total; i++) {
			while (!readFile.eof()) { //����ã��
				string info;
				getline(readFile, info);
				stringstream ss(info);
				string temp;
				string str[10];
				int index = 0;
				while (ss >> temp)
					str[index++] = temp;
				for (int j = 0; j < total; j++) {
					if (code[j] == str[0]) {
						string name = str[1]; //�����
						if (name.size() > 12 && name != "�߿ܽ�����(����)") {
							name = name.substr(0, 12);
							name += "..";
						}
						string professor = str[2]; //������
						string room = str[3]; //���ǽ�
						int time = 7;

						for (int k = 0; k < atoi(str[6].c_str()); k++) {
							string c[3];
							c[0] = str[time].substr(0, 2); //����
							c[1] = str[time].substr(2, 2); //���۽ð�
							c[2] = str[time].substr(4, 2); //����ð�
							time++;

							int x;
							if (c[0] == "��")x = 0;
							if (c[0] == "ȭ")x = 1;
							if (c[0] == "��")x = 2;
							if (c[0] == "��")x = 3;
							if (c[0] == "��")x = 4;
							if (c[0] == "��")x = 5;

							for (int y = stoi(c[1]); y <= stoi(c[2]); y++) {
								lec[y][x] = Lecture(name, professor, room);
							}
						}
						break;
					}
				}
			}
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                ��                  ȭ                 ��                 ��                 ��                  ��" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
	cout << endl;

	for (int i = 0; i < 24; i++) {
		cout << i;
		for (int j = 0; j < 6; j++) {

		}
		cout << endl;
		cout << endl;
	}

	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 2; k++) {
				if (k == 0) {
					gotoxy((j + 1) * 13 + j * 5, i + i + 4);
					//gotoxy(14 + (j * 19), i + i + 4);
					lec[i][j].printName();
				}
				else {
					gotoxy(10 + (j * 19), i + i + 5);
					lec[i][j].print();
				}
			}
		}
	}

	gotoxy(0, 52);
	string c;
	while (true) {
		cout << "���ư����� q�� �Է��ϼ���: ";
		getline(cin, c);
		if (c == "q")break;
		cout << "�ð�ǥ��ȸ�� ��Ģ �� '�ڷΰ��� ����' �����Դϴ�" << endl;
	}
	system("cls");
	for (int i = 0; i < 24; i++) {
		delete[] lec[i];
	}
	delete[] lec;
	system("mode con cols=140 lines=30");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
