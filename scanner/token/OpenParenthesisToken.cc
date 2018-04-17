//
//  OpenParenthesisToken.cpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "OpenParenthesisToken.h"

namespace cs160 {
namespace scanner {
namespace token {

OpenParenthesisToken::OpenParenthesisToken(){
    //do nothing ~ the const string and char are already created
}

void OpenParenthesisToken::set_token(std::string str){
    //do nothing ~ the const string and char are already created
}

char OpenParenthesisToken::get_token_char(){
    return token_char_;
}
} // namespace token
} // namespace scanner
} // namespace cs160
