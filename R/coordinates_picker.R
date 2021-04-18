
library(dplyr)
library(rgl)
library(stringr)

setwd("c:/Users/simiz/Desktop/rot_const/R")

###########データの取得#############
AN=26 #原子数

stb3=read.csv("stb3.csv")  

n=which(stb3[,]=="Standard orientation:") %>% max()


atm2=stb3[(n+5):(n+5+AN-1),]


atm_n2=atm2[] %>% stringr::str_split(" ") %>% type.convert() ##　文字列を分割して数値に変換

#  atm_n2 = atm2[] %>% stringr::str_split(" ") 

# atm_n2 = atm_n2[grep("^[9-9]{3}$",atm_n2)]

A=matrix(0,26,6)

f=A

for (i in 1:26) {for (j in 1:6)
{
  f[i,j]=atm_n2[[i]][complete.cases(atm_n2[[i]])][j]
}
  
}

