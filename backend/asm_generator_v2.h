// Copyright msg for cpplint
#ifndef BACKEND_ASM_GENERATOR_V2_H_
#define BACKEND_ASM_GENERATOR_V2_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"
#include "backend/ir_v1.h"

using std::endl;
using std::string;
using cs160::backend::StatementNode;
using cs160::backend::Instruction;
namespace cs160 {
namespace backend {

class AsmProgram {
 public:
  AsmProgram() {}
  ~AsmProgram() {}
  void IrToAsm(StatementNode* head);
  string GetASMString() { return asm_sstring_.str(); }
 private:
  void GenerateASM(StatementNode* node);
  stringstream asm_sstring_;
  stringstream asm_data_segment_;
};

void AsmProgram::IrToAsm(StatementNode* head) {
  asm_sstring_ << ".global main" << endl;
  asm_sstring_ << ".text" << endl;
  asm_sstring_ << "main:" << endl << endl;
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
  asm_sstring_ << "  .asciz  \"%0ld\\n\"" << endl;

  asm_sstring_ << asm_data_segment_ << endl;
  asm_sstring_ << endl;

}

void AsmProgram::GenerateASM(StatementNode* node) {
  node->GetOp1().PushToAsmSS(asm_sstring_);
  node->GetOp2().PushToAsmSS(asm_sstring_);

  switch (node->GetInstruction().GetOpcode()) {
  case Instruction::kAdd:
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "pop %rbx" << endl;
    asm_sstring_ << "add %rax, %rbx" << endl;
    asm_sstring_ << "push %rbx" << endl << endl;
    break;
  case Instruction::kSubtract:
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "pop %rbx" << endl;
    asm_sstring_ << "sub %rax, %rbx" << endl;
    asm_sstring_ << "push %rbx" << endl << endl;
    break;
  case Instruction::kMultiply:
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "pop %rbx" << endl;
    asm_sstring_ << "imul %rax, %rbx" << endl;
    asm_sstring_ << "push %rbx" << endl << endl;
    break;
  case Instruction::kDivide:
    asm_sstring_ << "pop %rbx" << endl;
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "mov $0, %rdx" << endl;
    asm_sstring_ << "idiv %rbx" << endl;
    asm_sstring_ << "push %rax" << endl << endl;
    break;
  default:
    break;
  }
}
}  // namespace backend
}  // namespace cs160

#endif  // BACKEND_ASM_GENERATOR_V2_H_
