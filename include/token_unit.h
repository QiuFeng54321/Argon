//
// Created by mac on 2021/1/12.
//

#ifndef ARGON_TOKEN_UNIT_H
#define ARGON_TOKEN_UNIT_H

#include "token.h"

namespace argon {
    class token_unit {
    public:
        bool finished = false;

        virtual char type();

        virtual bool matches(const char *from, int current);

        virtual bool completed(const char *from, int next);

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
    };
}


#endif //ARGON_TOKEN_UNIT_H
