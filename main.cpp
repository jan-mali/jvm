#include <iostream>

#include "Loader/ClassFile.h"

// Spec link: https://docs.oracle.com/javase/specs/jvms/se23/html/index.html
int main() {
    ClassFile* class_file = ClassFile::create_from_path("./Test.class");
    return 0;
}
