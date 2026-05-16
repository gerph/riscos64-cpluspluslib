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

## Tests

Small 64-bit smoke tests are provided below `tests`. They build absolutes using
`-nostdinc++` and `-isystem C:c++`, so they check that the exported libc++
headers are usable through the RISC OS include path and that the resulting
programs can link against `C:c++.o.libc++-64`.

Build the library exports first:

```sh
riscos-amu export
```

Then build and run the header-only test:

```sh
cd tests/header-basics
riscos-amu BUILD64=1
riscos-build-run --64 aif64/CxxHeaders,ff8 --command CxxHeaders
```

The expected output is:

```text
libc++ header basics passed
```

The `tests/runtime-link` test uses `std::string`, `std::vector`, `std::sort`,
and integral `std::to_chars` to check a small runtime-linked subset without
using iostreams, locale, filesystem, exceptions, or RTTI-heavy paths:

```sh
cd ../runtime-link
riscos-amu BUILD64=1
riscos-build-run --64 aif64/CxxRuntime,ff8 --command CxxRuntime
```

The expected output is:

```text
libc++ runtime link passed
```

The `tests/memory-basics` test exercises `std::unique_ptr`, `std::shared_ptr`,
`std::weak_ptr`, and smart pointers stored in `std::vector`:

```sh
cd ../memory-basics
riscos-amu BUILD64=1
riscos-build-run --64 aif64/CxxMemory,ff8 --command CxxMemory
```

The expected output is:

```text
libc++ memory basics passed
```

The `tests/associative-basics` test exercises ordered and unordered containers
with string keys:

```sh
cd ../associative-basics
riscos-amu BUILD64=1
riscos-build-run --64 aif64/CxxAssoc,ff8 --command CxxAssoc
```

The expected output is:

```text
libc++ associative basics passed
```
