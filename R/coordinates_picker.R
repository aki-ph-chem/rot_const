
library(dplyr)
library(rgl)
library(stringr)
setwd("c:/Users/simiz/Desktop/rot_const/R")

###########データの取得#############
#AN=26 #原子数

num_of_atoms = 21

#stb3=read.csv("stb3.csv")  

file_name = "DIBENZOTHIOPHENE_DFT_3-21G_B3LYP.LOG"

Log_file = readLines(file_name)

#n=which(stb3[,]=="Standard orientation:") %>% max()

flag_for_coordinates = Log_file[]== "                         Standard orientation:                         "

num_of_line = which(flag_for_coordinates) %>% max()

#atm2=stb3[(n+5):(n+5+AN-1),]

coordinates = Log_file[(num_of_line + 5):(num_of_line + 5 + num_of_atoms -1)]


#atm_n2=atm2[] %>% stringr::str_split(" ") %>% type.convert() ##　文字列を分割して数値に変換

coordinates_numerical_crude = coordinates[] %>% stringr::str_split(" ") %>% type.convert() 

coordinates_numerical_crude

#  atm_n2 = atm2[] %>% stringr::str_split(" ") 

# atm_n2 = atm_n2[grep("^[9-9]{3}$",atm_n2)]

A=matrix(0,num_of_atoms,6)

coordinates_numerical = A


for(i in 1:num_of_atoms){
    for(j in 1:6){

     coordinates_numerical[i,j]=coordinates_numerical_crude[[i]][complete.cases(coordinates_numerical_crude[[i]])][j]

    }
}

coordinates_numerical

