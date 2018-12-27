#include "parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    prev_total = 0;
    prev_idle = 0;
}
