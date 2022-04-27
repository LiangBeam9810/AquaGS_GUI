rm(list = ls())
print("-----------review_data.R output begin--------------")
args=commandArgs(T)

csv_path = args[1]
out_path = args[2]
print(paste("csv_path",csv_path))
print(paste("output",out_path))
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

if(require(DataExplorer)){
  print("DataExplorer is loaded correctly")
} else {
  print("trying to install DataExplorer")
  install.packages("DataExplorer")
  if(require(DataExplorer)){
    print("DataExplorer installed and loaded")
  } else {
    stop("could not install DataExplorer")
  }
}

##表型数据输入

data <- fread(
  input = csv_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE
)
str(data) 

png(filename=paste(out_path,'/plot_histogram.png',sep = ""))
plot_histogram(data)
dev.off()

png(filename=paste(out_path,'/plot_bar.png',sep = ""))
plot_bar(data)
dev.off()

print("-----------review_data.R output end--------------")