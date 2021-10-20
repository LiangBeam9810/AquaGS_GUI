rm(list = ls())

args=commandArgs(T)
input_path = args[1]
output_path = args[2]
raw_path = args[3]
modeltype = args[4]
kvalue = args[5]
iteration = args[6]
dropout = args[7]
target_effect = as.integer(args[8])+1
num = args[9]
#fixed_effect_list = args[10]
fixed_index = c(0)
j = 10
for(i in 1:num){
  fixed_index[i]  =  as.integer(args[j])+1
  j = j+1
}

#input_path = "/home/zhi/Desktop/AquaGS_GUI/Input/ABT20210617.csv"
#output_path = "/home/zhi/Desktop/AquaGS_GUI/Output"
#raw_path = "/home/zhi/Desktop/AquaGS_GUI/Output/raw_output.raw"
#modeltype = "BayesB"
#kvalue = "2"
#iteration = "15"
#dropout = "5"
#target_effect = as.integer("8")+1
#num = 1
####fixed_effect_list = list(4,5)
#fixed_index = c(0)
#fixed_index[1] = 4
#fixed_index[2] = 5

setwd("/home/zhi/Desktop/test")#这里需要修改
#setwd(output_path)
require(BGLR)
require(data.table)

abt_data <- fread(
  input = input_path, ##"/home/zhi/Desktop/AquaGS_GUI-main/Input/ABT20210617.csv",
  sep = ",",
  header = TRUE,
  stringsAsFactors = FALSE)
str(abt_data) 
##将用到的分类变量转化为因子格式（模型要求）
#abt_data[[fixed_effect]] <- as.factor(abt_data[[fixed_effect, exact = FALSE]])
#abt_data$poolID <- as.factor(abt_data$poolID)
#abt_data$shell_color <- as.factor(abt_data$shell_color)
#abt_data$famID <- as.factor(abt_data$famID)
#abt_data[[fixed_effect]] <- as.factor(abt_data[[fixed_effect, exact = FALSE]])

geno_012_DT <-
  fread(
    input = raw_path, ##"/home/zhi/Desktop/AquaGS_GUI-main/Output/raw_output.raw",
    sep = " ",
    header = TRUE,
    stringsAsFactors = FALSE
  )
geno_012_matrix <- as.matrix(geno_012_DT[, -1:-6])

name <- colnames(geno_012_matrix) ##前面此文件已经输入过
split_name <- tstrsplit(name,split = "_")[[1]]  #对snp数据的列名做修改
colnames(geno_012_matrix) <- split_name
snp <- as.matrix(geno_012_matrix)
#表型文件
#ABT_t <- abt_data$ABT_t
#poolID <- abt_data$poolID
#abt_y <- as.data.table(cbind(ABT_t,poolID))
#abt_y$ABT_t <- as.numeric(abt_y$ABT_t)
#abt_y$poolID <- as.factor(abt_y$poolID)


#  colnames(abt_data)[as.integer(fixed_effect_list[i])]
  
abt_y <- as.data.table(abt_data[[colnames(abt_data)[target_effect]]])
colnames(abt_y)[1] <- colnames(abt_data)[target_effect]
for(i in 1:num){
  fixed_effect1 <- abt_data[[colnames(abt_data)[as.integer(fixed_index[i])]]]
  abt_y <- as.data.table(cbind(abt_y,fixed_effect1))
  colnames(abt_y)[i+1] <- colnames(abt_data)[as.integer(fixed_index[i])]
}
#转化为模型需要的形式
abt_y[[colnames(abt_data)[target_effect]]] <- as.numeric(abt_y[[colnames(abt_data)[target_effect], exact = FALSE]])
for(i in 1:as.integer(num)){
  abt_y[[colnames(abt_data)[as.integer(fixed_index[i])]]] <- as.factor(abt_y[[colnames(abt_data)[as.integer(fixed_index[i])], exact = FALSE]])
}

#abt_y$fixed_effect1 <- as.factor(abt_y[["fixed_effect1", exact = FALSE]])
#abt_y$target_trait1 <- as.numeric(abt_y[["target_trait1", exact = FALSE]])

rep=as.integer(kvalue)
fold_num <- as.integer(kvalue)
pheno <- copy(abt_data)
nIter=as.integer(iteration); ##除了迭代次数和burnIn的值，其他参数一般是默认值
burnIn=as.integer(dropout);
saveAt='';
#ETA<-list(list(~factor(fixed_effect),data=abt_y,model='FIXED'),          ##固定效应
#          list(X=snp,model=modeltype,saveEffects=T)) 

