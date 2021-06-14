#include "include/parser.h"
#include "include/fwriter.h"
#include "include/fileIO.h"
void get_input(char *file_dest) {
	printf("Please input the directory of the target file:\n");
	scanf("%s", file_dest);
}

// void get_color_scheme(int *style_type) {
// 	printf("Please input the color scheme of your code:\n");
// 	int i;
// 	for (i = 0; i < SYNTAX_MAX; i++) {
// 		printf("%d.%s\n", i, syntax[i]);
// 	}
// 	while (1) {
// 		scanf("%d", style_type);
// 		if (*style_type != 0 && *style_type != 1 && *style_type != 2) {
// 			printf("Style not found!\nPlease input one of the style numbers above.\n");
// 		}
// 		else {
// 			break;
// 		}
// 	}
// }

int main(){
	FILE *in_fp, *out_fp;
	char input[100], output[100];
	//int code_color_scheme;
	// get the file address of input file
	get_input(input);
	//get_color_scheme(&code_color_scheme);
	// get the name of the output file
	// which is exactly the same as input file but format
    fileIO myfio;
    parser myparser;
    fwriter myfw;
    
	myfw.name_output(output, input, ".html");
    myfio.open_file(&in_fp,input);
    myfio.create_file(&out_fp,output);
	
	myparser.mdparser(out_fp, in_fp,myfw);

	myfio.close_files(&in_fp, &out_fp);
	return 0;
}