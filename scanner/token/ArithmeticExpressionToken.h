//
//  ArithmeticExpressionToken.hpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef ArithmeticExpressionToken_h
#define ArithmeticExpressionToken_h

#include <stdio.h>
#include "Token.h"

namespace cs160 {
namespace scanner {
namespace token {

class ArithmeticExpressionToken: public Token{

public:
    //Constructors
    explicit ArithmeticExpressionToken(char tok);
    explicit ArithmeticExpressionToken(std::string tok);

    //Getts and setters
    void set_token(std::string str);
    void set_token_char(char tok);
    char get_token_char();


private:
    char token_char_;
};

} // namespace token
} // namespace scanner
} // namespace cs160

#endif /* ArithmeticExpressionToken_hpp */
