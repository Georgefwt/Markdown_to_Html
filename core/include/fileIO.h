#ifndef __FILEIO_H__
#define __FILEIO_H__
#include <iostream>
using namespace std;

class fileIO
{
private:
    
public:
    int ERROR_CODE;
    fileIO();
    ~fileIO();
    int open_file(FILE **fp, const string file_dir1);
    int create_file(FILE **fp, const string file_dir1);
    void close_files(FILE **fpa, FILE **fpb);
};

#endif