#include "modify.h"

classinfo class_all[100];//전체 과목
int class_all_num = 0;//전체 과목 개수
student account_all[100];//전체 학생
int account_all_num = 0;//전체 학생 인원수
student logstudent;//로그인된 학생
classinfo nul;//초기화용 변수

void modify()
{
	int i, chksize, cksh;
	char chk[5];
	string inp;
	if (line_num != -1) {
		logstudent = account_all[line_num];
		while (true) {
			cout << "신청 과목 정보" << endl;
			cout << "과목번호 / 교과목명 / 담당교수 / 이수구분 / 학점 / 강의요일&시간" << endl;
			classout(logstudent.classlist, 0, logstudent.classlistnum, 0);//현재 신청된 강의 전부 출력
			cout << "과목번호: ";
			getline(cin, inp);
			chksize = inp.size();
			for (i = 0; i < chksize; ++i) {
				if ((inp.at(i) & 0x80) != 0) {//한글(CP949) 제외
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
					if (atoi(chk) == 0)stateout(4);//과목번호 0000제외
					else classlistchange(atoi(chk));//과목 신청 진행
				}
				else stateout(1);//숫자말고 다른거 입력
			}
			else {
				if (chksize == 1) {
					strcpy_s(chk, inp.c_str());
					if (chk[0] == 'q')break;//메뉴2 돌아가기
				}
				if (chksize > inplnth)stateout(2);//입력 4글자 초과
				if (chksize < inplnth)stateout(3);//입력 4글자 미만
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
	frt = ipt.timedate[0] + "요일 " + designlut(((ipt.timedurat[0][0] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[0][0] - 1) % 2) * 30, 2, '0');
	frt += " ~ " + designlut(((ipt.timedurat[0][1] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[0][1] - 1) % 2) * 30, 2, '0');
	if (ipt.timenum == 2) {
		frt += " , " + ipt.timedate[1] + "요일 " + designlut(((ipt.timedurat[1][0] - 1) / 2) + 9, 2, '0') + ":" + designlut(((ipt.timedurat[1][0] - 1) % 2) * 30, 2, '0');
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
		if (logstudent.classlist[i].classnum == chn) {//이미 신청한 것과 일치하는 과목번호인지 검사
			bcel = -2;
			//과목신청 철회
			for (j = i; j < cnt - 1; ++j) logstudent.classlist[j] = logstudent.classlist[j + 1];
			logstudent.classlist[cnt - 1] = nul;
			logstudent.classlistnum--;
			break;
		}
	}
	if (bcel == 5 && cnt == claslenth) bcel = 6;//최대 신청 가능 과목 수 도달
	else if (bcel == 5) {//과목신청
		for (i = 0; i < class_all_num; ++i) {
			if (class_all[i].classnum == chn) {//class_all 에서 강의정보 불러오기
				logstudent.classlist[logstudent.classlistnum] = class_all[i];
				logstudent.classlistnum++;
				bcel = -1;
				break;
			}
		}
		if (bcel == -1) {//분반 겹침 확인(제일 마지막에 추가한 것과 비교)
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
			if (bcel == -1) {//과목 시간 겹치는지 확인(제일 마지막에 추가한 것과 비교)
				for (j = 0; j < cnt - 1 && bcel == -1; ++j) {
					frt = logstudent.classlist[j];
					bkc = logstudent.classlist[cnt - 1];
					tokh = timecheck(frt, bkc);//시간이 겹치면(교실 상관X)
					if (tokh != "-1") {
						bcel = 7;
						break;
					}
				}
				if (bcel == 7) {//시간이 겹친 경우 롤백
					logstudent.classlist[cnt - 1] = nul;
					logstudent.classlistnum--;
				}
			}
			if (bcel == 8) {//분반이 겹친 경우 롤백
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
	case 1://입력 내용 오류(숫자 아님)
		cout << "과목번호의 문법규칙 중 '범위 조건' 오류입니다" << endl;
		break;
	case 2://입력 길이 초과
		cout << "과목번호의 문법규칙 중 '길이 조건' 오류입니다" << endl;
		break;
	case 3://입력 길이 미달
		cout << "과목번호의 문법규칙 중 '길이 조건' 오류입니다" << endl;
		break;
	case 4://과목번호 0000
		cout << "과목번호의 문법규칙 중 '범위 조건' 오류입니다" << endl;
		break;
	case 5://없는 과목번호 입력
		cout << "과목번호의 의미규칙 중 '강의존재 조건' 오류입니다" << endl;
		break;
	case 6://최대 신청 가능한 과목 수 초과
		cout << "과목번호의 의미규칙 중 '최대 강의 개수' 오류입니다" << endl;
		break;
	case 7://강의 시간이 겹치는 경우
		cout << "과목번호의 의미규칙 중 '강의시간 중복' 오류입니다" << endl;
		break;
	case 8://분반이 겹치는 경우
		cout << "과목번호의 의미규칙 중 '분반 중복' 오류입니다" << endl;
		break;
	case -1://과목 신청 완료
		cout << "과목신청이 정상적으로 완료되었습니다" << endl;
		break;
	case -2://과목 신청 철회
		cout << "과목신청 철회가 정상적으로 완료되었습니다" << endl;
		break;
	default:
		cout << "알 수 없는 오류가 발생하였습니다" << endl;
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
	string datchk[6] = { "월","화","수","목","금","토" }, cltchk[8] = { "전필","전선","지필","지교","기교","심교","교직","일선" };
	//datchk-요일 확인, cltchk-이수구분 확인
	classinfo iprd;
	vecarr chkarh;
	vector<vecarr> chkarr;
	if (clasin.is_open()) {//class_list.txt 파일 불러오기
		i = 0;
		while (!clasin.eof() && bcel == 1) {
			i++;
			getline(clasin, clin);
			if (clin.size() != 0) {//엔터만 있는경우 그냥 스킵
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
						case 0://과목번호
							if (strlen(tok) == inplnth) {
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] < '0'||tok[k] > '9') {//숫자아님
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									if (atoi(tok) != 0)iprd.classnum = atoi(tok);//과목번호 0000제외
									else bcel = 0;
								}
							}
							else bcel = 0;
							break;
						case 1://과목이름
							if (strlen(tok) <= cnmmax && strlen(tok) >= cnmmin)iprd.classname = tok;
							else bcel = 0;
							break;
						case 2://담당교수이름
							stltok = strlen(tok);
							if (stltok >= nmmin && stltok <= nmmax && stltok % 2 == 0) {//한글만으로 하면 짝수byte
								for (k = 0; k < stltok; ++k) {
									//한글체크
									if (tok[k] >= 0 && tok[k] <= 127) {//ASCII 코드일 경우(영숫특 처리, 실제로는 더 복잡함)
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.professor = tok;
							}
							else bcel = 0;
							break;
						case 3://강의실명
							iprd.classroom = tok;
							break;
						case 4://이수구분
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
						case 5://학점
							stltok = strlen(tok);
							for (k = 0; k < stltok; ++k){
								if (tok[k] < '0' || tok[k] > '9') {
									bcel = 0;
									break;
								}
							}
							if (bcel != 0)iprd.classscore = atoi(tok);
							break;
						case 6://강의시간 개수
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
						case 7://강의시간1
						case 8://강의시간2
							if (j - iprd.timenum == 7) {//강의시간 개수 1일때 - 분반 번호 입력받을 차례
								stltok = strlen(tok);
								for (k = 0; k < stltok; ++k) {
									if (tok[k]<'0' || tok[k]>'9') {//숫자 아닌게 있으면
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									iprd.classdivision = atoi(tok);
									if (iprd.classdivision < 0)bcel = 0;//분반 음수 없음
									else {
										bcel = 0;
										for (k = 0; k < chkarr.size(); ++k) {
											if (chkarr[k].num == iprd.classdivision) {//분반 번호 겹칠 때
												chkarh.num = iprd.classdivision;
												chkarh.cnt = chkarr[k].cnt + 1;
												chkarr.insert(chkarr.begin() + k, chkarh);
												chkarr.erase(chkarr.begin() + k + 1);
												bcel = 1;
												break;
											}
										}
										if (bcel == 0) {//분반 번호 안겹치면
											bcel = 1;
											chkarh.num = iprd.classdivision;
											chkarh.cnt = 1;
											chkarr.push_back(chkarh);
										}
									}
								}
							}
							else {//첫번째 강의시간이거나 강의시간 개수가 2일때 두번째 강의시간
								if (strlen(tok) == 6) {
									tokh = tok;
									sls = tokh.substr(0, 2);
									iprd.timedate[j - 7] = sls;
									sls = tokh.substr(2, 2);
									iprd.timedurat[j - 7][0] = atoi(sls.c_str());
									sls = tokh.substr(4, 2);
									iprd.timedurat[j - 7][1] = atoi(sls.c_str());
									bcel = 0;
									for (k = 0; k < 6; ++k) {//요일 검사
										if (iprd.timedate[j - 7] == datchk[k]) {
											bcel = 2;
											break;
										}
									}
									if (bcel == 2) {
										bcel = 0;
										if (iprd.timedurat[j - 7][0] >= 0 && iprd.timedurat[j - 7][0] <= 24)bcel = 3;//강의시간 검사
										if (bcel == 3) {
											bcel = 0;
											if (iprd.timedurat[j - 7][1] >= 0 && iprd.timedurat[j - 7][1] <= 24)bcel = 1;//강의시간 검사
										}
									}
								}
								else bcel = 0;
							}
							break;
						case 9:
							if (j - iprd.timenum == 7) {//강의시간 개수 2일때 - 분반 번호 입력받을 차례
								stltok = strlen(tok);
								for (k = 0; k < stltok; ++k) {
									if (tok[k]<'0' || tok[k]>'9') {//숫자 아닌게 있으면
										bcel = 0;
										break;
									}
								}
								if (bcel != 0) {
									iprd.classdivision = atoi(tok);
									if (iprd.classdivision < 0)bcel = 0;//분반 음수 없음
									else {
										bcel = 0;
										for (k = 0; k < chkarr.size(); ++k) {
											if (chkarr[k].num == iprd.classdivision) {//분반 번호 겹칠 때
												chkarh.num = iprd.classdivision;
												chkarh.cnt = chkarr[k].cnt + 1;
												chkarr.insert(chkarr.begin() + k, chkarh);
												chkarr.erase(chkarr.begin() + k + 1);
												bcel = 1;
												break;
											}
										}
										if (bcel == 0) {//분반 번호 안겹치면
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
						if (bcel == 0)break;//읽는 중 오류 발생
						tok = strtok(NULL, " ");
						j++;
					}
					if (bcel == 1) {//읽는데 문제가 없었음
						class_all[class_all_num] = iprd;
						class_all_num++;
					}
				}
				delete cln;//메모리 해제
			}
		}
		if (bcel != 0) {
			for (i = 0; i < chkarr.size(); ++i) {
				if (chkarr[i].num != 0 && chkarr[i].cnt == 1) {//분반인데 분반쌍이 없는경우
					bcel = 0;
					break;
				}
			}
			if (bcel != 0) {
				bcel = divisioncheck(class_all_num);
				if (bcel != 0) {//분반 겹침 문제 없는경우
					bcel = finalcheck(1);//추가 형식 검사(finalcheck 함수와 연동)
					if (bcel != 0) {
						for (i = 0; i < class_all_num; ++i) {
							if (class_all[i].classdivision == -1) {//뭔가 파일형식에 누락된게 있는 경우
								bcel = 0;
								break;
							}
						}
					}
				}
			}
		}
		vector<vecarr>().swap(chkarr);//메모리 해제
/*		if (bcel == 1)cout << "class_list.txt 파일 문제 없음" << endl;*/
		if (bcel == 0)cout << "파일의 내용이 형식에 맞지 않습니다" << endl;
	}
	else {
		cout << "파일 존재 오류입니다" << endl;
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
	if (accin.is_open()) {//account_list.txt 파일 불러오기
		i = 0;
		while (!accin.eof() && bcel == 1) {
			i++;
			getline(accin, clin);
			if (clin.size() != 0) {//엔터만 있는경우 그냥 스킵
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
						case 0://학번
							if (strlen(tok) == snlenth) {
								intchk = 0;
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//학번 숫자
									else {//아님
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentnum = atoi(tok);
							}
							else bcel = 0;
							break;
						case 1://비밀번호
							stltok = strlen(tok);
							if (stltok >= pwmin && stltok <= pwmax) {
								intchk = mechk = 0;
								for (k = 0; k < strlen(tok); ++k) {
									if (tok[k] >= 'a'&&tok[k] <= 'z')mechk++;//비밀번호 영어 소문자
									else if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//비밀번호 숫자
									else {//둘 다 아님
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentpw = tok;
							}
							else bcel = 0;
							break;
						case 2://이름
							stltok = strlen(tok);
							if (stltok >= nmmin && stltok <= nmmax && stltok % 2 == 0) {//한글만으로 하면 짝수byte
								for (k = 0; k < stltok; ++k) {
									//한글체크
									if (tok[k] >= 0 && tok[k] <= 127) {//ASCII 코드일 경우(영숫특 처리, 실제로는 더 복잡함)
										bcel = 0;
										break;
									}
								}
								if (bcel != 0)iprd.studentname = tok;
							}
							else bcel = 0;
							break;
						case 3://신청한 과목 수
							if (strlen(tok) == 1) {
								if (tok[0] >= '0'&&tok[0] <= '9') {
									if (atoi(tok) <= claslenth)iprd.classlistnum = atoi(tok);
									else bcel = 0;
								}
								else bcel = 0;
							}
							else bcel = 0;
							break;
						case 4://과목1
						case 5://과목2
						case 6://과목3
						case 7://과목4
						case 8://과목5
						case 9://과목6
							if (j - iprd.classlistnum > 3)bcel = 0;//과목 개수가 안맞음
							else {
								if (strlen(tok) == inplnth) {
									intchk = 0;
									for (k = 0; k < strlen(tok); ++k) {
										if (tok[k] >= '0'&&tok[k] <= '9')intchk++;//과목번호 숫자
										else {//아님
											bcel = 0;
											break;
										}
									}
									if (bcel != 0) {
										bcel = 0;
										for (k = 0; k < class_all_num; ++k) {//신청한 과목 정보 가져오기
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
						if (bcel == 0)break;//읽는 중 오류 발생
						tok = strtok(NULL, " ");
						if (tok == NULL && j >= 3 && (j - 3) < iprd.classlistnum)bcel = 0;//강의신청개수>강의목록 개수
						j++;
					}
					if (iprd.classlistnum == -1)bcel = 0;
					if (bcel == 1) {//읽는데 문제가 없었음
						account_all[account_all_num] = iprd;
						account_all_num++;
					}
				}
				delete cln;//메모리 해제
			}
		}
		if (bcel != 0)bcel = finalcheck(2);//형식 검사
/*		if (bcel == 1)cout << "account_list.txt 파일 문제 없음" << endl;*/
		if (bcel == 0) {
			cout << "파일의 내용이 형식에 맞지 않습니다" << endl;
			return false;
		}
	}
	else {
		cout << "파일 존재 오류입니다" << endl;
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
	for (i = 0; i < account_all_num; ++i) {//모든 학생 정보 저장
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
		if (cdnum != 0 && a[i] == false) {//분반번호가 존재하는 경우
			a[i] = true;
			vector<int>().swap(cp);//메모리 해제(초기화)
			for (j = i; j < class_all_num; ++j) {
				if (class_all[j].classdivision == cdnum) {
					a[j] = true;
					cp.push_back(j);
				}
			}
			for (j = 0; j < cp.size() - 1 && bcel == 1; ++j) {
				for (k = j + 1; k < cp.size() && bcel == 1; ++k) {
					if (class_all[cp[j]].professor == class_all[cp[k]].professor) {//같은 교수명이고
						th = timecheck(class_all[cp[j]], class_all[cp[k]]);//시간이 겹치면(교실 상관X)
						if (th != "-1") {
							bcel = 0;
							break;
						}
					}
				}
			}
		}
	}
	delete a;//메모리 해제
	vector<int>().swap(cp);//메모리 해제
	return bcel;
}
int finalcheck(int wh)
{
	int i, j, k, bcel = 1;
	string th;
	student aci;
	if (wh == 1) {//class_list.txt 형식 검사-과목번호 중복, 과목명 중복, 교실 및 시간 중복
		for (i = 0; i < class_all_num - 1 && bcel == 1; ++i) {
			for (j = i + 1; j < class_all_num && bcel == 1; ++j) {
				if (class_all[i].classnum == class_all[j].classnum) {//같은 과목번호
					bcel = 0;
					break;
				}
				if (class_all[i].classname == class_all[j].classname) {//같은 과목명
					bcel = 0;
					break;
				}
				if (class_all[i].classroom == class_all[j].classroom) {//같은 교실이고
					th = timecheck(class_all[i], class_all[j]);//시간이 겹치면
					if (th != "-1") {
						bcel = 0;
						break;
					}
				}
			}
		}
	}
	else if (wh == 2) {//account_list.txt 형식 검사-과목번호 중복
		for (i = 0; i < account_all_num; ++i) {
			aci = account_all[i];
			for (j = 0; j < aci.classlistnum - 1; ++j) {
				for (k = j + 1; k < aci.classlistnum; ++k) {
					if (aci.classlist[j].classnum == aci.classlist[k].classnum) {//같은 과목번호
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
			if (frt.timedate[k] == bkc.timedate[l]) {//요일 같고
				if (sortfind(frt, bkc, k, l)) {//시간이 겹치면
					rt = frt.classname + " 과목과 " + bkc.classname + " 과목";
					break;
				}
			}
		}
	}
	return rt;
}