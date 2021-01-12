//
// Created by mac on 2021/1/12.
//

#ifndef ARGON_TOKENIZER_H
#define ARGON_TOKENIZER_H

#include "token.h"
#include "token_unit.h"
#include <vector>

namespace argon {
    class tokenizer {
    protected:
        std::vector<token> tokens;
        char *str;
        char *current_offset;
        int index = 0;
    public:
        static token_unit* token_units[];

        tokenizer(char *str);

        token next_token();
    };
};

#endif //ARGON_TOKENIZER_H
