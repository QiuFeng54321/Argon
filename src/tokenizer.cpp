//
// Created by mac on 2021/1/12.
//

#include "tokenizer.h"
#include <iostream>
#include <string>

namespace argon {
    token_unit *tokenizer::token_units[]{
            // Tokens that overlaps and needs takeover feature shall be placed after
            new int_token,
            new decimal_token,
            new keyword_token(".", 1, '.'),
            new identity_token,
    };

    tokenizer::tokenizer(const char *str, int str_len) : str(str), str_len(str_len) {

    }

    token tokenizer::eof_token(int l, int c) {
        return token{l, c, new char(0), 0, '$'};
    }

    token tokenizer::error_token(int l, int c) {
        return token{l, c, new char(0), 0, 'E'};
    }

    void tokenizer::forward() {
        current_offset++;
        if (current_offset < str_len) {
            if (str[current_offset] == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
        }
    }

    void tokenizer::skip_ws() {
        while (current_offset < str_len) {
            const char *current = str + current_offset;
            if ((*current) == ' ' or (*current) == '\t') {
                column++;
                current_offset++;
            } else if ((*current) == '\n') {
                line++;
                column = 1;
                current_offset++;
            } else break;
        }
    }

    /**
     * Reads next token. <br/>
     * TODO: Currently it checks using 'unit->matches' and 'unit->completed'. <br/>
     *       Most of the tokens just use !matches(from, next) in 'unit->completed'.
     *       Maybe we should just merge the two methods into one.
     * @return next token. eof_token for end of file. error_token for errors.
     */
    token tokenizer::next_token() {
        // skips whitespaces
        skip_ws();
        // return eof_token if it's at the end of the data
        if (current_offset >= str_len) return eof_token(line, column);
        auto data = str + current_offset;
        int index = 0;
        char type = ' ';
        // This is recorded for storing the start line and column
        int tk_line = line, tk_column = column;
        for (auto& unit : token_units) {
            unit->finished = false;
        }

        bool finished = false;
        while (not finished) {
            bool any_match = false;
            bool any_complete = false;
            // iterate over token_units to match
            for (auto& unit : token_units) {
                if (unit->finished) continue;
//                std::cout << "Processing " << unit->type() << std::endl;
                if (unit->matches(data, index)) {
                    if (unit->completed(data, index + 1)) {
                        // A token has matched completely
//                        std::cout << unit->type() << " has completed at '" << std::string(data, index + 1) << "'"
//                                  << std::endl;
                        type = unit->type();
                        unit->finished = true;
                        any_complete = true;
                    } else {
                        if (any_complete) {
                            // Other tokens completed but this token still matches it
                            if (unit->takeover(data, index + 1)) {
                                any_complete = false;
                                break;
                            }
                        }
                    }
                    any_match = true;
                } else unit->finished = true;
            }
            // go to next char
            index++;
            forward();
            if (not any_match) return error_token(tk_line, tk_column);
            if (any_complete) break;
        }
        // Returns the read token with its position, type and data.
        return token{tk_line, tk_column, data, index, type};
    }
}