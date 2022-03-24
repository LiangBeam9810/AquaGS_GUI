rm(list = ls())
print("-----------random_effect_testing (Rdata).R output begin--------------")
args=commandArgs(T)

input_path_bf = args[1]
print(paste("input_path :",input_path_bf))
random_effect_path_bf = args[2]
print(paste("random_effect_path :",random_effect_path_bf))

AnimalID_index_bf = as.integer(args[3]) +1  # C++ start at 0, R at 1
print(paste("AnimalID_index :",AnimalID_index_bf))

target_index_bf = as.integer(args[4]) + 1  # C++ start at 0, R at 1
print(paste("target_index :",target_index_bf))

method_flag_bf = as.integer(args[5])
print(paste("method_flag :",method_flag_bf))
##########################fixed#################################################
j = 6
fixed_num_bf = as.integer(args[j]) 
print(paste("fixed_num :",fixed_num_bf))
fixed_index_bf = c(0)
if(fixed_num_bf){
  for(i in 1:fixed_num_bf){
  j = j+1
  fixed_index_bf[i]  =  as.integer(args[j])+1  # C++ start at 0, R at 1
}
print(paste("fixed_index :",fixed_index_bf))
}

##########################random################################################
j = j+1
random_num_bf = as.integer(args[j]) 
print(paste("random_num :",random_num_bf))
random_index_bf = c(0)
if(random_num_bf)
{
  for(i in 1:random_num_bf){
  j = j+1
  random_index_bf[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
}
print(paste("random_index :",random_index_bf))
}

################################################################################
#input_path= "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
#random_effect_path = "/home/liang/Documents/AquaGS_GUI/Output/random_effect.csv"
#A_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/A_matrix.txt"
#G_matrix_path = "/home/liang/Documents/AquaGS_GUI/Output/G_matrix.txt"
#AnimalID_index = 1
#target_index = 9
#method_flag = 1
#fixed_num = 1
#fixed_index = c(2)
#random_num = 0
#random_index = c(0)
#require(data.table)
################################################################################
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
input_path = input_path_bf
random_effect_path = random_effect_path_bf
AnimalID_index = AnimalID_index_bf
target_index = target_index_bf
method_flag = method_flag_bf
fixed_num = fixed_num_bf
fixed_index  =  fixed_index_bf
random_num = random_num_bf
random_index = random_index_bf
rm(input_path_bf,random_effect_path_bf,AnimalID_index_bf,target_index_bf,method_flag_bf,fixed_num_bf,fixed_index_bf,random_num_bf,random_index_bf)


#data = read.csv(input_path)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]
table = data.frame(
  phenotype = c(col_list),
  pr = c(0)
)
paste("target_item:",target_item)
paste("AnimalID_item:",AnimalID_item)



fixed_part_pama = ""
if(fixed_num)
{
  for(i in fixed_index){
    fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
    pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    eval(parse(text = pama))
  }
}
paste("fixed_part_pama:",fixed_part_pama)

random_part_pama = ""
random_past_part_pama = ""

if(random_num)
{
  for(i in random_index){
    random_part_pama = paste(random_part_pama,col_list[i],"+",sep="")
    pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    eval(parse(text = pama))
  }
}
paste("random_part_pama:",random_part_pama)

if(!method_flag) # using lmer to test 
{
  #require(lmerTest)

  if(require(lmerTest)){
  print("lmerTest is loaded correctly")
  } else {
  print("trying to install lmerTest")
  install.packages("lmerTest")
  if(require(lmerTest)){
    print("lmerTest installed and loaded")
  } else {
    stop("could not install lmerTest")
  }
  }

  #require(lme4)
  if(require(lme4)){
  print("lme4 is loaded correctly")
  } else {
  print("trying to install lme4")
  install.packages("lme4")
  if(require(lme4)){
    print("lme4 installed and loaded")
  } else {
    stop("could not install lme4")
  }
  }

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
        pama =paste(" fit <- try(lmer(",target_item,"~","(1|",item,"),data=data))",sep="")
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
    } ############################################################################
  }else{###############################################################################fixed_list list is  empty
    print("Fixed_list  are null!")
  }
  
  
  
  
  
}else if(method_flag == 2){
  require(sommer)
  if(fixed_num){#######################################################fixed_list  list is not empty
    fixed_part_pama = substr(fixed_part_pama,1,nchar(fixed_part_pama)-1)#delete the final "+"
    ######################################################################################
    pama =paste(" ans_G <- try(mmer(",target_item,"~",fixed_part_pama,","
                ,"random = ~ vs(",AnimalID_item,", Gu = G)",","
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
                      ,"random = ~ vs(",AnimalID_item,", Gu = G)+",random_past_part_pama,","
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
                      ,"random = ~ vs(",AnimalID_item,", Gu = G)+",random_part_pama,item,","
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
write.table(table,random_effect_path, row.names = FALSE,col.names = FALSE,sep=",")
print("-----------random_effect_testing (Rdata).R output end--------------")

