# **Code Generation**
## **Scope**
--------------
In the preceding stages of decompilation, we have meticulously collected and analyzed information about the binary file. At this juncture, we have successfully assimilated this data into the FuncInfo class. We have a clear understanding of the location and structure of loops and conditional statements, including the headers, branching conditions and subsequent nodes. It is now time to commence the process of generating code, utilizing the information we have gathered.

## **How we will generate**
---------------
- To begin with, we are operating under the assumption that the blocks we have identified have a one-to-one correspondence. Specifically, each instruction in the intermediate representation (IR) corresponds to a single instruction in the high-level programming language.
- We will design and implement a loosely coupled interface for our domain-specific language (DSL) that will handle the translation of all instructions in the LLVM intermediate representation (IR) into the corresponding instructions in a high-level programming language (HLL). Since we are only dealing with conditionals and loops and not more complex structures such as classes, we will allow the user to define their own DSL that adheres to the aforementioned interface, providing them with the flexibility to customize the translation process.

## **List of needed LLVM IR instructions**
-------------------

1. **Terminator instructions**
    - ***ret*** Instruction: This instruction is used to return a value from a function.
    - ***br*** Instruction: The br instruction is used to perform a branch.
    - ***switch*** Instruction: This instruction is used to perform a switch statement.
    - ***indirectbr*** Instruction: The indirectbr instruction is used to perform an indirect branch.
    - ***invoke*** Instruction: This instruction is used to invoke a function and handle exceptions.
    - ***callbr*** Instruction: The callbr instruction is used to call a function and perform a branch.
2. **Unary operations**
    - ***fneg*** Instruction: This instruction is used to negate a floating-point value.
3. ***Binary Operations***
    - ***add*** Instruction: This instruction is used to perform an integer addition.
    - ***fadd*** Instruction: This instruction is used to perform a floating-point addition.
    - ***sub*** Instruction: This instruction is used to perform an integer subtraction.
    - ***fsub*** Instruction: This instruction is used to perform a floating-point subtraction.
    - ***mul*** Instruction: This instruction is used to perform an integer multiplication.
    - ***fmul*** Instruction: This instruction is used to perform a floating-point multiplication.
    - ***udiv*** Instruction: This instruction is used to perform an unsigned integer division.
    - ***sdiv*** Instruction: This instruction is used to perform a signed integer division.
    - ***fdiv*** Instruction: This instruction is used to perform a floating-point division.
    - ***urem*** Instruction: This instruction is used to perform an unsigned integer remainder.
    - ***srem*** Instruction: This instruction is used to perform a signed integer remainder.
    - ***frem*** Instruction: This instruction is used to perform a floating-point remainder.
4. **Bitwise Binary operations**
    - ***shl*** Instruction: This instruction is used to perform a left-shift operation on integers.
    - ***lshr*** Instruction: This instruction is used to perform a logical right-shift operation on integers.
    - ***ashr*** Instruction: This instruction is used to perform an arithmetic right-shift operation on integers.
    - ***and*** Instruction: This instruction is used to perform a - bitwise AND operation on integers.
    - ***or*** Instruction: This instruction is used to perform a bitwise OR operation on integers.
    - ***xor*** Instruction: This instruction is used to perform a bitwise XOR operation on integers.
5. **Conversion Operations**
    - ***trunc .. to*** Instruction: This instruction is used to truncate a value from one type to another, with the destination type specified by the "to" keyword.
    - ***zext .. to*** Instruction: This instruction is used to zero-extend a value from one type to another, with the destination type specified by the "to" keyword.
    - ***sext .. to*** Instruction: This instruction is used to sign-extend a value from one type to another, with the destination type specified by the "to" keyword.
    - ***fptrunc .. to*** Instruction: This instruction is used to truncate a floating-point value from one type to another, with the destination type specified by the "to" keyword.
    - ***fpext .. to*** Instruction: This instruction is used to extend a floating-point value from one type to another, with the destination type specified by the "to" keyword.
    - ***fptoui .. to*** Instruction: This instruction is used to convert a floating-point value to an unsigned integer, with the destination type specified by the "to" keyword.
    - ***fptosi .. to*** Instruction: This instruction is used to convert a floating-point value to a signed integer, with the destination type specified by the "to" keyword.
    - ***uitofp .. to*** Instruction: This instruction is used to convert an unsigned integer to a floating-point value, with the destination type specified by the "to" keyword.
    - ***sitofp .. to*** Instruction: This instruction is used to convert a signed integer to a floating-point value, with the destination type specified by the "to" keyword.
    - ***ptrtoint .. to*** Instruction: This instruction is used to convert a pointer value to an integer, with the destination type specified by the "to" keyword.
    - ***inttoptr .. to*** Instruction: This instruction is used to convert an integer value to a pointer, with the destination type specified by the "to" keyword.
    - ***bitcast .. to*** Instruction: This instruction is used to reinterpret a value from one type to another, with the destination type specified by the "to" keyword.
    - ***addrspacecast .. to*** Instruction: This instruction is used to convert a value from one address space to another, with the destination type specified by the "to" keyword.
6. **Other operations**
    - ***icmp*** Instruction: this instruction performs an integer comparison and returns a boolean value based on the outcome of the comparison.
    - ***fcmp*** Instruction: this instruction performs a floating-point comparison and returns a boolean value based on the outcome of the comparison.
    - ***phi*** Instruction: this instruction performs a phi function, which is used in control flow analysis to handle multiple incoming values from different control flow paths.
    - ***select*** Instruction: this instruction performs a select operation, which is used to choose one of two values based on a condition.
    - ***freeze*** Instruction: this instruction is used to "freeze" a value, which is to say it makes sure that the value does not change in the future.   
    - ***call*** Instruction: this instruction is used to call a function or invoke a certain block.
    - ***va_arg*** Instruction: this instruction is used to access the next argument passed in a variable argument function.


