//
// Created by mac on 2021/1/12.
//

#ifndef ARGON_TOKEN_H
#define ARGON_TOKEN_H

namespace argon {
    struct token {
        int line, column;
        const char* data;
        long long length;
        char type;
    };
}


#endif //ARGON_TOKEN_H
