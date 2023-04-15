rm(list = ls())
print("-----------bayes.R begin--------------")
args =commandArgs(T)
input_path_bf = args[1]
GEBV_path_bf = args[2]
output_path_bf = args[3]
Animal_index_bf = as.integer(args[4])+1
target_index_bf = as.integer(args[5])+1
bayes_name_bf = args[6]
k_flod_rep_bf = as.integer(args[7])
k_flod_k_bf = as.integer(args[8])
bayes_iteration_bf = as.integer(args[9])
bayes_butnIn_bf = as.integer(args[10])
fixed_num_bf = args[11]

fixed_index_bf = c(0)
j = 12
for(i in 1:fixed_num_bf){
  fixed_index_bf[i]  =  as.integer(args[j])+1
  j = j+1
}

fixed_index_type_bf = c(0)
for(i in 1:fixed_num_bf){
  fixed_index_type_bf[i]  =  as.integer(args[j])
  j = j+1
}

runing_path = args[j]
setwd(runing_path)

load(input_path_bf)
input_path = input_path_bf
GEBV_path = GEBV_path_bf
output_path = output_path_bf
Animal_index = Animal_index_bf
target_index = target_index_bf
bayes_name = bayes_name_bf
k_flod_rep = k_flod_rep_bf
k_flod_k = k_flod_k_bf
bayes_iteration = bayes_iteration_bf
bayes_butnIn = bayes_butnIn_bf

fixed_num = fixed_num_bf
fixed_index = fixed_index_bf
fixed_index_type = fixed_index_type_bf


rm(input_path_bf,GEBV_path_bf,output_path_bf,
   target_index_bf,bayes_name_bf,k_flod_rep_bf,
   k_flod_k_bf,bayes_iteration_bf,bayes_butnIn_bf,fixed_index_bf,
   fixed_num_bf,fixed_index_type_bf,i,j)

#input_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/Rbuffer.Rdata"
#load(input_path)
#GEBV_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/bayes_GEBV.txt"
#output_path = "E:/OneDrive - mail.hfut.edu.cn/AquaGS/Output/bayes_output.txt"
#Animal_index = as.integer("0")+1
#target_index = as.integer("8")+1
#bayes_name = "BayesB"
#k_flod_rep = as.integer("2")
#k_flod_k = as.integer("2")
#bayes_iteration = as.integer("15")
#bayes_butnIn = as.integer("5")
#fixed_num = as.integer("2")
#fixed_index = c(5,8)
#fixed_index_type = c(1,0)
require(data.table)
require(ASRgenomics)
#require(BGLR)


if(require(BGLR)){
  print("BGLR is loaded correctly")
} else {
  print("trying to install BGLR")
  install.packages("BGLR")
  if(require(BGLR)){
    print("BGLR installed and loaded")
  } else {
    stop("could not install BGLR")
  }
}


#geno_012_matrix已经在rdata文件夹中
name <- colnames(geno_012_matrix) ##
split_name <- tstrsplit(name,split = "_")[[1]]  #对snp数据的列名做修改
colnames(geno_012_matrix) <- split_name
snp <- as.matrix(geno_012_matrix)
#
pheno <- copy(data)
saveAt='';
S0=NULL;
weights=NULL;
R2=0.5;
thin=3


col_list = colnames(data)#获取列名
target_item = col_list[target_index]
Animal_item = col_list[Animal_index]

#生成 abt_y <-data.frame(data[,..target_index],data$poolID) ，并运行

if(fixed_num>0)#if have fixed effects
{
  pama =""
  for(i in fixed_index){
    pama = paste(pama,"data$",col_list[i],",",sep="")
  }
  pama = substr(pama,1,nchar(pama)-1)#delete the final "+"
  pama = paste("abt_y <-data.frame(data[,..target_index],",pama,")",sep = "")
  print(pama)
  eval(parse(text = pama))
}

#ETA<-list(list(~factor(data$poolID),data=abt_y,model='FIXED'), ##固定效应
#          list(~factor(SL_initial), data=data, model='BRR'),  ##连续型
#          list(X=snp,model='BayesB',saveEffects=T)) 
if(fixed_num>0)#if have fixed effects
{
  #ETA<-list(
  pama ="ETA<-list("
  count = 1
  for(i in fixed_index){
    #list(~factor(data$poolID),data=abt_y,model='FIXED'),
    factor_flag = fixed_index_type[count]
    if(factor_flag ==1)#is factor?
    {
      part = ""
      part = paste("list(~factor(","data$",col_list[i],"),data=abt_y,model='FIXED'),",sep="")
    }else{##list(~factor(data$ww),data=abt_y,model='BRR'),
      part = ""
      part = paste("list(~factor(","data$",col_list[i],"),data=abt_y,model='BRR'),",sep="")
    }
    pama = paste(pama,part,sep = "")
    count = count+1
  }
  #),data=abt_y,model='FIXED'),list(X=snp,model='BayesB',saveEffects=T)) \
  #pama = substr(pama,1,nchar(pama)-1)#delete the final ","
  pama = paste(pama,"list(X=snp,model=\'",bayes_name,"\',saveEffects=T))",sep = "")
  print(pama)
  eval(parse(text = pama))
  rm(count)
}

