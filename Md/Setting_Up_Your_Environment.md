# Setting Up Your Environment
Before you can build mate plans ,you need to install some software and set up your build environment .This only has to be done once no matter how many mate plans you plan to compile for. 

There are 3 main sections to this guide:

# 1.Prerequisites 
There are only two pieces of software you'll need to get started.
-  [Install R(4.1.1)](Install_R.md)
- [Install Java(11+)](Install_Java.md)
# 2.[Install packages for R](./Md/../Install_packages_for%20R.md)
We’ve tried to make AquaGS as easy to set up as possible.Some of the packages required in AquaGS can be installed automatically when AquaGS first run.

**It can take a long time to install your missing packages, so be patient the first time you use AquaGS.**
# 3.Install AquaGS
1. Download the zip of AquaGS to local from [**releases page**](https://github.com/LiangBeam9810/AquaGS_GUI/releases).You can also download it directly [**here**](https://github.com/LiangBeam9810/AquaGS_GUI/releases/download/Beta/build-AquaGS_GUI-Desktop_Qt_5_9_0_GCC_64bit-Release.zip).
2. Open the path where the zip of AquaGS is,and unzip the package to create a folder.
3. Open the path of folder in Terminal(Enter the folder ,clik right key of mouse in the margin,and selet "Open in Terminal",or use ```cd <FolderPath>```).Run such command: (Change ```<FolderPath>``` to the decompressed folder in your device.)
```R
cd <FolderPath># in our computer the path is home/Ying-lab/Downloads/build-AquaGS_GUI-Desktop_Qt_5_9_0_GCC_64bit-Release
sudo apt-get install libqt5widgets5
chmod x+ ./Aqua_GUI
sudo ./AquaGS_GUI 
```
---
At this point, the installation is complete.You are now ready to create your own mate plans.Enjoy it!

**Instructions for each step are provided at [here](../README.md).**