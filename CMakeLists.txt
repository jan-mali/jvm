cmake_minimum_required(VERSION 3.31)
project(jvm)

set(CMAKE_CXX_STANDARD 20)

add_executable(jvm main.cpp
        ClassFile/ClassFile.cpp
        ClassFile/ClassFile.h
        ClassFile/ConstantPool.cpp
        ClassFile/ConstantPool.h
        ClassFile/AccessFlags.h
        ClassFile/Fields.cpp
        ClassFile/Fields.h
        ClassFile/Methods.cpp
        ClassFile/Methods.h
        ClassFile/Attributes.cpp
        ClassFile/Attributes.h)
