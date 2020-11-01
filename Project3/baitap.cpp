#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include<fstream>

using namespace std;
const char STX = '\002', ETX = '\003';
 
int compareStrings(const void *a, const void *b) {
    char *aa = *(char **)a;
    char *bb = *(char **)b;
    return strcmp(aa, bb);
}
 
int bwt(const char *s, char r[]) {
    int i, len = strlen(s) + 2;
    char *ss, *str;
    char **table;
    if (strchr(s, STX) || strchr(s, ETX)) return 1;
    ss = (char *)calloc(len + 1, sizeof(char ));
    sprintf(ss, "%c%s%c", STX, s, ETX);
    table = (char **)malloc(len * sizeof(char));
    for (i = 0; i < len; ++i) {
        str = (char *)calloc(len + 1, sizeof(char));
        strcpy(str, ss + i);
        if (i > 0) strncat(str, ss, i);
        table[i] = str;
    }
    qsort(table, len, sizeof(const char *), compareStrings);
    for(i = 0; i < len; ++i) {
        r[i] = table[i][len - 1];
        free(table[i]);
    }
    free(table);
    free(ss);
    return 0;
}
 
void ibwt(const char *r, char s[]) {
    int i, j, len = strlen(r);
    char **table =(char **) malloc(len * sizeof(char ));
    for (i = 0; i < len; ++i) table[i] = (char *)calloc(len + 1, sizeof(char));
    for (i = 0; i < len; ++i) {
        for (j = 0; j < len; ++j) {                        
            memmove(table[j] + 1, table[j], len);
            table[j][0] = r[j];
        }
        qsort(table, len, sizeof(const char *), compareStrings);
    }
    for (i = 0; i < len; ++i) {
        if (table[i][len - 1] == ETX) {
            strncpy(s, table[i] + 1, len - 2);
            break;
        }
    }
    for (i = 0; i < len; ++i) free(table[i]);
    free(table);
}
 
void makePrintable(const char *s, char t[]) {
    strcpy(t, s);
    for ( ; *t != '\0'; ++t) {
        if (*t == STX) *t = '$';
        else if (*t == ETX) *t = '@';
    }
}
 
int main() {
    int i, res, len;
    char *t, *r, *s;
    fstream f;
	f.open("test.txt", ios::in);
	string data;
	string line;
	while (!f.eof())
	{
		getline(f, line);
		data += line;
	}
    char* input_text = new char[data.size()+1];
	copy(data.begin(), data.end(), input_text);
	input_text[data.size()] = '\0';
    int len_text = strlen(input_text);     
    t = (char *)calloc(len_text + 1, sizeof(char));
    makePrintable(input_text, t);
    printf("%s\n", t);
    printf(" --> ");
    r =(char *) calloc(len + 3, sizeof(char));
    res = bwt(input_text, r);
    if (res == 1) {
            printf("ERROR: String can't contain STX or ETX\n");
        }
        else {
            makePrintable(r, t);
            printf("%s\n", t);
        }
        s = (char *)calloc(len + 1, sizeof(char));
        ibwt(r, s);
        makePrintable(s, t);
        printf(" --> %s\n\n", t);
        free(t);
        free(r);
        free(s);
    return 0;
}
	
  
