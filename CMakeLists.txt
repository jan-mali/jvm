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
        ClassFile/Attributes.h
        Loader/BootstrapClassLoader.cpp
        Loader/BootstrapClassLoader.h
        VM/MethodArea.cpp
        VM/MethodArea.h
        VM/VM.cpp
        VM/VM.h
        VM/Class.cpp
        VM/Class.h
        Loader/ClassLoader.h
        VM/Method.cpp
        VM/Method.h
        VM/VMThread.cpp
        VM/VMThread.h
        VM/CodeAddress.h
        VM/Frame.cpp
        VM/Frame.h
        VM/Variable.h
        VM/Instructions.cpp
        VM/Instructions.h)