accuracy = matrix(nrow=k_flod_k, ncol=1)
finalaccuracy=matrix(nrow=k_flod_rep, ncol=1)
for(i in 1:k_flod_rep) {
  animal_pos <- seq(nrow(pheno))
  s = matrix(sample(animal_pos, (floor(nrow(pheno) * (1/k_flod_k)) * k_flod_k)), ncol = k_flod_k)
  for (r in 1:k_flod_k) {
    #y <- copy(abt_y$ABT_t)
      
      pama ="y <- copy(abt_y$"
      pama = paste(pama,target_item,")",sep = "")
      print(pama)
      eval(parse(text = pama))
    test <- s[, r]
    #val_pheno_ABT = abt_y$ABT_t[s[, r]]
      pama ="val_pheno_ABT = abt_y$"
      pama = paste(pama,target_item,"[s[, r]]",sep = "")
      print(pama)
      eval(parse(text = pama))
    y[s[, r]] <- NA
    fit_BC=BGLR(y=y,ETA=ETA,nIter=bayes_iteration,burnIn=bayes_butnIn,
                thin=thin,saveAt=saveAt,df0=5,S0=S0,weights=weights,R2=R2)
    
    y_BC <- fit_BC$yHat
    y_BC_test <- y_BC[test]
    accuracy[r, 1] <- cor(y_BC_test, val_pheno_ABT, use = "complete")
  }
  finalaccuracy[i, 1] <- mean(accuracy[,1])
}

bayes_GEBV <- as.data.table(y_BC)
#rownames(bayes_GEBV) <- geno_012_DT$IID
  pama = ""
  pama = paste("rownames(bayes_GEBV) <- data$",Animal_item,sep="")
  print(pama)
  eval(parse(text = pama))

write.table(bayes_GEBV,file=GEBV_path, sep =",", row.names =TRUE, col.names =FALSE, quote =FALSE)

mt<- mean(finalaccuracy[,1])
sd<- sd(finalaccuracy[,1])
mt
sd

file_names <- list.files()
print(file_names)
bin <- grep("^ETA_[0-9]_b.bin",file_names,value = TRUE)

B=readBinMat(bin)

h2_new=rep(NA,nrow(B))
varU_new=h2_new
varE_new=h2_new
for(i in 1:length(h2_new)){
  u=data.table(snp%*%B[i,])
  varU_new[i]=var(u)
  #binddt <- data.table(abt =abt_y$ABT_t,U=u$V1)
    pama = ""
    pama ="binddt <- data.table(abt =abt_y$"
    pama = paste(pama,target_item,",U=u$V1)",sep="")
    print(pama)
    eval(parse(text = pama))

  binddt <- binddt[!binddt$abt %in% NA]
  abt_modi <- binddt$abt
  u_mod <- binddt$U
  varE_new[i]=var(abt_modi-u_mod)
  h2_new[i]=varU_new[i]/(varU_new[i]+varE_new[i])
}
h2 <- mean(h2_new)
sd <- sd(h2_new)
h2
sd
##加性遗传方差：
mean(varU_new)
#残差：
mean(varE_new)


ans = c(0,0,0,0,0,0,0,0)
ans[1] = mean(finalaccuracy[,1])
ans[2] = sd(finalaccuracy[,1])
ans[3] = mean(h2_new)
ans[4] = sd(h2_new)
ans[5] = mean(varU_new)
ans[6] = sd(varU_new)
ans[7] = mean(varE_new)
ans[8] = sd(varE_new)
write.table(ans,output_path, sep =",", row.names =FALSE, col.names =FALSE, quote =FALSE)
#varU_new <- as.data.table(varU_new)
#varE_new <- as.data.table(varE_new)
#h2_new <- as.data.table(h2_new)
#fwrite(h2_new,file="bayes_h2.csv",sep=",")
#fwrite(varU_new,file="varU_new.csv",sep=",")
#fwrite(varE_new,file="varE_new.csv",sep=",")
save.image(file = "Rbuffer_BAYES.Rdata")


