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


