//
//  ArithmeticExpressionToken.cpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "ArithmeticExpressionToken.h"
#include <sstream>

namespace cs160 {
namespace scanner {
namespace token {

//Constructor for simple input
ArithmeticExpressionToken::ArithmeticExpressionToken(char tok){

    token_char_ = tok;

    std::stringstream ss;
    ss << tok;
    std::string setter = "";
    ss >> setter;

    set_token_str(setter);
}

//Constructor for if input is more than single char
ArithmeticExpressionToken::ArithmeticExpressionToken(std::string tok){
    set_token_str(tok);

    token_char_ = tok[0];
}

//Method to set the value of a token given a string
void ArithmeticExpressionToken::set_token(std::string tok){
    set_token_str(tok);

    token_char_ = tok[0];
}

//Method to set value of a token given a char
void ArithmeticExpressionToken::set_token_char(char tok){
    token_char_ = tok;

    std::stringstream ss;
    ss << tok;
    std::string setter;
    set_token_str(setter);
}

//Getter
char ArithmeticExpressionToken::get_token_char(){
    return token_char_;
}

} // namespace token
} // namespace scanner
} // namespace cs160
