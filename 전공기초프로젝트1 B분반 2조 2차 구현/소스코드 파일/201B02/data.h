#pragma warning(disable:4996)
#include<iostream>

using namespace std;

static int ERROR_FLAG = 1;

enum error_flag_type {
	NOERROR = 1,
	FALSE = -1,
	ERROR_GRAMMAR_STUDENT_ID_LENGTH = -2,
	ERROR_GRAMMAR_STUDENT_ID_NUMBER = -3,
	ERROR_MEANING_STUDENT_ID_REGISTER = -4,
	ERROR_GRAMMAR_PASSWORD_LENGTH = -5,
	ERROR_GRAMMAR_PASSWORD_COMB = -6,
	ERROR_MEANING_PASSWORD_MATCH = -7,
	ERROR_GRAMMAR_STUDENT_ID_OVERLAP = -8,
	ERROR_GRAMMAR_PASSWORD_CHECK = -9,
	ERROR_GRAMMAR_NAME_LENGTH = -10,
	ERROR_MEANING_NAME_KOREAN = -11
};

void set_error_flag(int setError);
void show_error(int flag);

int filter_grammar_student_id_length(char* str);
int filter_grammar_student_id_number(char* str);
int filter_meaning_student_id_register(char* str);
int filter_grammar_password_length(char* str);
int filter_grammar_password_comb(char* str);
int filter_meaning_password_match(char* str, int line_num);

int filter_grammar_student_id_length(string str);
int filter_grammar_student_id_number(string str);
int filter_grammar_password_length(string str);
int filter_grammar_password_comb(string str);
int filter_meaning_student_id_overlap(string str);
int filter_meaning_password_check(string str1, string str2);
int filter_grammar_name_length(string str);
int filter_meaning_name_korean(string str);