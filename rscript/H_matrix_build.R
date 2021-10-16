#H matrix
print("-----------H_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path = args[1]
H_matrix_path =  args[2]                    
require(data.table)
require('ASRgenomics')
load(rdata_path)
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
save(data,A,G,H,AnimalID_item,id,geno_012_DT,geno_012_matrix,file = rdata_path)
rdata_path
#######################  G  ##################################################
print("-----------H_matirx_build.R output end--------------")