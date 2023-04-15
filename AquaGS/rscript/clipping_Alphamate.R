rm(list = ls())
print("-----------clipping_Alphamate begin--------------")
args=commandArgs(T)

NumOfCandidate = as.integer(args[1])
print(paste("NumOfCandidate:",NumOfCandidate))
gender_flag = as.integer(args[2])
print(gender_flag)
Criterion_path =  args[3] 
Nrm_path = args[4]

if(gender_flag==1)
{
  gender_path = args[5]
}

require(data.table) 
#NumOfCandidate = 10
#gender_flag = 1
#Criterion_path = "E:\\OneDrive - mail.hfut.edu.cn\\AquaGS\\Criterion.txt"
#Nrm_path = "E:\\OneDrive - mail.hfut.edu.cn\\AquaGS\\Nrm.txt"
#if(gender_flag)
#{
#  gender_path = "E:\\OneDrive - mail.hfut.edu.cn\\AquaGS\\gender.txt"
#}

table_Criterion = read.table(Criterion_path,
                   head=FALSE,sep = " ")
table_Nrm = read.table(Nrm_path,
                       head=FALSE,sep = " ")

table_Criterion = table_Criterion[order(table_Criterion$V2,decreasing = T),]#排序
select_table_Criterion = table_Criterion[1:NumOfCandidate,]
setnames(select_table_Criterion,c('ID','BV'))
write.table(select_table_Criterion,Criterion_path, 
            sep =" ", row.names =FALSE, col.names =FALSE, quote =FALSE)

ID_select = select_table_Criterion$ID #BV前NumOfCandidate的ID
ID_original = table_Nrm[,1] #全部的ID

list_index_select = c() #BV排名前NumOfCandidate 在原始的矩阵上的位置
for(i in c(ID_select))
{
  list_index_select<-append(list_index_select,grep(i, c(ID_original)))
}

ans_Nrm = matrix(data = NA, nrow = NumOfCandidate, ncol = NumOfCandidate, 
                 byrow = FALSE,dimnames = list(c(ID_select),c(ID_select)))#新的空矩阵
Matrix_Nrm <- as.matrix(table_Nrm[,-c(1)])#原始的关系矩阵
rownames(Matrix_Nrm)<-ID_original
colnames(Matrix_Nrm)<-ID_original
for(i in (1:NumOfCandidate))#构建新的关系矩阵
{
  for(j in (1:NumOfCandidate))
  {
    ans_Nrm[i,j]=Matrix_Nrm[list_index_select[i],list_index_select[j]] 
  }
}
ans_Nrm_dt <- as.data.table(ans_Nrm,keep.rownames = T)
fwrite(ans_Nrm_dt,file = Nrm_path,sep = " ",col.names = F)

if(gender_flag==1)
{
  table_gender = read.table(gender_path,
                            head=FALSE,sep = " ")
  colnames(table_gender) <- c("ID", "Gender")
  table_gender = table_gender[table_gender$ID %in% ID_select,]
  write.table(table_gender,gender_path, 
              sep =" ", row.names =FALSE, col.names =FALSE, quote =FALSE)
}
save.image(file = "./test_Rbuffer.Rdata")
print("-----------clipping_Alphamate end--------------")

