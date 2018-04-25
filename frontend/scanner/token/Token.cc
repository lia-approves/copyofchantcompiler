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
FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace frontend {

Token::Token() {
    token_str_ = "";
    type_ t = token_;
    SetCurrType(t);
}

Token::Token(std::string str) {
  token_str_ = str;
  type_ t = token_;
  SetCurrType(t);
}

Token::~Token() { }

// Basic getters and setters
std::string Token::GetToken() {
  return token_str_;
}

void Token::SetTokenStr(std::string str) {
  token_str_ = str;
}

void Token::SetToken(std::string str) {
  token_str_ = str;
}

std::string Token::Print() {
    return token_str_;
}


void Token::SetCurrType(type_ t) {
    curr_type_ = t;
}

type_ Token::GetCurrType() {
    return curr_type_;
}

}  // namespace frontend
}  // namespace cs160
