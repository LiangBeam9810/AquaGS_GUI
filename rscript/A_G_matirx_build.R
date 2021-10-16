rm(list = ls())
print("-----------A_G_matirx_build.R output begin--------------")
args=commandArgs(T)

csv_path = args[1]
raw_path = args[2]
rdata_path = args[3]
A_matrix_path = args[4]
G_matrix_path = args[5]
target_index = as.integer(args[6]) + 1  # C++ start at 0, R at 1
AnimalID_index = as.integer(args[7]) +1  
Dam_index =  as.integer(args[8]) + 1
Sire_index = as.integer(args[9]) + 1
Gender_index = as.integer(args[10]) + 1
Gender_path = args[11]

#csv_path= "/home/liang/Documents/AquaGS_GUI/Input/ABT20210617_outlier.csv"
#raw_path = "/home/liang/Documents/AquaGS_GUI/Output/raw_output.raw"
#rdata_path = "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
#A_matrix_path = "/home/l iang/Documents/AquaGS_GUI/Output/A_matrix.txt"
#G_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/G_matrix.txt"
#target_index = 8 + 1  # C++ start at 0, R at 1
#AnimalID_index = 0 +1 # C++ start at 0, R at 1
#Dam_index =  2 + 1
#Sire_index = 1 + 1
#Gender_index = 11


require(data.table)
require(nadiv)

data <- fread(
  input = csv_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE
  )

#data$poolID <- as.factor(data$poolID)
#data$shell_color <- as.factor(data$shell_color)
geno_012_DT <-fread(
    input = raw_path,
    sep = " ",
    header = TRUE,
    stringsAsFactors = FALSE
  )

col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]
Dam_item =  col_list[Dam_index]
Sire_item = col_list[Sire_index]
Gender_item = col_list[Gender_index]

Gender_data <-data.frame(ID = data[,..AnimalID_index],gender = data[,..Gender_index])
colnames(Gender_data) <- c("ID", "gender")
fwrite(Gender_data,file = Gender_path,sep = " ",col.names = F)

data_A <-data.frame(ID = data[,..AnimalID_index],Dam = data[,..Dam_index],sire = data[,..Sire_index])
colnames(data_A) <- c("ID", "Dam","Sire")
#####################matching A and G#############################################
id = data_A$ID
geno_012_DT = geno_012_DT[geno_012_DT$IID %in% id,]
id = geno_012_DT$IID
data_A = data_A[data_A$ID %in% id,]
########################  A  #################################################
ped_prepPed <- prepPed(data_A, gender = NULL, check = TRUE)  
A_makeA <- makeA(ped_prepPed)
A_dense <- as.matrix(A_makeA)
colnames(A_dense) <-rownames(A_dense) <-  ped_prepPed[,1]
A <- A_dense[id,id]
dim(A)
A[1:5,1:5]
A_dt <- as.data.table(A,keep.rownames = T)
setnames(A_dt,"rn",AnimalID_item)
fwrite(A_dt,file = A_matrix_path,sep = " ",col.names = F)
#######################  G  ##################################################
require(sommer)
geno_012_matrix <- as.matrix(geno_012_DT[, -1:-6])
geno_sommer_matrix <- geno_012_matrix - 1
G <- A.mat(geno_sommer_matrix) # additive relationship matrix
colnames(G) <- rownames(G) <-  id
dim(G)
G[1:5,1:5]
G_dt <- as.data.table(G,keep.rownames = T)
setnames(G_dt,"rn",AnimalID_item)
fwrite(G_dt,file = G_matrix_path,sep = " ",col.names = F)
#######################    ##################################################
save(data,A,G,AnimalID_item,id,geno_012_DT,geno_012_matrix,file = rdata_path)
rdata_path
#######################  G  ##################################################
print("-----------A_G_matirx_build.R output end--------------")

