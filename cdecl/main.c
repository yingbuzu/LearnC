
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <ctype.h>

static jmp_buf  _jmpbuf;
#define _errretc(ec,msg,...)    do { \
    fprintf(stderr, "\n(%s:%d) " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    longjmp(_jmpbuf, ec); } while(0)

#define _errret(msg,...)    _errretc(2,msg,##__VA_ARGS__)

#define MAX_TOKENNAME_SZ    64
#define MAX_TOKEN_SZ        128
#define MAX_INT_SZ          21

#define TAG_ID      0
#define TAG_TYPE    1
#define TAG_QUAL    2
#define TAG_NUM     3
#define TAG_ST      4
#define TAG_END     5

struct token {
    int type;
    char name[MAX_TOKENNAME_SZ + 16];
};

int top = -1;

static struct token _alltoks[MAX_TOKEN_SZ];
static struct token _curtok;

#define push_tok(t)   _alltoks[++top] = (t)
#define pop_tok()     _alltoks[top--]
#define top_tok()     _alltoks[top]

static int chk_tok()
{
    char tn[MAX_TOKENNAME_SZ + 4];
    sprintf(tn, "|%s|", _curtok.name);

    if (strstr("|const|volatile|", tn))
        return TAG_QUAL;

    if (strstr("|void|char|short|int|long|float|double|signed|unsigned|", tn))
        return TAG_TYPE;

    if (strstr("|struct|union|enum|", tn))
        return TAG_ST;

    return TAG_ID;
}

static int gettoken_low()
{
    char *s = _curtok.name;

    while ((*s = getchar()) != EOF) {
        if (' ' != *s && '\t' != *s)
            break;
    }
    if ('\n' == *s || '\r' == *s || EOF == *s) {
        _curtok.name[0] = 0;
        return _curtok.type = TAG_END;
    }

    if (isdigit(*s)) {
        while (isdigit(* ++s = getchar()) && s < &_curtok.name[MAX_INT_SZ-1])
            ;
        ungetc(*s, stdin);
        *s = 0;
        return _curtok.type = TAG_NUM;
    }

    if ('*' == *s) {
        strcpy(_curtok.name, "pointer to");
        return _curtok.type = '*';
    }

    if (isalnum(*s) || *s == '_') {
        for (; (isalnum(*s) || *s == '_') && s < &_curtok.name[MAX_TOKENNAME_SZ - 1]; *++s = getchar())
            ;

        if (isalnum(*s) || *s == '_') {
            *s = 0;
            _errret("identifier \"%s...\" is too long!", _curtok.name);
        }

        ungetc(*s, stdin);
        *s = 0;
        return _curtok.type = chk_tok();
    }

    _curtok.name[0] = *s;
    _curtok.name[1] = 0;
    return _curtok.type = *s;
}

static int gettoken()
{
    char buf[16 + MAX_TOKENNAME_SZ];

    int r = gettoken_low();
    if (r != TAG_ST) return r;

    strcpy(buf, _curtok.name);
    if (TAG_ID != gettoken_low())
        _errret("invalid \"%s\" type", buf);

    strcat(buf, " ");
    strcat(buf, _curtok.name);
    strcpy(_curtok.name, buf);
    return _curtok.type = TAG_TYPE;
}

static void _chk_arr()
{
    int t = gettoken();
    if (t != TAG_NUM && t != ']')
        _errret("invalid array token: %s", _curtok.name);

    printf("array");
    if (t == TAG_NUM)
        printf("[%d] of ", atoi(_curtok.name));
    else
        printf("[] of ");

    if (t != ']' && gettoken() != ']')
        _errret("expect ']' end the array");

    gettoken();

}

static void _chk_func() //FIXME: just dump function args
{
    int x = 0;

    printf("function(");
    while(TAG_END != gettoken()) {

        if (_curtok.type == ')') {
            if (x == 0) break;
            --x;
        }

        if (_curtok.type == '(') ++x;


        if (_curtok.type <= TAG_END)
            printf("%s ", _curtok.name);
        else
            printf("%c", _curtok.type);
    }
    printf(") returning ");

    gettoken();
}

static void chk_ptr()
{
    while(top_tok().type == '*' && top > 0)
        printf("%s ", pop_tok().name);

    if (top_tok().type == '*' && top == 0)
        _errret("can't start with a '*'");
}


static void _chk_decl()
{
    if (_curtok.type == '[') _chk_arr();
    if (_curtok.type == '(') _chk_func();

    chk_ptr();

    while (top >= 0) {
        if (top_tok().type != '(') {
            printf("%s ", pop_tok().name);
            continue;
        }
        pop_tok();
        if (_curtok.type!=')')
            _errret("expect ')'");

        gettoken();
        _chk_decl();
    }
}


int main()
{
    setjmp(_jmpbuf);

    printf("\n===================\n"
           "enter a c declarator: ");

    top = -1;
    gettoken();
    if (_curtok.type == TAG_END) {
        printf("Quit!\n");
        return 0;
    }

    while (_curtok.type != TAG_ID) {
        push_tok(_curtok);
        gettoken();
    }
    printf("%s : ", _curtok.name);

    gettoken();
    _chk_decl();
    printf("\n");

    longjmp(_jmpbuf, 99);
    return 0;
}
