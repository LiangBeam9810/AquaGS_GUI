rm(list = ls())

args=commandArgs(T)
packages_path = args[1]
lib_r = Sys.getenv("R_LIBS_USER")
print("lib of r lib :")
print(lib_r)
# create local user library path (not present by default)
dir.create(path = Sys.getenv("R_LIBS_USER"), showWarnings = FALSE,recursive = TRUE)
# install to local user library path
packages=c("DataExplorer","data.table","nadiv","sommer","gert","BGLR","ggplot2","bestNormalize","lmerTest","lme4","factoextra","scattermore","AGHmatrix","superheat")
ipak <- function(pkg){
    new.pkg <- pkg[!(pkg %in% installed.packages()[, "Package"])]
    if (length(new.pkg)) 
        install.packages(new.pkg, lib = Sys.getenv("R_LIBS_USER"),dependencies = TRUE,repos="https://mirrors.tuna.tsinghua.edu.cn/CRAN/")
    sapply(pkg, require, character.only = TRUE)
}
ipak(packages)

#require(ASRgenomics)
if(require(ASRgenomics)){
  print("ASRgenomics is loaded correctly")
} else {
  print("trying to install ASRgenomics")
  install.packages(packages_path,lib = Sys.getenv("R_LIBS_USER"),dependencies = TRUE)
  if(require(ASRgenomics)){
    print("ASRgenomics installed and loaded")
  } else {
    stop("could not install ASRgenomics")
  }
}
