rm(list = ls())
print("-----------classical_cross_validation(Rdata).R output begin--------------")
args=commandArgs(T)

input_path = args[1]
print(paste("input_path :",input_path))
output_path = args[2]
print(paste("output_path :",output_path))
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
for(i in 1:random_num){
  j = j+1
  random_index[i]  =  as.integer(args[j])+1 # C++ start at 0, R at 1
}
print(paste("random_index :",random_index))
j = j+1
rep = as.integer(args[j])
print(paste("rep :",rep))
j = j+1
fold_num = as.integer(args[j])
print(paste("fold_num :",fold_num))
################################################################################
input_path= "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
output_path = "/home/liang/Documents/AquaGS_GUI/Output/random_effect.csv"
AnimalID_index = 1
target_index = 9
method_flag = 1
fixed_num = 1
fixed_index = c(2)
random_num = 0
random_index = c(0)
rep = 2
fold_num = 5

require(data.table)
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
    pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    eval(parse(text = pama))
  }
}
paste("fixed_part_pama:",fixed_part_pama)

random_part_pama = ""
if(random_num)
{
  for(i in random_index){
    random_part_pama = paste(random_part_pama,col_list[i],"+",sep="")
    pama = paste("data$",col_list[i],"<-","as.factor(data$",col_list[i],")",sep = "")
    eval(parse(text = pama))
  }
}
paste("random_part_pama:",random_part_pama)


pheno <- copy(data)
y <- copy(pheno)
rep_accuracyA <-  matrix(nrow=fold_num, ncol=rep)

library(sommer)
for(i in 1:rep) {
  animal_pos <- seq(nrow(pheno))
  s = matrix(sample(animal_pos, (floor(nrow(pheno) * (1/fold_num)) * fold_num)), ncol = fold_num)
  for (r in 1:fold_num) {
    y <- copy(pheno)
    test = pheno[s[, r]]$AnimalID
    y[AnimalID %in% test, "ABT_t"] = NA
    y[,AnimalID := as.factor(AnimalID)]
    y$poolID <- as.factor(y$poolID)
    y$famID <- as.factor(y$famID)
    ans_A <- mmer(ABT_t ~ 1 + poolID,
                  random =  ~ vs(AnimalID, Gu = A),
                  rcov =  ~ units,
                  data = y)
    ans_A$U$`u:AnimalID`$ABT_t <-as.data.frame(ans_A$U$`u:AnimalID`$ABT_t)
    rownames(ans_A$U$`u:AnimalID`$ABT_t) <-gsub("AnimalID", "", rownames(ans_A$U$`u:AnimalID`$ABT_t))
    Y <- ans_A$U$`u:AnimalID`$ABT_t[test, ]
    rep_accuracyA[r, i] <- cor(Y, pheno[match(test,AnimalID), "ABT_t"], use = "complete")
  }
} 
final_accuracyA <- cbind(mean(apply(rep_accuracyA,2,mean)),mean(apply(rep_accuracyA,2,sd)))
ans = c(final_accuracyA)
write.table (ans, output_path, sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)

print("-----------check_normality.R output end--------------")
