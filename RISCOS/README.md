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

A small header and runtime smoke test is provided in `tests/header-basics`. It
builds a 64-bit absolute using `-nostdinc++` and `-isystem C:c++`, so it checks
that the exported libc++ headers are usable through the RISC OS include path and
that the resulting program can link against `C:c++.o.libc++-64`.

Build the library exports first:

```sh
riscos-amu export
```

Then build and run the test:

```sh
cd tests/header-basics
riscos-amu BUILD64=1
riscos-build-run --64 aif64/CxxHeaders,ff8 --command CxxHeaders
```

The expected output is:

```text
libc++ header basics passed
```
