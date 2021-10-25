rm(list = ls())
print("-----------G_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path = args[1]
G_matrix_path = args[2]
#rdata_path = "/home/liang/Desktop/Rbuffer.Rdata"
#G_matrix_path = "/home/liang/Desktop/G_matrix.txt"
require(data.table)
require(nadiv)
require(sommer)

load(rdata_path)
col_list = colnames(data)
geno_012_matrix <- as.matrix(geno_012_DT[, -1:-6])
geno_sommer_matrix <- geno_012_matrix - 1
id_g = geno_012_DT$IID
G <- A.mat(geno_sommer_matrix) # additive relationship matrix
colnames(G) <- rownames(G) <-  id_g
dim(G)

G_dt <- as.data.table(G,keep.rownames = T)
setnames(G_dt,"rn",AnimalID_item)
fwrite(G_dt,file = G_matrix_path,sep = " ",col.names = F)
#######################   ##################################################
G[1:5,1:5]
#######################    ##################################################
save.image(file = rdata_path)
rdata_path

print("-----------G_matirx_build.R output end--------------")

