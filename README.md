# MAT

A C++ implementation of [`mantler`](https://github.com/cbpark/mantler/), for reconstructing heavy resonances in the antler decay topology using the singularity variable.

For Haskell users, see [`mantler`](https://github.com/cbpark/mantler/).

# How to build

Internally, [GNU Scientific Library](https://www.gnu.org/software/gsl/) (GSL) is used to solve polynomial equations. In order to build this from source, make sure that `gsl-config` is in the `PATH`.

```
$ gsl-config --version
2.6
```

In Arch Linux, it can be installed by

```
$ sudo pacman -S gsl lapack
```

Then, build the source by running `make`. It will create the `lib` directory, and the generated library file (`libMAT.a`) will be placed there.

## How to use

See the [`mat.cc`](./examples/mat.cc) file. If you want to build it, run `make examples/mat`.

## References

If you use this library, please cite the paper given below.

```
@article{Park:2020rol,
    author = "Park, Chan Beom",
    title = "{A singular way to search for heavy resonances in missing energy events}",
    eprint = "2005.12297",
    archivePrefix = "arXiv",
    primaryClass = "hep-ph",
    reportNumber = "CTPU-PTC-20-14",
    month = "5",
    year = "2020"
}
```

This uses the [MT2](https://www.hep.phy.cam.ac.uk/~lester/mt2/) library, [`lester_mt2_bisect.h`](./src/lester_mt2_bisect.h), to calculate the MT2 variable. Therefore, please cite [arXiv:1411.4312](https://arxiv.org/abs/1411.4312) and [arXiv:0810.4853](https://arxiv.org/abs/0810.4853) if you use this code, in particular, the `mATmaos` function.

For MT2,

```
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

For MAOS,

```
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
