//
// Created by mac on 2021/1/12.
//

#ifndef ARGON_TOKEN_UNIT_H
#define ARGON_TOKEN_UNIT_H

#include "token.h"

namespace argon {
    class token_unit {
    public:
        virtual bool matches(char *from, int current);

        virtual bool takeover(char *from, int current);

        virtual bool completed(char *from, int next);
    };

    class int_token : public token_unit {
    public:
        bool matches(char *from, int current) override;

        bool takeover(char *from, int current) override;

        bool completed(char *from, int next) override;
    };
}


#endif //ARGON_TOKEN_UNIT_H
