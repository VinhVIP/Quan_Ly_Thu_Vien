
char* GetSystemDate(){
	time_t curTime = time(0);
	tm* now = localtime(&curTime);
	char ch[11] = {0};
	sprintf(ch, "%d/%d/%d", now->tm_mday, now->tm_mon+1, 1900+now->tm_year);
	return ch;
}


int* SplitDate(char s[]){
	int *a = new int[3];
	for(int i=0; i<3; i++) a[i] = -1;
	string txt;
	int index = 0;
	int n = strlen(s);

	for(int i=0; i<n; i++){
		if(s[i] == '/' || i == n-1){
			if(i == n-1) txt += s[i];
			int x = atoi(txt.c_str());
			a[index++] = x;
			txt = "";
		}else{
			txt += s[i];
		}
	}
	return a;
}

bool isLeapYear(int year){
	if(year%400 == 0 || (year%4 == 0 && year%100 != 0)){
		return true;
	}
	return false;
}

int DayOfMonth(int month, int year){
	if(month < 1 || month > 12) return 0;
	
	switch(month){
		case 2:
			if(isLeapYear(year)) return 29;
			else return 28;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
	}
	return 31;
}

bool CheckDate(char* s){
	int *a = SplitDate(s);
	bool res = true;
	if(a[2] < 1900 || a[1] <= 0 || a[1] > 12 || a[0] <= 0) res = false;
	if(a[0] > DayOfMonth(a[1], a[2])) res = false;
	delete a;
	return res;
}

time_t GetTime(char *s){
	tm t;
	int *a = SplitDate(s);
	t.tm_year = a[2]-1900;
	t.tm_mon = a[1]-1;
	t.tm_mday = a[0];
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	time_t timer = mktime(&t);

	delete a;
	return timer;
}

double DiffTime(char *time1, char *time2){
	time_t t1 = GetTime(time1);
	time_t t2 = GetTime(time2);

	return difftime(GetTime(time1), GetTime(time2));
}

int CompareDate(char *date1, char *date2){
	int *a = SplitDate(date1);
	int *b = SplitDate(date2);
	
	if(a[2] < b[2]) return -1;
	else if(a[2] > b[2]) return 1;
	else{
		if(a[1] < b[1]) return -1;
		else if(a[1] > b[1]) return 1;
		else{
			if(a[0] < b[0]) return -1;
			else if(a[0] > b[0]) return 1;
			else return 0;
		}
	}
	return 0;
}


