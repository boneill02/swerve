# Code Style Guidelines

Contributors should aim to stick to this style when submitting code for swerve.
This is adapted from the [suckless.org coding
style](https://suckless.org/coding_style/).

## 1. File Layout

1. Comment with license, optional description of file
2. Headers
3. Macros
4. Types
5. Function declarations grouped alphabetically
6. Global variables
7. Function definitions grouped alphabetically

## 2. C Features

1. Use C99 without extensions, as according to ISO/IEC 9899:1999
2. Use `/* */` for sections of code, `//` for notes on a single line

## 3. Code Blocks

1. `{` on the same line preceded by one space (except functions).
2. `}` on new line unless continuing statement (`if else`, `do while`, ...)
3. Use a block for a single statement if the inner statement needs a block.
4. If one branch of a statement needs a block, give all of them blocks.

## 4. Leading Whitespace

1. Use tabs for indentation and spaces for alignment.
2. Use spaces for multiline macros because that is considered aligning.

## 5. Functions

1. Return type, modifiers, name, and argument list on the same line.
2. Opening `{` on its own line.
3. Functions not used outside of source/header unit should be declared `static`.

## 6. Variables

1. Global variables not used outside of source/header unit should be declared
   `static`.
2. In declaration of pointers, the `*` is adjacent to the variable name, not
   type.

## 7. Keywords

1. Use a space after `if`, `for`, `while`, `switch`, as they are not function
   calls.
2. Do not use a space after the `(` or before the `)`.
3. Use `()` with `sizeof`.
4. Do not use a space with `sizeof()`.

## 8. Headers

1. Place system/libc headers first in alphabetical order, using `<>`
2. Place local headers after an empty line in alphabetical order, using `""`.
3. Avoid cyclic header inclusion dependencies.

## 9. User Defined Types

1. Use `CamelCase` for type definitions.
2. Do not use `_t` suffix.
3. Do not typedef builtin types.

## 10. Line Length

1. Keep lines <=80 characters.

## 11. Boolean Values

1. Do not use `bool` types (instead use integers)

## 12. Handling Errors

1. Always test against `0`, not `1` or `-1`.
2. Use `goto` to cleanup when necessary instead of multiple nested levels.
3. `return` early on failures instead of multiple nested levels.
4. Unreachable code should have a NOTREACHED comment.

## 13. Enums and #define

1. Use enums for values that are grouped semantically, otherwise `#define`.
