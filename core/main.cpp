#include "include/parser.h"
#include "include/fwriter.h"
#include "include/fileIO.h"
#include "iostream"
#include "string"

void get_input(string &file_dest) {
	printf("Please input the directory of the target file:\n");
	getline(cin, file_dest) ;
}

int main(){
	FILE *in_fp, *out_fp;
	string input, output;
    //*****TODO******
	//int code_color_scheme;
	// get the file address of input file
    //add different color scheme
    //**************
	get_input(input);
    fileIO myfio;
    parser myparser;
    fwriter myfw;

	string format = ".html";

	myfw.name_output(output, input, format);
    myfio.open_file(&in_fp,input);
    myfio.create_file(&out_fp,output);
	
	myparser.mdparser(out_fp, in_fp,myfw);

	myfio.close_files(&in_fp, &out_fp);
	return 0;
}