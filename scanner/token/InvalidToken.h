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

class InvalidToken: public Token{
    
public:
    InvalidToken();
    void set_token(std::string);
    
    
};

#endif /* InvalidToken_hpp */
