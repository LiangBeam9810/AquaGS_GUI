
# Install R(4.1.1)
### Install R(4.1.1) by Conda ( The recommended )
- We highly recommend using Conda to manage R environments, especially without root permission.   
  ( ps:open the Terminal(Alt+Ctrl+T) and run commands )
  1. Install Miniconda    
		If Conda is already installed, you can skip this step.
		
		```r
		wget -c https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
		bash Miniconda3-latest-Linux-x86_64.sh
		```
  2. Add the source   
  Add the source of Tsinghua for conda .
		```r
		# add the source of Tsinghua  in mainland China.
		conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
		conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge 
		conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/msys2/
		conda config --set show_channel_urls yes
		```
  3. Initializing the Environment 
    
       1. Add the environment for conda.You can also specify a particular environment by replacing `r411env` with `your env name`.  
			```r
			# create a new env for R 4.1.1 named "r411env"
			conda create -n r411env -y
			conda activate r411env  # activate the env
			```
       2. Setting default environment.    
			Before using AquaGS for the first time, edit `~/.bashrc`
 to make this environment the default environment for Conda.(You only have to do it once).Add `conda activate r411env` to the end of  `~/.bashrc`.Here's one way to do it.
			```r
			echo "conda activate r411env" >>  ~/.bashrc 
			source ~/.bashrc
			```
	4. Install R and dependency libraries    
   Add the source of Tsinghua for conda .
		```r
		conda install -y r-base=4.1.1 # install R 4.1.1
		conda install -y cmake # install cmake
		conda install -y libgit2 # install libgit2
		```
----
### Installed directly R(4.1.1)  (Not recommended)
To make your installation process easier, we do not recommend installing R directly. 
- You can reference  the [Official Installation Guide](https://cran.r-project.org/bin/linux/ubuntu/) to install the newest R.
	1. open the Terminal(Alt+Ctrl+T) and run commands :

		```r
		#set the password of root
		sudo passwd
		#enter your password 
		# get the root permission
		su root 
		#enter the password you set
		sudo apt update
		# update indices
		apt update -qq
		# install two helper packages we need
		apt install software-properties-common dirmngr
		# add the signing key (by Michael Rutter) for these repos
		# To verify key, run gpg --show-keys /etc/apt/trusted.gpg.d/cran_ubuntu_key.asc 
		# Fingerprint: 298A3A825C0D65DFD57CBB651716619E084DAB9
		wget -qO- https://cloud.r-project.org/bin/linux/ubuntu/marutter_pubkey.asc | sudo tee -a /etc/apt/trusted.gpg.d/cran_ubuntu_key.asc
		# add the R 4.0 repo from CRAN -- adjust 'focal' to 'groovy' or 'bionic' as needed
		add-apt-repository "deb https://cloud.r-project.org/bin/linux/ubuntu $(lsb_release -cs)-cran40/"
		# install R and its dependencies.
		apt install --no-install-recommends r-base
		# install R base dev
		apt-get install r-base-dev
		# Be sure to install the following dependent libraries
		apt-get install libcurl4-openssl-dev 
		apt-get install libgit2-dev
		apt-get install nloptr.so
		apt-get install cmake
		apt-get install libssl-dev
		```
	- If you see like this ,please run `su root` to get the root permission firstly .
		```shell
		E: Could not open lock file /var/lib/apt/lists/lock -open (13: Permission denied)
		E: Unable to lock directory /var/lib/apt/lists/
		W: Problem unlinking the file /var/cache/apt/pkgcache.bin - RemoveCaches (13: Permission denied)
		W: Problem unlinking the file /var/cache/apt/srcpkgcache.bin - RemoveCaches (13: Permission denied)
		```
  - Check R in Terminal
  	```shell
  	R -version
  	```
	if  R is installed ,you will see such like this.
	```shell
	YingWanglab@ubuntu:~$ R -version
	WARNING: unknown option '-version'


	R version 4.1.1 (2021-08-10) -- "Kick Things"
	Copyright (C) 2021 The R Foundation for Statistical Computing
	Platform: x86_64-pc-linux-gnu (64-bit)

	R is free software and comes with ABSOLUTELY NO WARRANTY.
	You are welcome to redistribute it under certain conditions.
	Type 'license()' or 'licence()' for distribution details.

		Natural language support but running in an English locale

	R is a collaborative project with many contributors.
	Type 'contributors()' for more information and
	'citation()' on how to cite R or R packages in publications.

	Type 'demo()' for some demos, 'help()' for on-line help, or
	'help.start()' for an HTML browser interface to help.
	Type 'q()' to quit R.

	```

		
