#include <iostream>
#include "include/parser.h"
#include "include/fwriter.h"
#include <string>
#define MAX 1000
using std::string;
#define CSS_PATH "css/style.css"

parser::parser()
{
    isNewLine = 1;
    isHr = 0;
	isQuote = 0;
    isCode = 0;
    isList = 0;
    isBlock = 0;
	isOrderList = 0;
}

parser::~parser()
{
}

int parser::onUrl(FILE *out_fp, FILE *in_fp) {
	// this function deals with url
	// if what it deals with is a url
	// it will return 0
	// if what it deals with is not a url
	// it will return from 1 to 5
	// if what it deals with is not a url and onUrl gets a '\n'
	// it will return 2 or 4

	char ch;
    string name;
    string url;
	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == ']' || ch == '\n') {
			break;
		}
        name.push_back(ch);
	}

	if (ch != ']') {
		fprintf(out_fp, "[%s%c", name.c_str(), ch);
		return 1;
	}

	while ((ch = fgetc(in_fp)) == ' ') {}

	if (ch != '(') {
		if (ch == '\n') {
			fprintf(out_fp, "[%s]", name.c_str());
			return 2;
		}
		else {
			fprintf(out_fp, "[%s]%c", name.c_str(), ch);
			return 3;
		}
	}

	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == ')' || ch == '\n') {
			break;
		}
        url.push_back(ch);
	}

	if (ch != ')') {
		if (ch == '\n') {
			fprintf(out_fp, "[%s](%s", name.c_str(), url.c_str());
			return 4;
		}
		else {
			fprintf(out_fp, "[%s](%s%c", name.c_str(), url.c_str(), ch);
			return 5;
		}
	}

	fprintf(out_fp, "<a href=\"%s\">%s</a>", url.c_str(), name.c_str());
	return 0;
}

int parser::onHeader(FILE *out_fp, FILE *in_fp) {
	// this function deals with Header
	// from <h1> to <h6>
	// if what it deals with is a header
	// it will return 0
	// if what it deals with is not a header
	// it will return 1

	int count = 1, onUrlstate;
	char ch;

	while ((ch = fgetc(in_fp)) == '#') {
		++count;
	}
	if (count > 6) {
		while (count--) {
			fprintf(out_fp, "#");
		}
		fprintf(out_fp, "%c", ch);
		return 1;
	}

	fprintf(out_fp, "<h%d>", count);

	while (ch != '\n' && ch != EOF) {
		if (ch == '[') {
			onUrlstate = onUrl(out_fp, in_fp);
			if (onUrlstate == 2 || onUrlstate == 4) {
				// there is a '\n'
				break;
			}
		}
		else {
			fprintf(out_fp, "%c", ch);
		}
		ch = fgetc(in_fp);
	}

	fprintf(out_fp, "</h%i>\n", count);
	return 0;
}

int parser::onHr(FILE *out_fp, FILE *in_fp) {
	int count = 1;
	char ch;

	ch = fgetc(in_fp);
	while (ch != '\n' && ch == '-') {
		++count;
		ch = fgetc(in_fp);
	}
	if (count >= 3) {
		fprintf(out_fp, "\n<hr/>\n");
		isHr = 1;
	}
	else {
		while (count--) {
			fprintf(out_fp, "-");
		}
		fputc(ch, out_fp);
		return 1;
	}
	return 0;
}

int parser::onImg(FILE *out_fp, FILE *in_fp) {//start with !
	char ch;
    string name;
    string url;
	ch = fgetc(in_fp);
	if (ch != '[') {
		fprintf(out_fp, "!%c", ch); //not a image
		return 1;
	}
	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == ']' || ch == '\n') {
			break;
		}
        name.push_back(ch);
	}

	if (ch == '\n' || ch == EOF) {
		fprintf(out_fp, "![%s%c", name.c_str(), ch);
		return 2;
	}
	
	while ((ch = fgetc(in_fp)) == ' ') {}
	if (ch != '(') {
		fprintf(out_fp, "![%s]%c", name.c_str(), ch);
		return 3;
	}

	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == ')' || ch == '\n') {
			break;
		}
        url.push_back(ch);
	}

	if (ch != ')') {
		fprintf(out_fp, "![%s](%s%c", name.c_str(), url.c_str(), ch);
		return 4;
	}

	fprintf(out_fp, "<img src=\"%s\" alt=\"%s\">", url.c_str(), name.c_str());
	return 0;
}

