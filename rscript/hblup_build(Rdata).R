rm(list = ls())
print("-----------hblup_build.R output begin--------------")
args=commandArgs(T)

input_path_bf = args[1]
GEBV_path_bf = args[2]
AnimalID_index_bf = as.integer(args[3]) +1  # C++ start at 0, R at 1
target_index_bf = as.integer(args[4]) + 1  # C++ start at 0, R at 1
mode_flag_bf = as.integer(args[5])+1#1:A BLUP  2:G GBLUP 3:HBLUP

##########################fixed#################################################
j = 6
fixed_num_bf = as.integer(args[j]) 
print(paste("fixed_num :",fixed_num_bf))
fixed_index_bf = c(0)
if(fixed_num_bf)
{
  for(i in 1:fixed_num_bf){
    j = j+1
    fixed_index_bf[i]  =  as.integer(args[j])+1  # C++ start at 0, R at 1
  }
}

print(paste("fixed_index :",fixed_index_bf))
##########################random################################################
j = j+1
random_num_bf = as.integer(args[j]) 
print(paste("random_num :",random_num_bf))
random_index_bf = c(0)
if(random_num_bf){
  for(i in 1:random_num_bf){
    j = j+1
    random_index_bf[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
  }
  print(paste("random_index :",random_index_bf))
}
j=j+1
formula_bf = args[j]
print(paste("formula :",formula_bf))

j = j+1
varcomp_path_bf = (args[j]) 
print(paste("varcomp_path :",varcomp_path_bf))

j = j+1
formula_ans_path_bf = (args[j]) 
print(paste("formula_ans_path :",formula_ans_path_bf))

###############################################################################
#require(data.table)

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
load(input_path_bf)
###############################################################################
input_path = input_path_bf
GEBV_path = GEBV_path_bf
AnimalID_index = AnimalID_index_bf
mode_flag = mode_flag_bf
target_index = target_index_bf
fixed_num = fixed_num_bf
fixed_index = fixed_index_bf
random_num = random_num_bf
random_index = random_index_bf
formula = formula_bf
varcomp_path = varcomp_path_bf
formula_ans_path = formula_ans_path_bf
#####################delete the buff###########################################
rm(input_path_bf)
rm(GEBV_path_bf)
rm(AnimalID_index_bf)
rm(mode_flag_bf)
rm(target_index_bf)
rm(fixed_num_bf)
rm(fixed_index_bf)
rm(random_num_bf)
rm(random_index_bf)
rm(formula_bf)
rm(varcomp_path_bf)
rm(formula_ans_path_bf)
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
paste("mode_flag:",mode_flag)
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
    #setnames(GEBV,"ans_G$U$`u:AnimalID`$ABT_t","GEBV")
    pama = ""
    pama = paste("setnames(GEBV,\"ans_G$U$`u:",AnimalID_item,"`$",target_item,"\",\"GEBV\")",sep = "")
    print(pama)
    eval
    print(GEBV)
    fwrite(GEBV,file = GEBV_path,sep = " ",col.names = F)
  }
}
ans_varcomp = summary(ans_G)$varcomp
write.table (ans_varcomp, varcomp_path, sep =",", row.names =TRUE, col.names =FALSE, quote =FALSE)
print(ans_varcomp)

ans_vpredict =c(0,0)
pama = ""
pama = paste("ans_vpredict[1] = vpredict(ans_G,",formula,")$Estimate[1]",sep = "")
eval(parse(text = pama))

pama = ""
pama = paste("ans_vpredict[2] = vpredict(ans_G,",formula,")$SE[1]",sep = "")
eval(parse(text = pama))

print(ans_vpredict)
write.table(ans_vpredict,formula_ans_path, sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)

if(file.exists(GEBV_path)){
  print("GEBV building is completed.")
}
#######################    ##################################################

save.image(file = rdata_path)
#######################    ##################################################
##save(file = "/home/liang/Documents/GEBVRbuffer.Rdata")

print("-----------hblup_build.R output end--------------")
