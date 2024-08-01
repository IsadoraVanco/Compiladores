#include "parser.h"
#include "tokens.h"
#include <iostream>
#include <FlexLexer.h>

using std::cout;
using std::endl;

void Parser::start()
{
    while ((numeroToken = scanner.yylex()) != 0)
    {
        switch (numeroToken)
        {
            case IF:
                cout << "IF" << endl;
                break;
            case THEN:
                cout << "THEN" << endl;
                break;
            case ELSE:
                cout << "ELSE" << endl;
                break;
            case ID:
                cout << "ID(" << scanner.YYText() << ")" << endl;
                break;
            case NUMERO:
                cout << "NUMERO(" << scanner.YYText() << ")" << endl;
                break;
            case OPERADOR:
                cout << "OPERADOR(" << scanner.YYText() << ")" << endl;
                break;
        }
    }
}
