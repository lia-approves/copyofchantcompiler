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
#include "frontend/v1/scanner/token/ArithmeticExpressionToken.h"

namespace cs160 {
namespace frontend {

// Constructor for simple input
ArithmeticExpressionToken::ArithmeticExpressionToken(char tok) {
    token_char_ = tok;
    switch (tok) {
      case '+': SetCurrType(plusToken);
        break;
      case '-': SetCurrType(minusToken);
        break;
      case '/': SetCurrType(divideToken);
        break;
      case '*': SetCurrType(multToken);
        break;
      default: SetCurrType(invalidToken);
        break;
    }

    std::stringstream ss;
    ss << tok;
    std::string setter = "";
    ss >> setter;

    SetTokenStr(setter);
}

// Constructor for if input is more than single char
ArithmeticExpressionToken::ArithmeticExpressionToken(std::string tok) {
    SetTokenStr(tok);
    token_char_ = tok[0];
    if (tok.length() == 1) {
      switch (token_char_) {
        case '+': SetCurrType(plusToken);
          break;
        case '-': SetCurrType(minusToken);
          break;
        case '/': SetCurrType(divideToken);
          break;
        case '*': SetCurrType(multToken);
          break;
        default: SetCurrType(invalidToken);
          break;
      }
    } else {
      SetCurrType(invalidToken);
    }
}

// Method to set the value of a token given a string
void ArithmeticExpressionToken::SetToken(std::string tok) {
    SetTokenStr(tok);

    token_char_ = tok[0];
}

// Method to set value of a token given a char
void ArithmeticExpressionToken::SetTokenChar(char tok) {
    token_char_ = tok;

    std::stringstream ss;
    ss << tok;
    std::string setter;
    SetTokenStr(setter);
}

// Getter
char ArithmeticExpressionToken::GetTokenChar() {
    return token_char_;
}
}  // namespace frontend
}  // namespace cs160
