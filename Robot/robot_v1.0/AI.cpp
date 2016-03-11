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
#include "algorithm.h"
using namespace std;

int sort(string src) {
	int dis;
	float sim, sim1, sim2;
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	
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
	string time_str1 = "what time it is";
	string time_str2 = "what time it is now";
	string time_str3 = "what is the time now";
	dis = ldistance(src, time_str1);
	sim = float(dis)/float(sizeof(src));
	dis = ldistance(src, time_str2);
	sim1 = float(dis)/float(sizeof(src));
	dis = ldistance(src, time_str3);
	sim2 = float(dis)/float(sizeof(src));
	if (sim < 0.1 || sim1 < 0.1 || sim2 < 0.1) {
		printf("robot: %4d/%02d/%02d %02d:%02d\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute);
		return 0;
	}
	
	/*----------personal information----------*/
	string per_str = "who are you";
	dis = ldistance(src, per_str);
	sim = float(dis)/float(src.length());
	if (sim < 0.1) {
		printf("robot: i am ben\n");
		return 0;
	}
	
	string age_str = "how old are you";
	dis = ldistance(src, age_str);
	sim = float(dis)/float(src.length());
	if (sim <= 0.3) {
		printf("robot: i am %d years old\n", sys.wYear-2015);
		return 0;
	}
	
	/*----------basic operation----------*/
	string exit_str = "exit";
	dis = ldistance(src, exit_str);
	sim = float(dis)/float(src.length());
	if (sim < 0.1) {
		exit(0);
	}
	
	return 1;
}

void auto_talk() {
	srand(time(0));
	int n = 4;	//	update_with_change
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
	while (str[line][3]-'0' != choice) fgets(str[++line], 1024, f);
	line++;
	fgets(tmpA, 1024, f);
	while (tmpA[3]-'0' != choice+1 && tmpA[0] != '\0') {
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
			if (sort(ans) == 0) break;
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
}


void talk_1() {
	int line = 0;
	int col = 0;
	int col_s = 0;
	int pos = 0;
	int length[2];
	int dis = 0;
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
		for (int i = 0; i < 2 && !is; i++) {
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
			dis = ldistance(res[i], ans);
			sim = float(dis)/float(length[i]);
			//printf("%d/%d\n", dis, length[i]);
			if (sim <= 0.2) {
				for (int v = 0; v < length[(i+1)%2]; v++) {
					res_m[v] = res[(i+1)%2][v];
				}
				printf("robot: %s\n", &res_m);
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
	if (!is && !can_sort) printf("robot: Sorry, I didn¡¯t catch you.\n");
	fclose(f);
}

int main() {
	
    printf("|********************|\n");
    printf("|robot version 1.0   |\n");
    printf("|********************|\n");
	
 	SYSTEMTIME sys;
	GetLocalTime( &sys );
	printf("%4d/%02d/%02d %02d:%02d\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute); 
	
	bool if_check = false;
	srand(time(0));
	
	while (true) {
		if (sys.wHour >= 23 && sys.wMinute >= 0 && !if_check) {
			agenda_check();
			if_check = true;
		}
		if (rand()%10 <= 1) auto_talk();
		else talk_1();
	}
	
	return 0;
}

