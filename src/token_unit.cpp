//
// Created by mac on 2021/1/12.
//

#include "token_unit.h"

namespace argon {
    bool int_token::matches(char *from, int current) {
        auto current_char = from[current];
        // 0x, 0b, 0o convention
        if (current == 2 and from[0] == '0') {
            if (current_char == 'x' or current_char == 'b' or current_char == 'o') return true;
        }
        return current_char >= '0' and current_char <= '9';
    }

    bool int_token::takeover(char *from, int current) { return false; }

    bool int_token::completed(char *from, int next) {
        auto next_char = from[next];
        // 0x, 0b, 0o convention
        if (next == 2 and from[0] == '0') {
            if (next_char == 'x' or next_char == 'b' or next_char == 'o') return false;
        }
        return next_char < '0' or next_char > '9';
    }
}