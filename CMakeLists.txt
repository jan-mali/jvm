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
        VM/Instructions.h
        Utils/HashTools.h
        Utils/DescriptorTools.h
        VM/Native/NativeClass.h
        VM/Native/JVM/JVMClass.cpp
        VM/Native/JVM/JVMClass.h
        VM/Native/NativeClassRegistry.h
        VM/Native/NativeClassRegistry.cpp)

# Java Runtime
set(RUNTIME_DIR ${CMAKE_SOURCE_DIR}/Runtime)

# Find all Java source files in the Runtime directory
file(GLOB_RECURSE JAVA_FILES "${RUNTIME_DIR}/*.java")

# Locate Java tools
find_package(Java REQUIRED)
find_package(JNI REQUIRED)

if(JAVA_FILES)
    # Specify the output directory for compiled .class files
    set(JAVA_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Runtime)

    # Create a custom target for Java compilation
    add_custom_target(CompileJava ALL
            COMMAND ${Java_JAVAC_EXECUTABLE} -d ${JAVA_OUTPUT_DIR} ${JAVA_FILES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Compiling Java files in Runtime directory"
    )

    # Ensure the target is built before the main executable
    add_dependencies(jvm CompileJava)

    # Copy Runtime directory to the build output folder
    add_custom_command(TARGET jvm POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RUNTIME_DIR} ${CMAKE_BINARY_DIR}/Runtime
            COMMENT "Copying Runtime directory to build output folder"
    )
else()
    message(WARNING "No Java files found in ${RUNTIME_DIR}")
endif()
