cmake_minimum_required(VERSION 2.8.11)

project(automobi)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)


# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_PREFIX_PATH "../../../Qt/5.4/gcc_64/lib/cmake")

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

# Generate code from ui files
# qt5_wrap_ui(UI_HEADERS mainwindow.ui)

# Generate rules for building source files from the resources
qt5_add_resources(QRCS resources.qrc)

set(AutoMobiController AutoMobiController.cpp AutoMobiController.h)
set(Car Car.cpp Car.h)
set(Wall Wall.cpp Wall.h)
set(Fuzzy Fuzzy/Fuzzy.cpp Fuzzy/Fuzzy.h Fuzzy/Rule.cpp Fuzzy/Rule.h) 
set(MF Fuzzy/MF/Membership_func.h

       Fuzzy/MF/Left_offset.cpp
       Fuzzy/MF/Left_offset.h 
       Fuzzy/MF/Slight_Left_offset.cpp
       Fuzzy/MF/Slight_Left_offset.h 
       Fuzzy/MF/None_offset.cpp
       Fuzzy/MF/None_offset.h 
       Fuzzy/MF/Slight_Right_offset.cpp
       Fuzzy/MF/Slight_Right_offset.h 
       Fuzzy/MF/Right_offset.cpp
       Fuzzy/MF/Right_offset.h 

       Fuzzy/MF/Slight_Short_dist.cpp 
       Fuzzy/MF/Slight_Short_dist.h 
       Fuzzy/MF/Short_dist.cpp 
       Fuzzy/MF/Short_dist.h 
       Fuzzy/MF/Slight_Long_dist.cpp 
       Fuzzy/MF/Slight_Long_dist.h 
       Fuzzy/MF/Long_dist.cpp 
       Fuzzy/MF/Long_dist.h 

       Fuzzy/MF/Slight_Left_steer.cpp 
       Fuzzy/MF/Slight_Left_steer.h
       Fuzzy/MF/Left_steer.cpp 
       Fuzzy/MF/Left_steer.h
       Fuzzy/MF/Slight_Right_steer.cpp 
       Fuzzy/MF/Slight_Right_steer.h
       Fuzzy/MF/Right_steer.cpp 
       Fuzzy/MF/Right_steer.h
   )
set(GA GA/GA.cpp GA/GA.h) 
set(PSO PSO/PSO.cpp PSO/PSO.h) 

# Tell CMake to create the automobi executable ${UI_HEADERS}
add_executable(automobi main.cpp mainwindow.cpp constants.h ${QRCS} ${AutoMobiController} ${Car} ${Wall} ${Fuzzy} ${MF} ${GA} ${PSO})

# Add the Qt5 Widgets for linking
target_link_libraries(automobi Qt5::Widgets)
