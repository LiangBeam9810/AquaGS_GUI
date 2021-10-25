rm(list = ls())
print("-----------data_init.R output begin--------------")
args=commandArgs(T)

csv_path = args[1]
raw_path = args[2]
rdata_path = args[3]
target_index = as.integer(args[4]) + 1  # C++ start at 0, R at 1
print(paste("target_index:",target_index))
AnimalID_index = as.integer(args[5]) +1 
print(paste("AnimalID_index:",AnimalID_index))

#csv_path= "/home/liang/Documents/AquaGS_GUI/Input/ABT20210617_outlier.csv"
#csv_path = "/home/liang/Desktop/input/data1120.csv"
#raw_path = "/home/liang/Documents/AquaGS_GUI/Output/raw_output.raw"
#raw_path = "/home/liang/Desktop/raw_output.raw"
#rdata_path = "/home/liang/Desktop/Rbuffer.Rdata"
#target_index = 8 + 1  # C++ start at 0, R at 1
#target_index = 7+1
#AnimalID_index = 0 +1 # C++ start at 0, R at 1
#AnimalID_index = 1

require(data.table)
require(nadiv)

data <- fread(
  input = csv_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE
)

geno_012_DT <-fread(
  input = raw_path,
  sep = " ",
  header = TRUE,
  stringsAsFactors = FALSE
)
geno_012_DT$IID

col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]


#####################matching A and G#############################################
ID_data <-data.frame(ID = data[,..AnimalID_index])
colnames(ID_data) <- c("ID")
id = ID_data$ID
geno_012_DT = geno_012_DT[geno_012_DT$IID %in% id,]
id = geno_012_DT$IID
ID_data = ID_data[ID_data$ID %in% id,]
#data = data[data$ID %in% id,]
pama = ""
pama = paste("data = data[data$ ",AnimalID_item,"%in% id,]",sep = "")
print(pama)
eval(parse(text = pama))

#######################    ##################################################
save.image(file = rdata_path)
rdata_path

print("-----------data_init.R output end--------------")

