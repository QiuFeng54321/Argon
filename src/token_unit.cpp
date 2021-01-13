//
// Created by mac on 2021/1/12.
//

#include "token_unit.h"

namespace argon {

    char token_unit::type() { return ' '; }

    char int_token::type() { return 'I'; };

    char decimal_token::type() { return 'D'; }

    char identity_token::type() { return 'i'; }

    char keyword_token::type() { return _type; }

    token_unit::token_unit() {}

    bool token_unit::matches(const char *from, int current) { return false; }

    bool token_unit::completed(const char *from, int next) { return false; }

    bool token_unit::takeover(const char *from, int next) { return false; }


    bool int_token::matches(const char *from, int current) {
//        if (use_last_complete) {
//            use_last_complete = false;
//            return not (bool)last_complete_result;
//        }
        auto current_char = from[current];
        // 0x, 0b, 0o convention
        if (current == 2 and from[0] == '0') {
            if (current_char == 'x' or current_char == 'b' or current_char == 'o') return true;
        }
        return current_char >= '0' and current_char <= '9';
    }

    bool int_token::completed(const char *from, int next) {
        auto match = not matches(from, next);
//        use_last_complete = true;
//        last_complete_result = match;
        return match;
    }

    unsigned short decimal_token::count_dots(const char *from, int next) {
        unsigned short count = 0;
        for (int i = 0; i <= next; i++) {
            if (from[i] == '.') count++;
        }
        return count;
    }

    bool decimal_token::matches(const char *from, int current) {
        auto current_char = from[current];
        // Between 0-9 inclusive, contains less than two dots
        return (current_char >= '0' and current_char <= '9' or current_char == '.') and count_dots(from, current) <= 1;
    }

    bool decimal_token::completed(const char *from, int next) {
        auto dots = count_dots(from, next);
        // If the next char no longer matches and there is only one dot,
        //      or there are two dots next, it's finished
        return not matches(from, next) and dots == 1 or
                                           dots == 2;
    }

    bool decimal_token::takeover(const char *from, int next) {
        // The so-far-read token should contain exactly one dot so it can be confirmed as a decimal.
        return count_dots(from, next) == 1;
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

    bool identity_token::takeover(const char *from, int next) { return true; }

    keyword_token::keyword_token(const char *match_data, int data_len, char type) : match_data(match_data),
                                                                                    data_len(data_len), _type(type) {}

    bool keyword_token::matches(const char *from, int current) {
        return from[current] == match_data[current] and current < data_len;
    }

    bool keyword_token::completed(const char *from, int next) {
        return not matches(from, next) and next == data_len;
    }
    bool keyword_token::takeover(const char *from, int next) {return matches(from, next);}

}