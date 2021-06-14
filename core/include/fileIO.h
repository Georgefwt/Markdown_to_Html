#ifndef __FILEIO_H__
#define __FILEIO_H__
#include <iostream>
class fileIO
{
private:
    
public:
    int ERROR_CODE;
    fileIO();
    ~fileIO();
    int open_file(FILE **fp, const char *file_dir);
    int create_file(FILE **fp, const char *file_dir);
    void close_files(FILE **fpa, FILE **fpb);
};

#endif