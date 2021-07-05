#include "include/fwriter.h"
#include "include/constant.h"
#include <cstring>
#include <iostream>
using namespace std;

fwriter::fwriter()
{
	//memset(title,0,sizeof(title));
	string title(257,0);
}

fwriter::~fwriter()
{
}

void fwriter::name_output(string &new_name, const string old_name, const string format) {
	//int dot, len = (int)strlen(old_name);
	int dot, len = old_name.length();
	//strcpy(new_name, old_name);
	new_name = old_name;
	for (dot = len-1; new_name[dot] != '.'; dot--) {}
	new_name[dot] = '\0';
	//get filename
	for (--dot; new_name[dot] != '/' && dot >= 0; dot--) {}
	//strcpy(title, new_name + dot + 1);
	title = new_name.substr(dot + 1);
	//strcat(new_name, format);
	new_name += format;
}

void add_style(FILE *out_fp, const char *css_file) {
	FILE *css_fp;
	char ch;

	fprintf(out_fp, "%s", "<style>\n");
	if ((css_fp = fopen(css_file, "rw+")) == NULL) {
		cout << endl << "error!" << endl <<  "can't open style file " << css_file << endl ;
	}
	else {
		while ((ch = fgetc(css_fp)) != EOF) {
			fputc(ch, out_fp);
		}
	}
	fprintf(out_fp, "%s", "\n</style>\n");
}

void fwriter::add_head(FILE *out_fp, const char *css_file) {
	fprintf(out_fp, "%s", head1);
	add_style(out_fp, css_file);
	fprintf(out_fp, "%s%s%s", head2, title.c_str(), head3);
}

void fwriter::add_foot(FILE *out_fp) {
	fprintf(out_fp, "%s", foot);
	cout << "Done.\n" << endl;
}