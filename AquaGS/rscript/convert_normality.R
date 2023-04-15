rm(list = ls())

args=commandArgs(T)
input_path = args[1]
index = as.integer(args[2]) + 1##C++ start at 0, R at 1
flag = as.integer(args[3])

#input_path = "/home/liang/Documents/AquaGS_QTtest_demo/Input/ABT20210617.csv"
#input_path = "/home/liang/Documents/AquaGS_QTtest_demo/Input/ABT20210617_new.csv"
#index = 7
#flag = 1
#flag = 0

print("-----------convert_normality.R output begin--------------")
paste("input_path:",input_path)
paste("index:",index)

paste("flag:",flag)
##if it is the fist time to convert ,the input file is original csv file,
##if not, selecting the new csv file ,which was converted last time.
if(flag){
  output_path = gsub(".csv", "_converted.csv", input_path)
}else{
  output_path = input_path
  print("continue")
}

data = read.csv(input_path)
phnotype = data[,index]
target_name = colnames(data)[index]

#require(bestNormalize)
if(require(bestNormalize)){
  print("bestNormalize is loaded correctly")
} else {
  print("trying to install bestNormalize")
  install.packages("bestNormalize")
  if(require(bestNormalize)){
    print("bestNormalize installed and loaded")
  } else {
    stop("could not install bestNormalize")
  }
}
(orderNorm_obj <- orderNorm(phnotype))

data$new = orderNorm_obj$x.t;

names(data)[names(data) == 'new'] <- paste(target_name,"_converted",sep = "")
write.csv(data,output_path, row.names = FALSE,quote=F)
print("converted!")
print("-----------convert_normality.R output end--------------")
