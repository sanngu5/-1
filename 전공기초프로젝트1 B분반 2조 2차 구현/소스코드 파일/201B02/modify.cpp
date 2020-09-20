#include "modify.h"

classinfo class_all[100];//��ü ����
int class_all_num = 0;//��ü ���� ����
student account_all[100];//��ü �л�
int account_all_num = 0;//��ü �л� �ο���
student logstudent;//�α��ε� �л�
classinfo nul;//�ʱ�ȭ�� ����

void modify()
{
	int i, chksize, cksh;
	char chk[5];
	string inp;
	if (line_num != -1) {
		logstudent = account_all[line_num];
		while (true) {
			cout << "��û ���� ����" << endl;
			cout << "�����ȣ / ������� / ��米�� / �̼����� / ���� / ���ǿ���&�ð�" << endl;
			classout(logstudent.classlist, 0, logstudent.classlistnum, 0);//���� ��û�� ���� ���� ���
			cout << "�����ȣ: ";
			getline(cin, inp);
			chksize = inp.size();
			for (i = 0; i < chksize; ++i) {
				if ((inp.at(i) & 0x80) != 0) {//�ѱ�(CP949) ����
					chksize = -1;
					break;
				}
			}
			if (chksize == -1)stateout(1);
			else if (chksize == inplnth) {
				strcpy_s(chk, inp.c_str());
				bool chkps = true;
				for (i = 0; i < chksize; ++i) {
					if (chk[i] < '0' || chk[i] > '9') {
						chkps = false;
						break;
					}
				}
				if (chkps) {
					if (atoi(chk) == 0)stateout(4);//�����ȣ 0000����
					else classlistchange(atoi(chk));//���� ��û ����
				}
				else stateout(1);//���ڸ��� �ٸ��� �Է�
			}
			else {
				if (chksize == 1) {
					strcpy_s(chk, inp.c_str());
					if (chk[0] == 'q')break;//�޴�2 ���ư���
				}
				if (chksize > inplnth)stateout(2);//�Է� 4���� �ʰ�
				if (chksize < inplnth)stateout(3);//�Է� 4���� �̸�
			}
		}
		account_all[line_num] = logstudent;
		accountfilesave();
	}
}
void classout(classinfo *clis, int st, int ed, int filt)
{
	int i;
	classinfo clh;
	switch (filt) {
	case 0:
		for (i = st; i < ed; ++i) {
			clh = clis[i];
			cout << designlut(clh.classnum, inplnth, '0') << " / " << clh.classname << " / " << clh.professor << " / ";
			cout << clh.classtype << " / " << clh.classscore << " / " << cltout(clh) << endl;
		}
		break;
	default:
		break;
	}
}
string designlut(int prt, int ln, char fil)
{
	string rt = to_string(prt);
	int k, cnt = rt.size();
	if (cnt < ln) {
		for (k = 0; k < ln - cnt; ++k) {
			rt = fil + rt;
		}
	}
	return rt;
}
string cltout(classinfo ipt)
{
	string frt;
	frt = ipt.timedate[0] + "���� " + designlut(((ipt.timedurat[0][0] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[0][0] - 1) % 2) * 30, 2, '0');
	frt += " ~ " + designlut(((ipt.timedurat[0][1] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[0][1] - 1) % 2) * 30, 2, '0');
	if (ipt.timenum == 2) {
		frt += " , " + ipt.timedate[1] + "���� " + designlut(((ipt.timedurat[1][0] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[1][0] - 1) % 2) * 30, 2, '0');
		frt += " ~ " + designlut(((ipt.timedurat[1][1] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[1][1] - 1) % 2) * 30, 2, '0');
	}
	return frt;
}
void classlistchange(int chn)
{
	ifstream clasin("class_list.txt");
	int bcel = 5, i, j, k, l, cnt = logstudent.classlistnum;
	string tokh;
	classinfo frt, bkc;
	for (i = 0; i < cnt; ++i) {
		if (logstudent.classlist[i].classnum == chn) {//�̹� ��û�� �Ͱ� ��ġ�ϴ� �����ȣ���� �˻�
			bcel = -2;
			//�����û öȸ
			for (j = i; j < cnt - 1; ++j) logstudent.classlist[j] = logstudent.classlist[j + 1];
			logstudent.classlist[cnt - 1] = nul;
			logstudent.classlistnum--;
			break;
		}
	}
	if (bcel == 5 && cnt == claslenth) bcel = 6;//�ִ� ��û ���� ���� �� ����
	else if (bcel == 5) {//�����û
		for (i = 0; i < class_all_num; ++i) {
			if (class_all[i].classnum == chn) {//class_all ���� �������� �ҷ�����
				logstudent.classlist[logstudent.classlistnum] = class_all[i];
				logstudent.classlistnum++;
				bcel = -1;
				break;
			}
		}
		if (bcel == -1) {//�й� ��ħ Ȯ��(���� �������� �߰��� �Ͱ� ��)
			cnt = logstudent.classlistnum;
			k = logstudent.classlist[cnt - 1].classdivision;
			if (k != 0) {
				for (j = 0; j < cnt - 1 && bcel == -1; ++j) {
					if (logstudent.classlist[j].classdivision == k) {
						bcel = 8;
						break;
					}
				}
			}
			if (bcel == -1) {//���� �ð� ��ġ���� Ȯ��(���� �������� �߰��� �Ͱ� ��)
				for (j = 0; j < cnt - 1 && bcel == -1; ++j) {
					frt = logstudent.classlist[j];
					bkc = logstudent.classlist[cnt - 1];
					tokh = timecheck(frt, bkc);//�ð��� ��ġ��(���� ���X)
					if (tokh != "-1") {
						bcel = 7;
						break;
					}
				}
				if (bcel == 7) {//�ð��� ��ģ ��� �ѹ�
					logstudent.classlist[cnt - 1] = nul;
					logstudent.classlistnum--;
				}
			}
			if (bcel == 8) {//�й��� ��ģ ��� �ѹ�
				logstudent.classlist[cnt - 1] = nul;
				logstudent.classlistnum--;
			}
		}
	}
	stateout(bcel);
}
bool sortfind(classinfo frt, classinfo bkc, int k, int l)
{
	bool rt = false;
	int srt[4], shk[4], kl;
	if (frt.timedurat[k][0] < bkc.timedurat[l][0]) {
		srt[0] = frt.timedurat[k][0];
		srt[1] = frt.timedurat[k][1];
		srt[2] = bkc.timedurat[l][0];
		srt[3] = bkc.timedurat[l][1];
	}
	else {
		srt[0] = bkc.timedurat[l][0];
		srt[1] = bkc.timedurat[l][1];
		srt[2] = frt.timedurat[k][0];
		srt[3] = frt.timedurat[k][1];
	}
	copy(srt, srt + 4, shk);
	sort(srt, srt + 4);
	for (kl = 0; kl < 4; ++kl) {
		if (srt[kl] != shk[kl]) {
			rt = true;
			break;
		}
	}
	return rt;
}
void stateout(int swt)
{
	switch (swt) {
	case 1://�Է� ���� ����(���� �ƴ�)
		cout << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl;
		break;
	case 2://�Է� ���� �ʰ�
		cout << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl;
		break;
	case 3://�Է� ���� �̴�
		cout << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl;
		break;
	case 4://�����ȣ 0000
		cout << "�����ȣ�� ������Ģ �� '���� ����' �����Դϴ�" << endl;
		break;
	case 5://���� �����ȣ �Է�
		cout << "�����ȣ�� �ṉ̀�Ģ �� '�������� ����' �����Դϴ�" << endl;
		break;
	case 6://�ִ� ��û ������ ���� �� �ʰ�
		cout << "�����ȣ�� �ṉ̀�Ģ �� '�ִ� ���� ����' �����Դϴ�" << endl;
		break;
	case 7://���� �ð��� ��ġ�� ���
		cout << "�����ȣ�� �ṉ̀�Ģ �� '���ǽð� �ߺ�' �����Դϴ�" << endl;
		break;
	case 8://�й��� ��ġ�� ���
		cout << "�����ȣ�� �ṉ̀�Ģ �� '�й� �ߺ�' �����Դϴ�" << endl;
		break;
	case -1://���� ��û �Ϸ�
		cout << "�����û�� ���������� �Ϸ�Ǿ����ϴ�" << endl;
		break;
	case -2://���� ��û öȸ
		cout << "�����û öȸ�� ���������� �Ϸ�Ǿ����ϴ�" << endl;
		break;
	default:
		cout << "�� �� ���� ������ �߻��Ͽ����ϴ�" << endl;
		break;
	}
	cout << endl;
}
bool filecheck()
{
	bool check = false;
	if (classfilecheck() == 1)check = accountfilecheck();
	return check;
}
int classfilecheck()
{
	ifstream clasin("class_list.txt");
	int bcel = 1, i, j, k, stltok;
	char* tok;
	string clin, sls, tokh;
	string datchk[6] = { "��","ȭ","��","��","��","��" }, cltchk[8] = { "����","����","����","����","�ⱳ","�ɱ�","����","�ϼ�" };
	//datchk-���� Ȯ��, cltchk-�̼����� Ȯ��
	classinfo iprd;
	vecarr chkarh;
	vector<vecarr> chkarr;
	if (clasin.is_open()) {//class_list.txt ���� �ҷ�����
		i = 0;
		while (!clasin.eof() && bcel == 1) {
			i++;
			getline(clasin, clin);
			if (clin.size() != 0) {//���͸� �ִ°�� �׳� ��ŵ
				char* cln = new char[clin.size() + 1];
				copy(clin.begin(), clin.end(), cln);
				cln[clin.size()] = '\0';
				tok = strtok(cln, " ");
				if (tok == NULL)bcel = 0;
				else {
					j = 0;
					iprd.classdivision = -1;
					while (tok != NULL) {
						switch (j) {
						case 0://�����ȣ
							if (strlen(tok) == inplnth) {
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] < '0'||tok[k] > '9') {//���ھƴ�
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									if (atoi(tok) != 0)iprd.classnum = atoi(tok);//�����ȣ 0000����
									else bcel = 0;
								}
							}
							else bcel = 0;
							break;
						case 1://�����̸�
							if (strlen(tok) <= cnmmax && strlen(tok) >= cnmmin)iprd.classname = tok;
							else bcel = 0;
							break;
						case 2://��米���̸�
							stltok = strlen(tok);
							if (stltok >= nmmin && stltok <= nmmax && stltok % 2 == 0) {//�ѱ۸����� �ϸ� ¦��byte
								for (k = 0; k < stltok; ++k) {
									//�ѱ�üũ
									if (tok[k] >= 0 && tok[k] <= 127) {//ASCII �ڵ��� ���(����Ư ó��, �����δ� �� ������)
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.professor = tok;
							}
							else bcel = 0;
							break;
						case 3://���ǽǸ�
							iprd.classroom = tok;
							break;
						case 4://�̼�����
							if (strlen(tok) == cltlenth) {
								iprd.classtype = tok;
								bcel = 0;
								for (k = 0; k < 8; ++k) {
									if (iprd.classtype == cltchk[k]) {
										bcel = 1;
										break;
									}
								}
							}
							else bcel = 0;
							break;
						case 5://����
							stltok = strlen(tok);
							for (k = 0; k < stltok; ++k){
								if (tok[k] < '0' || tok[k] > '9') {
									bcel = 0;
									break;
								}
							}
							if (bcel != 0)iprd.classscore = atoi(tok);
							break;
						case 6://���ǽð� ����
							switch (atoi(tok)) {
							case 1:
							case 2:
								iprd.timenum = atoi(tok);
								break;
							default:
								bcel = 0;
								break;
							}
							break;
						case 7://���ǽð�1
						case 8://���ǽð�2
							if (j - iprd.timenum == 7) {//���ǽð� ���� 1�϶� - �й� ��ȣ �Է¹��� ����
								stltok = strlen(tok);
								for (k = 0; k < stltok; ++k) {
									if (tok[k]<'0' || tok[k]>'9') {//���� �ƴѰ� ������
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									iprd.classdivision = atoi(tok);
									if (iprd.classdivision < 0)bcel = 0;//�й� ���� ����
									else {
										bcel = 0;
										for (k = 0; k < chkarr.size(); ++k) {
											if (chkarr[k].num == iprd.classdivision) {//�й� ��ȣ ��ĥ ��
												chkarh.num = iprd.classdivision;
												chkarh.cnt = chkarr[k].cnt + 1;
												chkarr.insert(chkarr.begin() + k, chkarh);
												chkarr.erase(chkarr.begin() + k + 1);
												bcel = 1;
												break;
											}
										}
										if (bcel == 0) {//�й� ��ȣ �Ȱ�ġ��
											bcel = 1;
											chkarh.num = iprd.classdivision;
											chkarh.cnt = 1;
											chkarr.push_back(chkarh);
										}
									}
								}
							}
							else {//ù��° ���ǽð��̰ų� ���ǽð� ������ 2�϶� �ι�° ���ǽð�
								if (strlen(tok) == 6) {
									tokh = tok;
									sls = tokh.substr(0, 2);
									iprd.timedate[j - 7] = sls;
									sls = tokh.substr(2, 2);
									iprd.timedurat[j - 7][0] = atoi(sls.c_str());
									sls = tokh.substr(4, 2);
									iprd.timedurat[j - 7][1] = atoi(sls.c_str());
									bcel = 0;
									for (k = 0; k < 6; ++k) {//���� �˻�
										if (iprd.timedate[j - 7] == datchk[k]) {
											bcel = 2;
											break;
										}
									}
									if (bcel == 2) {
										bcel = 0;
										if (iprd.timedurat[j - 7][0] >= 0 && iprd.timedurat[j - 7][0] <= 24)bcel = 3;//���ǽð� �˻�
										if (bcel == 3) {
											bcel = 0;
											if (iprd.timedurat[j - 7][1] >= 0 && iprd.timedurat[j - 7][1] <= 24)bcel = 1;//���ǽð� �˻�
										}
									}
								}
								else bcel = 0;
							}
							break;
						case 9:
							if (j - iprd.timenum == 7) {//���ǽð� ���� 2�϶� - �й� ��ȣ �Է¹��� ����
								stltok = strlen(tok);
								for (k = 0; k < stltok; ++k) {
									if (tok[k]<'0' || tok[k]>'9') {//���� �ƴѰ� ������
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									iprd.classdivision = atoi(tok);
									if (iprd.classdivision < 0)bcel = 0;//�й� ���� ����
									else {
										bcel = 0;
										for (k = 0; k < chkarr.size(); ++k) {
											if (chkarr[k].num == iprd.classdivision) {//�й� ��ȣ ��ĥ ��
												chkarh.num = iprd.classdivision;
												chkarh.cnt = chkarr[k].cnt + 1;
												chkarr.insert(chkarr.begin() + k, chkarh);
												chkarr.erase(chkarr.begin() + k + 1);
												bcel = 1;
												break;
											}
										}
										if (bcel == 0) {//�й� ��ȣ �Ȱ�ġ��
											bcel = 1;
											chkarh.num = iprd.classdivision;
											chkarh.cnt = 1;
											chkarr.push_back(chkarh);
										}
									}
								}
							}
							else bcel = 0;
							break;
						default:
							bcel = 0;
							break;
						}
						if (bcel == 0)break;//�д� �� ���� �߻�
						tok = strtok(NULL, " ");
						j++;
					}
					if (bcel == 1) {//�дµ� ������ ������
						class_all[class_all_num] = iprd;
						class_all_num++;
					}
				}
				delete cln;//�޸� ����
			}
		}
		if (bcel != 0) {
			for (i = 0; i < chkarr.size(); ++i) {
				if (chkarr[i].num != 0 && chkarr[i].cnt == 1) {//�й��ε� �йݽ��� ���°��
					bcel = 0;
					break;
				}
			}
			if (bcel != 0) {
				bcel = divisioncheck(class_all_num);
				if (bcel != 0) {//�й� ��ħ ���� ���°��
					bcel = finalcheck(1);//�߰� ���� �˻�(finalcheck �Լ��� ����)
					if (bcel != 0) {
						for (i = 0; i < class_all_num; ++i) {
							if (class_all[i].classdivision == -1) {//���� �������Ŀ� �����Ȱ� �ִ� ���
								bcel = 0;
								break;
							}
						}
					}
				}
			}
		}
		vector<vecarr>().swap(chkarr);//�޸� ����
/*		if (bcel == 1)cout << "class_list.txt ���� ���� ����" << endl;*/
		if (bcel == 0)cout << "������ ������ ���Ŀ� ���� �ʽ��ϴ�" << endl;
	}
	else {
		cout << "���� ���� �����Դϴ�" << endl;
		bcel = 0;
	}
	return bcel;
}
bool accountfilecheck()
{
	ifstream accin("account_list.txt");
	int bcel = 1, i, j, k, stltok, intchk, mechk;
	bool chk = false;
	char* tok;
	string clin, sls, tokh;
	student iprd;
	if (accin.is_open()) {//account_list.txt ���� �ҷ�����
		i = 0;
		while (!accin.eof() && bcel == 1) {
			i++;
			getline(accin, clin);
			if (clin.size() != 0) {//���͸� �ִ°�� �׳� ��ŵ
				char* cln = new char[clin.size() + 1];
				copy(clin.begin(), clin.end(), cln);
				cln[clin.size()] = '\0';
				tok = strtok(cln, " ");
				if (tok == NULL)bcel = 0;
				else {
					j = 0;
					iprd.classlistnum = -1;
					while (tok != NULL) {
						switch (j) {
						case 0://�й�
							if (strlen(tok) == snlenth) {
								intchk = 0;
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//�й� ����
									else {//�ƴ�
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentnum = atoi(tok);
							}
							else bcel = 0;
							break;
						case 1://��й�ȣ
							stltok = strlen(tok);
							if (stltok >= pwmin && stltok <= pwmax) {
								intchk = mechk = 0;
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] >= 'a'&&tok[k] <= 'z')mechk++;//��й�ȣ ���� �ҹ���
									else if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//��й�ȣ ����
									else {//�� �� �ƴ�
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentpw = tok;
							}
							else bcel = 0;
							break;
						case 2://�̸�
							stltok = strlen(tok);
							if (stltok >= nmmin && stltok <= nmmax && stltok % 2 == 0) {//�ѱ۸����� �ϸ� ¦��byte
								for (k = 0; k < stltok; ++k) {
									//�ѱ�üũ
									if (tok[k] >= 0 && tok[k] <= 127) {//ASCII �ڵ��� ���(����Ư ó��, �����δ� �� ������)
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentname = tok;
							}
							else bcel = 0;
							break;
						case 3://��û�� ���� ��
							if (strlen(tok) == 1) {
								if (tok[0] >= '0'&&tok[0] <= '9') {
									if (atoi(tok) <= claslenth)iprd.classlistnum = atoi(tok);
									else bcel = 0;
								}
								else bcel = 0;
							}
							else bcel = 0;
							break;
						case 4://����1
						case 5://����2
						case 6://����3
						case 7://����4
						case 8://����5
						case 9://����6
							if (j - iprd.classlistnum > 3)bcel = 0;//���� ������ �ȸ���
							else {
								if (strlen(tok) == inplnth) {
									intchk = 0;
									for (k = 0; k < strlen(tok); ++k) {
										if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//�����ȣ ����
										else {//�ƴ�
											bcel = 0;
											break;
										}
									}
									if (bcel != 0) {
										bcel = 0;
										for (k = 0; k < class_all_num; ++k) {//��û�� ���� ���� ��������
											if (atoi(tok) == class_all[k].classnum) {
												iprd.classlist[j - 4] = class_all[k];
												bcel = 1;
												break;
											}
										}
									}
								}
								else bcel = 0;
							}
							break;
						default:
							bcel = 0;
							break;
						}
						if (bcel == 0)break;//�д� �� ���� �߻�
						tok = strtok(NULL, " ");
						if (tok == NULL && j >= 3 && (j - 3) < iprd.classlistnum)bcel = 0;//���ǽ�û����>���Ǹ�� ����
						j++;
					}
					if (iprd.classlistnum == -1)bcel = 0;
					if (bcel == 1) {//�дµ� ������ ������
						account_all[account_all_num] = iprd;
						account_all_num++;
					}
				}
				delete cln;//�޸� ����
			}
		}
		if (bcel != 0)bcel = finalcheck(2);//���� �˻�
/*		if (bcel == 1)cout << "account_list.txt ���� ���� ����" << endl;*/
		if (bcel == 0) {
			cout << "������ ������ ���Ŀ� ���� �ʽ��ϴ�" << endl;
			return false;
		}
	}
	else {
		cout << "���� ���� �����Դϴ�" << endl;
		return false;
	}
	return true;
}
void accountfilesave()
{
	int i, j;
	student ach;
	fstream accout;
	accout.open("account_list.txt", ios::out);
	for (i = 0; i < account_all_num; ++i) {//��� �л� ���� ����
		ach = account_all[i];
		accout << designlut(ach.studentnum, snlenth, '0') << " " << ach.studentpw << " " << ach.studentname << " " << ach.classlistnum;
		for (j = 0; j < ach.classlistnum; ++j) {
			accout << " " << designlut(ach.classlist[j].classnum, inplnth, '0');
		}
		accout << endl;
	}
	accout.close();
}
string* classnumbers()
{
	int i;
	string *rt = new string[6];
	for (i = 0; i < account_all[line_num].classlistnum; ++i) {
		rt[i] = designlut(account_all[line_num].classlist[i].classnum, inplnth, '0');
	}
	return rt;
}
string logname()
{
	return account_all[line_num].studentname;
}
int classnumberi()
{
	return account_all[line_num].classlistnum;
}
void registersuccess()
{
	account_all_num = 0;
	accountfilecheck();
}
int divisioncheck(int many)
{
	int i, j, k, l, bcel = 1, cdnum;
	bool* a = new bool[many];
	string th;
	vector<int> cp;
	for (i = 0; i < many; ++i)a[i] = false;
	for (i = 0; i < class_all_num && bcel == 1; ++i) {
		cdnum = class_all[i].classdivision;
		if (cdnum != 0 && a[i] == false) {//�йݹ�ȣ�� �����ϴ� ���
			a[i] = true;
			vector<int>().swap(cp);//�޸� ����(�ʱ�ȭ)
			for (j = i; j < class_all_num; ++j) {
				if (class_all[j].classdivision == cdnum) {
					a[j] = true;
					cp.push_back(j);
				}
			}
			for (j = 0; j < cp.size() - 1 && bcel == 1; ++j) {
				for (k = j + 1; k < cp.size() && bcel == 1; ++k) {
					if (class_all[cp[j]].professor == class_all[cp[k]].professor) {//���� �������̰�
						th = timecheck(class_all[cp[j]], class_all[cp[k]]);//�ð��� ��ġ��(���� ���X)
						if (th != "-1") {
							bcel = 0;
							break;
						}
					}
				}
			}
		}
	}
	delete a;//�޸� ����
	vector<int>().swap(cp);//�޸� ����
	return bcel;
}
int finalcheck(int wh)
{
	int i, j, k, bcel = 1;
	string th;
	student aci;
	if (wh == 1) {//class_list.txt ���� �˻�-�����ȣ �ߺ�, ����� �ߺ�, ���� �� �ð� �ߺ�
		for (i = 0; i < class_all_num - 1 && bcel == 1; ++i) {
			for (j = i + 1; j < class_all_num && bcel == 1; ++j) {
				if (class_all[i].classnum == class_all[j].classnum) {//���� �����ȣ
					bcel = 0;
					break;
				}
				if (class_all[i].classname == class_all[j].classname) {//���� �����
					bcel = 0;
					break;
				}
				if (class_all[i].classroom == class_all[j].classroom) {//���� �����̰�
					th = timecheck(class_all[i], class_all[j]);//�ð��� ��ġ��
					if (th != "-1") {
						bcel = 0;
						break;
					}
				}
			}
		}
	}
	else if (wh == 2) {//account_list.txt ���� �˻�-�����ȣ �ߺ�
		for (i = 0; i < account_all_num; ++i) {
			aci = account_all[i];
			for (j = 0; j < aci.classlistnum - 1; ++j) {
				for (k = j + 1; k < aci.classlistnum; ++k) {
					if (aci.classlist[j].classnum == aci.classlist[k].classnum) {//���� �����ȣ
						bcel = 0;
						break;
					}
				}
			}
		}
	}
	return bcel;
}
string timecheck(classinfo frt, classinfo bkc)
{
	int k, l;
	string rt = "-1";
	for (k = 0; k < frt.timenum && rt == "-1"; ++k) {
		for (l = 0; l < bkc.timenum && rt == "-1"; ++l) {
			if (frt.timedate[k] == bkc.timedate[l]) {//���� ����
				if (sortfind(frt, bkc, k, l)) {//�ð��� ��ġ��
					rt = frt.classname + " ����� " + bkc.classname + " ����";
					break;
				}
			}
		}
	}
	return rt;
}