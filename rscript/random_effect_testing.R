rm(list = ls())
print("-----------random_effect.R output begin--------------")
args=commandArgs(T)

input_path = args[1]
output_path = args[2]
A_matrix_path = args[3]
G_matrix_path = args[4]

AnimalID_index = as.integer(args[5]) +1  # C++ start at 0, R at 1

target_index = as.integer(args[6]) + 1  # C++ start at 0, R at 1

method_flag = as.integer(args[7])
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
################################################################################
#input_path= "/home/liang/Documents/AquaGS_GUI/Input/ABT20210617_outlier.csv"
#output_path = "/home/liang/Documents/AquaGS_GUI/Output/random_effect.csv"
#A_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/A_matrix.txt"
#G_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/G_matrix.txt"
#AnimalID_index = 1
#target_index = 9
#method_flag = 1
#fixed_num = 1
#fixed_index = c(2)
#random_num = 1
#random_index = c(4)

require(data.table)
#data = read.csv(input_path)
data <- fread(
  input = input_path,
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]
table = data.frame(
  phenotype = c(col_list),
  pr = c(0)
)
paste("target_item:",target_item)
paste("AnimalID_item:",AnimalID_item)
################################################################################
A_read <- read.table(A_matrix_path)[,-1]
A = as.matrix(A_read)
colnames(A) <-rownames(A) <-  as.character(data$AnimalID)
################################################################################
G_read <- read.table(G_matrix_path)[,-1]
G = as.matrix(G_read)
colnames(G) <-rownames(G) <-  as.character(data$AnimalID)
################################################################################


fixed_part_pama = ""
if(fixed_num)
{
  for(i in fixed_index){
    fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
  }
}
paste("fixed_part_pama:",fixed_part_pama)

random_part_pama = ""
random_past_part_pama = ""

if(random_num)
{
  for(i in random_index){
    random_part_pama = paste(random_part_pama,col_list[i],"+",sep="")
  }
}
paste("random_part_pama:",random_part_pama)

if(!method_flag) # using lmer to test 
{
  require(lmerTest)
  require(lme4)
  i = 1
  for(item in col_list[]){
    print(paste("=================== ==",item,"===================",sep = ''))
    pama= ""
    if(fixed_num) #if the fixed_list is Null ?
    {
      if(( i %in% fixed_index))#if this item in the fixed_list already, set "Fixed"
      {
          print("the effect already in selected_fixed_list.")
          pr = "Fixed"
          
      }else{
          pama =paste(" fit <- try(lmer(",target_item,"~",fixed_part_pama,"(1|",item,"),data=data))",sep="")
          print(pama)
          eval(parse(text = pama))
          if("try-error" %in% class(fit))
          {
              pr = "Err" 
              print(paste("!!!error in ",item,sep = ""))
          }else{
              p =  rand(fit)
              pr<- p$`Pr(>Chisq)`[2]
          }
      }
    }else{
        # pama =paste(" fit <- try(lmer(",target_item,"~","(1|",item,"),data=data))",sep="")
        print(pama)
        eval(parse(text = pama))
        if("try-error" %in% class(fit))
        {
          pr = "Err" 
          print(paste("!!!error in ",item,sep = ""))
        }else{
          p =  rand(fit)
          pr<- p$`Pr(>Chisq)`[2]
        }
    }
    table$pr[i] = as.character(pr)
    print(pr)
    i = i+1
  }
}else if(method_flag == 1){
  require(sommer)
  if(fixed_num){#######################################################fixed_list  list is not empty
    fixed_part_pama = substr(fixed_part_pama,1,nchar(fixed_part_pama)-1)#delete the final "+"
    ######################################################################################
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,", Gu = A)",","
                ,"rcov = ~ units,data = data))",sep="")
    print(pama)
    eval(parse(text = pama))
    if("try-error" %in% class(ans_G))####################### ans_G is broken
    {
      table$pr = "Err"
      print(paste("Error in ans_G",ans_G,sep = ""))
    }else{################################################### if ans_G is ready
      i = 1
      for(item in col_list[])
      {
        if(( i %in% fixed_index)){#####################################if this item in the fixed_list already, set "Fixed"
  
          print("the effect already in selected_fixed_list.")
          pr = "Fixed"
        }else if(( i %in% random_index)){##################################################if this item in the random_list
          
          print("the effect already in selected_random_list.")
          random_past_part_pama = ""
          for(j in random_index[1:which(random_index == i)])##link all random effect before the item in the random_list
          {
            random_past_part_pama = paste(random_past_part_pama,col_list[j],"+",sep="")
          }
          random_past_part_pama = substr(random_past_part_pama,1,nchar(random_past_part_pama)-1)
          paste("random_past_part_pama",random_past_part_pama)
          
          pama =paste(" ans_G2 <- try(mmer(",target_item,"~",fixed_part_pama,","
                      ,"random = ~ vs(",AnimalID_item,", Gu = A)+",random_past_part_pama,","
                      ,"rcov = ~ units, data = data))",sep="")
          print(pama)
          eval(parse(text = pama))
          if("try-error" %in% class(ans_G2))
          {
            table$pr[i] = "Err"
            print(paste("Error in ",item,"'s ans_G2",sep = ""))
          }else{
            pama =" fit<-try(anova.mmer(ans_G,ans_G2))"
            print(pama)
            eval(parse(text = pama))
            if("try-error" %in% class(fit))
            {
              pr = "Err" 
              print(paste("!!!error in ",item,"anova",sep = ""))
            }else{
              pr<-fit$PrChisq[2]
            }
          }
        }else{##################################################################if this item out of fixed and random effect
    
          pama =paste(" ans_G2 <- try(mmer(",target_item,"~",fixed_part_pama,","
                      ,"random = ~ vs(",AnimalID_item,", Gu = A)+",random_part_pama,item,","
                      ,"rcov = ~ units,data = data))",sep="")
          print(pama)
          eval(parse(text = pama))
          if("try-error" %in% class(ans_G2))
          {
            table$pr[i] = "Err"
            print(paste("Error in ",item,"'s ans_G2",sep = ""))
          }else{
            pama =" fit<-try(anova.mmer(ans_G,ans_G2))"
            print(pama)
            eval(parse(text = pama))
            if("try-error" %in% class(fit))
            {
              pr = "Err" 
              print(paste("!!!error in ",item,"anova",sep = ""))
            }else{
              pr<-fit$PrChisq[2]
            }
          }
          
        }
        table$pr[i] = as.character(pr)
        print(paste("\n",item,"\'s pr :",pr,sep =  ""))
        i = i+1
      }
    }
    ############################################################################
  }else{###############################################################################fixed_list list is  empty
    print("Fixed_list  are null!")
  }
}
write.table(table,output_path, row.names = FALSE,col.names = FALSE,sep=",")
print("-----------random_effect.R output end--------------")

