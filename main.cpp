#include <iostream>

#include "ClassFile/ClassFile.h"
#include "VM/VM.h"

// Spec link: https://docs.oracle.com/javase/specs/jvms/se23/html/index.html
int main() {
    const auto vm = new VM();
    vm->start("Test");
    return 0;
}
