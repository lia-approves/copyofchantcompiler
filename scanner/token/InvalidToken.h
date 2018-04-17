//
//  InvalidToken.hpp
//
//
//  Created by Maggie Schmit on 4/16/18.
//
//

#ifndef InvalidToken_h
#define InvalidToken_h

#include <stdio.h>
#include <string>
#include "Token.h"

namespace cs160 {
namespace scanner {
namespace token {

class InvalidToken: public Token{

//Nothing much here, default constructor always used for invalid token
//Generates a invalid token when called
//Set token for setting a given token to invalid
public:
    InvalidToken();
    void set_token(std::string);


};
} // namespace token
} // namespace scanner
} // namespace cs160
#endif /* InvalidToken_hpp */
