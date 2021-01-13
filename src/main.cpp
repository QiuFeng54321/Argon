//
// Created by mac on 2021/1/12.
//

#include <iostream>
#include <string>
#include "tokenizer.h"

int main() {
    char *str = "func test_func (int a, int b) {do(a, b); a = b; if (a == b) {b = a;} else if (a >= b) {a = b;}}";
//    char *str = "identity 123 123.456\n Whitespace      e123 \n 123.do do.123 12.34.do 12.34.5 \n .321 .abc 123 . do \n 12345.67890 09876.54321 \n 13846104610284.12486123086120 \n sophfesohepsohfcdnpvbsbwevbipsvbdpbvd \n abc.?abc.cba.!acb.!..?";
    argon::tokenizer tokenizer(str, strlen(str));
    auto tk_start = std::chrono::high_resolution_clock::now();
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        auto token = tokenizer.next_token();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        auto elapsed_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds);
        std::cout << token.type << ": " <<
                  token.line << ":" << token.column << " : " << std::string(token.data, token.length) << " ("
                  << elapsed_nanoseconds.count() << "ns)" << std::endl;
//        std::cout << std::string(token.data, token.length) << " ";
        if (token.type == '$') break; // EOF
    }
    std::cout << std::endl;
    auto tk_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = tk_end - tk_start;
    auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds);
    std::cout << "Total microseconds elapsed: " << elapsed_microseconds.count() << "us" << std::endl;
}
