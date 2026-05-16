# RISC OS libc++ build

This directory contains the RISC OS AMU build for the libc++ sources in the
parent tree.

Build and export headers with:

```sh
riscos-amu export_hdrs
```

Build the library with:

```sh
riscos-amu
```

Build and export the library and headers with:

```sh
riscos-amu export
```

The makefile is configured for the 64-bit GCC-based RISC OS C++ wrapper
(`riscos64-c++`). Extensionless C++ headers are exported in place below
`<Exports$Dir>.Lib.c++`. Files with a `.h` suffix are exported to a sibling
`h` directory with the suffix removed; for example, `uchar.h` becomes
`<Exports$Dir>.Lib.c++.h.uchar`, and `__exception/exception.h` becomes
`<Exports$Dir>.Lib.c++.__exception.h.exception`. The library export targets
are `<Exports$Dir>.Lib.c++.o.libc++-64` and
`<Exports$Dir>.Lib.c++.o.libc++zm-64`.

This source tree is LLVM libc++ 17.0.6, which still supports GCC 12. The RISC
OS site configuration disables unavailable runtime features such as threads,
filesystem, localisation, random-device support, wide-character support, and
the parallel STL backend.

## Status

The following areas have passing 64-bit smoke tests:

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

The following areas are known not to work, or are intentionally disabled in
this port:

- Exceptions and RTTI are not supported by the current test configuration; the
  library and runtime tests build with `-fno-exceptions -fno-rtti`.
- Threads, monotonic clock support, filesystem, localisation, random-device
  support, wide-character support, and the parallel STL backend are disabled in
  `__config_site`.
- libc++ library aligned allocation is disabled because the RISC OS C library
  does not currently provide `aligned_alloc`.
- Floating-point `std::from_chars` is not available in the current
  configuration.
- Iostreams and locale-dependent facilities are not currently covered by
  passing tests and should be treated as unsupported until tested.

## Tests

Small 64-bit smoke tests are provided below `tests`. They build absolutes using
`-nostdinc++` and `-isystem C:c++`, so they check that the exported libc++
headers are usable through the RISC OS include path and that the resulting
programs can link against `C:c++.o.libc++-64`.

Build the library exports first:

```sh
riscos-amu export
```

Then build and run a test from its directory with:

```sh
cd tests/<test-name>
riscos-amu BUILD64=1
riscos-build-run --64 aif64/<component>,ff8 --command <component>
```

The passing smoke tests are:

- `tests/header-basics`: exported header layout, `std::array`, `std::span`, `std::tuple`, `std::optional`, and basic algorithms.
- `tests/runtime-link`: `std::string`, `std::vector`, `std::sort`, and integral `std::to_chars`.
- `tests/memory-basics`: `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, and smart pointers stored in `std::vector`.
- `tests/associative-basics`: ordered and unordered containers with string keys.
- `tests/sequence-basics`: `std::deque`, `std::list`, and `std::forward_list`.
- `tests/charconv-basics`: integer `std::to_chars` and `std::from_chars`, plus floating-point `std::to_chars`.
- `tests/numeric-basics`: `std::iota`, `std::accumulate`, `std::partial_sum`, `std::adjacent_difference`, `std::inner_product`, `std::gcd`, and `std::lcm`.
- `tests/comparison-basics`: three-way comparison, generated comparison operators, pairs, tuples, and lexicographical comparison helpers.
- `tests/iterator-basics`: `std::distance`, `std::next`, `std::prev`, `std::reverse_iterator`, and `std::iter_swap`.
- `tests/ranges-basics`: `std::ranges::sort`, `std::ranges::find`, `std::ranges::all_of`, `std::ranges::copy`, and simple `std::views` pipelines.
