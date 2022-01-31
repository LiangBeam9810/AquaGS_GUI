
># lmerTest
>问题描述：缺少CMake
>```shell
>
>------------------ CMAKE NOT FOUND --------------------
>
>CMake was not found on the PATH. Please install CMake:
>
> - yum install cmake          (Fedora/CentOS; inside a terminal)
> - apt install cmake          (Debian/Ubuntu; inside a terminal).
> - pacman -S cmake            (Arch Linux; inside a terminal).
> - brew install cmake         (MacOS; inside a terminal with Homebrew)
> - port install cmake         (MacOS; inside a terminal with MacPorts)
>
>Alternatively install CMake from: <https://cmake.org/>
>```
> 解决方案：
>```shell
> sudo apt-get install cmake

># lme4
>问题描述：缺少lnlopt
>```shell
>
>/usr/share/R/share/make/shlib.mk:10: recipe for target 'nloptr.so' failed
>
>/usr/bin/ld: cannot find -lnlopt
>```
> 解决方案：
>```shell
>  sudo apt-get install libnlopt-dev


># bestNormalize
>问题描述：缺少libgit2 
>```shell
>Execution halted
>
>Using PKG_CFLAGS=
>Using PKG_LIBS=-lgit2
>
>----------------------------- ANTICONF -------------------------------
>Configuration failed to find libgit2 library. Try installing:
> * brew: libgit2 (MacOS)
> * deb: libgit2-dev (Debian, Ubuntu, etc)
> * rpm: libgit2-devel (Fedora, CentOS, RHEL)
>If libgit2 is already installed, check that 'pkg-config' is in your
>PATH and PKG_CONFIG_PATH contains a libgit2.pc file. If pkg-config
>is unavailable you can set INCLUDE_DIR and LIB_DIR manually via:
>R CMD INSTALL --configure-vars='INCLUDE_DIR=... LIB_DIR=...'
>-------------------------- [ERROR MESSAGE] ---------------------------
>
><stdin>:1:10: fatal error: git2.h: No such file or directory
>compilation terminated
>```
> 解决方案：
>```shell
>  sudo apt-get install libgit2-dev



> # bestNormalize 
>问题描述：缺少openssl/opensslv.h文件
>
>ERROR: configuration failed for package ‘openssl’
>
>![Image]('/../Pasted%20image%2020211027173536.png)
>
>  解决方案：
>```shell
>sudo apt-get install openssl-devel
>```

>问题描述：缺少libcurl4-openssl-dev
>
>```
>Configuration failed because libcurl was not found. Try installing:
> * deb: libcurl4-openssl-dev (Debian, Ubuntu, etc)
> * rpm: libcurl-devel (Fedora, CentOS, RHEL)
> * csw: libcurl_dev (Solaris)
>```
>![Image](./Pasted%20image%2020211027175705.png)
> 
> 解决方案：
>```shell
>sudo apt install libcurl4-openssl-dev 
---
># sommer
>问题描述：缺少openssl/opensslv.h文件
>```shell
>/usr/bin/ld: cannot find -llapack
>/usr/bin/ld: cannot find -lblas
>/usr/bin/ld: cannot find -lgfortran
>```
> 解决方案：
>```shell
>sudo apt install liblapack-dev
>sudo apt install libblas-dev
>sudo apt-get install gfortran
>```
>或者
>```shell
>sudo apt-get install r-base-dev
>```

># ASRgenomics
>只能使用本地安装
>
>```
>cd <yourpath>/AquaGS_GUI/rscript/  #  <yourpach> is replaced by the path of floder where  AquaGS_GUI resides .The ASRgenomics_1.0.0_R_x86_64-pc-linux-gnu.tar.gz is in this path.
>R CMD INSTALL ASRgenomics_1.0.0_R_x86_64-pc-linux-gnu.tar.gz
>```
>```
>install.packages('factoextra')
>install.packages('scattermore')
>install.packages('AGHmatrix')
>install.packages('superheat')
>```


