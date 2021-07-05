#include "include/fileIO.h"
#include <iostream>
#include<string.h>
using namespace std;

fileIO::fileIO()
{
}

fileIO::~fileIO()
{
}

int fileIO::open_file(FILE **fp, const string file_dir1) {
	char file_dir[100] ;
	//strcpy(file_dir, file_dir1.c_str());
	for (int i = 0; i < file_dir1.length();i++)
		file_dir[i] = file_dir1[i];
	file_dir[file_dir1.length()] ='\0';
	
	if ((*fp = fopen(file_dir, "r")) == NULL) {
		ERROR_CODE = 1;
		cout << endl << "error!" << endl << "ERROR_CODE:" << ERROR_CODE << "\tcan't open style file " << file_dir << endl ;
		return 1;
	}
	return 0;
}

int fileIO::create_file(FILE **fp, const string file_dir1) {
	char file_dir[100] ;
	//strcpy(file_dir, file_dir1.c_str());
	for (int i = 0; i < file_dir1.length();i++)
		file_dir[i] = file_dir1[i];
	file_dir[file_dir1.length()] ='\0';

	if ((*fp = fopen("index.html", "w")) == NULL) {
		ERROR_CODE = 2;
		cout << endl << "error!" << endl << "ERROR_CODE:" << ERROR_CODE << "\tcan't open style file " << file_dir << endl ;
		return 1;
	}
	return 0;
}

void fileIO::close_files(FILE **fpa, FILE **fpb) {
	if (!ERROR_CODE) {
		cout << endl << "done" << endl;
	}
	fclose(*fpa);
	fclose(*fpb);
	*fpa = NULL;
	*fpb = NULL;
}