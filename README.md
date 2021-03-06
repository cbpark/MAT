MAT
===

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://travis-ci.com/cbpark/MAT.svg?branch=master)](https://travis-ci.com/cbpark/MAT)

A C++ implementation of [`mantler`](https://github.com/cbpark/mantler/), for reconstructing heavy resonances in the antler decay topology using the singularity variable.

For Haskell users, see [`mantler`](https://github.com/cbpark/mantler/).

## How to build

The C++ compiler must support **C++14** features. See [C++ compiler support](https://en.cppreference.com/w/cpp/compiler_support) and

* [C++ Standards Support in GCC](https://gcc.gnu.org/projects/cxx-status.html),
* [C++ Support in Clang](https://clang.llvm.org/cxx_status.html).

Internally, [GNU Scientific Library](https://www.gnu.org/software/gsl/) (GSL) is used to solve polynomial equations. In order to build this from source, make sure that `gsl-config` is in the `PATH`.

```
$ gsl-config --version
2.6
```

In Arch Linux, it can be installed by

```
$ sudo pacman -S gsl lapack
```

In Debian and Ubuntu,

```
$ sudo apt-get install libgsl-dev liblapack-dev
```

Otherwise, appropriately modify `CXXFLAGS` and `LIBS` in [`Makefile`](./Makefile):

``` makefile
CXXFLAGS += $(shell gsl-config --cflags)
LIBS     += $(shell gsl-config --libs)
```

Then, build the source by running `make`. It will create the `lib` directory, and the generated library file (`libMAT.a`) will be placed there.

## How to use

See the [`mat.cc`](./examples/mat.cc) file. If you want to build it, run `make examples/mat`.

The library and header files can be install via `make install`. The destination directory can be set by `DESTDIR`. For example,

``` makefile
DESTDIR=/usr/local make install
```

(You may have to supply the `sudo` command with a password.) The content of installed files are:

```
├── include
│   └── MAT
│       ├── antler.h
│       ├── lester_mt2_bisect.h
│       ├── maos.h
│       ├── matrix.h
│       ├── momentum.h
│       └── polynomial.h
└── lib
    ├── libMAT.a
    └── libMAT.so
```

Include the header file `yam2.h` in your analysis code as

``` c++
#include "yam2.h"
```

Then, build and link your analysis code (ex. `my_analysis.cc`):

```
g++ -o my_analysis my_analysis.cc -I/usr/local/include/MAT -L/usr/local/lib -lMAT -lgsl -lgslcblas
```

## References

If you use this library, please cite the [paper](https://doi.org/10.1007/JHEP07(2020)089) given below.

``` bibtex
@article{Park:2020rol,
    author = "Park, Chan Beom",
    title = "{A singular way to search for heavy resonances in missing energy events}",
    eprint = "2005.12297",
    archivePrefix = "arXiv",
    primaryClass = "hep-ph",
    reportNumber = "CTPU-PTC-20-14",
    doi = "10.1007/JHEP07(2020)089",
    journal = "JHEP",
    volume = "07",
    pages = "089",
    year = "2020"
}
```

This uses the [MT2](https://www.hep.phy.cam.ac.uk/~lester/mt2/) library, [`lester_mt2_bisect.h`](./src/lester_mt2_bisect.h), to calculate the MT2 variable. Therefore, please cite [arXiv:1411.4312](https://arxiv.org/abs/1411.4312) and [arXiv:0810.4853](https://arxiv.org/abs/0810.4853) if you use this code, in particular, the `mATmaos` function.

For the MT2 variable,

``` bibtex
@article{Lester:2014yga,
    author = "Lester, Christopher G. and Nachman, Benjamin",
    title = "{Bisection-based asymmetric M$_{T2}$ computation: a higher precision calculator than existing symmetric methods}",
    eprint = "1411.4312",
    archivePrefix = "arXiv",
    primaryClass = "hep-ph",
    reportNumber = "CAV-HEP-14-13, CAV-HEP-14/13",
    doi = "10.1007/JHEP03(2015)100",
    journal = "JHEP",
    volume = "03",
    pages = "100",
    year = "2015"
}
```

For the MAOS method,

``` bibtex
@article{Cho:2008tj,
    author = "Cho, Won Sang and Choi, Kiwoon and Kim, Yeong Gyun and Park, Chan Beom",
    title = "{M(T2)-assisted on-shell reconstruction of missing momenta and its application to spin measurement at the LHC}",
    eprint = "0810.4853",
    archivePrefix = "arXiv",
    primaryClass = "hep-ph",
    doi = "10.1103/PhysRevD.79.031701",
    journal = "Phys. Rev. D",
    volume = "79",
    pages = "031701",
    year = "2009"
}
```