int parser::onBold(FILE *out_fp, FILE *in_fp) {
	int i = 0;
	char ch;
    string content;
	while ((ch = fgetc(in_fp)) == ' ') {}
	if (ch == '*') {
		ch = fgetc(in_fp);
		if (ch == '*') {
			fprintf(out_fp, "<strong></strong>");
			return 1;
		}
		else {
			fprintf(out_fp, "<i>*</i>");
			return 2;
		}
	}
	else if (ch == '\n') {
		fputc(ch, out_fp);
		return 3;
	}
    content.push_back(ch);
	//content[i++] = ch;
	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == '*' || ch == '\n' || i > 999) {
			break;
		}
        content.push_back(ch);
	}

	if (ch != '*') {
		fprintf(out_fp, "%s%c", content.c_str(), ch);
		return 4;
	}
	
	ch = fgetc(in_fp);
	if (ch != '*') {
		fprintf(out_fp, "<i>*%s</i>%c", content.c_str(), ch);
		return 5;
	}

	fprintf(out_fp, "<strong>%s</strong>", content.c_str());
	return 0;
}

int parser::onIorB(FILE *out_fp, FILE *in_fp) {
	// this function deal with italic or bold style
	// if what it deals with is bold style
	// it will return -1
	// if what it deals with is italic style
	// it will return -2

	int i = 0, state, isSpace;
	char ch;
	string content;
	ch = fgetc(in_fp);
	if (ch == '*') {
		state = onBold(out_fp, in_fp);
		if (state != 0) {
			return state;
		}
		else {
			return -1;
		}
	}
	else if (ch == ' ') {
		isSpace = 1;
	}
	else {
		isSpace = 0;
        content.push_back(ch);
	}
	if (isSpace) {
		while ((ch = fgetc(in_fp)) == ' ') {}
        content.push_back(ch);
	}
	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == '*' || ch == '\n' || i> 999) {
			break;
		}
        content.push_back(ch);
	}

	if (ch != '*') {
		fprintf(out_fp, "*%s%c", content.c_str(), ch);
		return 10;
	}

	fprintf(out_fp, "<i>%s</i>", content.c_str());
	return -2;
}

int parser::onList(FILE *out_fp, FILE *in_fp,const int sign) {
	int onUrlstate;
	char ch;
	if (sign == 1) {
		fprintf(out_fp, "<ul>\n");
	}
	if (sign == 1 || sign == 2) {
		fprintf(out_fp, "<li>");
		ch = fgetc(in_fp);
		while (ch != '\n' && ch != EOF) {
			if (ch == '[') {
				onUrlstate = onUrl(out_fp, in_fp);
				if (onUrlstate == 2 || onUrlstate == 4) {
					// there is a '\n'
					break;
				}
			}
			else {
				fprintf(out_fp, "%c", ch);
			}
			ch = fgetc(in_fp);
		}

		fprintf(out_fp, "</li>\n");
	}

	if (sign == 3) {
		fprintf(out_fp, "</ul>\n");
	}
	return 0;
}

int parser::onOrdList(FILE *out_fp, FILE *in_fp,const int sign){
	printf("onordlist!!!\n");
	printf("sign:%d\n",sign);
	int onUrlstate;
	char ch;
	if (sign == 1) {
		fprintf(out_fp, "<ol>\n");
	}
	if (sign == 1 || sign == 2) {
		fprintf(out_fp, "<li>");
		//while ((ch = fgetc(in_fp)) == ' ') {}
		ch = fgetc(in_fp);
		while (ch != '\n' && ch != EOF) {
			if (ch == '[') {
				onUrlstate = onUrl(out_fp, in_fp);
				if (onUrlstate == 2 || onUrlstate == 4) {
					// there is a '\n'
					break;
				}
			}
			else {
				fprintf(out_fp, "%c", ch);
			}
			ch = fgetc(in_fp);
		}
		fprintf(out_fp, "</li>\n");
	}
	if (sign == 3) {
		fprintf(out_fp, "</ol>\n");
	}
	return 0;
}

int parser::onNumber(FILE *out_fp, FILE *in_fp, const int sign){
	// if what it deal with is normal number
	// it will return -1
	// and if what it deal with is a ordlist
	// it will return -3
	printf("onNumber!!!\n");
	int state;
	char ch;
    string content;
	char tmpch=fgetc(in_fp);
	if (tmpch == '.'){
		char tmpch2=fgetc(in_fp);
		if (tmpch2==' '){
			isOrderList = 1;
			state = onOrdList(out_fp,in_fp,sign);
			if (state == 0)
				return -3;
			else {
				return state;
			}
		}
		else{
			fprintf(out_fp, "%c",ch);
			fprintf(out_fp, "%c",tmpch);
			fprintf(out_fp, "%c",tmpch2);
			isOrderList = 0;
		}
	}
	else{
		fprintf(out_fp, "%c",ch);
		fprintf(out_fp, "%c",tmpch);
		isOrderList = 0;
	}
	return -1;
}

