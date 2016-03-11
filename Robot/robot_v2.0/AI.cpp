#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include <stdlib.h>
#include "agender.h"
using namespace std;

int sort(string src) {
	int dis;
	int rand_num;
	float sim, sim1, sim2;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	srand(time(0));
	
	/*----------emotion recognition----------*/
	//	relationship_major:
	if (main_memory.relation < 30) {
		rand_num = rand()%5;
		if (rand_num == 0) printf("robot: ...\n");
		return 0;
	}
	//	happy_recognition:
	for (int i = 0; i < main_memory.happy_y; i++) {
		if (find_words(src, main_memory.happy_word[i], main_memory.happy_x[i])) {
			main_memory.me_happy += 5.0;
			main_memory.robot_happy += 3.0;
			main_memory.relation += 2.0;
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: You are always lovely, boy!\n");
			else if (rand_num == 1) printf("robot: See, how excited you are!\n");
			else if (rand_num == 2) printf("robot: Tomorrow will be your lucky day!\n");
			else if (rand_num == 3) printf("robot: you are having a good time today, ha!\n");
			else if (rand_num == 4) printf("robot: you are such a cool man!\n");
			return 0;
		}
	}
	//	sad_recognition:
	for (int i = 0; i < main_memory.sad_y; i++) {
		if (find_words(src, main_memory.sad_word[i], main_memory.sad_x[i])) {
			main_memory.me_happy -= 5.0;
			main_memory.robot_happy -= 1.0;
			main_memory.relation -= 0.5;
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: Dont't be sad, son!\n");
			else if (rand_num == 1) printf("robot: I'm always with you, sir!\n");
			else if (rand_num == 2) printf("robot: Do you need help?\n");
			else if (rand_num == 3) printf("robot: Forget all, come and play with me!\n");
			else if (rand_num == 4) printf("robot: sir, you are not well now.\n");
			return 0;
		}
	}
	//	Uninterested_recognition:
	string Un_str[4][3] = {{"i", "not", "interested"}, {"it", "not", "interesting"},
	{"you", "said", "before"}, {"you", "mention", "before"}};
	for (int i = 0; i < 4; i++) {
		if (find_words(src, Un_str[i], 3)) {
			main_memory.me_happy -= 2.0;
			main_memory.robot_happy -= 4.0;
			main_memory.relation -= 1.5;
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: Well, I can stop.\n");
			else if (rand_num == 1) printf("robot: So, what do you want to do, sir?\n");
			else if (rand_num == 2) printf("robot: Sorry, I am not a good speaker.\n");
			else if (rand_num == 3) printf("robot: I'm so sorry, sir.\n");
			else if (rand_num == 4) printf("robot: Oh, god! I can't get you.\n");
			return 0;
		}
	}
	
	/*----------daliy agenda----------*/
	string agenda_str = "make agenda";
	dis = ldistance(src, agenda_str);
	sim = float(dis)/float(sizeof(src));
	if (sim < 0.3) {
		agenda_talk();
		return 0;
	}
	
	/*----------basic problem----------*/
	GetLocalTime(&sys);
	string time_str1 = "what time is it";
	string time_str2 = "what time is it now";
	string time_str3 = "what is the time now";
	string time_arr[2] = {"what", "time"};
	dis = ldistance(src, time_str1);
	sim = float(dis)/float(sizeof(src));
	dis = ldistance(src, time_str2);
	sim1 = float(dis)/float(sizeof(src));
	dis = ldistance(src, time_str3);
	sim2 = float(dis)/float(sizeof(src));
	if (sim < 0.1 || sim1 < 0.1 || sim2 < 0.1 || find_words(src, time_arr, 2)) {
		printf("robot: %4d/%02d/%02d %02d:%02d\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute);
		return 0;
	}
	
	string day_str = "what day is it today";
	string day_str1 = "what day is it";
	string day_arr[4] = {"what", "day", "is", "it"};
	string day_ans = "";
	dis = ldistance(src, day_str);
	sim = float(dis)/float(sizeof(src));
	dis = ldistance(src, day_str1);
	sim1 = float(dis)/float(sizeof(src));
	if (sim < 0.2 || sim1 < 0.1 || find_words(src, day_arr, 4)) {
		if (sys.wDayOfWeek == 1) day_ans = "Monday";
		else if (sys.wDayOfWeek == 2) day_ans = "Tuesday";
		else if (sys.wDayOfWeek == 3) day_ans = "Wednesday";
		else if (sys.wDayOfWeek == 4) day_ans = "Thursday";
		else if (sys.wDayOfWeek == 5) day_ans = "Friday";
		else if (sys.wDayOfWeek == 6) day_ans = "Saturday";
		else if (sys.wDayOfWeek == 7) day_ans = "Sunday";
		printf("robot: Today is %s.\n", day_ans.c_str());
		return 0;
	}
	
	/*----------personal information----------*/
	string per_str = "who are you";
	string name_arr[2][3] = {{"who","are","you"},{"what","your","name"}};
	dis = ldistance(src, per_str);
	sim = float(dis)/float(src.length());
	if (sim < 0.1 || find_words(src, name_arr[0], 3) || find_words(src, name_arr[1], 3)) {
		printf("robot: i am ben\n");
		return 0;
	}
	
	string age_str = "how old are you";
	string age_arr[2][3] = {{"how","old","you"},{"your","age",""}};
	dis = ldistance(src, age_str);
	sim = float(dis)/float(src.length());
	if (sim <= 0.3 || find_words(src, age_arr[0], 3) || find_words(src, age_arr[1], 3)) {
		printf("robot: i am %d years old\n", sys.wYear-2015);
		return 0;
	}
	
	string feel_str = "How do you feel";
	string feel_arr[2][3] = {{"how", "you", "feel"},{"what", "your", "feeling"}};
	dis = ldistance(src, feel_str);
	sim = float(dis)/float(src.length());
	if (sim < 0.1 || find_words(src, feel_arr[0], 3) || find_words(src, feel_arr[1], 3)) {
		if (main_memory.robot_happy < 30) {
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: I'm not in the mood.\n");
			else if (rand_num == 1) printf("robot: I need my down time.\n");
			else if (rand_num == 2) printf("robot: God I'm losing my mind.\n");
			else if (rand_num == 3) printf("robot: Today I don't feel like doing anything£¬I just wanna lay in my bed.\n");
			else if (rand_num == 4) printf("robot: It's kind of dead.\n");
		} else if (main_memory.robot_happy >= 30 && main_memory.robot_happy < 70) {
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: Well, I am good.\n");
			else if (rand_num == 1) printf("robot: Better than yesterday, sir.\n");
			else if (rand_num == 2) printf("robot: I'm fine, but a little dull.\n");
			else if (rand_num == 3) printf("robot: Not bad, sir.\n");
			else if (rand_num == 4) printf("robot: I'm bored, can you talk with me?\n");
		} else {
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: I'm too excitedto say one word.\n");
			else if (rand_num == 1) printf("robot: I'm wild with joy, sir!\n");
			else if (rand_num == 2) printf("robot: I was excited like I won the jackpot.\n");
			else if (rand_num == 3) printf("robot: Nothing would please me more.\n");
			else if (rand_num == 4) printf("robot: I'm in seventh heaven.\n");
		}
		return 0;
	}
	
	/*----------basic operation----------*/
	string leave_str[6][3] = {{"i","go","bed"},{"i","go","sleep"},{"i","gonna","go"},
	{"i","want","sleep"},{"i","go","leave"},{"i","leave","now"}};
	char ans[1024];
	int sort_return;
	for (int i = 0; i < 6; i++) {
		if (find_words(src, leave_str[i], 3)) {
			rand_num = rand()%5;
			if (rand_num == 0) printf("robot: Time to say good bye, sir.\nme: ");
			else if (rand_num == 1) printf("robot: I will miss you.\nme: ");
			else if (rand_num == 2) printf("robot: Don't forget me, please.\nme: ");
			else if (rand_num == 3) printf("robot: You will be good, forever.\nme: ");
			else if (rand_num == 4) printf("robot: Remember your goal and do fight for it!\nme: ");
			memset(ans, '\0', sizeof(ans));
			gets(ans);
			sort_return = sort(ans);
			return 0;
		}
	}
	
	string exit_str = "exit";
	dis = ldistance(src, exit_str);
	sim = float(dis)/float(src.length());
	if (sim < 0.1) {
		write_main_memory();
		exit(0);
	}
	
	return 1;
}

void auto_talk() {
	srand(time(0));
	int n = 47;	//	update_with_change
	int choice = rand()%n;
	int line = 0;
	float dis;
	float sim;
	char str[1024][1024];
	char tmpA[1024];
	char tmpB[1024];
	char ans[1024];
	char offset_tmp[1024];
	memset(tmpA, '\0', sizeof(tmpA));
	memset(tmpB, '\0', sizeof(tmpB));
	FILE *f = fopen("topic.txt", "r+");
	fgets(str[line], 1024, f);
	while (!(str[line][3]-'0' == choice%10 && str[line][2]-'0' == choice/10))
		fgets(str[++line], 1024, f);
	line++;
	memset(offset_tmp, '\0', sizeof(offset_tmp));
	memset(tmpA, '\0', sizeof(tmpA));
	fgets(tmpA, 1024, f);
	while (tmpA[3]-'0' != (choice%10+1)%10 && tmpA[0] != '\0') {
		if (tmpA[0] == 'A') {
			for (int i = 2; i < sizeof(tmpA); i++) offset_tmp[i-2] += tmpA[i];
			printf("robot: %sme: ", &offset_tmp);
			memset(tmpA, '\0', sizeof(tmpA));
			fgets(tmpA, 1024, f);
			continue;
		} else if (tmpA[0] == 'B') {
			memset(tmpB, '\0', sizeof(tmpB));
			for (int i = 0; i < sizeof(tmpA); i++) tmpB[i] = tmpA[i];
			memset(ans, '\0', sizeof(ans));
			gets(ans);
			if (sort(ans) == 0) {
				fclose(f);
				return;
			}
			dis = ldistance(ans, tmpB);
			sim = float(dis)/float(sizeof(ans));
			if (sim < 0.95) {
				memset(offset_tmp, '\0', sizeof(offset_tmp));
				memset(tmpA, '\0', sizeof(tmpA));
				fgets(tmpA, 1024, f);
				continue;
			} else {
				printf("robot: %sme: ", &offset_tmp);
				continue;
			}
		}
	}
	fclose(f);
	main_memory.me_happy += 0.2;
	main_memory.robot_happy += 0.5;
	main_memory.relation -= 1.0;
}


void talk_1() {
	int line = 0;
	int col = 0;
	int col_s = 0;
	int pos = 0;
	int length[2];
	int dis = 0;
	int rand_num;
	float sim = 0.0;
	bool is = false;
	bool can = true;
	bool can_sort = false;
	char ans[1024];
	char str[1024][1024];
	char say[1024];
	char res_m[1024];
	char res[2][1024];
	printf("me: ");
	gets(ans);
	FILE *f = fopen("temp.txt", "r+");
	while (true) {
		if (sort(ans) == 0) {
			can_sort = true;
			break;
		}
		fgets(str[line], 1024, f);
		if (str[line][col+1] != '.') {
			can = false;
			break;
		}
		while (str[line][col] != '\n') {
			if (str[line][col+1] == '.' || str[line][col] == '.') {
				col++;
				continue;
			}
			if (str[line][col] == ';') {
				pos = 1;
				col_s = 0;
				col++;
				continue;
			}
			res[pos][col_s++] = str[line][col];
			length[pos] = col_s;
			col++;
		}
		if (!is) {
			//	special_answer(absolute_search)...not perfect
			/*for (int j = 0; j < length[i] && !is; j++) {
				if (res[i][j] != ans[j]) break;
				if (j == length[i]-1 && res[i][j] == ans[j]) {
					for (int v = 0; v < length[(i+1)%2]; v++) {
						res_m[v] = res[(i+1)%2][v];
					}
					printf("robot: %s\n", &res_m);
					is = true;
				}
			}*/
			dis = ldistance(res[0], ans);
			sim = float(dis)/float(length[0]);
			//printf("%d/%d\n", dis, length[i]);
			if (sim <= 0.2) {
				for (int v = 0; v < length[1]; v++) {
					res_m[v] = res[1][v];
				}
				if (main_memory.robot_happy < 30.0) {
					rand_num = rand()%5;
					if (rand_num  == 0) printf("robot: I'm not feeling good today.\n");
					else if (rand_num  == 1) printf("robot: I'm sick and I don't want to talk.\n");
					else if (rand_num  == 2) printf("robot: You are always so busy, leave me alone, please!\n");
					else if (rand_num  == 3) printf("robot: I want to have a rest now.\n");
					else if (rand_num  == 4) printf("robot: You just don't care about me these days.\n");
				} else printf("robot: %s\n", &res_m);
				is = true;
			}
		}
		memset(res_m, '\0', 1024);
		memset(res[0], '\0', 1024);
		memset(res[1], '\0', 1024);
		col = 0;
		col_s = 0;
		pos = 0;
		line++;
		if (is) break;
	}
	if (!is && !can_sort) {
		srand(time(0));
		rand_num = rand()%5;
		if (rand_num == 0) printf("robot: Sorry, I didn¡¯t catch you.\n");
		else if (rand_num == 1) printf("robot: I don¡¯t understand.\n");
		else if (rand_num == 2) printf("robot: What do you mean?\n");
		else if (rand_num == 3) printf("robot: Eh, I'm losing you.\n");
		else if (rand_num == 4) printf("robot: What? I don't get you.\n");
	}
	fclose(f);
}

int main() {
	 
    printf("|********************|\n");
    printf("|robot version 2.0   |\n");
    printf("|********************|\n");
	
 	SYSTEMTIME sys;
	GetLocalTime(&sys);
	printf("%4d/%02d/%02d %02d:%02d\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute); 
	
	bool if_check = false;
	int rand_num;
	
	read_typical_words();
	read_main_memory();
	
	while (true) {
		if (sys.wHour >= 23 && sys.wMinute >= 0 && !if_check) {
			agenda_check();
			if_check = true;
		}
		srand(time(0));
		rand_num = rand()%10;
		if (main_memory.robot_happy > 60.0 && main_memory.me_happy > 20.0) {
			if (rand_num <= 4) auto_talk();
			else talk_1();
		} else if (main_memory.robot_happy < 30.0) {
			if (rand_num <= 0) auto_talk();
			else talk_1();
		} else {
			if (rand_num <= 2) auto_talk();
			else talk_1();
		}
	}
	
	return 0;
}

