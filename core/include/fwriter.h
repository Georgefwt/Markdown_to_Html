#ifndef __FWRITER_H__
#define __FWRITER_H__
#include <iostream>
using namespace std;

class fwriter
{  
public:
    string title;
    int ERROR_CODE;
    fwriter();
    ~fwriter();
    void name_output(string &new_name, const string old_name, const string format);//get the filename of output file
    void add_head(FILE *out_fp, const char *css_file);
    void add_foot(FILE *out_fp);
};

#endif