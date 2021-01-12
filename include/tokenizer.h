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
        const char *str;
        int str_len;
        int current_offset = 0;
        int line = 1, column = 1;

        void skip_ws();

        void forward();

    public:
        token eof_token(int l, int c), error_token(int l, int c);

        static token_unit *token_units[];

        tokenizer(const char *str, int str_len);

        token next_token();
    };
};

#endif //ARGON_TOKENIZER_H
