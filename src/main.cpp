//
// Created by mac on 2021/1/12.
//

#include <iostream>
#include <string>
#include "tokenizer.h"

int main() {
    std::cout << "Hello" << std::endl;
    char *str = "identity 123 123.456\n Whitespace      e123 \n 123.do do.123 12.34.do";
    argon::tokenizer tokenizer(str, strlen(str));
    while (true) {
        auto token = tokenizer.next_token();
        std::cout << token.type << ": " <<
                  token.line << ":" << token.column << " : " << std::string(token.data, token.length) << std::endl;
        if (token.type == '$') break;
    }
}