int parser::onAster(FILE *out_fp, FILE *in_fp, const int sign) {
	// if what it deal with is bold style
	// it will return -1
	// and if what it deal with is italic style
	// it will return -2
	// and if what it deal with is a list
	// it will return -3

	int state;
	char ch;
    string content;

	ch = fgetc(in_fp);
	if (ch == ' ') { //situration:|* |,means is a list
		state = onList(out_fp, in_fp, sign);
		if (state == 0) {
			return -3;
		}
		else {
			return state;
		}
	}
	else if (ch == '*') {//situration:|**|,means bold
		fputc('\n', out_fp);
		state = onBold(out_fp, in_fp);
		if (state == 0) {
			return -1;
		}
		else {
			return state;
		}
	}
	else if (ch == '\n') {
		fprintf(out_fp, "<p>*</p>\n");
	}
    content.push_back(ch);
	
	while ((ch = fgetc(in_fp)) != EOF) {
		if (ch == '*' || ch == '\n') {
			break;
		}
        content.push_back(ch);
	}

	if (ch != '*') {
        fprintf(out_fp, "<p>*%s</p>\n", content.c_str());//normal *
		return 10;
	}

	fprintf(out_fp, "<p><i>%s</i>", content.c_str()); //italic
	return -2;

}

void onSpecialChar(FILE *out_fp, const char ch) {
	if (ch == '&') fprintf(out_fp, "&amp;");
	else if (ch == '<') fprintf(out_fp, "&lt;");
    else if (ch == '>') fprintf(out_fp,"&gt;");
}

int parser::onCode(FILE *out_fp, FILE *in_fp) {
	int j, isSpace=0, isNewLine=0,isCodeBlock=0;
	char ch;
    string content;
	ch = fgetc(in_fp);
	if (ch == ' ') {
		isSpace = 1;
	}
    if (ch == '`'){
        if(ch= fgetc(in_fp) == '`'){
            isCodeBlock=1;
            //****对于代码格式的支持，先留一手
            ch=fgetc(in_fp);//把\n吃掉
            if(ch='\r') fgetc(in_fp);//CRLF
            //****
        }
        else{
            content.push_back(ch);
        }
    }
	else {
		isSpace = 0;
        content.push_back(ch);
	}
	if (isSpace) {
		while ((ch = fgetc(in_fp)) == ' ') {}//jump the space
        content.push_back(ch);
	}

	while ((ch = fgetc(in_fp)) != EOF) {
        if (isCodeBlock!=1){
            if (isNewLine && ch == '\n') {
                break;
            }
            else if (!isNewLine && ch == '\n') {
                isNewLine = 1;
            }
            else {
                isNewLine = 0;
                if (ch == '`') {
                    break;
                }
            }
            content.push_back(ch);
        }
        else{
            if (ch == '`'){
                fgetc(in_fp);
                fgetc(in_fp);
                break;
            }
            content.push_back(ch);
        }
	}
	if (ch != '`') {
		fprintf(out_fp, "`%s%c", content.c_str(), ch);
		return 1;
	}
    if(isCodeBlock==1) fprintf(out_fp, "<pre>\n<code>\n");
	else fprintf(out_fp, "<code>");
	for (j=0; j<content.length(); j++) {
		if (content[j] == '&' || content[j] == '<') {
			onSpecialChar(out_fp, content[j]);
		}
		else {
			fputc(content[j], out_fp);
		}
	}

    if(isCodeBlock==1) {
        fprintf(out_fp,"</code>\n</pre>\n");
        fgetc(in_fp);
        fgetc(in_fp);
    }
	else fprintf(out_fp, "</code>");
	return 0;
}

int parser::onQuote(FILE *out_fp, const int sign) {
	// this function deals with blockquote
	if (sign == 1) {
		fprintf(out_fp, "<blockquote>\n");
	}
	else if (sign == 2) {
		fprintf(out_fp, "\n</blockquote>\n");
	}
	return 0;
}

