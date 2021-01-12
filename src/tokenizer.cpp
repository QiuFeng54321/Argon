//
// Created by mac on 2021/1/12.
//

#include "tokenizer.h"

namespace argon {
    token_unit *tokenizer::token_units[]{
            new int_token
    };

    tokenizer::tokenizer(char *str) : str(str), current_offset(str) {

    }

    token tokenizer::next_token() {

    }
}