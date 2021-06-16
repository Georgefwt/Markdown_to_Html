#ifndef __PARSER_H__
#define __PARSER_H__
#include <iostream>
#include "fwriter.h"
class parser
{
    
public:
    char ch;
	int isNewLine, isQuote, isCode, isList, isBlock,isHr;
    parser();
    ~parser();
    int onUrl(FILE *out_fp, FILE *in_fp);
    int onHeader(FILE *out_fp, FILE *in_fp);
    int onHr(FILE *out_fp, FILE *in_fp);
    int onImg(FILE *out_fp, FILE *in_fp);
    int onBold(FILE *out_fp, FILE *in_fp);
    int onIorB(FILE *out_fp, FILE *in_fp);
    int onList(FILE *out_fp, FILE *in_fp,const int sign);
    int onAster(FILE *out_fp, FILE *in_fp, const int sign);
    int onCode(FILE *out_fp, FILE *in_fp);
    int onQuote(FILE *out_fp, const int sign);
    int onBlock(FILE *out_fp, FILE *in_fp,const int sign);
    void mdparser(FILE *out_fp, FILE *in_fp,fwriter& myfw);
};

#endif