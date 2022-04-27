rm(list = ls())
print("-----------data_init.R output begin--------------")
args=commandArgs(T)

csv_path = args[1]
raw_path = args[2]
rdata_path = args[3]
target_index = as.integer(args[4]) + 1  # C++ start at 0, R at 1
AnimalID_index = as.integer(args[5]) +1 
factor_num_bf = as.integer(args[6])
j = 7
factor_index_bf = c(0)
for(i in 1:factor_num_bf){
  factor_index_bf[i]  =  as.integer(args[j])+1
  j = j+1
}
numeric_index_bf = c(0)
numeric_num_bf = as.integer(args[j])
j = j+1
for(i in 1:numeric_num_bf){
  numeric_index_bf[i]  =  as.integer(args[j])+1
  j = j+1
}



#csv_path= "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Input/ABT20210617_outlier.csv"
#raw_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/raw_data.raw"
#rdata_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/Rbuffer.Rdata"
#target_index = 8 + 1  # C++ start at 0, R at 1
#AnimalID_index = 0 +1 # C++ start at 0, R at 1
#AnimalID_index = 1
#factor_num_bf = 7
#factor_index_bf  =  c(1,2,3,4,5,6,10)
#numeric_num_bf = 3
#numeric_index_bf = c(7,8,9)

#csv_path= "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Input/data1120_outlier.csv"
#raw_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/raw_data.raw"
#rdata_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/Rbuffer.Rdata"
#target_index = 8 + 1  # C++ start at 0, R at 1
#AnimalID_index = 0 +1 # C++ start at 0, R at 1
#AnimalID_index = 1
#factor_num_bf = 7
#factor_index_bf  =  c(1,2,3,4,5,6,10)
#numeric_num_bf = 3
#numeric_index_bf = c(7,8,9)

print(paste("raw_path:",raw_path))
print(paste("target_index:",target_index))
print(paste("AnimalID_index:",AnimalID_index))
print(paste("factor_index:",factor_index_bf))
print(paste("numeric_index:",numeric_index_bf))  

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

data <- fread(
  input = csv_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE
)
str(data) 

geno_012_DT <-fread(
  input = raw_path,
  sep = " ",
  header = TRUE,
  stringsAsFactors = FALSE
)
str(geno_012_DT)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]


#####################matching A and G#############################################
#保证snp文件里的个体顺序和表型里的顺序一致
pama = ""
pama = paste("ID_data <-data.frame(ID = data$",AnimalID_item,")",sep = "")
print(pama)
eval(parse(text = pama))
id = ID_data$ID
geno_012_DT = geno_012_DT[geno_012_DT$IID %in% id,]
id = geno_012_DT$IID
ID_data = ID_data[ID_data$ID %in% id,]

pama = ""
pama = paste("data = data[data$",AnimalID_item,"%in% id,]",sep = "")
print(pama)
eval(parse(text = pama))
setorder(geno_012_DT,IID)

#setorder(data,AnimalID_item) 
pama = ""
pama = paste("setorder(data,",AnimalID_item,")",sep = "")
print(pama)
eval(parse(text = pama))
#######################    ##################################################
for(i in 1:factor_num_bf){
  data[[factor_index_bf[i]]] <- as.factor(data[[factor_index_bf[i]]])
}
for(i in 1:numeric_num_bf){
  data[[numeric_index_bf[i]]] <- as.numeric(data[[numeric_index_bf[i]]])
}
save.image(file = rdata_path)
rdata_path

print("-----------data_init.R output end--------------")

