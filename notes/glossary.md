# Glossary

Short explanations of terms that appear in the handouts. Entries are alphabetical. Each has a plain definition, a small example and a pointer to where the term is used.

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

**See:** [Handout 2, section 1.2](../handouts/02-basics.md) and [`division_demo.cpp`](../examples/02-basics/division_demo.cpp).

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

**See:** [Handout 2, section 5.2](../handouts/02-basics.md) (Fibonacci uses `long long` for this reason).
