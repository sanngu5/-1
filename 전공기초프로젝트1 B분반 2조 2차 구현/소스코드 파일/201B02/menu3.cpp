#include "menu3.h"

void menu3() {
	string num;
	int e_code;

	while (1) {
		//system("cls");
		while (1) {
			cout << "[�޴�3]" << endl;
			cout << "1. �����ȣ�� ��ȸ" << endl << "2. ��������� ��ȸ" << endl << "3. ��ü��ȸ" << endl << "�޴��� �����ϼ���: ";
			getline(cin, num);
			e_code = f_smenu(num);
			if (e_code == 0) {
				cout << "�޴�3�� ��Ģ �� '�޴����� ����' �����Դϴ�" << endl; //1,2,3,q�� ������ ����ó��
			}
			else {
				if (e_code == 1) search_num();	//���Ǹ����� �˻�
				else if (e_code == 2) search_name();	//���ǹ�ȣ�� �˻�
				else if (e_code == 3) search_all();	//��ü����
				else if (e_code == 4) {
					//system("cls");
					return;	//���θ޴���
				}
				break;
			}
		}
	}
}