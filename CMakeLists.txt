cmake_minimum_required(VERSION 3.31)
project(jvm)

set(CMAKE_CXX_STANDARD 20)

add_executable(jvm main.cpp
        Loader/ClassFile.cpp
        Loader/ClassFile.h
        Loader/ConstantPool.cpp
        Loader/ConstantPool.h
        Loader/AccessFlags.h
        Loader/Fields.cpp
        Loader/Fields.h
        Loader/Methods.cpp
        Loader/Methods.h
        Loader/Attributes.cpp
        Loader/Attributes.h)
