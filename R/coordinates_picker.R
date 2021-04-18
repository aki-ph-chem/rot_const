
#This tool is made for pick up coordinates from Gaussian .LOG file

##load library

library(dplyr)
library(rgl)
library(stringr)

## set working directry 

my_working_directory = "c:/Users/simiz/Desktop/rot_const/R"

setwd(my_working_directory)




##########  information of input #######
num_of_atoms = 21                                         # number of atoms
 
input_file_name = "DIBENZOTHIOPHENE_DFT_3-21G_B3LYP.LOG"  # name of input file name

name_of_output_file = "dbt.csv"                           # name of output file name

##############################

#load .LOG file

Log_file = readLines(input_file_name)


flag_for_coordinates = Log_file[]== "                         Standard orientation:                         "

num_of_line = which(flag_for_coordinates) %>% max()


coordinates = Log_file[(num_of_line + 5):(num_of_line + 5 + num_of_atoms -1)]


coordinates_numerical_crude = coordinates[] %>% stringr::str_split(" ") %>% type.convert() 


A=matrix(0,num_of_atoms,6)

coordinates_numerical = A


for(i in 1:num_of_atoms){
    for(j in 1:6){

     coordinates_numerical[i,j]=coordinates_numerical_crude[[i]][complete.cases(coordinates_numerical_crude[[i]])][j]

    }
}


coordinates_numerical


ファイル出力



write.table(coordinates_numerical,name_of_output_file,sep = ",",col.name = F)  #コンマ区切り

write.table(coordinates_numerical,name_of_output_file,sep = " ",col.name = F)  #スペース区切り

