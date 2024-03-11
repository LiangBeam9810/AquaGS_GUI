> # lmerTest
>
> Description: Missing CMake
>
> ```shell
>
> ------------------ CMAKE NOT FOUND --------------------
>
> CMake was not found on the PATH. Please install CMake:
>
> - yum install cmake          (Fedora/CentOS; inside a terminal)
> - apt install cmake          (Debian/Ubuntu; inside a terminal).
> - pacman -S cmake            (Arch Linux; inside a terminal).
> - brew install cmake         (MacOS; inside a terminal with Homebrew)
> - port install cmake         (MacOS; inside a terminal with MacPorts)
>
> Alternatively install CMake from: <https://cmake.org/>
> ```
>
> Solution:
>
> ```shell
> sudo apt-get install cmake
> ```

> # lme4
>
> Description: Missing lnlopt
>
> ```shell
>
> /usr/share/R/share/make/shlib.mk:10: recipe for target 'nloptr.so' failed
>
> /usr/bin/ld: cannot find -lnlopt
> ```
>
> Solution:
>
> ```shell
>  sudo apt-get install libnlopt-dev
> ```

> # bestNormalize
>
> Description:Missing libgit2
>
> ```shell
> Execution halted
>
> Using PKG_CFLAGS=
> Using PKG_LIBS=-lgit2
>
> ----------------------------- ANTICONF -------------------------------
> Configuration failed to find libgit2 library. Try installing:
> * brew: libgit2 (MacOS)
> * deb: libgit2-dev (Debian, Ubuntu, etc)
> * rpm: libgit2-devel (Fedora, CentOS, RHEL)
> If libgit2 is already installed, check that 'pkg-config' is in your
> PATH and PKG_CONFIG_PATH contains a libgit2.pc file. If pkg-config
> is unavailable you can set INCLUDE_DIR and LIB_DIR manually via:
> R CMD INSTALL --configure-vars='INCLUDE_DIR=... LIB_DIR=...'
> -------------------------- [ERROR MESSAGE] ---------------------------
>
> <stdin>:1:10: fatal error: git2.h: No such file or directory
> compilation terminated
> ```
>
> Solution:
>
> ```shell
>  sudo apt-get install libgit2-dev
> ```

> # bestNormalize
>
> Description:Missing openssl/opensslv.h文件
>
> ERROR: configuration failed for package ‘openssl’
>
> ![Image]('/../Pasted%20image%2020211027173536.png)
>
> Solution:
>
> ```shell
> sudo apt-get install openssl-devel
> ```

> Description:Missing libcurl4-openssl-dev
>
> ```
> Configuration failed because libcurl was not found. Try installing:
> * deb: libcurl4-openssl-dev (Debian, Ubuntu, etc)
> * rpm: libcurl-devel (Fedora, CentOS, RHEL)
> * csw: libcurl_dev (Solaris)
> ```
>
> ![Image](./Pasted%20image%2020211027175705.png)
>
> Solution:
>
> ```shell
> sudo apt install libcurl4-openssl-dev 
> ```

---

> # sommer
>
> Description:Missing file openssl/opensslv.h
>
> ```shell
> /usr/bin/ld: cannot find -llapack
> /usr/bin/ld: cannot find -lblas
> /usr/bin/ld: cannot find -lgfortran
> ```
>
> Solution:
>
> ```shell
> sudo apt install liblapack-dev
> sudo apt install libblas-dev
> sudo apt-get install gfortran
> ```
>
> or
>
> ```shell
> sudo apt-get install r-base-dev
> ```

> # ASRgenomics
>
> You can only use local installation
>
> ```
> cd <yourpath>/AquaGS_GUI/rscript/  #  <yourpach> is replaced by the path of floder where  AquaGS_GUI resides .The ASRgenomics_1.0.0_R_x86_64-pc-linux-gnu.tar.gz is in this path.
> R CMD INSTALL ASRgenomics_1.0.0_R_x86_64-pc-linux-gnu.tar.gz
> ```
> ```
> install.packages('factoextra')
> install.packages('scattermore')
> install.packages('AGHmatrix')
> install.packages('superheat')
> ```
