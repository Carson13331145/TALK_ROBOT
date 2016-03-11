#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

char* string_to_char(string src) {
	char *ch = new char[src.length()+1];
	for (int i = 0; i < src.length(); i++) {
		ch[i] = src[i];
	}
	ch[src.length()] = '\0';
	return ch;
}

bool find_words(const string src, string str[], int num) {
	string source = src;
	transform(source.begin(), source.end(), source.begin(), ::tolower);
	char *chs = string_to_char(source);
	char *tmp = string_to_char(str[0]);
	char *p = strstr(chs , tmp);
	if (p == NULL) return false;
	for (int i = 1; i < num; i++) {
		tmp = string_to_char(str[i]);
		p = strstr(p+1 , tmp);
		if (p == NULL) return false;
	}
	return true;
}

void get_time(const string str, int& y, int& m, int& d) {
	int pos = 0;
	int pos_m = 0;
	int pos_d = 0;
	int pos_y = 0;
	char month[1024];
	char day[1024];
	char year[1024];
	while (str[pos] != '/') {
		year[pos_y++] = str[pos++];
	}
	while (str[pos+1] != '/') {
		month[pos_m++] = str[++pos];
	}
	pos++;
	while (str[pos+1] != '\n') {
		day[pos_d++] = str[++pos];
	}
	for (int i = pos_y-1; i >= 0; i--) {
		if (i == 0) {
			y += (year[i]-'0')*1000;
		} else if (i == 1) {
			y += (year[i]-'0')*100;
		} else if (i == 2) {
			y += (year[i]-'0')*10;
		} else if (i == 3) {
			y += year[i]-'0';
		}
	}
	for (int i = pos_m-1; i >= 0; i--) {
		if (pos_m == 2) {
			if (i == 1) {
				m += month[i]-'0';
			} else {
				m += (month[i]-'0')*10;
			}
		} else {
			m += month[i]-'0';
		}
	}
	for (int i = pos_d-1; i >= 0; i--) {
		if (pos_d == 2) {
			if (i == 1) {
				d += day[i]-'0';
			} else {
				d += (day[i]-'0')*10;
			}
		} else {
			d += day[i]-'0';
		}
	}
}

int ldistance(const string src, const string tar)
{
	string source = src;
	string target = tar;
	transform(source.begin(), source.end(), source.begin(), ::tolower);
	transform(target.begin(), target.end(), target.begin(), ::tolower);
	
    int n=source.length();
    int m=target.length();
    if (m==0) return n;
    if (n==0) return m;

	typedef vector< vector<int> >  Tmatrix;
    Tmatrix matrix(n+1);
    for(int i=0; i<=n; i++)  matrix[i].resize(m+1);

    for(int i=1;i<=n;i++) matrix[i][0] = i;
    for(int i=1;i<=m;i++) matrix[0][i] = i;

     for(int i=1;i<=n;i++)
     {
        const char si=source[i-1];
        for(int j=1;j<=m;j++)
        {
            const char dj=target[j-1];
            int cost;
            if(si == dj) {
                cost = 0;
            }
            else {
                cost = 1;
            }
            const int above = matrix[i-1][j]+1;
            const int left = matrix[i][j-1]+1;
            const int diag = matrix[i-1][j-1]+cost;
            matrix[i][j] = min(above,min(left,diag));
        }
    }
    return matrix[n][m];
}

#endif

