# generate a.out from main.cpp

#add_executable(a.out main.cpp)
add_executable(a.out main_2.cpp)

# link grad then generating a.out

target_link_libraries(a.out grad)
