#include "include/fwriter.h"
#include "include/constant.h"
#include <cstring>
fwriter::fwriter()
{
	memset(title,0,sizeof(title));
}

fwriter::~fwriter()
{
}

void fwriter::name_output(char *new_name, const char *old_name, const char *format) {
	int dot, len = (int)strlen(old_name);
	strcpy(new_name, old_name);
	for (dot = len-1; new_name[dot] != '.'; dot--) {}
	new_name[dot] = '\0';
	//get filename
	for (--dot; new_name[dot] != '/' && dot >= 0; dot--) {}
	strcpy(title, new_name + dot + 1);
	strcat(new_name, format);
}

void add_style(FILE *out_fp, const char *css_file) {
	FILE *css_fp;
	char ch;

	fprintf(out_fp, "%s", "<style>\n");
	if ((css_fp = fopen(css_file, "rw+")) == NULL) {
		printf("\nerror!\ncan't open style file(%s)\n", css_file);
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
	fprintf(out_fp, "%s%s%s", head2, title, head3);
}

void fwriter::add_foot(FILE *out_fp) {
	fprintf(out_fp, "%s", foot);
}