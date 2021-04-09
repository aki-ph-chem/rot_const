

x = read.csv("stb_degree_1~30_by_1.csv")

#角度を０~30まで1ずつ変化させた時の回転定数


x

degree = x[,1]

A = x[,1]
B = x[,2]
C = x[,3] 

delta_I = 1/C -(1/A + 1/B)


# degree vs A

degree_vs_A = cbind(degree,A)
degree_vs_B = cbind(degree,B)
degree_vs_C = cbind(degree,C)
degree_vs_delta_I = cbind(degree,delta_I)

plot(degree_vs_A)
plot(degree_vs_B)
plot(degree_vs_C)

plot(degree_vs_delta_I)

degree_vs_delta_I



