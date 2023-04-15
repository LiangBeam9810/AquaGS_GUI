rm(list = ls())
print("-----------Gender_build.R output begin--------------")
args=commandArgs(T)
rdata_path_bf = args[1]
Gender_path_bf = args[2]
Gender_index_bf = as.integer(args[3]) + 1  # C++ start at 0, R at 1

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
Gender_path = Gender_path_bf
Gender_index = Gender_index_bf
rm(rdata_path_bf,Gender_path_bf,Gender_index_bf)


Gender_item = col_list[Gender_index]

Gender_data <-data.frame(ID = data[,..AnimalID_index],gender = data[,..Gender_index])
colnames(Gender_data) <- c("ID", "gender")
fwrite(Gender_data,file = Gender_path,sep = " ",col.names = F)

save.image(file = rdata_path)
rdata_path

print("-----------data_init.R output end--------------")