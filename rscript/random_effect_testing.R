rm(list = ls())
print("-----------random_effect.R output begin--------------")
args=commandArgs(T)
input_path = args[1]
output_path = args[2]
index = as.integer(args[3]) + 1##vbC++ start at 0, R at 1

num = as.integer(args[4]) 

fixed_index = c(0)
j = 5
for(i in 1:num){
  fixed_index[i]  =  as.integer(args[j])+1
  j = j+1
}
paste("fixed_index :",fixed_index)

#input_path= "/home/liang/Documents/AquaGS_GUI/Input/ABT20210617_outlier_converted.csv"
#output_path = "/home/liang/Documents/AquaGS_GUI/Output/rondom_effect.csv"
#index = 11
#num = 2
#fixed_index = c(4)

require(data.table)
data = read.csv(input_path)
col_list = colnames(data)
target_item = col_list[index]
table = data.frame(
  phenotype = c(col_list),
  pr = c(0)
)
paste("target_item",target_item)

require(lmerTest)
require(lme4)

fixed_part_pama = ""
for(i in fixed_index){
  fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
}
paste("fixed_part_pama",fixed_part_pama)

i = 1
for(item in col_list[]){
  if(item == "AnimalID")
  {
    table$pr[i] = NA
  }else{
    pama = paste(" fit <- lmer(",target_item,"~",fixed_part_pama,"(1|",item,"),data=data)",sep="")
  print(pama)
  eval(parse(text = pama))
  if(( i %in% fixed_index))
  {
    print("the effect already in selected_fixed_list.")
    p =  anova(fit)
    selected_in_fixed_index = (which(fixed_index == i))[1]
    pr<- p$`Pr(>F)`[selected_in_fixed_index]
  }else{
    p = rand(fit)
    pr<- p$`Pr(>Chisq)`[2]
  }
  print(pr)
  table$pr[i] = pr
  }
  
  i = i+1
}
write.table(table,output_path, row.names = FALSE,col.names = FALSE,sep=",")


print("-----------random_effect.R output end--------------")
