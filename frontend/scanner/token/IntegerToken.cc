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
#include <sstream>
#include <string>
#include "frontend/scanner/token/IntegerToken.h"

namespace cs160 {
namespace frontend {

IntegerToken::IntegerToken(std::string str) : Token(str) {
  // first, check that the string is a number
  for (int i=0; i < str.size(); i++) {
    char curr_char = str.at(i);
    if (!std::isdigit(curr_char)) {
      // curr_char is not a number
      // throw exception
      throw "1";
      return;
    }
  }


    type_ t = integerToken;
    SetCurrType(t);
    SetToken(str);
}

IntegerToken::IntegerToken(int tok_integer) {
    type_ t = integerToken;
    SetCurrType(t);
    std::string str_arg = std::to_string(tok_integer);
    SetTokenStr(str_arg);

    token_int_ = tok_integer;
}

void IntegerToken::SetToken(std::string str) {
    SetTokenStr(str);

    std::stringstream cast_to_int(str);

    cast_to_int >> token_int_;
}

int IntegerToken::GetTokenInt() {
    return token_int_;
}
}  // namespace frontend
}  // namespace cs160
