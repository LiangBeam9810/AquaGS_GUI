rm(list = ls())

print("-----------continuous_fixed_effect_testing(Rdata).R output begin--------------")

args=commandArgs(T)
rdata_path = args[1]
continupus_fix_path = args[2]
target_index = as.integer(args[3]) + 1##C++ start at 0, R at 1
num = as.integer(args[4]) 
fixed_index = c(0)
j = 5
for(i in 1:num){
  fixed_index[i]  =  as.integer(args[j])+1
  j = j+1
}

#rdata_path = "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
#continupus_fix_path = "/home/liang/Documents/AquaGS_GUI/Input/fixed_effect.csv"
#target_index = 8 + 1  # C++ start at 0, R at 1
#AnimalID_index = 0 +1 # C++ start at 0, R at 1
#num = 1
#fixed_index  =  c(10)

load(rdata_path)

col_list = colnames(data)
target_item = col_list[target_index]
table = data.frame(
  phenotype = c(col_list),
  pr = c(0)
)


if(num)
{
  fixed_part_pama = ""
  for(i in fixed_index){
    pama = ""
    fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
    pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    eval(parse(text = pama))
  }
  paste("fixed_part_pama",fixed_part_pama)
}

i = 1
for(item in col_list){
  print(paste("=====================",item,"===================",sep = ''))
  pama= ""
  if(num)
  {
    if(( i %in% fixed_index))
    {
      print("the effect already in selected_fixed_list.")
      pama =paste(" fit <- try(lm(",target_item,"~",substr(fixed_part_pama,1,nchar(fixed_part_pama)-1),",data=data))",sep="")#delete the final char "+"
      print(pama)
      eval(parse(text = pama))
      if("try-error" %in% class(fit))
      {
        pr = "Err" 
        table$pr[i] = as.character(pr)
        print(paste("!!!error in ",item,sep = ""))
        i = i+1
        next
      }else
      {
        p =  anova(fit)
        selected_in_fixed_index = (which(fixed_index == i))[1]
        pr<- p$`Pr(>F)`[selected_in_fixed_index]
        print(p)
      }
      
    }else{
      pama =paste(" fit <- try(lm(",target_item,"~",fixed_part_pama,item,",data=data))",sep="")#delete the final char "+"
      print(pama)
      eval(parse(text = pama))
      if("try-error" %in% class(fit))
      {
        pr = "Err" 
        table$pr[i] = as.character(pr)
        print(paste("!!!error in ",item,sep = ""))
        i = i+1
        next
      }else
      {
        p =  anova(fit)
        pr<- p$`Pr(>F)`[num+1]#1:num is the selected fixed effect.the last one is item's p value 
        print(p)
      }
    }
  }else{
    pama =paste(" fit <- try(lm(",target_item,"~",item,",data=data))",sep="")
    print(pama)
    eval(parse(text = pama))
    if("try-error" %in% class(fit))
    {
      pr = "Err" 
      table$pr[i] = as.character(pr)
      print(paste("!!!error in ",item,sep = ""))
      i = i+1
      next
    }else
    {
      p =  anova(fit)
      pr<- p$`Pr(>F)`[num+1]#1:num is the selected fixed effect.the last one is item's p value 
      print(p)
    }
  }
  table$pr[i] = as.character(pr)
  i = i+1
}
write.table(table,continupus_fix_path, row.names = FALSE,col.names = FALSE,sep=",")
print("-----------continuous_fixed_effect_testing(Rdata). output end--------------")
