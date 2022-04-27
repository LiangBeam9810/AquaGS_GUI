rm(list = ls())
print("-----------A_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path_bf = args[1]
A_matrix_path_bf = args[2]
Dam_index_bf =  as.integer(args[3]) + 1
Sire_index_bf = as.integer(args[4]) + 1

#require(data.table)
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
A_matrix_path = A_matrix_path_bf
Dam_index =  Dam_index_bf
Sire_index = Sire_index_bf

rm(rdata_path_bf)
rm(A_matrix_path_bf)
rm(Dam_index_bf)
rm(Sire_index_bf)

#require(nadiv)
if(require(nadiv)){
  print("nadiv is loaded correctly")
} else {
  print("trying to install nadiv")
  install.packages("nadiv")
  if(require(nadiv)){
    print("nadiv installed and loaded")
  } else {
    stop("could not install nadiv")
  }
}

col_list = colnames(data)

Dam_item =  col_list[Dam_index]
Sire_item = col_list[Sire_index]

data_A <-data.frame(ID = data[,..AnimalID_index],Dam = data[,..Dam_index],sire = data[,..Sire_index])
colnames(data_A) <- c("ID", "Dam","Sire")
data_A = data_A[data_A$ID %in% id,]

########################  A  #################################################
ped_prepPed <- prepPed(data_A, gender = NULL, check = TRUE)  
A_makeA <- makeA(ped_prepPed)
A_dense <- as.matrix(A_makeA)
colnames(A_dense) <-rownames(A_dense) <-  ped_prepPed[,1]
id_A = as.character(data_A$ID)
A <- A_dense[id_A,id_A]
dim(A)
A[1:5,1:5]
A_dt <- as.data.table(A,keep.rownames = T)
setnames(A_dt,"rn",AnimalID_item)
fwrite(A_dt,file = A_matrix_path,sep = " ",col.names = F)
#######################   ##################################################
A[1:5,1:5]

#######################    ##################################################
rm(A_dt,A_dense,data_A,id_A)
save.image(file = rdata_path)
rdata_path

print("-----------A_matirx_build.R output end--------------")