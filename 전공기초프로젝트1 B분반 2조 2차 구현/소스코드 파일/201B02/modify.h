#include "file.h"
#include <iostream>
#include <fstream>//���� ó��
#include <string>//string ó��
#include <algorithm>//sort�Լ���
#include <vector>//����
using namespace std;
enum limit_numbers {
	inplnth = 4,         //�����ȣ ����
	claslenth = 6,       //��û������ �ִ� ���� ��
	snlenth = 9,         //�й� ����
	pwmin = 5,           //��й�ȣ �ּұ���
	pwmax = 15,          //��й�ȣ �ִ����
	nmmin = 4,           //�̸� �ּ�byte
	nmmax = 10,          //�̸� �ִ�byte
	cltlenth = 4,        //�̼����� ����
	cnmmin = 2,          //�����̸� �ּұ���
	cnmmax = 40          //�����̸� �ִ����
};
struct classinfo {//���� ����
	int classnum = 0;//�����ȣ
	string classname = "";//�����̸�
	string professor = "";//��米��
	string classroom = "";//���ǽǸ�
	string classtype = "";//�̼�����
	int classscore = 0;//����
	int timenum = 0;//���ǽð� ����
	string timedate[2] = { "" };//����
	int timedurat[2][2] = { 0 };//�ð�
	int classdivision = 0;//�й�
};
struct student {//�л� ����
	int studentnum;//�й�
	string studentpw;//��й�ȣ
	string studentname;//�̸�
	int classlistnum = 0;//��û�� ���� ����
	classinfo classlist[claslenth];//�����
};
struct vecarr {//���� �迭
	int num;
	int cnt;
};

void modify();
int table(); //�ð�ǥ �߰�
void classout(classinfo *clis, int st, int ed, int filt);//���������� st~ed���� ���(flit�� ���Ͱ�� ����)
string designlut(int prt, int ln, char fil);//prt ���� ln������ ���� ����(���ڸ��� fil�� ä��)
string cltout(classinfo ipt);//���ǽð� ���
void classlistchange(int chn);//�����ȣ �ߺ� �˻� �� �ߺ��� �������� �ߺ��ƴҽ� �����߰�
bool sortfind(classinfo frt, classinfo bkc, int k, int l);//��ġ�� �ð� �˻�
void stateout(int swt);//������ȣ, ���λ���
bool filecheck();//���α׷� �� ó�� ���� �� ���� �˻� �κ�
int classfilecheck();//class_list.txt ���� �˻�
bool accountfilecheck();//account_list.txt ���� �˻�
void accountfilesave();//account_list.txt ���� ����
string* classnumbers();//�� ��ȯ
string logname();//�� ��ȯ
int classnumberi();//�� ��ȯ
void registersuccess();//account_list.txt �ٽ� �ҷ�����(ȸ������ �Ϸ� ����)
int divisioncheck(int many);//�й� ��ħ �˻�
int finalcheck(int wh);//���� ���� �˻�
string timecheck(classinfo frt, classinfo bkc);

extern classinfo class_all[100];//��ü ����
extern int class_all_num;//��ü ���� ����
extern student account_all[100];//��ü �л�
extern int account_all_num;//��ü �л� �ο���
extern student logstudent;//�α��ε� �л�
extern classinfo nul;//�ʱ�ȭ�� ����
extern int line_num;