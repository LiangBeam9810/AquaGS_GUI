rm(list = ls())
print("-----------Gender_build.R output begin--------------")
args=commandArgs(T)
rdata_path = args[1]
Gender_path = args[2]
Gender_index = as.integer(args[3]) + 1  # C++ start at 0, R at 1

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

load(rdata_path)
Gender_item = col_list[Gender_index]

Gender_data <-data.frame(ID = data[,..AnimalID_index],gender = data[,..Gender_index])
colnames(Gender_data) <- c("ID", "gender")
fwrite(Gender_data,file = Gender_path,sep = " ",col.names = F)

save.image(file = rdata_path)
rdata_path

print("-----------data_init.R output end--------------")