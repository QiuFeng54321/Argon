//
// Created by mac on 2021/1/12.
//

#include "token_unit.h"

namespace argon {
    token_unit::token_unit() {}

    bool token_unit::matches(const char *from, int current) { return false; }

    bool token_unit::completed(const char *from, int next) { return false; }

    bool token_unit::takeover(const char *from, int next) {return false;}

    char token_unit::type() { return ' '; }

    bool int_token::matches(const char *from, int current) {
        auto current_char = from[current];
        // 0x, 0b, 0o convention
        if (current == 2 and from[0] == '0') {
            if (current_char == 'x' or current_char == 'b' or current_char == 'o') return true;
        }
        return current_char >= '0' and current_char <= '9';
    }

    bool int_token::completed(const char *from, int next) {
        return not matches(from, next);
    }

    char int_token::type() { return 'I'; };

    char decimal_token::type() {
        return 'D';
    }

    // TODO: Add a check that only decimals with one dot should be matched
    bool decimal_token::matches(const char *from, int current) {
        auto current_char = from[current];
        return current_char >= '0' and current_char <= '9' or current_char == '.';
    }

    bool decimal_token::completed(const char *from, int next) {
        // The token read should contain digits and a dot
        return not matches(from, next) and takeover(from, next);
    }

    bool decimal_token::takeover(const char *from, int next) {
        // The so-far-read token should contain a dot so it can be confirmed as a decimal.
        for (int i = 0; i <= next; i++) {
            if (from[i] == '.') return true;
        }
        return false;
    }

    bool identity_token::matches(const char *from, int current) {
        auto current_char = from[current];
        return (current_char >= 'A' and current_char <= 'Z') or
               (current_char >= 'a' and current_char <= 'z') or
               current_char == '_' or current_char == '$' or
               (current != 0 and current_char >= '0' and current_char <= '9');

    }

    bool identity_token::completed(const char *from, int next) {
        return not matches(from, next);
    }

    char identity_token::type() { return 'i'; }
}