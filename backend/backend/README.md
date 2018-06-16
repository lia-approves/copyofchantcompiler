# Team CHANT Backend

## Lowering from AST to IR
Relevant files: lowerer_v5.h and lowerer_v5.cc

This is where we lower the AST into the IR, using the visitor pattern. We have a VarCountVisitor class and an IrGenVisitor class, both of which are AstVisitors.

### VarCountVisitor
This class is just used to count variables in order to construct the symbol table

### IrGenVisitor
This is the main class used for lowering. As we visit each node of the AST, we create the appropriate StatementNodes and add them to our IR.

We also use a vector of Operands called the ir_stack as a stack for the IR. This is helpful, for instance, when visiting a Dereference. We visit the left hand side, then the right hand side, and then can pop from the ir_stack to get the index and address of the Dereference.

## Our Intermediate Representation
Relevant file: ir_v5.h

We chose to implement a 3 address code for our intermediate representation.
The StatementNode class represents a single instruction, which has a label, a target, two operands and an instruction.
The Operand class has three subclasses: Register, Variable and Constant.

## Generating Assembly from IR
Relevant file: asm_generator_v5.h

Our assembly generator is fairly straightforward. It adds some x86 assembly
instructions based on the opcode of each StatementNode. This usually involves
assigning a value to a variable at a particular address, or computing a value
and leaving it on the top of the stack for the next StatementNode.
Our AsmProgram class also maintains a symbol table that keeps track of function
parameters and local variables. This allows it to look up the appropriate
offsets for each variable when generating the assembly code.

## Control Flow Graph
Relevant files: SSA.h and SSA.cc

We create a control flow graph from our intermediate representation by splitting
our vector of StatementNodes into BasicBlocks.
In ControlFlowGraph::CreateCFG(), we iterate through all the StatementNodes, and
detect whether they should be a leader (first node) of a BasicBlock. Whenever
there is a branching instruction (LessThan, LessThanEqualTo, GreaterThan,
GreaterThanEqualTo, EqualTo), two BasicBlocks are created (one for the true
branch and one for the false branch).
When we hit a Goto node, only one new BasicBlock is created.

We then iterate through the blocks to make sure there are no dead-end blocks.

When we print the CFG, we output each block, its incoming edges, outgoing edges,
and StatementNodes.

## SSA
Relevant files: SSA.h and SSA.cc

## Tests

Our tests cover the functionality of versions 1 through 5, as well as producing
printing the IR, control flow graphs and SSA.

### Arithmetic Operations Tests

These tests generate assembly for ASTs that add, subtract, multiply, divide,
and evaluate simple conditional statements.

To run tests with no extra output printed:
```
bazel run backend:v5_arithmetic
```
With SSA (and dominators) for each test printed:
```
bazel run backend:ssa_arithmetic
```
With control flow graph (and dominators) for each test printed:
```
bazel run backend:cfg_arithmetic
```

### Assignables Tests

These tests generate assembly for ASTs that create and assign variables,
dereferences and functions.

To run tests with no extra output printed:
```
bazel run backend:v5_assignables
```
With SSA (and dominators) for each test printed:
```
bazel run backend:ssa_assignables
```
With control flow graph (and dominators) for each test printed:
```
bazel run backend:cfg_assignables
```

### Loop Test

This is a simple test of a loop.

To run test with no extra output printed:
```
bazel run backend:v5_loop
```
With SSA (and dominators) for each test printed:
```
bazel run backend:ssa_loop
```
With control flow graph (and dominators) for each test printed:
```
bazel run backend:cfg_loop
```

### Logicals Tests

These tests generate assembly for ASTs that use logical AND, OR and NOT, and
also includes more complicated tests where these operations are used together.

To run tests with no extra output printed:
```
bazel run backend:v5_logicals
```
With SSA (and dominators) for each test printed:
```
bazel run backend:ssa_logicals
```
With control flow graph (and dominators) for each test printed:
```
bazel run backend:cfg_logicals
```

### Integration Tests

This very complex test involves many nested tuples.

To run test with no extra output printed:
```
bazel run backend:v5_integration
```
With SSA (and dominators) for each test printed:
```
bazel run backend:ssa_integration
```
With control flow graph (and dominators) for each test printed:
```
bazel run backend:cfg_integration
```
