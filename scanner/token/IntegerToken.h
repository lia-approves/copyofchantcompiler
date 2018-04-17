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

namespace cs160 {
namespace scanner {
namespace token {

class IntegerToken: public Token{

public:
    //Constructors
    explicit IntegerToken(std::string str);
    explicit IntegerToken(int tok_integer);

    //Getters and Setters
    void set_token(std::string str);
    int get_token_int();

private:
    int token_int_;


};

} // namespace token
} // namespace scanner
} // namespace cs160

#endif /* IntegerToken_hpp */
