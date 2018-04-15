//
//  Token.h
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef Token_h
#define Token_h

#include <string>

public class Token{
public:
    
    virtual Token(std::string str);
    
    string get_token();
    
    virtual void set_token(std::string str) = 0;
    
private:
    std::string token_str; //string representation of the token being represented
    
    

};
#endif /* Token_h  */
