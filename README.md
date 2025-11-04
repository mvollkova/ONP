# ONP  
Calculator ONP (odwrotna notacja polska / reverse Polish notation)


## Input:

- `n` – number of formulas  
- `n` formulas, each in the form given below.

Each formula is a valid expression in infix notation with functions and ends with a dot (`.`).  
Each token is separated by whitespace characters.  
Each operand is a positive integer (although the result of an operation might be negative).  
Each operator is a single character and every function name consists only of capital letters.

The following operations are available, in the ascending order of priority:

- `a + b`, `a - b`
- `a * b`, `a / b` — all operations are made on integers, results of division are rounded down (standard C `/` operator). You cannot divide by 0.
- `IF(a, b, c)` — if `a > 0` return `b`, otherwise `c`
- `N a` — unary negation, i.e. `-a`
- `MIN(a1, a2, ...)`, `MAX(a1, a2, ...)` — functions with no restriction on the number of parameters
- `( ... )` — parentheses

---

## Output:

For each formula, the program prints:

1. the formula in the postfix notation;
2. before executing each operation print the operator or function and the content of the stack;
3. the final result;
4. if you encounter a division by 0, print "ERROR" and move to the next expression.
