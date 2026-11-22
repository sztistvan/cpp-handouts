# Glossary

Short explanations of terms that appear in the handouts. Entries are alphabetical. Each has a plain definition, a small example and a pointer to where the term is used. The outputs shown were produced with g++ 13.1 (MinGW).

**Contents:** [Bounds checking](#bounds-checking) · [Buffer overflow](#buffer-overflow) · [Compile time and run time](#compile-time-and-run-time) · [Compiler warning and error](#compiler-warning-and-error) · [Container](#container) · [Convergence](#convergence) · [Copy and reference](#copy-and-reference) · [Declaration and definition](#declaration-and-definition) · [Default argument](#default-argument) · [Deterministic chaos and bifurcation](#deterministic-chaos-and-bifurcation) · [Exit code](#exit-code) · [Floating-point number](#floating-point-number) · [Function signature](#function-signature) · [Implicit conversion, cast, narrowing](#implicit-conversion-cast-narrowing) · [Integer division](#integer-division) · [Iteration](#iteration) · [Literal](#literal) · [Magic number](#magic-number) · [NaN and infinity](#nan-and-infinity) · [npos](#npos) · [Off-by-one error](#off-by-one-error) · [Overflow](#overflow) · [Overloading](#overloading) · [Parallel vectors](#parallel-vectors) · [Pass by value, by reference, by const reference](#pass-by-value-by-reference-by-const-reference) · [Range-based for loop](#range-based-for-loop) · [Scope](#scope) · [Sentinel value](#sentinel-value) · [size_t and unsigned numbers](#size_t-and-unsigned-numbers) · [Stack overflow](#stack-overflow) · [Stream and flush](#stream-and-flush) · [Time complexity](#time-complexity) · [Tolerance](#tolerance) · [Truncation (discretization) error](#truncation-discretization-error) · [Undefined behavior](#undefined-behavior) · [Uninitialized variable](#uninitialized-variable) · [Vector](#vector)

---

## Bounds checking

**What:** testing, before an element is accessed, that its index lies inside the container. C++ arrays and `vector[...]` do **not** do this. `vector::at(...)` does.

**Example:**

```cpp
std::vector<int> v = {1, 2, 3};
v[5];     // no check: undefined behavior
v.at(5);  // throws std::out_of_range
```

The message of the `at(5)` exception: `vector::_M_range_check: __n (which is 5) >= this->size() (which is 3)`.

**Why it matters:** an index error without a check does not announce itself, the program just reads or writes other data. `at()` is slower but turns the silent error into a visible one, which is good while you are still debugging.

**See also:** [Buffer overflow](#buffer-overflow), [Undefined behavior](#undefined-behavior). Used in [Handout 2, section 1.5](../handouts/02-basics.md).

---

## Buffer overflow

**What:** writing past the end of an array (a *buffer*), so that neighboring memory is overwritten.

**Example (a bug):**

```cpp
int samples[3];
samples[3] = 42; // valid positions are 0, 1, 2: this overwrites something else
```

**Why it matters:** it is undefined behavior. Typical effects range from wrong results somewhere else in the program, to crashes, to security holes: attackers have long used buffer overflows to take over programs. Keep the size of an array next to it, loop with `i < count`, and prefer `std::vector` (handout 4).

**See also:** [Bounds checking](#bounds-checking), [Undefined behavior](#undefined-behavior).

---

## Compile time and run time

**What:** two phases in which a problem can appear. *Compile time* is while the compiler translates your source code. *Run time* is later, while the finished program runs.

**Example:** a missing semicolon is found at compile time, and no program is produced. Typing `abc` where a number is expected is only found at run time, when the program reads it.

**Why it matters:** compile-time problems are the easy ones: the compiler shows the file, line and a message. Run-time problems appear only for certain inputs, so they need checks in the program (for example `if (!(std::cin >> a >> b))`) and tests.

**See:** [Handout 1, section 5](../handouts/01-hello.md) (compiler errors) and [`greeting.cpp`](../examples/01-hello/greeting.cpp) (a run-time check).

---

## Compiler warning and error

**What:** an *error* means the program is not valid. No program is produced. A *warning* means the program can be built, but the compiler suspects a mistake.

**Example:** with `-Wall -Wextra`, an unused variable gives a warning:

```text
warn.cpp:1:18: warning: unused variable 'unused' [-Wunused-variable]
```

Writing `int b{3.7};` is an **error**:

```text
error: narrowing conversion of '3.7000000000000002e+0' from 'double' to 'int' [-Wnarrowing]
```

**Why it matters:** warnings are free bug reports. Switch them on (`-Wall -Wextra`, already done in this repository's `CMakeLists.txt`) and read them until you understand each one. The text in brackets names the warning, which helps when searching.

**See:** [Handout 1, section 5](../handouts/01-hello.md).

---

## Container

**What:** an object that holds a collection of values. The standard library offers several: `std::string` (characters), `std::vector` (a growing row), and later `std::map` and `std::set`. They share a common style: they know their `size()`, can be looped over with a [range-based for loop](#range-based-for-loop), and work with the same library algorithms.

**Example:**

```cpp
std::vector<double> rates = {98.2, 101.5, 99.8};   // a row of numbers
std::string seq = "ATGGCC";                         // a row of characters
```

**Why it matters:** the choice of container decides how easy and how fast a task is. `std::vector` is the default choice, and others fit special jobs, for example a `map` for looking up values by name (handout 6). Learning one container well makes the others easy.

**See also:** [Vector](#vector), [Range-based for loop](#range-based-for-loop), [Bounds checking](#bounds-checking). Used in [Handout 4](../handouts/04-vectors.md).

---

## Convergence

**What:** an iterative method *converges* if its repeated steps get closer and closer to the answer. How fast it does is the *rate* of convergence. With **quadratic** convergence the number of correct digits roughly **doubles** with every step. With *linear* convergence the error shrinks by a constant factor per step.

**Example:** Newton's method for the square root of 2 (handout 3). The error after each step:

```text
step 0: 5.86e-01
step 1: 8.58e-02
step 2: 2.45e-03
step 3: 2.12e-06
step 4: 1.59e-12
step 5: 2.22e-16     (the limit of a double)
```

**Why it matters:** the rate tells you how many steps to expect. A method that does not converge never reaches the answer, so every iteration needs a stop rule: a [tolerance](#tolerance) and a maximum number of steps (`max_iterations`).

**See also:** [Iteration](#iteration), [Tolerance](#tolerance). Used in [Handout 3, section 6.3](../handouts/03-functions.md) and [`newton_sqrt.cpp`](../examples/03-functions/newton_sqrt.cpp).

---

## Copy and reference

**What:** assigning a `std::vector` or `std::string` to a new variable makes an **independent copy of all elements**. A *reference* (`&`) is just another name for the same object: no copy is made, and a change through one name is visible through the other.

**Example:**

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = a;          // a copy
b[0] = 99;                       // a[0] is still 1

std::vector<int>& r = a;         // another name for a
r[0] = 99;                       // a[0] is now 99
```

**Why it matters:** there are two surprises. If you know a language where `b = a` makes both names share one list (Python does this), C++ behaves differently: it copies. And copying a vector with millions of elements takes time, which is why big data are passed to functions by `const` reference and range-for loops over big elements use `const std::string&` and the like.

**See also:** [Pass by value, by reference, by const reference](#pass-by-value-by-reference-by-const-reference), [Range-based for loop](#range-based-for-loop). Used in [Handout 4, sections 1.2 and 1.4](../handouts/04-vectors.md).

---

## Declaration and definition

**What:** a *declaration* tells the compiler that a name exists and what type or signature it has. A *definition* supplies the actual thing: the function body, or the memory of the variable. A function may be declared several times but defined only once. `int n = 5;` is a declaration and a definition in one.

**Example:**

```cpp
double mean(double a, double b);   // declaration (prototype): ends with ;

double mean(double a, double b)    // definition: has a body
{
    return (a + b) / 2.0;
}
```

**Why it matters:** C++ reads the file from top to bottom, so a function must be declared **before** it is used. Otherwise the error is `'mean' was not declared in this scope`. If a function is declared and used but never defined, the program compiles and the **linker** reports "undefined reference".

**See also:** [Function signature](#function-signature), [Compile time and run time](#compile-time-and-run-time). Used in [Handout 3, section 1.1](../handouts/03-functions.md) and [`tour.cpp`](../examples/03-functions/tour.cpp).

---

## Default argument

**What:** a value given in the function's parameter list that is used when the caller leaves that argument out.

**Example:**

```cpp
double to_micro(double value, double factor = 1.0e6)
{
    return value * factor;
}

to_micro(0.25)           // 250000   (factor = 1.0e6)
to_micro(0.25, 1000.0)   // 250      (factor given)
```

**Why it matters:** it shortens calls for the usual case, such as a standard temperature or a tolerance. Default values must be the **last** parameters. Write the default in the declaration only, not again in the definition. Too many defaults make calls hard to read.

**See also:** [Overloading](#overloading), [Tolerance](#tolerance). Used in [Handout 3, section 1.3](../handouts/03-functions.md) and [`ideal_gas.cpp`](../examples/03-functions/ideal_gas.cpp).

---

## Deterministic chaos and bifurcation

**What:** *Deterministic* means a fixed rule without any randomness. *Chaos* means that, despite this, the long-run behavior looks irregular and depends very sensitively on the starting values. A *bifurcation* is a parameter value at which the long-run behavior changes qualitatively, for example from one settled value to a two-value cycle.

**Example:** in the logistic growth model of handout 2, `r = 0.4` settles at 1000, `r = 2.2` alternates between two values, `r = 2.5` between four, and `r = 2.8` never repeats. The splitting at `r = 2` is a bifurcation.

**Why it matters:** the simple model fits in a few lines of code. The program can simulate behavior that you would not guess from the formula, so a simulation result needs interpretation, not just trust.

**See:** [Handout 2, section 2](../handouts/02-basics.md), the [bifurcation diagram](../figures/02_logistic_bifurcation.png) and [`logistic_bifurcation.cpp`](../examples/02-basics/logistic_bifurcation.cpp). Reference: R. M. May, *Nature* **261**, 459-467 (1976), doi:[10.1038/261459a0](https://doi.org/10.1038/261459a0).

---

## Exit code

**What:** the integer that `main` returns, which the program hands back to the operating system. By convention `0` means success, anything else means failure.

**Example:** [`greeting.cpp`](../examples/01-hello/greeting.cpp) returns `1` when the input is not a number. In PowerShell the last exit code is in `$LASTEXITCODE`, in cmd.exe in `%ERRORLEVEL%`.

```powershell
.\greeting.exe
$LASTEXITCODE
```

**Why it matters:** scripts and batch jobs use the exit code to find out whether a step worked, so a failing program should not return `0`. A crashed program has an exit code too, for example a large negative number on Windows (see [Stack overflow](#stack-overflow)).

**See:** [Handout 1, section 2](../handouts/01-hello.md).

---

## Floating-point number

**What:** the way computers store decimal numbers (`double`, `float`): a limited number of significant digits, stored in binary. A `double` carries about 15 decimal digits.

**Example:**

```cpp
std::cout << std::setprecision(17) << 0.1 + 0.2;  // 0.30000000000000004
0.1 + 0.2 == 0.3                                    // false
```

Many decimal fractions, such as 0.1, have no exact binary representation, just as 1/3 has no exact decimal one.

**Why it matters:** results are accurate to many digits, but rarely exact, and small errors can accumulate. Never test two `double` values for equality with `==`. Compare with a tolerance (`std::abs(a - b) < 1e-9`), or restructure the test.

**See also:** [NaN and infinity](#nan-and-infinity), [Integer division](#integer-division). Used in [Handout 2, section 1.3](../handouts/02-basics.md). A dedicated note on floating-point pitfalls is planned.

---

## Function signature

**What:** the first line of a function: its return type, name and parameter list. It is everything a caller needs to know to use the function.

**Example:**

```cpp
double michaelis_menten(double vmax, double km, double substrate)
//  ^ return type   ^ name       ^ parameters
```

**Why it matters:** the compiler checks every call against the signature (number and types of the arguments). For [overloading](#overloading) only the name and the parameter types count: two functions cannot differ in the return type alone.

**See also:** [Declaration and definition](#declaration-and-definition), [Overloading](#overloading). Used in [Handout 3, section 1.1](../handouts/03-functions.md).

---

## Implicit conversion, cast, narrowing

**What:** C++ converts between number types automatically when it needs to (*implicit conversion*). A *cast* is a conversion that you request explicitly, with `static_cast<type>(value)`. *Narrowing* is a conversion that may lose information, such as `double` to `int`.

**Example:**

```cpp
int a = 3.7;                      // a is 3: the decimals are cut off, and no warning appears
int b{3.7};                       // error: narrowing conversion
double d = static_cast<double>(7) / 2;  // 3.5: explicit and visible
```

**Why it matters:** an implicit narrowing conversion silently changes your values. Writing initial values with braces (`int b{...}`) makes the compiler reject narrowing, and `static_cast` shows the reader that the conversion is intentional.

**See also:** [Integer division](#integer-division). Used in [Handout 2, sections 1.2 and 3](../handouts/02-basics.md).

---

## Integer division

**What:** when both operands of `/` are integers, C++ divides and **throws away the decimals** (it truncates toward zero). The result is again an integer.

**Example:**

```cpp
7 / 2      // 3     (not 3.5)
-7 / 2     // -3    (toward zero, not -4)
-7 % 2     // -1    (the remainder keeps the sign of the dividend)
1 / 3      // 0
1.0 / 3    // 0.333333   (one decimal operand makes the division decimal)
```

**Why it matters:** the compiler does not complain, because the program is legal. A mean or a fraction computed with integers is quietly wrong. Convert one operand first: `static_cast<double>(total) / n`, or multiply by `1.0`. The order of operations matters too: `3 / 4 * 100` is `0`, while `100.0 * 3 / 4` is `75`.

**See also:** [Implicit conversion, cast, narrowing](#implicit-conversion-cast-narrowing). Used in [Handout 2, section 1.2](../handouts/02-basics.md) and [`division_demo.cpp`](../examples/02-basics/division_demo.cpp).

---

## Iteration

**What:** one round of a repeated process. A loop runs through *iterations*, and an *iterative method* improves an estimate in each of them until it is good enough.

**Example:** every pass of a `for` loop is one iteration. In Newton's method each call of `newton_step` is one iteration, and the method stops when the change is smaller than the [tolerance](#tolerance) or after `max_iterations`.

**Why it matters:** counting iterations measures the work and shows the [convergence](#convergence). A loop whose condition never becomes false iterates forever, so give iterative methods a maximum number of iterations.

**See also:** [Convergence](#convergence), [Tolerance](#tolerance). Used in [Handout 2, section 1.4](../handouts/02-basics.md) and [Handout 3, section 6.3](../handouts/03-functions.md).

---

## Literal

**What:** a value written directly in the source code. Its type is given by how you write it.

**Example:**

| Literal | Type | Note |
|---|---|---|
| `42` | `int` | whole number |
| `1000.0` | `double` | the decimal point makes it a `double` |
| `1e-3` | `double` | scientific notation, 0.001 |
| `3.14f` | `float` | the suffix `f` makes it a `float` |
| `'A'` | `char` | one character, single quotes |
| `"text"` | text (string literal) | double quotes |
| `true`, `false` | `bool` | |

**Why it matters:** `1000` and `1000.0` are different types. `1000` in a division makes it an integer division. Write the decimal point whenever you mean a decimal number.

**See also:** [Integer division](#integer-division), [Magic number](#magic-number).

---

## Magic number

**What:** a number that appears in code without a name or explanation, so a reader has to guess what it means.

**Example:**

```cpp
amount *= 0.917004;                                  // what is 0.917004?

const double half_life = 8.0;                        // days
const double daily_factor = std::pow(0.5, 1.0 / half_life);
amount *= daily_factor;                              // clear, and changes with the half-life
```

**Why it matters:** when the half-life changes, the magic number must be found and recalculated by hand, and might be missed in one place. Give every meaningful constant a name (`const`).

**See also:** [Literal](#literal). Used in [`half_life.cpp`](../examples/02-basics/half_life.cpp).

---

## NaN and infinity

**What:** special `double` values for results that have no ordinary number. *Infinity* (`inf`) results from, for example, dividing a non-zero number by `0.0` or exceeding the largest `double`. *NaN* ("not a number") results from undefined operations such as `0.0 / 0.0`.

**Example:**

```text
1.0 / 0.0       = inf
-1.0 / 0.0      = -inf
0.0 / 0.0       = nan
inf + 1         = inf
inf - inf       = nan
sqrt(-1)        = nan
DBL_MAX * 10    = inf          (the largest double, times 10)
nan == nan      is false       (use std::isnan(x) to test)
```

**Why it matters:** floating-point arithmetic does not stop or crash. It carries `inf` or `nan` through all later calculations, so a single bad value can turn a whole table of results into `nan`. Because `nan` is not equal to anything, not even itself, test with `std::isnan(x)` and `std::isinf(x)` (`<cmath>`). Other compilers may print these values differently. Integer division by zero is a different case: it is undefined behavior, not `inf`.

**See also:** [Floating-point number](#floating-point-number), [Overflow](#overflow), [Undefined behavior](#undefined-behavior).

---

## npos

**What:** the constant `std::string::npos` ("no position"). `find` returns it when the text is not found. It is the largest value of the unsigned type `size_t`, not a negative number.

**Example:**

```cpp
std::string seq = "ATGGCC";
seq.find("GCC")                        // 3
seq.find("XYZ") == std::string::npos   // true: not found
std::string::npos                      // 18446744073709551615 on a 64-bit system
```

**Why it matters:** `npos` is a [sentinel value](#sentinel-value) that looks like a huge but valid position. If you use the result of `find` without comparing it with `npos`, you index far outside the string. Always compare first.

**See also:** [Sentinel value](#sentinel-value), [size_t and unsigned numbers](#size_t-and-unsigned-numbers). Used in [Handout 4, sections 1.5 and 5](../handouts/04-vectors.md) and [`grid.cpp`](../examples/04-vectors/grid.cpp).

---

## Off-by-one error

**What:** a loop or index that is wrong by exactly one, usually from `<` versus `<=`, or from counting positions from 1 instead of 0.

**Example:**

```cpp
int ids[5] = {10, 20, 30, 40, 50};
for (int i = 0; i <= 5; ++i) {   // wrong: visits i = 0 to 5, six elements
    std::cout << ids[i];          // ids[5] does not exist
}
```

**Why it matters:** the typical result is reading or writing one element past the end (see [Buffer overflow](#buffer-overflow)), or one round too few. Count from 0 and use `i < count`.

**See also:** [Bounds checking](#bounds-checking). Used in [Handout 2, section 1.4](../handouts/02-basics.md).

---

## Overflow

**What:** a result is too large for the type that has to hold it. Every integer type has a fixed range, set by its number of bits. A typical `int` has 32 bits and holds values up to 2 147 483 647 (`INT_MAX`, in `<climits>`).

**Example:** the 47th Fibonacci number is 2 971 215 073, which is larger than `INT_MAX`. Computed in an `int`, it overflows. Computed in a `long long` (64 bits, up to about 9.2 · 10^18), it is fine.

For unsigned types, C++ defines what happens: the value **wraps around**. The largest `unsigned int` is 4 294 967 295, and adding 1 gives `0`:

```cpp
unsigned int u = UINT_MAX; // 4294967295
u + 1u                      // 0
```

For ordinary (signed) integers the C++ standard does **not** define the result. This is called *undefined behavior*: the program may print a wrong number, crash, or appear to work. On typical computers it often wraps around to a large negative number, but you must not rely on it.

**Why it matters:** nothing announces an overflow. The program continues with a wrong number, for example a negative population count. Before using an integer type, estimate the largest value it will ever have to hold. If in doubt, use `long long`.

**See also:** [Undefined behavior](#undefined-behavior), [NaN and infinity](#nan-and-infinity) (what decimal numbers do instead), [Buffer overflow](#buffer-overflow) and [Stack overflow](#stack-overflow) (different problems with a similar name). Used in [Handout 2, section 5.2](../handouts/02-basics.md) (Fibonacci uses `long long` for this reason).

---

## Overloading

**What:** several functions with the **same name** but different parameter lists. The compiler chooses the one that fits the arguments of the call.

**Example:**

```cpp
double mean(double a, double b);            // two values
double mean(double a, double b, double c);  // three values

mean(4.0, 7.0)         // 5.5
mean(4.0, 7.0, 10.0)   // 7
```

**Why it matters:** it keeps names simple when the same operation works on different inputs. Use it only when the functions really do the same thing. Overloads that behave differently under one name confuse the reader.

**See also:** [Function signature](#function-signature), [Default argument](#default-argument). Used in [Handout 3, section 1.3](../handouts/03-functions.md).

---

## Parallel vectors

**What:** several vectors that describe the same set of things, where entry `i` of every vector belongs together.

**Example:** from the element table of handout 4:

```cpp
std::vector<std::string> symbols = {"H", "C", "N", "O", "P"};
std::vector<double> masses = {1.008, 12.011, 14.007, 15.999, 30.974};
// symbols[3] and masses[3] both describe oxygen
```

**Why it matters:** nothing enforces that the vectors have the same length or the same order. If you insert, delete or sort one of them, the matching silently breaks and a mass is attached to the wrong element. The remedy is **one record per item**: a `struct` (handout 6) or a class (handout 9). Parallel vectors are acceptable only for small, fixed data.

**See also:** [Vector](#vector). Used in [Handout 4, section 7](../handouts/04-vectors.md) and [`element_table_v2.cpp`](../examples/04-vectors/element_table_v2.cpp).

---

## Pass by value, by reference, by const reference

**What:** three ways to give an argument to a function.

| Way | Parameter | What happens |
|---|---|---|
| by value | `int n` | the function gets a **copy**. The caller's variable cannot change. |
| by reference | `int& n` | the function works on the **original**. Changes are visible to the caller. |
| by `const` reference | `const std::string& s` | no copy, and the function may **not** change it |

**Example:**

```cpp
void increment_copy(int n) { ++n; }
void increment(int& n)     { ++n; }

int counter = 10;
increment_copy(counter);   // counter is still 10
increment(counter);        // counter is now 11
```

**Why it matters:** the difference is invisible at the call site, and a function that works on a copy "does nothing" without any error message. Rule of thumb: small values by value, big values that are only read by `const` reference, and a variable that must change by reference.

**See also:** [Scope](#scope). Used in [Handout 3, section 1.2](../handouts/03-functions.md) and [`swap_demo.cpp`](../examples/03-functions/swap_demo.cpp).

---

## Range-based for loop

**What:** a loop that visits every element of a [container](#container) in order: `for (type name : container)`. It has no index, so it cannot have an [off-by-one error](#off-by-one-error).

**Example:**

```cpp
for (double t : temperatures)         // t is a copy of each element
for (double& t : temperatures)        // t is the element itself: changes are kept
for (const std::string& s : names)    // no copy, read only
```

**Why it matters:** a copy (no `&`) is fine for small values, but changes are lost and every round copies the element, which is slow for big ones. Never add or remove elements of the container inside the loop ([undefined behavior](#undefined-behavior)). If you need the position or the neighbors of an element, use an index loop instead.

**See also:** [Copy and reference](#copy-and-reference), [Pass by value, by reference, by const reference](#pass-by-value-by-reference-by-const-reference), [Iteration](#iteration). Used in [Handout 4, section 1.2](../handouts/04-vectors.md).

---

## Scope

**What:** the part of the program in which a name is visible. A variable declared inside a function (or inside any `{ }`) exists only there, and disappears at the closing brace.

**Example:** a function cannot see the variables of `main`. If it needs a value, the value must come in as a parameter. Two functions can each have their own variable `x` without interfering. A `const` declared outside every function is visible in the whole file.

**Why it matters:** local variables keep functions independent and easy to test. If an inner variable has the same name as an outer one, the inner one *hides* the outer one, which can cause confusing bugs. Avoid file-level variables that change.

**See also:** [Pass by value, by reference, by const reference](#pass-by-value-by-reference-by-const-reference). Used in [Handout 3, section 1.4](../handouts/03-functions.md).

---

## Sentinel value

**What:** a special value of an ordinary type that is agreed to mean "nothing" or "no result". Also called a marker value.

**Example:** in the linear search, `-1` means "not found". It can never be a real position, because positions start at 0:

```cpp
int found_at = -1;                 // marker: not found
// ... search ...
if (found_at >= 0) { /* found */ }
```

**Why it matters:** the marker looks like a normal value, so it must be checked. If you forget and use `-1` as an index, you read memory outside the array. Later handouts show safer ways to say "no result".

**See also:** [Bounds checking](#bounds-checking), [Magic number](#magic-number). Used in [`linear_search.cpp`](../examples/02-basics/linear_search.cpp).

---

## size_t and unsigned numbers

**What:** `std::size_t` is the unsigned integer type used by `size()`, `length()` and positions. Unsigned numbers are never negative, and when they go below 0 they **wrap around** (this is defined for unsigned types). On a 64-bit system `size_t` has 8 bytes.

**Example:**

```cpp
std::vector<int> v;                 // empty
v.size() - 1                        // 18446744073709551615, not -1
int i = 0;
if (i < v.size()) { /* ... */ }     // compiler warning, see below
```

The warning of g++ with `-Wall -Wextra`:

```text
warning: comparison of integer expressions of different signedness: 'int' and
'std::vector<int>::size_type' {aka 'long long unsigned int'} [-Wsign-compare]
```

**Why it matters:** subtracting from a size can silently give a huge number. Write conditions with addition (`i + 1 < v.size()`), use a `std::size_t` index in loops, and count down with `i > 0` and `v[i - 1]`.

**See also:** [Overflow](#overflow), [Off-by-one error](#off-by-one-error), [npos](#npos), [Bounds checking](#bounds-checking). Used in [Handout 4, section 1.3](../handouts/04-vectors.md).

---

## Stack overflow

**What:** the program has run out of *stack* memory. The stack is the limited area where each function call keeps its local variables. It overflows typically when a function calls itself without ever stopping (*infinite recursion*), or when a function keeps very large arrays as local variables.

**Example:** a function that calls itself forever:

```cpp
int depth(int n) {
    volatile char pad[1024];       // each call needs 1 KB of stack
    pad[0] = 1;
    return depth(n + 1) + pad[0];  // never stops
}
```

This program printed its first line and then crashed. Its exit code on Windows was `-1073741571`, which is `0xC00000FD`, the code for a stack overflow.

**Why it matters:** the stack is much smaller (typically 1 to 8 MB) than the memory that is available to your program in total. A stack overflow is **not** the same as an integer overflow or a buffer overflow, even though the name is similar. Put large data in a `std::vector` (handout 4), which keeps its elements elsewhere, and always give a recursive function a case where it stops.

**See also:** [Exit code](#exit-code), [Overflow](#overflow).

---

## Stream and flush

**What:** a *stream* is a flow of characters into or out of a program (`std::cin` for input, `std::cout` for output). Output is usually collected in a *buffer* and sent out in chunks. To *flush* means to send the collected text out right away.

**Example:** `'\n'` starts a new line. `std::endl` starts a new line **and flushes**. `std::flush` only flushes.

```cpp
std::cout << "result\n";        // fast: may stay in the buffer for a while
std::cout << "result" << std::endl;  // flushes every time: slow for many lines
```

**Why it matters:** flushing thousands of lines is a typical reason why a program that prints a lot is slow. But if a program crashes, text still in the buffer may be lost, so flush before a risky step if you need to see how far the program got.

**See:** [Handout 1, section 2](../handouts/01-hello.md).

---

## Time complexity

**What:** a statement about how the amount of work grows with the size of the input, ignoring constant factors. It is written with a capital O: `O(n)` means the work grows in proportion to the input size `n`.

**Example:** linear search looks at up to `n` elements, so it is `O(n)`: ten times more data, about ten times more comparisons. In the program of handout 2, the missing ID needed all 8 comparisons for 8 elements. Two nested loops over `n` elements each are `O(n²)`: ten times more data means a hundred times more work.

**Why it matters:** with small data any method is fast. With large data, a method with lower complexity can be the difference between seconds and days. Counting operations, as the search example does, is a simple way to see it. Handout 3 compares linear search with binary search.

**See:** [Handout 2, section 3](../handouts/02-basics.md). Reference: T. H. Cormen et al., *Introduction to Algorithms*, 4th ed., MIT Press, 2022.

---

## Tolerance

**What:** how close counts as "good enough". A tolerance is used as a stop rule for an iterative method, and when two `double` values are compared. It can be *absolute* (a fixed amount, `1.0e-12`) or *relative* (a fraction of the value).

**Example:**

```cpp
if (std::abs(next - x) < tolerance) { return next; }   // stop when the change is small
```

In handout 3, Newton's method with a tolerance of `1.0e-3` still returned `1.414213562375`, correct to about 1e-12. The tolerance tests the size of the **last step**, and the error after a step is much smaller than the step itself.

**Why it matters:** `==` is not a reliable test for `double` values (see [Floating-point number](#floating-point-number)), so a tolerance is the usual replacement. Too loose gives poor results. Too tight (below what a `double` can resolve, about 1e-16 relative) may never be reached.

**See also:** [Convergence](#convergence), [Iteration](#iteration), [Default argument](#default-argument). Used in [Handout 3, section 6.3](../handouts/03-functions.md).

---

## Truncation (discretization) error

**What:** the error that comes from replacing an exact mathematical process (an integral, a derivative, continuous time, an infinite series) by a finite approximation. It is a property of the **method**, and differs from rounding error, which comes from the limited digits of a `double` (see [Floating-point number](#floating-point-number)).

**Example:** the trapezoid rule for the area under a curve (handout 3). Doubling the number of strips divides the error by about 4:

```text
     n          area       error     ratio
     1     52.489353   2.082e+01         -
     8     32.044074   3.703e-01      3.97
  1024     31.673787   2.265e-05      4.00
```

**Why it matters:** a smaller step (more strips, shorter time step) reduces this error, but costs more work, and at some point rounding errors take over. Knowing how the error shrinks with the step, here as 1/n², tells you how fine a step you need. Test the method against a case with a known exact answer.

**See also:** [Convergence](#convergence), [Floating-point number](#floating-point-number). Used in [Handout 3, section 3](../handouts/03-functions.md) and [`trapezoid.cpp`](../examples/03-functions/trapezoid.cpp).

---

## Undefined behavior

**What:** a situation for which the C++ standard prescribes **no** behavior at all. The program may crash, print a wrong number, appear to work, or behave differently on another compiler, another day or with other optimisation settings.

**Example (all of these are undefined):**

- reading or writing outside an array (`ids[5]` for five elements),
- overflow of a signed integer,
- integer division by zero,
- reading a variable that was never given a value.

**Why it matters:** the compiler is allowed to assume that undefined behavior never happens, so it can optimise your code in surprising ways. A program with undefined behavior may "work" for months and then fail. This is why the handouts insist on initialised variables, checked indices and enough range in the integer types.

**See also:** [Overflow](#overflow), [Buffer overflow](#buffer-overflow), [Bounds checking](#bounds-checking), [Uninitialized variable](#uninitialized-variable).

---

## Uninitialized variable

**What:** a variable declared without a value. Its content is whatever happened to be in that memory.

**Example:**

```cpp
int n;                      // no value
std::cout << n;             // undefined behavior: may print anything
int m = 0;                  // correct: always give a value
```

**Why it matters:** the result can differ from run to run, and the compiler may or may not warn you. Give every variable a value where you declare it.

**See also:** [Undefined behavior](#undefined-behavior). Used in [Handout 2, section 1.1](../handouts/02-basics.md).

---

## Vector

**What:** `std::vector<T>` (header `<vector>`) is a row of elements of type `T` that knows its size and can grow. The elements sit next to each other in memory, so access by index is fast.

**Example:**

```cpp
std::vector<double> temperatures = {36.6, 37.1, 38.4};
temperatures.push_back(36.9);    // append at the end
temperatures.size();             // 4
temperatures[0];                 // 36.6, no check of the index
temperatures.at(10);             // checked: throws std::out_of_range
std::vector<int> zeros(5, 0);    // five elements, all 0
```

**Why it matters:** `std::vector` is the default [container](#container) and replaces C arrays in almost all code: no separate count, no fixed size, and growing is cheap on average. One exception: `std::vector<bool>` behaves differently from all other vectors, so keep yes/no flags in a `std::vector<int>` instead.

**See also:** [Container](#container), [Bounds checking](#bounds-checking), [Range-based for loop](#range-based-for-loop), [size_t and unsigned numbers](#size_t-and-unsigned-numbers), [Copy and reference](#copy-and-reference). Used in [Handout 4](../handouts/04-vectors.md).
