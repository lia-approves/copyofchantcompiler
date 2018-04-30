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
#ifndef FRONTEND_V1_SCANNER_TOKEN_INVALIDTOKEN_H_
#define FRONTEND_V1_SCANNER_TOKEN_INVALIDTOKEN_H_

#include "Token.h"
#include <stdio.h>
#include <string>

namespace cs160 {
namespace frontend {

class InvalidToken: public Token{
// Nothing much here, default constructor always used for invalid token
// Generates a invalid token when called
// Set token for setting a given token to invalid
 public:
    InvalidToken();
    explicit InvalidToken(std::string str);
    void SetToken(std::string);
};
}  // namespace frontend
}  // namespace cs160
#endif  // FRONTEND_V1_SCANNER_TOKEN_INVALIDTOKEN_H_
