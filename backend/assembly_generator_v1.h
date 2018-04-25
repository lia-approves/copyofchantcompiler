// Copyright msg for cpplint
#ifndef BACKEND_ASSEMBLY_GENERATOR_V1_H_
#define BACKEND_ASSEMBLY_GENERATOR_V1_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"
#include "backend/intermediate_representation_v1.h"

using std::endl;
using std::string;
using cs160::backend::StatementNode;
using cs160::backend::Instruction;


class AsmProgram {
 public:
  AsmProgram() {}
  ~AsmProgram() {}
  void GenerateASM(StatementNode* node);
  void IrToAsm(StatementNode* head) {
  while (head != nullptr) {
      GenerateASM(head);
      head = head->GetNext();
    }
  }
  string GetASM() { return asm_sstring_.str(); }

 private:
  stringstream asm_sstring_;
};

void AsmProgram::GenerateASM(StatementNode* node) {
  node->GetOp1().PushToAsmSS(asm_sstring_);
  node->GetOp2().PushToAsmSS(asm_sstring_);
  asm_sstring_ << "pop %ax" << endl;
  asm_sstring_ << "pop %bx" << endl;
  switch (node->GetInstruction().GetOpcode()) {
  case Instruction::kAdd:
    asm_sstring_ << "add %ax, %bx" << endl;
    break;
  case Instruction::kSubtract:
    asm_sstring_ << "sub %ax, %bx" << endl;
    break;
  case Instruction::kMultiply:
    asm_sstring_ << "mul %ax, %bx" << endl;
    break;
  case Instruction::kDivide:
    asm_sstring_ << "div %ax, %bx" << endl;
    break;
    asm_sstring_ << "push %bx" << endl;

  default:
    break;
  }
}

#endif  // BACKEND_ASSEMBLY_GENERATOR_V1_H_
