#H matrix
print("-----------H_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path_bf = args[1]
H_matrix_path_bf =  args[2]                    

if(require(data.table)){
  print("data.table is loaded correctly")
} else {
  print("trying to install data.table")
  install.packages("data.table")
  if(require(data.table)){
    print("data.table installed and loaded")
  } else {
    stop("could not install data.table")
  }
}
load(rdata_path_bf)
rdata_path = rdata_path_bf
H_matrix_path = H_matrix_path_bf
rm(rdata_path_bf,H_matrix_path_bf)

#require(ASRgenomics)
if(require(ASRgenomics)){
  print("ASRgenomics is loaded correctly")
} else {
  print("trying to install ASRgenomics")
  install.packages('factoextra')
  install.packages('scattermore')
  install.packages('AGHmatrix')
  install.packages('superheat')
  install.packages("ASRgenomics")
  if(require(ASRgenomics)){
    print("ASRgenomics installed and loaded")
  } else {
    stop("could not install ASRgenomics")
  }
}


rownames(geno_012_matrix) <- geno_012_DT$IID
# Reading genotypic data and making some filters
M_filter <- qc.filtering(M=geno_012_matrix, base=FALSE, ref=NULL, maf=0.05, marker.callrate=0.2,
                         ind.callrate=0.20, impute=FALSE, na.string='-9', plots=TRUE)
G <- G.matrix(M=geno_012_matrix, method='VanRaden', na.string='-9')$G
check_G <- kinship.diagnostics(K=G)
check <- match.G2A(A=A, G=G, clean=TRUE, ord=TRUE, mism=TRUE, RMdiff=TRUE)
G_align <- G.tuneup(G=check$Gclean, A=check$Aclean, align=TRUE, sparseform=FALSE)$Gb
# Getting Ginverse using the G aligned
Ginv <- G.inverse(G=G_align, sparseform=FALSE)$Ginv
H <- H.inverse(A=A, G=Ginv, lambda=0.90, sparseform=FALSE, inverse=FALSE)
H[1:5,1:5]

H_dt <- as.data.table(A,keep.rownames = T)
setnames(H_dt,"rn",AnimalID_item)
fwrite(H_dt,file = H_matrix_path,sep = " ",col.names = F)
#######################    ##################################################
save.image(file = rdata_path)
rdata_path
#######################  G  ##################################################
print("-----------H_matirx_build.R output end--------------")