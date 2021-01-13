//
// Created by mac on 2021/1/12.
//

#include <iostream>
#include <string>
#include "tokenizer.h"

int main() {
    char *str = "identity 123 123.456\n Whitespace      e123 \n 123.do do.123 12.34.do 12.34.5 \n .321 .abc 123 . do";
    argon::tokenizer tokenizer(str, strlen(str));
    auto tk_start = std::chrono::system_clock::now();
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        auto token = tokenizer.next_token();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        auto elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds);
        std::cout << token.type << ": " <<
                  token.line << ":" << token.column << " : " << std::string(token.data, token.length) << " ("
                  << elapsed_nanoseconds.count() << "ns)" << std::endl;
        if (token.type == '$') break;
    }
    auto tk_end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = tk_end - tk_start;
    auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds);
    std::cout << "Total microseconds elapsed: " << elapsed_microseconds.count() << "us" << std::endl;
}
