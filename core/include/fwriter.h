#ifndef __FWRITER_H__
#define __FWRITER_H__
#include <iostream>
class fwriter
{  
public:
    char title[257];
    int ERROR_CODE;
    fwriter();
    ~fwriter();
    void name_output(char *new_name, const char *old_name, const char *format);//get the filename of output file
    void add_head(FILE *out_fp, const char *css_file);
    void add_foot(FILE *out_fp);
};

#endif