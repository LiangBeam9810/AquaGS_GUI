# rm(list = ls())
print("-----------blup_gblup_build.R output begin--------------")
args=commandArgs(T)

input_path = args[1]
output_path = args[2]
A_matrix_path = args[3]
G_matrix_path = args[4]

AnimalID_index = as.integer(args[5]) +1  # C++ start at 0, R at 1

target_index = as.integer(args[6]) + 1  # C++ start at 0, R at 1

mode_flag = as.integer(args[7])#1:A BLUP  2:G GBLUP
##########################fixed#################################################
j = 8
fixed_num = as.integer(args[j]) 
print(paste("fixed_num :",fixed_num))
fixed_index = c(0)
for(i in 1:fixed_num){
  j = j+1
  fixed_index[i]  =  as.integer(args[j])+1  # C++ start at 0, R at 1
}
print(paste("fixed_index :",fixed_index))
##########################random################################################
j = j+1
random_num = as.integer(args[j]) 
print(paste("random_num :",random_num))
random_index = c(0)
for(i in 1:random_num){
  j = j+1
  random_index[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
}
print(paste("random_index :",random_index))
###############################################################################
#input_path= "/home/liang/Documents/AquaGS_GUI/Input/ABT20210617.csv"
#output_path = "/home/liang/Documents/AquaGS_GUI/Output/GEBV.csv"
#A_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/A_matrix.txt"
#G_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/G_matrix.txt"
#AnimalID_index = 1
#target_index = 9
#mode_flag = 1
#fixed_num = 2
#fixed_index = c(5,4)
#random_num = 0
#random_index = c(0)

#trans_formula = "h2 ~ V1/(V1+V2)"

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
#data = read.csv(input_path)
data <- fread(
  input = input_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]

paste("target_item:",target_item)
paste("AnimalID_item:",AnimalID_item)

########################################################################################## ######
A_read <- read.table(A_matrix_path)[,-1]
A = as.matrix(A_read)
colnames(A) <-rownames(A) <-  as.character(data$AnimalID)
#################################################################################################
G_read <- read.table(G_matrix_path)[,-1]
G = as.matrix(G_read)
colnames(G) <-rownames(G) <-  as.character(data$AnimalID)
#################################################################################################
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
#require(sommer)
if(require(sommer)){
  print("sommer is loaded correctly")
} else {
  print("trying to install sommer")
  install.packages("sommer")
  if(require(sommer)){
    print("sommer installed and loaded")
  } else {
    stop("could not install sommer")
  }
}
if(mode_flag)
{
  if(random_num==0)
  {
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
              ,"random = ~ vs(",AnimalID_item,",Gu = G)",","
              ,"rcov = ~ units,data = data))",sep="")
  }else{
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,",Gu = G)+",random_part_pama,","
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
    fwrite(GEBV,file = output_path,sep = " ",col.names = T)
  }
}else{
  if(random_num==0)
  {
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,", Gu = A)",","
                ,"rcov = ~ units,data = data))",sep="")
  }else{
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,", Gu = A)+",random_part_pama,","
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
    fwrite(GEBV,file = output_path,sep = " ",col.names = T)
    
  }
}

if(file.exists(output_path)){
  print("GEBV building is completed.")
}
save.image(file = paste(".\projectimage.RData"))
print("-----------blup_gblup_build.R output end--------------")