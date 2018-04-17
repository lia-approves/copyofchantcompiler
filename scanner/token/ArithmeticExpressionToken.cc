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

#include "ArithmeticExpressionToken.h"
#include <sstream>
#include <string>

namespace cs160 {
namespace scanner {
namespace token {

// Constructor for simple input
ArithmeticExpressionToken::ArithmeticExpressionToken(char tok){

    token_char_ = tok;

    std::stringstream ss;
    ss << tok;
    std::string setter = "";
    ss >> setter;

    set_token_str(setter);
}

// Constructor for if input is more than single char
ArithmeticExpressionToken::ArithmeticExpressionToken(std::string tok){
    set_token_str(tok);

    token_char_ = tok[0];
}

// Method to set the value of a token given a string
void ArithmeticExpressionToken::set_token(std::string tok){
    set_token_str(tok);

    token_char_ = tok[0];
}

// Method to set value of a token given a char
void ArithmeticExpressionToken::set_token_char(char tok){
    token_char_ = tok;

    std::stringstream ss;
    ss << tok;
    std::string setter;
    set_token_str(setter);
}

// Getter
char ArithmeticExpressionToken::get_token_char(){
    return token_char_;
}

}  // namespace token
}  // namespace scanner
}  // namespace cs160
