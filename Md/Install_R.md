
# Install R(4.1.1)
 
- You can reference  the [Official Installation Guide](https://cran.r-project.org/bin/linux/ubuntu/) to install the newest R.
	- open the Terminal(Alt+Ctrl+T) and run commands :

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
	- If you see like this ,please run =="su root"== to get the root permission firstly .
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

		
