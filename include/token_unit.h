//
// Created by mac on 2021/1/12.
//

#ifndef ARGON_TOKEN_UNIT_H
#define ARGON_TOKEN_UNIT_H

#include "token.h"

namespace argon {
    class token_unit {
    public:
        // Every time the char is consumed, when it matches completely or doesn't match, this is set to true
        bool finished = false;
        // This stores the result from matches(). completed() can use this
        bool last_match_result = false;

        // Returns the type of this token represented as a char
        virtual char type();

        // Returns whether the current char matches
        virtual bool matches(const char *from, int current);

        // Returns if it completed matching
        virtual bool completed(const char *from, int next);

        // Returns if it should take over.
        virtual bool takeover(const char *from, int next);

        token_unit();
    };

    class int_token : public token_unit {
    public:
        char type() override;

        bool matches(const char *from, int current) override;

        bool completed(const char *from, int next) override;
    };

    class decimal_token : public token_unit {
        short count_dots(const char *from, int next);

    public:
        char type() override;

        bool matches(const char *from, int current) override;

        bool completed(const char *from, int next) override;

        bool takeover(const char *from, int next) override;
    };

    class identity_token : public token_unit {
    public:
        char type() override;

        bool matches(const char *from, int current) override;

        bool completed(const char *from, int next) override;

        bool takeover(const char *from, int next) override;
    };

    class keyword_token : public token_unit {
        const char *match_data;
        int data_len;
        char _type;
    public:
        keyword_token(const char *match_data, int data_len, char type);

        char type() override;

        bool matches(const char *from, int current) override;

        bool completed(const char *from, int next) override;
    };
}


#endif //ARGON_TOKEN_UNIT_H
