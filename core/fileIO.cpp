#include "include/fileIO.h"
fileIO::fileIO()
{
}

fileIO::~fileIO()
{
}

int fileIO::open_file(FILE **fp, const char *file_dir) {
	if ((*fp = fopen(file_dir, "r")) == NULL) {
		ERROR_CODE = 1;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, file_dir);
		return 1;
	}
	return 0;
}

int fileIO::create_file(FILE **fp, const char *file_dir) {
	if ((*fp = fopen(file_dir, "w")) == NULL) {
		ERROR_CODE = 2;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, file_dir);
		return 1;
	}
	return 0;
}

void fileIO::close_files(FILE **fpa, FILE **fpb) {
	if (!ERROR_CODE) {
		printf("\nDone!\n");
	}
	fclose(*fpa);
	fclose(*fpb);
	*fpa = NULL;
	*fpb = NULL;
}