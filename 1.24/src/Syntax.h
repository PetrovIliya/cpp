#include "../config/operatorCodes.h"

class Syntax
{
public:

    bool table[8][8];

    Syntax()
    {
        table[BEGIN][BEGIN] = true;
        table[BEGIN][END] = true;
        table[BEGIN][REPEAT] = true;
        table[BEGIN][UNTIL] = true;
        table[BEGIN][RECORD] = false;
        table[BEGIN][CASE] = true;
        table[BEGIN][CONST] = false;
        table[BEGIN][TYPE] = false;
        table[BEGIN][OF] = false;
        table[END][BEGIN] = true;
        table[END][END] = true;
        table[END][REPEAT] = true;
        table[END][UNTIL] = true;
        table[END][RECORD] = false;
        table[END][CASE] = true;
        table[END][CONST] = true;
        table[END][TYPE] = true;
        table[END][OF] = false;
        table[REPEAT][BEGIN] = true;
        table[REPEAT][END] = true;
        table[REPEAT][REPEAT] = true;
        table[REPEAT][UNTIL] = true;
        table[REPEAT][RECORD] = false;
        table[REPEAT][CASE] = true;
        table[REPEAT][CONST] = false;
        table[REPEAT][TYPE] = false;
        table[REPEAT][OF] = false;
        table[UNTIL][BEGIN] = true;
        table[UNTIL][END] = true;
        table[UNTIL][REPEAT] = true;
        table[UNTIL][UNTIL] = false;
        table[UNTIL][RECORD] = false;
        table[UNTIL][CASE] = true;
        table[UNTIL][CONST] = false;
        table[UNTIL][TYPE] = false;
        table[UNTIL][OF] = false;
        table[RECORD][BEGIN] = false;
        table[RECORD][END] = true;
        table[RECORD][REPEAT] = false;
        table[RECORD][UNTIL] = false;
        table[RECORD][RECORD] = false;
        table[RECORD][CASE] = false;
        table[RECORD][CONST] = false;
        table[RECORD][TYPE] = false;
        table[RECORD][OF] = false;
        table[CASE][BEGIN] = true;
        table[CASE][END] = true;
        table[CASE][REPEAT] = false;
        table[CASE][UNTIL] = false;
        table[CASE][RECORD] = false;
        table[CASE][CASE] = false;
        table[CASE][CONST] = false;
        table[CASE][TYPE] = false;
        table[CASE][OF] = true;
        table[CONST][BEGIN] = true;
        table[CONST][END] = true;
        table[CONST][REPEAT] = false;
        table[CONST][UNTIL] = false;
        table[CONST][RECORD] = false;
        table[CONST][CASE] = false;
        table[CONST][CONST] = false;
        table[CONST][TYPE] = false;
        table[CONST][OF] = false;
        table[TYPE][BEGIN] = true;
        table[TYPE][END] = false;
        table[TYPE][REPEAT] = false;
        table[TYPE][UNTIL] = false;
        table[TYPE][RECORD] = false;
        table[TYPE][CASE] = false;
        table[TYPE][CONST] = true;
        table[TYPE][TYPE] = false;
        table[TYPE][OF] = false;
        table[TYPE][BEGIN] = true;
        table[OF][END] = true;
        table[OF][REPEAT] = true;
        table[OF][UNTIL] = false;
        table[OF][RECORD] = false;
        table[OF][CASE] = true;
        table[OF][CONST] = false;
        table[OF][TYPE] = false;
        table[OF][BEGIN] = true;
        table[OF][OF] = false;
        table[NO_OPERATOR][BEGIN] = true;
        table[NO_OPERATOR][END] = false;
        table[NO_OPERATOR][REPEAT] = false;
        table[NO_OPERATOR][UNTIL] = false;
        table[NO_OPERATOR][RECORD] = true;
        table[NO_OPERATOR][CASE] = false;
        table[NO_OPERATOR][CONST] = false;
        table[NO_OPERATOR][TYPE] = true;
        table[NO_OPERATOR][OF] = false;
    }

    bool chek(int col, int row)
    {
        return table[col][row];
    }

};

