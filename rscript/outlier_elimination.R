rm(list = ls())

args=commandArgs(T)
input_path = args[1]
outlier_flag = as.integer(args[2])##Get the value

index = as.integer(args[3]) + 1##C++ start at 0, R at 1
#input_path = "/home/liang/Documents/AquaGS_QTtest_demo/Input/ABT20210617.csv"
#outlier_flag = 1
#index = 7
print("-----------outiler_eliminatuon.R output begin--------------")
paste("input_path:",input_path)
paste("outlier_flag:",outlier_flag)
paste("index:",index)
output_path = gsub(".csv", "_outlier.csv", input_path)
paste("output_path: ",output_path)

require(data.table)
data = read.csv(input_path)
x = data[,index]

if(outlier_flag){
  print("Runing outlier elimination .")
  outlier.low <- quantile(x,probs=c(0.25))-IQR(x)*1.5
  outlier.high <- quantile(x,probs=c(0.75))+IQR(x)*1.5
  W = which(x>outlier.high | x<outlier.low)
  paste(" the outlier index:",W)
  y=integer(0)
  if(setequal(W,y)){
    data_outlier =  data
  }else{
    data_outlier = data[-W,]
    outlier_list = data.frame(
      list_index = W
    )
    outlier_list_output_path = gsub(".csv", "_outlier_list.csv", input_path)
    write.csv(outlier_list,outlier_list_output_path, row.names = TRUE)
  }
}else{
  print("Do not change original data")
  data_outlier =  data
}
write.csv(data_outlier,output_path, row.names = FALSE)
print(" outliered! ")
print("-----------outiler_eliminatuon.R output end--------------")