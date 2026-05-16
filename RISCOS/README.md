# RISC OS libc++ tests

This directory contains the RISC OS AMU build for the libc++ sources in the
parent tree, plus the 64-bit smoke tests for the current port.

Project status, supported areas, and known limitations are summarised in the
[top-level README](../README.md).

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
- `tests/string-basics`: `std::string`, `std::string_view`, `find`, `substr`, `append`, `replace`, `starts_with`, and `ends_with`.
- `tests/utility-basics`: `std::optional`, `std::pair`, `std::tuple`, `std::exchange`, `std::move`, and `std::variant`.
- `tests/chrono-basics`: `std::chrono::duration`, `std::chrono::time_point`, and `duration_cast`/`time_point_cast` arithmetic.
- `tests/bit-basics`: `std::popcount`, `std::countr_zero`, `std::countl_zero`, `std::bit_width`, `std::has_single_bit`, `std::bit_floor`, `std::bit_ceil`, `std::rotl`, and `std::rotr`.
- `tests/memory-basics`: `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, and smart pointers stored in `std::vector`.
- `tests/associative-basics`: ordered and unordered containers with string keys.
- `tests/sequence-basics`: `std::deque`, `std::list`, and `std::forward_list`.
- `tests/charconv-basics`: integer `std::to_chars` and `std::from_chars`, plus floating-point `std::to_chars`.
- `tests/numeric-basics`: `std::iota`, `std::accumulate`, `std::partial_sum`, `std::adjacent_difference`, `std::inner_product`, `std::gcd`, and `std::lcm`.
- `tests/comparison-basics`: three-way comparison, generated comparison operators, pairs, tuples, and lexicographical comparison helpers.
- `tests/iterator-basics`: `std::distance`, `std::next`, `std::prev`, `std::reverse_iterator`, and `std::iter_swap`.
- `tests/ranges-basics`: `std::ranges::sort`, `std::ranges::find`, `std::ranges::all_of`, `std::ranges::copy`, and simple `std::views` pipelines.
- `tests/algorithm-basics`: `std::sort`, `std::binary_search`, `std::lower_bound`, `std::upper_bound`, `std::remove_if`, `std::copy`, `std::reverse`, `std::rotate`, `std::for_each`, `std::accumulate`, and `std::minmax_element`.
- `tests/iostream-basics`: narrow `std::cout`, `std::cerr`, and `std::cin` support; this test expects `input,ffe` to contain `hello from cin` on the first line and `Q` on the second, and is run with `--command 'exec input,ffe' --command 'CxxIO'`.
- `tests/iostream-format`: `std::ostringstream`, `std::istringstream`, `std::stringstream`, stream positioning, unformatted read/write, and simple width/fill formatting on strings.
- `tests/iostream-numeric`: integral and floating-point formatted stream output, including `std::hex`, `std::showbase`, `std::showpos`, `std::fixed`, `std::scientific`, and `std::setprecision`.
- `tests/iostream-numeric-input`: formatted integral, floating-point, and `std::boolalpha` extraction through `std::istringstream`.
- `tests/iostream-state`: `std::skipws`, `std::noskipws`, width-limited extraction with `std::setw`, and repeated base switching on one input stream.
- `tests/iostream-output-state`: fill, alignment, internal padding, width reset behaviour, `std::boolalpha`, and repeated precision/base changes on output streams.
- `tests/iostream-recovery`: failed extraction, `failbit` handling, `clear()`-based recovery, and `unget()`/`putback()` character recovery.
- `tests/iostream-text`: `std::quoted`, `std::ws`, `std::getline`, and delimiter-based text extraction.
- `tests/iostream-manipulators`: `std::endl`, `std::flush`, `std::ends`, and `std::unitbuf` on narrow output streams and string buffers.
- `tests/fstream-basics`: file creation, readback, append, and seek-based access with `std::ofstream`, `std::ifstream`, and `std::fstream`.
- `tests/fstream-state`: missing-file failure, `failbit`/EOF handling, `clear()`, `close()`, and reopen cycles for narrow file streams.
- `tests/fstream-binary`: binary-mode byte round-trips, embedded NUL data, and fixed-size read/write.
- `tests/filebuf-basics`: direct `std::filebuf` open/read/write/seek coverage through the narrow stream buffer API.
- `tests/filebuf-state`: direct `std::filebuf` failure, EOF, seek, and closed-buffer state coverage.
- `tests/fstream-modes`: `out|trunc`, `in|out`, `in|out|app`, and `ate` mode behaviour and resulting file contents.

Descriptor-backed file stream opens remain unsupported in the current port. The
runtime shim in `cpp/riscos_iostream_support` provides `fdopen()` as a stub
returning `nullptr`, so descriptor-based constructors and `open()` overloads
are intentionally outside the supported smoke-test surface.
