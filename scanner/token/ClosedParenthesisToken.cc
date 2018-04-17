//
//  ClosedParenthesisToken.cpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//
namespace cs160 {
namespace scanner {
namespace token {

#include "ClosedParenthesisToken.h"

ClosedParenthesisToken::ClosedParenthesisToken(){
    //do nothing ~ the const string and char are already created
}

void ClosedParenthesisToken::set_token(std::string str){
    //do nothing ~ the const string and char are already created
}

char ClosedParenthesisToken::get_token_char(){
    return token_char_;
}

} // namespace token
} // namespace scanner
} // namespace cs160
