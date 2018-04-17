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
    explicit IntegerToken(std::string str);
    explicit IntegerToken(int tok_integer);
    void set_token(std::string str);
    int get_token_int();

private:
    int token_int_;


};

#endif /* IntegerToken_hpp */
