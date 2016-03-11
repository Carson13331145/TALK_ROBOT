#ifndef MEMORY_H
#define MEMORY_H

/*--------------------------------------------------
emotion_measure:
robot_happy (0-20)unhappy; (30-60)usual; (70-99)happy
me_happy (0-20)unhappy; (30-60)usual; (70-99)happy
relation (0-20)nice; (30-60)usual; (70-99)bad
--------------------------------------------------*/
struct memory {
	float robot_happy;
	float me_happy;
	float relation;
	string last_end;
	string happy_word[1024][50];
	string sad_word[1024][50];
	int happy_x[1024];
	int sad_x[1024];
	int happy_y;
	int sad_y;
	memory() {
		robot_happy = 50.0;
		me_happy = 50.0;
		relation = 50.0;
		last_end = "";
	}
}main_memory;

void read_main_memory() {
	SYSTEMTIME sys;
	FILE *f = fopen("main_memory.txt", "r+");
	char robot_happy_str[1024];
	char me_happy_str[1024];
	char relation_str[1024];
	char last_end_str[1024];
	fgets(robot_happy_str, 1024, f);
	main_memory.robot_happy =  (robot_happy_str[12]-'0')*10+robot_happy_str[13]-'0';
	fgets(me_happy_str, 1024, f);
	main_memory.me_happy =  (me_happy_str[9]-'0')*10+me_happy_str[10]-'0';
	fgets(relation_str, 1024, f);
	main_memory.relation =  (relation_str[9]-'0')*10+relation_str[10]-'0';
	fgets(last_end_str, 1024, f);
	for (int i = 9; last_end_str[i] != '\n'; i++) main_memory.last_end += last_end_str[i];
	//	read time from string
	int year = 0;
	int month = 0;
	int day = 0;
	GetLocalTime(&sys);
	get_time(main_memory.last_end+"\n", year, month, day);
	if (year > sys.wYear || (year == sys.wYear && month > sys.wMonth)
	|| (year == sys.wYear && month == sys.wMonth && day - sys.wDay >= 3)) {
		main_memory.robot_happy -= ((day-sys.wDay)%10)*10;
		main_memory.relation -= ((day-sys.wDay)%10)*10;
	} else if (year == sys.wYear && month == sys.wMonth && day - sys.wDay == 2) {
		main_memory.robot_happy -= 10.0;
		main_memory.relation -= 5.0;
	} else if (year == sys.wYear && month == sys.wMonth && day == sys.wDay) {
		main_memory.robot_happy += 5.0;
		main_memory.relation += 2.5;
	}
	fclose(f);
}

void write_main_memory() {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	int m = sys.wMonth;
	int d = sys.wDay;
	int y = sys.wYear;
	stringstream year_str;
	stringstream month_str;
	stringstream day_str;
	stringstream robot_happy_ss; 
	stringstream me_happy_ss;
	stringstream relation_ss;
	string robot_happy_str;
	string me_happy_str;
	string relation_str;
	year_str << y;
	month_str << m;
	day_str << d;
	robot_happy_ss << int(main_memory.robot_happy);
	me_happy_ss << int(main_memory.me_happy);
	relation_ss << int(main_memory.relation);
	robot_happy_str = robot_happy_ss.str();
	me_happy_str = me_happy_ss.str();
	relation_str = relation_ss.str();
	if (main_memory.robot_happy < 0) robot_happy_str = "00";
	else if (main_memory.robot_happy > 99) robot_happy_str = "99";
	else if (main_memory.robot_happy < 10) robot_happy_str = "0"+robot_happy_str;
	if (main_memory.me_happy < 0) me_happy_str = "00";
	else if (main_memory.me_happy > 99) me_happy_str = "99";
	else if (main_memory.me_happy < 10) me_happy_str = "0"+me_happy_str;
	if (main_memory.relation < 0) relation_str = "00";
	else if (main_memory.relation > 99) relation_str = "99";
	else if (main_memory.relation < 10) relation_str = "0"+relation_str;
	string time_str;
	string robot_happy_strs = "robot_happy:"+robot_happy_str+"\n";
	string me_happy_strs = "me_happy:"+me_happy_str+"\n";
	string relation_strs = "relation:"+relation_str+"\n";
	time_str = "last_end:"+year_str.str()+"/"+month_str.str()+"/"+day_str.str()+"\n";
	FILE *f = fopen("main_memory.txt", "w+");
	fputs(string_to_char(robot_happy_strs), f);
	fputs(string_to_char(me_happy_strs), f);
	fputs(string_to_char(relation_strs), f);
	fputs(string_to_char(time_str), f);
	fclose(f);
}

void read_typical_words() {
	int line = 0;
	int col = 0;
	bool is_happy = false;
	bool is_sad = false;
	string happy_str = "Happy";
	string sad_str = "Sad";
	string temp_str;
	char line_str[1024];
	char *p_happy;
	char *p_sad;
	char *happy_ch = string_to_char(happy_str);
	char *sad_ch = string_to_char(sad_str);
	FILE *f = fopen("typical_words.txt", "r+");
	memset(line_str, '\0', sizeof(line_str));
	fgets(line_str, sizeof(line_str), f);
	while (line_str[0] != '#') {
		if (line_str[0] == '.') {
			p_happy = strstr(line_str, happy_ch);
			p_sad = strstr(line_str, sad_ch);
			if (p_happy != NULL) {
				is_happy = true;
				is_sad = false;
			} else if (p_sad != NULL) {
				is_happy = false;
				is_sad = true;
			}
			line = col = 0;
			memset(line_str, '\0', sizeof(line_str));
			fgets(line_str, sizeof(line_str), f);
			continue;
		}
		if (is_happy) {
			temp_str = "";
			temp_str = temp_str.insert(0, line_str);
			main_memory.happy_word[line][col] = "";
			main_memory.happy_x[line] = 0;
			for (int i = 0; i < temp_str.length() && temp_str[i] != '\n'; i++) {
				if (temp_str[i] != '|') main_memory.happy_word[line][col] += temp_str[i];
				else main_memory.happy_word[line][++col] = "";
				main_memory.happy_x[line] = col+1;
			}
			main_memory.happy_y = line+1;
			col = 0;
			line++;
		} else if(is_sad) {
			temp_str = "";
			temp_str = temp_str.insert(0, line_str);
			main_memory.sad_word[line][col] = "";
			main_memory.sad_x[line] = 0;
			for (int i = 0; i < temp_str.length() && temp_str[i] != '\n'; i++) {
				if (temp_str[i] != '|') main_memory.sad_word[line][col] += temp_str[i];
				else main_memory.sad_word[line][++col] = "";
				main_memory.sad_x[line] = col+1;
			}
			main_memory.sad_y = line+1;
			col = 0;
			line++;
		}
		memset(line_str, '\0', sizeof(line_str));
		fgets(line_str, sizeof(line_str), f);
	}
	fclose(f);
}

#endif

