rm(list = ls())
print("-----------A_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path = args[1]
A_matrix_path = args[2]
Dam_index =  as.integer(args[3]) + 1
Sire_index = as.integer(args[4]) + 1

require(data.table)
require(nadiv)

load(rdata_path)

col_list = colnames(data)

Dam_item =  col_list[Dam_index]
Sire_item = col_list[Sire_index]

data_A <-data.frame(ID = data[,..AnimalID_index],Dam = data[,..Dam_index],sire = data[,..Sire_index])
colnames(data_A) <- c("ID", "Dam","Sire")
data_A = data_A[data_A$ID %in% id,]
id_A = data_A$ID
########################  A  #################################################
ped_prepPed <- prepPed(data_A, gender = NULL, check = TRUE)  
A_makeA <- makeA(ped_prepPed)
A_dense <- as.matrix(A_makeA)
colnames(A_dense) <-rownames(A_dense) <-  ped_prepPed[,1]
A <- A_dense[id_A,id_A]
dim(A)
A[1:5,1:5]
A_dt <- as.data.table(A,keep.rownames = T)
setnames(A_dt,"rn",AnimalID_item)
fwrite(A_dt,file = A_matrix_path,sep = " ",col.names = F)
#######################   ##################################################
A[1:5,1:5]
#######################    ##################################################
save.image(file = rdata_path)
rdata_path

print("-----------A_matirx_build.R output end--------------")