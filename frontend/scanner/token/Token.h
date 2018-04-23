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
#ifndef FRONTEND_SCANNER_TOKEN_TOKEN_H_
#define FRONTEND_SCANNER_TOKEN_TOKEN_H_

#include <string>

namespace cs160 {
namespace scanner {
namespace token {

    enum type_{ token, integerToken,
        invalidToken,
        openParenthesisToken,
        closedParenthesisToken,
        arithmeticExpressionToken};
class Token{
 public:
    // Constructors and destructors
    // Note: default does not do anything
    Token();
    explicit Token(std::string str);
    virtual ~Token();

    // Getters and setters
    virtual std::string get_token();
    virtual void set_token(std::string str);
    void set_token_str(std::string str);
    virtual std::string print();
    virtual void set_curr_type(type_ t);
    virtual type_ get_curr_type();

 private:
    std::string token_str_;
    type_ curr_type_  = static_cast<type_>(0);

    // string representation of the token being represented
};
}  // namespace token
}  // namespace scanner
}  // namespace cs160
#endif  // FRONTEND_SCANNER_TOKEN_TOKEN_H_
