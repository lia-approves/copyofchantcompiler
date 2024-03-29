/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef FRONTEND_V1_SCANNER_STATE_MACHINE_STATE_STATE_H_
#define FRONTEND_V1_SCANNER_STATE_MACHINE_STATE_STATE_H_

#include <map>
#include <functional>
#include <string>
#include <memory>
#include "frontend/v1/scanner/token/Token.h"
#include "frontend/v1/scanner/token/InvalidToken.h"

/*
  Every state must have a unique POSITIVE id.
  It can also have transitions to other states, referred to by id.

  "Error" states are denoted by negative ids.
  Creating a state without providing an id causes it to be an error state by default

  Provide a token in the constructor to create an Accepting State
*/

namespace cs160 {
namespace frontend {

class State {
 public:
    // Constructors for creating states, default value is -1
    // Otherwise initialize it with a Token
    explicit State(int id = -1);
    explicit State(int id, Token token);


    // Destructor for State object
    ~State(void);

    // set the output type for the state
    void setTokenOutput(std::function<std::shared_ptr<Token>(std::string)>func);
    // return the correct output type
    std::shared_ptr<Token> getToken(std::string str);

    // Method for adding transition to a state, input is a character
    // and where the state should go
    void addTransition(char trigger, int nextStateId);
    void addTransition(char startChar, char endChar, int nextStateId);
    void makeAccepting();
    int nextState(char input);

    // Basic getters
    int getId() const { return id_; }
    bool isAccepting() const { return accepting_; }
    Token getToken() const { return token_; }

 private:
    int id_;
    bool accepting_;
    Token token_;
    std::map<char, int> transitions_;
    std::function<std::shared_ptr<Token>(std::string)> createToken_;
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_V1_SCANNER_STATE_MACHINE_STATE_STATE_H_
