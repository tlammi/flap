# Specification for flap Programming Language

This document describes the flap programming language.

## Introduction

Flap is an imperative programming language with support for functional programming.
It is influenced mainly by languages C++, Rust and Haskell.

## Lexical Analysis

Character set: ASCII (utf-8 maybe later):
```
a b c d e f g h i j k l m o p q r s t u v w x y z
A B C D E F G H I J K L M O P Q R S T U V W X Y Z
0 1 2 3 4 5 6 7 8 9
_ { } [ ] # ( ) < > % : ; . ? * + - / ^ & | ~ ! = @ $ , \ " '
```

Keywords:
```
for, in, as, is, mut, const
```

## Basics

### Declarations and Definitions

- Variable declaration: `var: i32`
- Variable definitions:
    - `var: i32 := 100`
    - `var := 100`
    - `var: mut i32 := 100`
    - `var: mut := 100`
- Function declaration: `func: () -> i32`
- Function short body: `func: () -> i32 := 100 * 20`
- Function long body:
    - ```
    func: () -> i32 := {
        myvar := 100
        return myvar * 10
    }
    ```
- Module definition: `module modulename`
- Namespace definition:
    - Whole file: `namespace namespace_name`
    - Part of the file `namespace namespace_name {}`

- Importing a module: `import modulename`
- Call a function from a namespace: `namespace_name::sample_function()`


### Builtin Types

- Integers:
    - signed: `i8, i16, i32, i64`
    - unsigned: `u8, u16, u32, u64`
- Floating point:
    - `f32, f64`
- Arrays of above types:
    - `[i8; 64]` -- Array of `i8` with `64` entries
- Slices:
    - `[u64]` -- Nonowning reference to a continuous range of `u64`s
- Unit type: `()`

### Control Flow
The language does not have normal control flow mechnisms like if, else or while
and instead relies on pattern matching and tail call optimizations for loops.
For loop is provided for iterating.

- Function pattern matching by value:
    - called if no pattern matches: `func: (i: i32) -> () := i`
    - pattern to match `func(0) => 100`

- Loops:
    ```
    loop: (i: i32) -> () := {
       loop(i-1)
    }
    loop: (0) => ()
    ```
- For loops:
    ```
    arr: [i8; 10] := {0,1,2,3,4,5,6,7,8,9}
    out: i64 := 0
    for i in arr {
        out += i
    }
    ```
