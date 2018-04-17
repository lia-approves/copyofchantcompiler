//
//  InvalidToken.cpp
//
//
//  Created by Maggie Schmit on 4/16/18.
//
//

namespace cs160 {
namespace scanner {
namespace token {
  
#include "InvalidToken.h"

InvalidToken::InvalidToken(){
    Token("Invalid Token");
}

void InvalidToken::set_token(std::string str){
    set_token_str("Invalid Token");
}

} // namespace token
} // namespace scanner
} // namespace cs160
