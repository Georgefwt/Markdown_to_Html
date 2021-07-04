#ifndef __PARSER_H__
#define __PARSER_H__
#include <iostream>
#include "fwriter.h"
class parser
{
    
public:
    char ch;
	int isNewLine, isQuote, isCode, isList, isBlock,isHr,isOrderList,listspaces,isDel;
    parser();
    ~parser();
    int onUrl(FILE *out_fp, FILE *in_fp);
    int onHeader(FILE *out_fp, FILE *in_fp);
    int onHr(FILE *out_fp, FILE *in_fp);
    int onImg(FILE *out_fp, FILE *in_fp);
    int onBold(FILE *out_fp, FILE *in_fp);
    int onIorB(FILE *out_fp, FILE *in_fp,int sign);
    int onList(FILE *out_fp, FILE *in_fp,const int sign);
    int onOrdList(FILE *out_fp, FILE *in_fp,const int sign);
    int onNumber(FILE *out_fp, FILE *in_fp, const int sign,char ch);
    int onAster(FILE *out_fp, FILE *in_fp, const int sign);
    int onDash(FILE *out_fp, FILE *in_fp, const int sign);
    int onTilde(FILE *out_fp, FILE *in_fp);
    int onCode(FILE *out_fp, FILE *in_fp);
    int onQuote(FILE *out_fp, const int sign);
    int onBlock(FILE *out_fp, FILE *in_fp,const int sign);
    void mdparser(FILE *out_fp, FILE *in_fp,fwriter& myfw);
};

#endif