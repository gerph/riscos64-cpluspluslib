# libc++ RISC OS port

This repository contains LLVM libc++ 17.0.6 together with a RISC OS build in
[`RISCOS`](RISCOS) for the 64-bit GCC-based toolchain (`riscos64-c++`).

The RISC OS port exports the libc++ headers and builds the `c++` library in a
layout suitable for the RISC OS build system. The current work has focused on
getting a practical subset of libc++ building, linking, and running under the
current GCC 12 based environment.

## Current status

The following areas have passing 64-bit smoke tests in the RISC OS build:

- Header export and inclusion through `-nostdinc++` and `-isystem C:c++`.
- Basic algorithms, arrays, spans, tuples, optionals, and type traits.
- Runtime linking for `std::string`, `std::vector`, `std::sort`, and integral
  `std::to_chars`.
- Smart pointers: `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
- Sequence containers: `std::deque`, `std::list`, and `std::forward_list`.
- Associative containers: `std::map`, `std::set`, and `std::unordered_map`.
- Character conversion: integer `std::to_chars` and `std::from_chars`, plus
  floating-point `std::to_chars`.
- Numeric algorithms: `std::iota`, `std::accumulate`, `std::partial_sum`,
  `std::adjacent_difference`, `std::inner_product`, `std::gcd`, and `std::lcm`.
- Narrow iostream support for `std::cout`, `std::cerr`, `std::cin`,
  `std::ostringstream`, `std::istringstream`, `std::stringstream`, simple
  string formatting, and integral formatted stream output.

## Known limitations

- Exceptions and RTTI are not supported by the current test configuration; the
  library and runtime tests build with `-fno-exceptions -fno-rtti`.
- Threads, monotonic clock support, filesystem, random-device support,
  wide-character support, and the parallel STL backend are disabled in
  `RISCOS/__config_site`.
- libc++ library aligned allocation is disabled because the RISC OS C library
  does not currently provide `aligned_alloc`.
- Floating-point `std::from_chars` is not available in the current
  configuration.
- Floating-point formatted iostream output is not working yet; the current
  locale-backed `num_put` path still aborts under RISC OS.
- Locale-dependent facilities beyond the currently tested narrow iostream path
  should be treated as unsupported.

## RISC OS build and tests

Build details and the smoke test list are documented in
[`RISCOS/README.md`](RISCOS/README.md).
