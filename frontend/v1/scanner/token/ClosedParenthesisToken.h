/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef FRONTEND_V1_SCANNER_TOKEN_CLOSEDPARENTHESISTOKEN_H_
#define FRONTEND_V1_SCANNER_TOKEN_CLOSEDPARENTHESISTOKEN_H_

#include <stdio.h>
#include <string>
#include "Token.h"

namespace cs160 {
namespace frontend {

class ClosedParenthesisToken : public Token{
 public:
    // Constructor
    // cannot use the Token(string) constructor, or it will be bad
    ClosedParenthesisToken();
    explicit ClosedParenthesisToken(std::string str);

    // Getter and Setters
    void SetToken(std::string str);
    char GetTokenChar();

 private:
    const char token_char_ = ')';
    const std::string token_str_ = ")";
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_V1_SCANNER_TOKEN_CLOSEDPARENTHESISTOKEN_H_
