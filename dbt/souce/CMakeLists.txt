add_library(dbt

	SHARED

	calc_I.cpp
	calc_g.cpp
	geo.cpp
        csv_i.cpp
	grad_n.cpp
	)

target_include_directories( dbt

	PUBLIC ${PROJECT_SOURCE_DIR}/include
	)

