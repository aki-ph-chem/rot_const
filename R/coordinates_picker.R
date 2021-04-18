
#This tool is made for pick up coordinates from Gaussian .LOG file

##load library###

library(dplyr)
library(rgl)
library(stringr)

## set working directry 

my_working_directory = "c:/Users/simiz/Desktop/rot_const/R"

setwd(my_working_directory)


##########  information of input #######
num_of_atoms = 21
 
input_file_name = "DIBENZOTHIOPHENE_DFT_3-21G_B3LYP.LOG"

#load .LOG file

Log_file = readLines(input_file_name)


flag_for_coordinates = Log_file[]== "                         Standard orientation:                         "

num_of_line = which(flag_for_coordinates) %>% max()


coordinates = Log_file[(num_of_line + 5):(num_of_line + 5 + num_of_atoms -1)]


coordinates_numerical_crude = coordinates[] %>% stringr::str_split(" ") %>% type.convert() 

coordinates_numerical_crude


A=matrix(0,num_of_atoms,6)

coordinates_numerical = A


for(i in 1:num_of_atoms){
    for(j in 1:6){

     coordinates_numerical[i,j]=coordinates_numerical_crude[[i]][complete.cases(coordinates_numerical_crude[[i]])][j]

    }
}


coordinates_numerical


