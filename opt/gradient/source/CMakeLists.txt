# resistration of souce

add_library(grad

	SHARED

        function.cpp
	# func_2.cpp   
       grad_n.cpp
       )

# path to include

target_include_directories(

	grad

	PUBLIC ${PROJECT_SOURCE_DIR}/include

	)


