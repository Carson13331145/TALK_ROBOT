#ifndef AGENDER_H
#define AGENDER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <windows.h>
#include "algorithm.h"
using namespace std;

char ag[1024][1024];

void agenda_check() {
	int pos = 0;
	int month = 0;
	int day = 0;
	int year = 0;
	int total = 0;
	int finish = 0;
	float sim = 0.0;
	float score = 0.0;
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	int m = sys.wMonth;
	int d = sys.wDay;
	int y = sys.wYear;
	char data[1024][1024];
	char ans[1024];
	string yes = "yes";
	string no = "no";
	string ok = "ok";
	string okay = "okay";
	string sure = "sure";
	string time_str;
	string score_output;
	stringstream score_s;
	stringstream year_str;
	stringstream month_str;
	stringstream day_str;
	char* time_ch;
	year_str << y;
	month_str << m;
	day_str << d;
	FILE *f = fopen("agenda.txt", "a+");
	FILE *fs = fopen("agenda_score.txt", "a+");
	time_str = year_str.str()+"/"+month_str.str()+"/"+day_str.str()+"\n";
	time_ch = string_to_char(time_str);
	fgets(data[pos], 1024, f);
	int count = 0;
	bool is_check = false;
	while (true) {
		year =  month = day = 0;
		if (data[pos][0] >= '0' && data[pos][0] <= '9') {
			get_time(data[pos], year, month, day);
		}
		if ((year == y && month == m && day == d-1)
		|(year == y && month == m-1 && day == 1)
		|(year == y-1 && month == 1 && day == 1)) {
			printf("robot: i gonna check your work, sir\nme: ");
			while (true) {
				memset(ans, '\0', 1024);
				gets(ans);
				if ((float(ldistance(yes, ans))/5.0 < 0.1)
				|(float(ldistance(ok, ans))/5.0 < 0.1)
				|(float(ldistance(okay, ans))/5.0 < 0.1)
				|(float(ldistance(sure, ans))/5.0 < 0.1)) {
					fgets(data[++pos], 1024, f);
					while (data[pos][0] != '\0') {
						if (data[pos][0] >= '0' && data[pos][0] <= '9') {
							is_check = true;
							break;
						}
						total++;
						memset(ans, '\0', 1024);
						printf("robot: have you finish -> %sme: ", data[pos]);
						gets(ans);
						if ((float(ldistance(yes, ans))/5.0 < 0.1)
						|(float(ldistance(sure, ans))/5.0 < 0.1)) {
							finish++;
						}
						fgets(data[++pos], 1024, f);
					}
					score = float(finish)/float(total);
					printf("robot: all checked, sir\n");
					if (score == 1) {
						printf("robot: %.0lf%% are finished, good job\n", score*100);
					} else if (score >= 0.8 && score < 1) {
						printf("robot: %.0lf%% are finished, not well actually\n", score*100);
					} else if (score >= 0.5 && score < 0.8) {
						printf("robot: %.0lf%% are finished, a little bad\n", score*100);
					} else {
						printf("robot: %.0lf%% are finished, you totally ruin today\n", score*100);
					}
					score_s << score*100;
					score_output = time_str+"score: "+score_s.str()+"\n";
					fputs(string_to_char(score_output), fs);
					fclose(fs);
					fclose(f);
					return;
				} else if (float(ldistance(no, ans))/float(sizeof(ans)) < 0.6) {
					printf("robot: ok, sir\n");
					fclose(fs);
					fclose(f);
					return;
				} else {
					printf("robot: sorry, i don't understand you\n");
					continue;
				}
			}
		}
		fgets(data[++pos], 1024, f);
	}
	fclose(fs);
	fclose(f);
}

void agenda_talk() {
	int pos = 1;
	stringstream year_str;
	stringstream month_str;
	stringstream day_str;
	string time_str;
	char* time_ch;
	FILE *f = fopen("agenda.txt", "at+");
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	year_str << sys.wYear;
	month_str << sys.wMonth;
	day_str << sys.wDay;
	time_str = year_str.str()+"/"+month_str.str()+"/"+day_str.str()+"\n";
	time_ch = string_to_char(time_str);
	fputs(time_ch, f);
	printf("\nwrite down your plan here, end with 'null'.\n1.");
	gets(ag[0]);
	while(ag[pos-1][0] != 'n') {
		fputs(ag[pos-1], f);
		fputs("\n", f);
		printf("%d.", pos+1);
		gets(ag[pos]);
		pos++;
	}
	fclose(f);
	printf("\n");
}

#endif

