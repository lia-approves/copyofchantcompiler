//
//  IntegerToken.hpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef IntegerToken_h
#define IntegerToken_h

#include <stdio.h>
#include <string>
#include "Token.h"

class IntegerToken: public Token{

public:
    IntegerToken(std::string str);
    void set_token(std::string str);
    int get_token_int();

private:
    int token_int_;


};

#endif /* IntegerToken_hpp */
