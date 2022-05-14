# Setting Up Your Environment
Before you can build mate plans ,you need to install some software and set up your build environment .This only has to be done once no matter how many mate plans you plan to compile for. 

There are 3 main sections to this guide:

# 1.Prerequisites 
There are only two pieces of software you'll need to get started.
-  [Install R(4.1.1)](Install_R.md)
- [Install Java(11+)](Install_Java.md)
# 2.Install packages for R
We’ve tried to make AquaGS as easy to set up as possible.Some of the [packages](./Md/../Install_packages_for%20R.md) required in AquaGS can be installed automatically when AquaGS first run.

# 3.Install AquaGS
1. Make sure that the version of R for the default environment for Conda is 4.1.1 .

2. Download the zip of AquaGS to local from [**releases page**](https://github.com/LiangBeam9810/AquaGS_GUI/releases). Open the path where the zip of AquaGS is,and unzip the package to create a folder. This can be done directly by running the following command or manually.
    ```r
    wget -c https://github.com/LiangBeam9810/AquaGS_GUI/releases/download/Beta/AquaGS_GUI_release.zip
    unzip AquaGS_GUI_release.zip
    ```
3. Open the path of folder in Terminal(Enter the folder ,clik right key of mouse in the margin,and selet "Open in Terminal",or use ```cd <AquaGS_GUI_release>```).Run such command: (Change ```<AquaGS_GUI_release>``` to the decompressed folder in your device.)
    ```R
    cd AquaGS_GUI_release
    chmod a+x ./Aqua_GUI
    ./AquaGS_GUI 
    ```
---
At this point, the installation is complete.You are now ready to create your own mate plans.Enjoy it!

**Instructions for each step are provided at [here](../README.md).**
