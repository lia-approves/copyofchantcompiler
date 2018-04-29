// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_PARSER_PARSER_H_
#define FRONTEND_PARSER_PARSER_H_

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "frontend/v1/scanner/token/Token.h"
#include "abstract_syntax/abstract_syntax.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Parser {
 public:
    explicit Parser(std::vector<std::shared_ptr<Token>> tokens);
    ~Parser(void);
    std::unique_ptr<abstract_syntax::frontend::AstNode> Parse() {
      return ExpressionRule();
    }

 private:
    std::vector<std::shared_ptr<Token>> tokens_;
    int current_ = 0;

    // CFG methods
    std::unique_ptr<abstract_syntax::frontend::AstNode> ExpressionRule() {
      return AddRule();
    }
    std::unique_ptr<abstract_syntax::frontend::AstNode> AddRule();
    std::unique_ptr<abstract_syntax::frontend::AstNode> MultRule();
    std::unique_ptr<abstract_syntax::frontend::AstNode> UnaryRule();
    std::unique_ptr<abstract_syntax::frontend::AstNode> PrimaryRule();

    // helpers
    std::shared_ptr<Token> Next() {
      if (!AtEnd()) current_ = current_ + 1;
      return Prev();
    }
    std::shared_ptr<Token> Prev() {
      return tokens_[current_ - 1];
    }
    bool AtEnd() {
      return (current_ > tokens_.size() - 1);
    }
    std::shared_ptr<Token> GetCurrent() {
      return tokens_[current_];
    }
    bool Match(std::vector<token_type_> types) {
      for (auto const& type : types) {
        if (Check(type)) {
          Next();
          return true;
        }
      }
      return false;
    }
    bool Check(token_type_ type) {
      if (AtEnd()) return false;
      return GetCurrent()->GetCurrType() == type;
    }
    std::shared_ptr<Token> Consume(token_type_ until, std::string error) {
      if (Check(until)) return Next();
      throw error;
    }
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_PARSER_PARSER_H_
