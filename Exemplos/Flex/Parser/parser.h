#ifndef _PARSER_H_
#define _PARSER_H_

#include <FlexLexer.h>

class Parser
{
    private:
    yyFlexLexer scanner;
    int numeroToken;

    public:
    void start();
};

#endif