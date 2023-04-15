rm(list = ls())

args=commandArgs(T)
input_path = args[1]
output_path = args[2]
index = as.integer(args[3]) + 1##C++ start at 0, R at 1
type = args[4]
print(index)
#input_path = "/home/liang/Documents/AquaGS_QTtest_demo/Input/ABT20210617.csv"
#output_path = "/home/liang/Documents/AquaGS_QTtest_demo/Output"
#index= 7
#type = "original"
#input_path = "/home/liang/Documents/AquaGS_QTtest_demo/Input/ABT20210617_new.csv"
#output_path = "/home/liang/Documents/AquaGS_QTtest_demo/Output"
#index= 11
#type = "convert"
print("-----------check_normality.R output begin--------------")
paste("input_path:",input_path)
paste("output_path:",output_path)
paste("index:",index)
paste("type:",type)

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

data = read.csv(input_path)

x1 = data[,index]
x <- na.omit(x1)
target_name = colnames(data)[index]

if(require(ggplot2)){
  print("ggplot2 is loaded correctly")
} else {
  print("trying to install ggplot2")
  install.packages("ggplot2")
  if(require(ggplot2)){
    print("ggplot2 installed and loaded")
  } else {
    stop("could not install ggplot2")
  }
}

ggplot(data = data,aes_string(x= target_name))+
  theme_linedraw()+
  geom_histogram(aes(,y=..density..),colour="black",fill="white")+
  labs(x = target_name,y = "Density")+
  geom_density(alpha=0.15 ,fill="black")
ggsave(paste(output_path,"/histogram_of_",type,".png",sep = ""), plot = last_plot(), device = NULL, path = NULL,
       scale = 1, width = NA, height = NA, units =c("mm"),
       dpi = 500)

ans = c(0,0)
std <- function(x) sd(x)/sqrt(length(x))
stdan = std(x)
ans[1]  = mean(((x-mean(x))/sd(x))^3)
ans[2]  = mean(((x-mean(x))/sd(x))^4)
write.table (ans, paste(output_path,"/ske_kur_of_",type,".csv",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
print("done")

print("-----------check_normality.R output end--------------")