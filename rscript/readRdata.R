rm(list = ls())
rdata_path = "/home/liang/Documents/AquaGS_GUI/Output/Rbuffer.Rdata"
load(rdata_path)

require(sommer)
data$poolID <- as.factor(data$poolID)
data$shell_color <- as.factor(data$shell_color)
ans_G <- mmer(ABT_t ~  poolID+shell_color,
              random =  ~ vs(AnimalID, Gu = G),    
              rcov =  ~ units,
              data = data)
summary(ans_G)$varcomp
vpredict(ans_G, h2 ~ V1/(V1+V2))$Estimate[1]

ans_G$U$`u:AnimalID`$ABT_t <-as.data.frame(ans_G$U$`u:AnimalID`$ABT_t)
rownames(ans_G$U$`u:AnimalID`$ABT_t) <-gsub("AnimalID", "", rownames(ans_G$U$`u:AnimalID`$ABT_t))

GEBV <- as.data.table(ans_G$U$`u:AnimalID`$ABT_t,keep.rownames = T)
setnames(GEBV,"rn","AnimalID")
setnames(GEBV,"ans_G$U$`u:AnimalID`$ABT_t","GEBV")
fwrite(GEBV,file = "/home/liang/Documents/AquaGS_GUI/Output/GEBV.txt",sep = " ",col.names = T)
