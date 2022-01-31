# Setting Up Your Environment
Before you can build mate plans ,you need to install some software and set up your build environment .This only has to be done once no matter how many mate plans you plan to compile for. 

There are 3 main sections to this guide:

# 1.Prerequisites 
There are only two pieces of software you'll need to get started.
-  [Install R(4.1.1)](Install_R.md)
- [Install Java(11+)](Install_Java.md)
# 2.Install packages for R
We’ve tried to make AquaGS as easy to set up as possible.Some of the [packages](./Md/../Install_packages_for%20R.md) required in AquaGS can be installed automatically when AquaGS first run.
## 📌Attention
Automatic installation works fine if the following dependent libraries are installed:
* libcurl (lme4 needs)
* openssl (sommer needs)
* CMake  (lmerTest needs)
* lnlopt (lme4 needs)
* libgit2 (bestNormalize needs)
  
**Make sure these dependency libraries are installed in your linux! ! !**   
**It can take a long time to install your missing packages, so be patient the first time you use AquaGS.**
# 3.Install AquaGS
1. Download the zip of AquaGS to local from [**releases page**](https://github.com/LiangBeam9810/AquaGS_GUI/releases).You can also download it directly [**here**](https://github.91chi.fun//https://github.com//LiangBeam9810/AquaGS_GUI/archive/refs/tags/BetaV0.2.zip).
2. Open the path where the zip of AquaGS is,and unzip the package to create a folder.
3. Open the path of folder in Terminal(Enter the folder ,clik right key of mouse in the margin,and selet "Open in Terminal",or use ```cd <FolderPath>```).Run such command: (Change ```<FolderPath>``` to the decompressed folder in your device.)
```R
cd <FolderPath># in our computer the path is home/Ying-lab/Downloads/build-AquaGS_GUI-Desktop_Qt_5_9_0_GCC_64bit-Release
chmod a+x ./Aqua_GUI
./AquaGS_GUI 
```
---
At this point, the installation is complete.You are now ready to create your own mate plans.Enjoy it!

**Instructions for each step are provided at [here](../README.md).**