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
#ifndef SCANNER_TOKEN_INVALIDTOKEN_H
#define SCANNER_TOKEN_INVALIDTOKEN_H

#include "Token.h"
#include <stdio.h>
#include <string>

namespace cs160 {
namespace scanner {
namespace token {

class InvalidToken: public Token{

// Nothing much here, default constructor always used for invalid token
// Generates a invalid token when called
// Set token for setting a given token to invalid
  public:
    InvalidToken();
    void set_token(std::string);
};
}  // namespace token
}  // namespace scanner
}  // namespace cs160
#endif //SCANNER_TOKEN_INVALIDTOKEN_H