#include "class_style.h"

void class_style(string c_line) {
	char c_array[100];
	char c_num[5];
	char c_name[41];
	char c_prof[10];
	char c_room[10];
	char c_type[5];
	char c_grades[2];
	int c_time;
	char c_time1[7];
	char c_time2[7];
	char* ptr;
	string class_info;

	strcpy(c_array, c_line.c_str());
	ptr = strtok(c_array, " ");
	strcpy(c_num, ptr);
	ptr = strtok(NULL, " ");
	strcpy(c_name, ptr);
	ptr = strtok(NULL, " ");
	strcpy(c_prof, ptr);
	ptr = strtok(NULL, " ");
	strcpy(c_room, ptr);
	ptr = strtok(NULL, " ");
	strcpy(c_type, ptr);
	ptr = strtok(NULL, " ");
	strcpy(c_grades, ptr);
	class_info = string(c_num) + " " + string(c_name) + " " + string(c_prof) + "±³¼ö´Ô " + string(c_room) + " " + string(c_type) + " " + string(c_grades) + "ÇÐÁ¡ ";
	ptr = strtok(NULL, " ");
	c_time = atoi(ptr);
	if (c_time == 1) {
		ptr = strtok(NULL, "\n");
		strcpy(c_time1, ptr);
		class_info += string(c_time1);
	}
	else if (c_time == 2) {
		ptr = strtok(NULL, " ");
		strcpy(c_time1, ptr);
		ptr = strtok(NULL, "\n");
		strcpy(c_time2, ptr);
		class_info += string(c_time1) + ", ";
		class_info += string(c_time2);
	}

	cout << class_info << endl;
	return;
}