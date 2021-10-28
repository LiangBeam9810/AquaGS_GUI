rm(list = ls())
print("-----------G_matirx_build.R output begin--------------")
args=commandArgs(T)
rdata_path_bf = args[1]
G_matrix_path_bf = args[2]

#rdata_path = "/home/liang/Desktop/Rbuffer.Rdata"
#G_matrix_path = "/home/liang/Desktop/G_matrix.txt"

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

rdata_path =rdata_path_bf
G_matrix_path = G_matrix_path_bf

rm(rdata_path_bf,G_matrix_path_bf)
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
#require(sommer)
if(require(sommer)){
  print("sommer is loaded correctly")
} else {
  print("trying to install sommer")
  install.packages("sommer")
  if(require(sommer)){
    print("sommer installed and loaded")
  } else {
    stop("could not install sommer")
  }
}


#col_list = colnames(data)
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