int parser::onBlock(FILE *out_fp, FILE *in_fp,const int sign) {
	// this function deals with code block
	// it works the same as onList
	int j;
	char ch;
    string content;
	
    if (sign == 1) {
        fprintf(out_fp, "<pre>\n<code>\n");
    }

    if (sign == 1 || sign == 2) {
        while ((ch = fgetc(in_fp)) != EOF) {
            if (ch == '\n') {
                break;
            }
            content.push_back(ch);
        }

        for (j=0; j<content.length(); j++) {
            if (content[j] == '&' || content[j] == '<') {
                onSpecialChar(out_fp, content[j]);
            }
            else {
                fputc(content[j], out_fp);
            }
        }
        fputc('\n', out_fp);
    }

    if (sign == 3) {
        fprintf(out_fp, "</code>\n</pre>\n");
    }
	return 0;
}

bool is_number(char ch){
	if ('0'<= ch && ch <= '9') return true;
	return false;
}

void parser::mdparser(FILE *out_fp, FILE *in_fp,fwriter& myfw){
    myfw.add_head(out_fp, CSS_PATH);
    //handle List Quote Header
    while ((ch = fgetc(in_fp)) != EOF) {
		if (isNewLine && ch != '*' && isList) {
			onList(out_fp, in_fp, 3);
			isList = 0;
		}
		if (isNewLine && !is_number(ch) && isOrderList) {
			onOrdList(out_fp, in_fp, 3);
			isOrderList = 0;
		}
		if (isNewLine && ch != '\t' && isBlock) {
			onBlock(out_fp, in_fp, 3);
			isBlock = 0;
		}
		if (isNewLine && ch != '>' && isQuote) {
			onQuote(out_fp, 2);
			isQuote = 0;
		}

		if (isNewLine &&
			(ch == '>' ||  ch == '#' || ch == '-' || ch == '*' || ch == '\t'|| ch=='\n'|| is_number(ch))) {
			if (ch == '>') {
				if (isQuote == 0) {
					onQuote(out_fp, 1);
					isQuote = 1;
				}
			}
			else if (ch == '#') {
				onHeader(out_fp, in_fp);
				ch = '\n';
			}
			else if (ch == '-') {
				onHr(out_fp, in_fp);
			}
			else if (ch == '*') {
				int state;
				if (isList == 0) {
					state = onAster(out_fp, in_fp, 1);
				}
				else {
					state = onAster(out_fp, in_fp, 2);
				}
				if (state == -3) { // if it is a list
					ch ='\n';
					isList = 1;
				}
			}
			else if (is_number(ch)){
				int state;
				if (isOrderList == 0) {
					state = onNumber(out_fp, in_fp, 1);
				}
				else {
					state = onNumber(out_fp, in_fp, 2);
				}
				if (state == -3) { // if it is a list
					ch ='\n';
					isList = 1;
				}
			}
			else if(ch == '\n'){
				fprintf(out_fp, "<p></p>\n");
			}
			else if (ch == '\t') {
				if (isBlock == 0) {
					onBlock(out_fp, in_fp, 1);
				}
				else {
					onBlock(out_fp, in_fp, 2);
				}
				ch = '\n';
				isBlock = 1;
				isNewLine = 1;
			}
			else {
				fputc(ch, out_fp);
			}
		}
		else if (ch == '[') {
			if (isNewLine) {
				fprintf(out_fp, "<p>");
			}
            onUrl(out_fp, in_fp);
        }
		else if (ch == '!') {
			if (isNewLine) {
				fprintf(out_fp, "<p>");
			}
			onImg(out_fp, in_fp);
		}
		else if (ch == '`') {
			if (isNewLine) {
				fprintf(out_fp, "<p>");
			}
			onCode(out_fp, in_fp);
		}
		else if (ch == '*') {
			if (isNewLine) {
				fprintf(out_fp, "<p>%c", ch);
			}
			onIorB(out_fp, in_fp);
			// if ch is a asterisk and not in a new line,
			// it can be italic style
			// or it can be bold style
		}
        else if (ch != '\n') {
			if (isNewLine && !isQuote) {
				fprintf(out_fp, "%c", ch);
				//printf("heeeee!\n");
			}
			else {
            	fputc(ch, out_fp);
			}
        }

        if (ch != '\n') {
            isNewLine = 0;
        }
        else {
			if (!isHr && !isQuote && !isNewLine) {
				fprintf(out_fp, "\n");
			}
			isNewLine = 1;
			isHr = 0;
        }
	}
	myfw.add_foot(out_fp);
}