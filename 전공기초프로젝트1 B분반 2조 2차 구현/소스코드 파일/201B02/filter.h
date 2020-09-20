#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<string>
#include <conio.h>

using namespace std;

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

int f_smenu(string num);
int f_num(string s_num);
int f_name(string s_name);
int f_all(string back);