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
    asm_sstring_ << ".global main" << endl;
    asm_sstring_ << ".text" << endl;
    asm_sstring_ << "main:" << endl;
  while (head != nullptr) {
      GenerateASM(head);
      head = head->GetNext();
    }
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "mov     $format, %rdi" << endl;
    asm_sstring_ << "mov     %rax, %rsi" << endl;
    asm_sstring_ << "xor     %rax, %rax" << endl;
    asm_sstring_ << "call    printf" << endl;

    asm_sstring_ << "  ret" << endl;

    asm_sstring_ << "format:" << endl;
    asm_sstring_ << "  .asciz  \"%20ld\\n\"" << endl;
    asm_sstring_ << endl;
  }
  string GetASM() { return asm_sstring_.str(); }

 private:
  stringstream asm_sstring_;
};

void AsmProgram::GenerateASM(StatementNode* node) {
  node->GetOp1().PushToAsmSS(asm_sstring_);
  node->GetOp2().PushToAsmSS(asm_sstring_);
  asm_sstring_ << "pop %rax" << endl;
  asm_sstring_ << "pop %rbx" << endl;
  switch (node->GetInstruction().GetOpcode()) {
  case Instruction::kAdd:
    asm_sstring_ << "add %rax, %rbx" << endl;
    break;
  case Instruction::kSubtract:
    asm_sstring_ << "sub %rax, %rbx" << endl;
    break;
  case Instruction::kMultiply:
    asm_sstring_ << "mul %rax, %rbx" << endl;
    break;
  case Instruction::kDivide:
    asm_sstring_ << "div %rax, %rbx" << endl;
    break;
  default:
    break;
  }
  asm_sstring_ << "push %rbx" << endl << endl;
}

#endif  // BACKEND_ASSEMBLY_GENERATOR_V1_H_
