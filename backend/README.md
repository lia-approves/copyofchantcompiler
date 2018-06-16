## Design Choices

### General

### IR generation
We decided to use a three-address code IR not only because it was recommended, but because we felt that it was suitably between the AST and the assembly to function as a useful intermediate representation.  The form of the IR is a vector of shared pointers to StatementNode objects.

#### CountVisitor
We have a count visitor in order to improve the performance of the compiler. It counts the variables that are local to each function and main function as well. This is so we could pre-allocate how much space we could need in the stack.  

### Assembly generation

#### Storing variables
As of AST v4, we put all our variables on the stack to handle recursive functions.  In other words, we no longer store our variables in global data, and registers store only intermediate values for calculations.

### Control Flow Graph (CFG)
Each function, in addition to the main function, has its own CFG.  Each CFG wraps each of its StatementNodes from the IR in a BasicBlock wrapper class.  StatementNodes with the same block id are part of the same basic block, which is the statement number of the first StatementNode of that basic block.

### Static Single-Assignment (SSA)
The SSA uses a Dominance helper class to calculate, for each basic block in a CFG:
* which basic blocks it dominates, including itself
* which basic block is its immediate dominator, to build the dominator tree
* which basic blocks are its descendants in the dominator tree
* which basic blocks are its dominance frontiers
Then, the SSA class performs a liveness analysis of each graph's variables, adding variables as appropriate to the global functions list.  The phi functions are inserted.

### Work Acomplished
We were able to get the full functionality of all the features of v5. Our chosen optimization was to transform the Intermediate Representation to Single Static Assignment form. We accomplished this by first creating a per function control graph. After we were able to divide the function into blocks, we created a list of dominators for each node. Then we used that info to create the immediate dominators for each node and the Domination Tree for the each graph. The we were able to compute the domination frontiers for each node. We then perfomed a live variable analysis and determined the global variables. For each live variable we then placed each phi function according to the domination frontier. After that we used a preorder walk to rename the variables.

We had to choose between the two versions of the SSA we had: one that worked for v5 and printed the SSA, and one that converted the SSA back to IR but didn't work for dereferences and tuples.  Getting the SSA to work with dereferences wasn't part of the contract because the instructors claimed it was difficult.
We decided that for the master branch, we should only print the SSA but still run the pre-SSA IR, because we did not want to throw away our existing tuple and dereference test cases.