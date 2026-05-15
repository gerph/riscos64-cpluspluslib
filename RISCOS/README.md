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
(`riscos64-c++`). Headers are exported to `<Exports$Dir>.Lib.c++.h`, and the
library export targets are `<Exports$Dir>.Lib.c++.o.libc++-64` and
`<Exports$Dir>.Lib.c++.o.libc++zm-64`.

This source tree is LLVM libc++ 17.0.6, which still supports GCC 12. The RISC
OS site configuration disables unavailable runtime features such as threads,
filesystem, localisation, random-device support, wide-character support, and
the parallel STL backend.