pama = "ETA<-list("
for(i in 1:as.integer(num)){
  pama1=colnames(abt_data)[as.integer(fixed_index[i])]
  pama2=paste("list(~factor(",pama1,"),data=abt_y,model='FIXED'),",sep="")
  pama = paste(pama,pama2,sep = "")
}
pama = paste(pama,"list(X=snp,model=modeltype,saveEffects=T))",sep = "")
print(pama)
eval(parse(text = pama))
##交叉验证

accuracy = matrix(nrow=fold_num, ncol=1)
finalaccuracy=matrix(nrow=rep, ncol=1)
for(i in 1:rep) {
  animal_pos <- seq(nrow(pheno))
  s = matrix(sample(animal_pos, (floor(nrow(pheno) * (1/fold_num)) * fold_num)), ncol = fold_num)
  for (r in 1:fold_num) {
#    y <- copy(abt_y$ABT_t)
    y <- copy(abt_y[[colnames(abt_data)[target_effect], exact = FALSE]])
    test <- s[, r]
#    val_pheno_ABT = abt_y$ABT_t[s[, r]]
    val_pheno_ABT = abt_y[[colnames(abt_data)[target_effect], exact = FALSE]][s[, r]]
    y[s[, r]] <- NA
    fit_BC=BGLR(y=y,ETA=ETA,nIter=nIter,burnIn=burnIn,
                thin=3,saveAt=saveAt,df0=5,S0=NULL,weights=NULL,R2=0.5)
    y_BC <- fit_BC$yHat
    y_BC_test <- y_BC[test]
    accuracy[r, 1] <- cor(y_BC_test, val_pheno_ABT, use = "complete")
  }
  finalaccuracy[i, 1] <- mean(accuracy[,1])
  
}
mt<- mean(finalaccuracy[,1])
sd<- sd(finalaccuracy[,1])
mt
#fwrite(mt,file="bayes_result.csv",sep=",")
#write.table (mt, paste(output_path,"/h2.csv",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)

fit_BC=BGLR(y=y, ETA=ETA,nIter=nIter, burnIn=burnIn, saveAt=saveAt)
y_BC <- fit_BC$yHat  
y_BC_test <- y_BC[test] #提取估计值
##准确性
accuracy[r, 1] <- cor(y_BC_test, val_pheno_ABT, use = "complete")

##计算贝叶斯方法估计的遗传力
file_names <- list.files()
bin <- grep("^ETA_[0-9]_b.bin",file_names,value = TRUE)
B=readBinMat(bin)
h2_new=rep(NA,nrow(B))
varU_new=h2_new
varE_new=h2_new
for(i in 1:length(h2_new)){
  u=snp%*%B[i,]
  varU_new[i]=var(u)
  varE_new[i]=var(abt_y[[colnames(abt_data)[target_effect], exact = FALSE]]-u)
  h2_new[i]=varU_new[i]/(varU_new[i]+varE_new[i])
}

write.table (h2_new, paste(output_path,"/h2.csv",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
write.table (varU_new, paste(output_path,"/varU_new.csv",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
write.table (varE_new, paste(output_path,"/varE_new.csv",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
#fwrite(h2_new,file="h2.csv",sep=",")
#fwrite(varU_new,file="varU_new.csv",sep=",")
#fwrite(varE_new,file="varE_new.csv",sep=",")
h2 <- mean(h2_new)
#sd <- sd(h2_new)(sd,file="sd.csv",sep=",")  
#h2
#sd
gebvlabel=abt_data[,1]
gebvvalue=fit_BC$yHat
gebv=data.frame(gebvlabel,gebvvalue)
write.table (gebv, paste(output_path,"/bayes_GEBV.txt",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
#write.table (gebv, paste("/home/zhi/Desktop/AquaGS_GUI-main/Output/bayes_GEBV.txt",sep = ""), sep =" ", row.names =FALSE, col.names =FALSE, quote =FALSE)

ans = c(0,0)
ans[1]=mean(accuracy)
ans[2]=h2
ans[3]=mean(varU_new)
ans[4]=mean(varE_new)
write.table (ans, paste(output_path,"/bayes_output.txt",sep = ""), sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)

