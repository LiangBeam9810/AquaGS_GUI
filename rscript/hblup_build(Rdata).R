rm(list = ls())
print("-----------hblup_build.R output begin--------------")
args=commandArgs(T)

input_path = args[1]
GEBV_path = args[2]
AnimalID_index = as.integer(args[3]) +1  # C++ start at 0, R at 1
target_index = as.integer(args[4]) + 1  # C++ start at 0, R at 1
mode_flag = as.integer(args[5])#1:A BLUP  2:G GBLUP 3:HBLUP

##########################fixed#################################################
j = 6
fixed_num = as.integer(args[j]) 
print(paste("fixed_num :",fixed_num))
fixed_index = c(0)
if(fixed_num)
{
  for(i in 1:fixed_num){
    j = j+1
    fixed_index[i]  =  as.integer(args[j])+1  # C++ start at 0, R at 1
  }
}

print(paste("fixed_index :",fixed_index))
##########################random################################################
j = j+1
random_num = as.integer(args[j]) 
print(paste("random_num :",random_num))
random_index = c(0)
if(random_num){
  for(i in 1:random_num){
    j = j+1
    random_index[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
  }
  print(paste("random_index :",random_index))
}
j=j+1
formula = args[j]
print(paste("formula :",formula))

j = j+1
varcomp_path = (args[j]) 
print(paste("varcomp_path :",varcomp_path))

j = j+1
formula_ans_path = (args[j]) 
print(paste("formula_ans_path :",formula_ans_path))

###############################################################################
#input_path= "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
#GEBV_path = "/home/liang/Documents/AquaGS_GUI/Output/GEBV.txt"

#AnimalID_index = 1
#target_index = 9
#mode_flag = 1   
#param.append(blup_input.A_matrix_path);//3
#param.append(" ");
#param.append(blup_input.G_matrix_path);//4
#fixed_num = 2
#fixed_index = c(5,4)
#random_num = 0
#random_index = c(0)

#trans_formula = "h2 ~ V1/(V1+V2)"formula

require(data.table)
load(input_path)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]

paste("target_item:",target_item)
paste("AnimalID_item:",AnimalID_item)

########################################################################################## ######

fixed_part_pama = ""
if(fixed_num)
{
  for(i in fixed_index){
    fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
    pama = ""
    pama = paste("data$",col_list[i],"<-as.factor(data$",col_list[i],")",sep="")
    print(pama)
    eval(parse(text = pama))
  }
}
fixed_part_pama = substr(fixed_part_pama,1,nchar(fixed_part_pama)-1)#delete the final "+"
paste("fixed_part_pama:",fixed_part_pama)
#################################################################################################
random_part_pama = ""
if(random_num)
{
  for(i in random_index){
    random_part_pama = paste(random_part_pama,col_list[i],"+",sep="")
    pama = ""
    pama = paste("data$",col_list[i],"<-as.factor(data$",col_list[i],")",sep="")
    print(pama)
    eval(parse(text = pama))
  }
}
random_part_pama = substr(random_part_pama,1,nchar(random_part_pama)-1)#delete the final "+"
paste("random_part_pama:",random_part_pama)
################################################################################################

###############################################################################
library(sommer)

if(mode_flag == 3)
{
  if(random_num==0)
  {
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,",Gu = H)",","
                ,"rcov = ~ units,data = data))",sep="")
  }else{
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,",Gu = H)+",random_part_pama,","
                ,"rcov = ~ units,data = data))",sep="")
  }
  print(paste("pama:",pama))
  eval(parse(text = pama))
  if("try-error" %in% class(ans_G))####################### ans_G is broken
  {
    print(paste("Error in ans_G",ans_G,sep = ""))
  }else{
    pama = ""
    pama = paste("ans_G$U$`u:",AnimalID_item,"`$",target_item,"<-as.data.frame(ans_G$U$`u:",AnimalID_item,"`$",target_item,")",sep = "")
    eval(parse(text = pama))
    
    pama = ""
    pama = paste("rownames(ans_G$U$`u:",AnimalID_item,"`$",target_item,") <-gsub(\"AnimalID\",\"\", rownames(","ans_G$U$`u:",AnimalID_item,"`$",target_item,"))",sep = "")
    pama
    eval(parse(text = pama))
    
    pama = ""
    pama = paste("GEBV <- as.data.table(ans_G$U$`u:",AnimalID_item,"`$",target_item,",keep.rownames = T)",sep = "")
    eval(parse(text = pama))
    
    setnames(GEBV,"rn","AnimalID")
    setnames(GEBV,"ans_G$U$`u:AnimalID`$ABT_t","GEBV")
    fwrite(GEBV,file = GEBV_path,sep = " ",col.names = F)
  }
}
#######################    ##################################################
##save(file = "/home/liang/Documents/GEBVRbuffer.Rdata")

print("-----------hblup_build.R output end--------------")
