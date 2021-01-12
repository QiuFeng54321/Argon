//
// Created by mac on 2021/1/12.
//

#include <iostream>
#include <string>
#include "tokenizer.h"

int main() {
    std::cout << "Hello" << std::endl;
    char *str = "hello 123 hi123.1 321abc \n   1432.3 e 12.345   \n1.23asd12";
    argon::tokenizer tokenizer(str, strlen(str));
    while (true) {
        auto token = tokenizer.next_token();
        std::cout << token.type << ": " <<
                  token.line << ":" << token.column << " : " << std::string(token.data, token.length) << std::endl;
        if (token.type == '.') break;
    }
}
