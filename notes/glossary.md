# Glossary

Short explanations of terms that appear in the handouts. Entries are alphabetical. Each has a plain definition, a small example and a pointer to where the term is used. The outputs shown were produced with g++ 13.1 (MinGW).

**Contents:** [Bounds checking](#bounds-checking) · [Buffer overflow](#buffer-overflow) · [Compile time and run time](#compile-time-and-run-time) · [Compiler warning and error](#compiler-warning-and-error) · [Deterministic chaos and bifurcation](#deterministic-chaos-and-bifurcation) · [Exit code](#exit-code) · [Floating-point number](#floating-point-number) · [Implicit conversion, cast, narrowing](#implicit-conversion-cast-narrowing) · [Integer division](#integer-division) · [Literal](#literal) · [Magic number](#magic-number) · [NaN and infinity](#nan-and-infinity) · [Off-by-one error](#off-by-one-error) · [Overflow](#overflow) · [Sentinel value](#sentinel-value) · [Stack overflow](#stack-overflow) · [Stream and flush](#stream-and-flush) · [Time complexity](#time-complexity) · [Undefined behavior](#undefined-behavior) · [Uninitialized variable](#uninitialized-variable)

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
