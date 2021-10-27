rm(list = ls())
print("-----------classical_cross_validation(Rdata).R output begin--------------")
args=commandArgs(T)

input_path = args[1]
print(paste("input_path :",input_path))
v_output_path = args[2]
print(paste("v_output_path :",v_output_path))
AnimalID_index = as.integer(args[3]) +1  # C++ start at 0, R at 1
print(paste("AnimalID_index :",AnimalID_index))
target_index = as.integer(args[4]) + 1  # C++ start at 0, R at 1
print(paste("target_index :",target_index))
method_flag = as.integer(args[5])
print(paste("method_flag :",method_flag))
##########################fixed#################################################
j = 6
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
if(random_num)
{
  for(i in 1:random_num){
  j = j+1
  random_index[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
}
}
print(paste("random_index :",random_index))
j = j+1
rep = as.integer(args[j])+1
print(paste("rep :",rep))
j = j+1
fold_num = as.integer(args[j])+1
print(paste("fold_num :",fold_num))

j=j+1
formula = args[j]
print(paste("formula :",formula))
################################################################################
#input_path= "/home/liang/Desktop/Rbuffer.Rdata"
#v_output_path = "/home/liang/Desktop/classical_accuracy.csv"
#AnimalID_index = 0+1
#target_index = 11+1
#mode_flag = 1   
#fixed_num = 1
#fixed_index = c(9)
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
load(input_path)
col_list = colnames(data)
target_item = col_list[target_index]
AnimalID_item = col_list[AnimalID_index]
paste("target_item:",target_item)
paste("AnimalID_item:",AnimalID_item)
fixed_part_pama = ""

if(fixed_num)
{
  for(i in fixed_index){
    fixed_part_pama = paste(fixed_part_pama,col_list[i],"+",sep="")
    #pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    #eval(parse(text = pama))
  }
  fixed_part_pama = substr(fixed_part_pama,1,nchar(fixed_part_pama)-1)#delete the final "+"
}
paste("fixed_part_pama:",fixed_part_pama)

random_part_pama = ""
if(random_num)
{
  for(i in random_index){
    random_part_pama = paste(random_part_pama,col_list[i],"+",sep="")
    #pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    #eval(parse(text = pama))
  }
  random_part_pama = substr(random_part_pama,1,nchar(random_part_pama)-1)#delete the final "+"
}
paste("random_part_pama:",random_part_pama)





pheno <- copy(data)
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
rep_accuracyA <-  matrix(nrow=fold_num, ncol=rep)
reg_A <- matrix(nrow=fold_num, ncol=rep)

for(i in 1:rep) {
  animal_pos <- seq(nrow(pheno))
  s = matrix(sample(animal_pos, (floor(nrow(pheno) * (1/fold_num)) * fold_num)), ncol = fold_num)
  for (r in 1:fold_num) {
    y <- copy(pheno)
    #test = pheno[s[, r]]$AnimalID
    pama = paste("test = pheno[s[, r]]$",AnimalID_item,sep = "")
    print(pama)
    eval(parse(text = pama))
    #val_pheno <- pheno[match(test,AnimalID)]$ABT
    pama = paste("val_pheno = pheno[match(test,",AnimalID_item,")]$",target_item,sep = "")
    print(pama)
    eval(parse(text = pama))
    
    #y[AnimalID %in% test, "ABT_t"] = NA
    #pama = paste("y[",AnimalID_item, "%in%test,","\"",target_item,"\"","]= NA",sep = "")
    #print(pama)
    #eval(parse(text = pama))
    
    #y[,AnimalID := as.factor(AnimalID)]
    pama = paste("y[,",AnimalID_item, " := as.factor(",AnimalID_item,")]",sep = "")
    print(pama)
    eval(parse(text = pama))
    y$poolID <- as.factor(y$poolID)
    y$famID <- as.factor(y$famID)
    #ans_A <- mmer(ABT_t ~ 1 + poolID,
    #              random =  ~ vs(AnimalID, Gu = A),
    #              rcov =  ~ units,
    #              data = y)
    if(random_num){
      if(method_flag)
      {
          pama =paste(" ans_A <- mmer(",target_item,"~1+",fixed_part_pama,","
                    ,"random =~vs(",AnimalID_item,",Gu=G)+",random_part_pama,","
                    ,"rcov =~units, data= y)",sep="")
        
      }else
      {
        pama =paste(" ans_A <- mmer(",target_item,"~ 1+",fixed_part_pama,","
                    ,"random=~vs(",AnimalID_item,", Gu=A)+",random_part_pama,","
                    ,"rcov=~units, data= y)",sep="")
      }
    }else{
      if(method_flag)
      {
        pama =paste(" ans_A<- mmer(",target_item,"~1+",fixed_part_pama,","
                    ,"random=~vs(",AnimalID_item,", Gu=G),"
                    ,"rcov=~units, data= y)",sep="")
        
      }else
      {
        pama =paste(" ans_A <-mmer(",target_item,"~1+",fixed_part_pama,","
                    ,"random =~vs(",AnimalID_item,",Gu=A),"
                    ,"rcov =~units,data = y)",sep="")
      }
    }
    print(pama)
    eval(parse(text = pama))
      
    
    pama = ""
    pama = paste("h2 <- vpredict(ans_A,",formula,")$Estimate[1]",sep = "")
    print(pama)
    eval(parse(text = pama))
    #ans_A$U$`u:AnimalID`$ABT_t <-as.data.frame(ans_A$U$`u:AnimalID`$ABT_t)
    pama = paste("ans_A$U$`u:",AnimalID_item,"`$",target_item,"<-as.data.frame(ans_A$U$`u:",AnimalID_item,"`$",target_item,")",sep = "")
    print(pama)
    eval(parse(text = pama))
    
    #rownames(ans_A$U$`u:AnimalIst csv_list;D`$ABT_t) <-gsub("AnimalID", "", rownames(ans_A$U$`u:AnimalID`$ABT_t))
    pama = paste("rownames(ans_A$U$`u:",AnimalID_item,"`$",target_item,")","<-gsub(\"AnimalID\",","\"\",","rownames(ans_A$U$`u:",AnimalID_item,"`$",target_item,"))",sep = "")
    print(pama)
    eval(parse(text = pama))
    
    #Y_A <- ans_A$U$`u:AnimalID`$ABT_t[test, ]
    pama = paste("Y_A <- ans_A$U$`u:",AnimalID_item,"`$",target_item,"[test,]",sep = "")
    print(pama)
    eval(parse(text = pama))
    
    rep_accuracyA[r, i] <- (cor(Y_A, val_pheno, use = "complete"))/sqrt(h2)
    numerator_A <- sum((Y_A-mean(Y_A))*(val_pheno-mean(val_pheno)))
    denomirator_A <- sum((Y_A-mean(Y_A))^2)
    reg_A[r, i] <- numerator_A/denomirator_A
  }
} 
meanaccuracy  <- cbind(mean(apply(rep_accuracyA,2,mean)),mean(apply(rep_accuracyA,2,sd)))
meanreg <- cbind(mean(apply(reg_A,2,mean)),mean(apply(reg_A,2,sd)))
print("meanaccuracy:")
meanaccuracy
print("meanreg:")
meanreg
ans = c(0,0)
ans[1] = meanaccuracy[1]
ans[2] = meanreg[1]

write.table(ans,v_output_path, sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
#######################    ##################################################
#save.image(file = rdata_path)
#######################  G  ##################################################
print("-----------classical_cross_validation(Rdata).R output end--------------")

