# Team Chant Backend

## Code Organization

### Lowerer

We have a lowerer, which lowers an AST into our IR.

code: lowerer_v1.h
tests: lowerer_v1_test.cc

Run lowerer tests with:
```

```

### Intermediate Representation

Our IR is a three-address code.

code: ir_v1.h
tests: none

### Assembly Code Generator

We also have code to translate an IR into x86 assembly.

code: asm_generator_v1.h
tests: asm_generator_test.cc

Run ASM generator tests with:
```
$ bazel run backend:asm_generator_test
```

### Integeration tests

There are also tests that test the entire backend, from AST to the output of the generated assembly file.

Run integration tests with:
```
$ bazel run backend:integration_test
```
