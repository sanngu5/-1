#include "file.h"
#include <iostream>
#include <fstream>//파일 처리
#include <string>//string 처리
#include <algorithm>//sort함수용
#include <vector>//벡터
using namespace std;
enum limit_numbers {
	inplnth = 4,         //과목번호 길이
	claslenth = 6,       //신청가능한 최대 과목 수
	snlenth = 9,         //학번 길이
	pwmin = 5,           //비밀번호 최소길이
	pwmax = 15,          //비밀번호 최대길이
	nmmin = 4,           //이름 최소byte
	nmmax = 10,          //이름 최대byte
	cltlenth = 4,        //이수구분 길이
	cnmmin = 2,          //과목이름 최소길이
	cnmmax = 40          //과목이름 최대길이
};
struct classinfo {//과목 정보
	int classnum = 0;//과목번호
	string classname = "";//과목이름
	string professor = "";//담당교수
	string classroom = "";//강의실명
	string classtype = "";//이수구분
	int classscore = 0;//학점
	int timenum = 0;//강의시간 개수
	string timedate[2] = { "" };//요일
	int timedurat[2][2] = { 0 };//시간
	int classdivision = 0;//분반
};
struct student {//학생 정보
	int studentnum;//학번
	string studentpw;//비밀번호
	string studentname;//이름
	int classlistnum = 0;//신청한 과목 개수
	classinfo classlist[claslenth];//과목들
};
struct vecarr {//벡터 배열
	int num;
	int cnt;
};

void modify();
int table(); //시간표 추가
void classout(classinfo *clis, int st, int ed, int filt);//강의정보를 st~ed사이 출력(flit로 필터경우 구분)
string designlut(int prt, int ln, char fil);//prt 수를 ln길이의 수로 변경(빈자리는 fil로 채움)
string cltout(classinfo ipt);//강의시간 출력
void classlistchange(int chn);//과목번호 중복 검사 및 중복시 과목제거 중복아닐시 과목추가
bool sortfind(classinfo frt, classinfo bkc, int k, int l);//겹치는 시간 검사
void stateout(int swt);//오류번호, 세부사항
bool filecheck();//프로그램 맨 처음 실행 시 파일 검사 부분
int classfilecheck();//class_list.txt 파일 검사
bool accountfilecheck();//account_list.txt 파일 검사
void accountfilesave();//account_list.txt 파일 저장
string* classnumbers();//값 반환
string logname();//값 반환
int classnumberi();//값 반환
void registersuccess();//account_list.txt 다시 불러오기(회원가입 완료 직후)
int divisioncheck(int many);//분반 겹침 검사
int finalcheck(int wh);//파일 형식 검사
string timecheck(classinfo frt, classinfo bkc);

extern classinfo class_all[100];//전체 과목
extern int class_all_num;//전체 과목 개수
extern student account_all[100];//전체 학생
extern int account_all_num;//전체 학생 인원수
extern student logstudent;//로그인된 학생
extern classinfo nul;//초기화용 변수
extern int line_num;