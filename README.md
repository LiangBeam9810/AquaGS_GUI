# AquaGS
## What is AquaGS?
AquaGS is an open source tool for Aquaculture breeding programs with friendly graphical user interfaces(GUI).

AquaGS offers click-by-click running from inputting variant call file (.vcf) to the final mate allocation scheme. No need to prepare anything just except variant call file and phenotype file(.csv).

Everything Genomic Selection(GS) workflow needs are contained by AquaGS, such as preprocessing,effect testing,breeding-value calculating and mate allocating.Users no longer need to switch between software on different platforms. At the sametime, we  provide [a simple way](./Md/Setting_Up_Your_Environment.md) to install, try to put a lot of power into your hands by making easy things easy, and hard things possible. 

## How to start?
1. Installation step-by-step 
   
   Download the zip of AquaGS to local from [releases page](https://github.com/LiangBeam9810/AquaGS_GUI/releases).

   Following [the install tutorial(Setting Up Your Environment)](./Md/Setting_Up_Your_Environment.md), AquaGS can be easily installed by anyone even without programming experience.
   
2. <span id="RunningInstructions"> Runing </span>
   
    Make sure  [the install tutorial](./Md/Setting_Up_Your_Environment.md) is completed before you run AquaGS.Then you will start using AquaGS normally.

    1. Launched AquaGS
    
        AquaGS can be launched by simply double-clicking the "AquaGS_GUI",which in the decompressed folder.
    
    1. Select/Enter input and output
   
        In this page,you should select the path of phenotype file(.csv) , variant call file(.vcf) and output folder.

    2. Phenotype Preprocessing

        All Preprocessing of phentype will be completed in this page.Here contain 

    3. Genotype Preprocessing(Quality Control)
    4. Effects testing
    5. Calculation of breeding values
    6. Mating

## Functions detail
1. Preprocessing
   1. Phenotype Preprocessing
        1.  [Outlier Elimination](./Md/Outlier_elimination.md)
        2. [Normality Testing and Converting](./Md/Normality.md)

   2. Genotype Preprocessing(Quality Control)
        1. [Genotype imputation](./Md/imputation.md)
        1. [HW Balance](./Md/HWBalance.md)
        2. [Plink](./Md/PLink.md)
   1. Matirx Building
      1. [A Matirx](./Md/A.md)
      2. [G Matirx](./Md/G.md)
      3. [H Matrix](./Md/H.md)

2. Effect Testing
     1. Fixed Effect
         1. [Discrete Effect]()
         2. [Continuous Effect]()
     2. [Random Effect]()

  
3. Genotype Seletion(GS) / Calculating [GEBV]()
   1. Classical Method
      1. [BLUP]()
      2. [GBLUP]()
      3. [ssGBLUP]()
   2. Bayes Method
   
4.[Mate Allocation]()


---
# Feedback
If you have any doubt, you can ask us for Email.

You can also open an [issue on GitHub](https://github.com/LiangBeam9810/AquaGS_GUI/issues). This is especially handy when your issue will require long-term discussion or debugging.





