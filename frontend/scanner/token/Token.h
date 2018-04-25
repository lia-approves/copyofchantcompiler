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
namespace frontend {

    enum token_type_{ token_, integerToken,
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
    virtual std::string GetToken() const;
    virtual void SetToken(std::string str);
    void SetTokenStr(std::string str);
    virtual std::string Print();
    virtual void SetCurrType(token_type_ t);
    virtual token_type_ GetCurrType();

 private:
    std::string token_str_;
    token_type_ curr_token_type_  = static_cast<token_type_>(0);

    // string representation of the token being represented
};
}  // namespace frontend
}  // namespace cs160
#endif  // FRONTEND_SCANNER_TOKEN_TOKEN_H_
