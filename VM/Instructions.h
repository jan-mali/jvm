#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>

#define __ENUMERATE_OPCODES      \
	__ENUM(0, nop)               \
	__ENUM(1, aconst_null)       \
	__ENUM(2, iconst_m1)         \
	__ENUM(3, iconst_0)          \
	__ENUM(4, iconst_1)          \
	__ENUM(5, iconst_2)          \
	__ENUM(6, iconst_3)          \
	__ENUM(7, iconst_4)          \
	__ENUM(8, iconst_5)          \
	__ENUM(9, lconst_0)          \
	__ENUM(10, lconst_1)         \
	__ENUM(11, fconst_0)         \
	__ENUM(12, fconst_1)         \
	__ENUM(13, fconst_2)         \
	__ENUM(14, dconst_0)         \
	__ENUM(15, dconst_1)         \
	__ENUM(16, bipush)           \
	__ENUM(17, sipush)           \
	__ENUM(18, ldc)              \
	__ENUM(19, ldc_w)            \
	__ENUM(20, ldc2_w)           \
	__ENUM(21, iload)            \
	__ENUM(22, lload)            \
	__ENUM(23, fload)            \
	__ENUM(24, dload)            \
	__ENUM(25, aload)            \
	__ENUM(26, iload_0)          \
	__ENUM(27, iload_1)          \
	__ENUM(28, iload_2)          \
	__ENUM(29, iload_3)          \
	__ENUM(30, lload_0)          \
	__ENUM(31, lload_1)          \
	__ENUM(32, lload_2)          \
	__ENUM(33, lload_3)          \
	__ENUM(34, fload_0)          \
	__ENUM(35, fload_1)          \
	__ENUM(36, fload_2)          \
	__ENUM(37, fload_3)          \
	__ENUM(38, dload_0)          \
	__ENUM(39, dload_1)          \
	__ENUM(40, dload_2)          \
	__ENUM(41, dload_3)          \
	__ENUM(42, aload_0)          \
	__ENUM(43, aload_1)          \
	__ENUM(44, aload_2)          \
	__ENUM(45, aload_3)          \
	__ENUM(46, iaload)           \
	__ENUM(47, laload)           \
	__ENUM(48, faload)           \
	__ENUM(49, daload)           \
	__ENUM(50, aaload)           \
	__ENUM(51, baload)           \
	__ENUM(52, caload)           \
	__ENUM(53, saload)           \
	__ENUM(54, istore)           \
	__ENUM(55, lstore)           \
	__ENUM(56, fstore)           \
	__ENUM(57, dstore)           \
	__ENUM(58, astore)           \
	__ENUM(59, istore_0)         \
	__ENUM(60, istore_1)         \
	__ENUM(61, istore_2)         \
	__ENUM(62, istore_3)         \
	__ENUM(63, lstore_0)         \
	__ENUM(64, lstore_1)         \
	__ENUM(65, lstore_2)         \
	__ENUM(66, lstore_3)         \
	__ENUM(67, fstore_0)         \
	__ENUM(68, fstore_1)         \
	__ENUM(69, fstore_2)         \
	__ENUM(70, fstore_3)         \
	__ENUM(71, dstore_0)         \
	__ENUM(72, dstore_1)         \
	__ENUM(73, dstore_2)         \
	__ENUM(74, dstore_3)         \
	__ENUM(75, astore_0)         \
	__ENUM(76, astore_1)         \
	__ENUM(77, astore_2)         \
	__ENUM(78, astore_3)         \
	__ENUM(79, iastore)          \
	__ENUM(80, lastore)          \
	__ENUM(81, fastore)          \
	__ENUM(82, dastore)          \
	__ENUM(83, aastore)          \
	__ENUM(84, bastore)          \
	__ENUM(85, castore)          \
	__ENUM(86, sastore)          \
	__ENUM(87, pop)              \
	__ENUM(88, pop2)             \
	__ENUM(89, dup)              \
	__ENUM(90, dup_x1)           \
	__ENUM(91, dup_x2)           \
	__ENUM(92, dup2)             \
	__ENUM(93, dup2_x1)          \
	__ENUM(94, dup2_x2)          \
	__ENUM(95, swap)             \
	__ENUM(96, iadd)             \
	__ENUM(97, ladd)             \
	__ENUM(98, fadd)             \
	__ENUM(99, dadd)             \
	__ENUM(100, isub)            \
	__ENUM(101, lsub)            \
	__ENUM(102, fsub)            \
	__ENUM(103, dsub)            \
	__ENUM(104, imul)            \
	__ENUM(105, lmul)            \
	__ENUM(106, fmul)            \
	__ENUM(107, dmul)            \
	__ENUM(108, idiv)            \
	__ENUM(109, ldiv)            \
	__ENUM(110, fdiv)            \
	__ENUM(111, ddiv)            \
	__ENUM(112, irem)            \
	__ENUM(113, lrem)            \
	__ENUM(114, frem)            \
	__ENUM(115, drem)            \
	__ENUM(116, ineg)            \
	__ENUM(117, lneg)            \
	__ENUM(118, fneg)            \
	__ENUM(119, dneg)            \
	__ENUM(120, ishl)            \
	__ENUM(121, lshl)            \
	__ENUM(122, ishr)            \
	__ENUM(123, lshr)            \
	__ENUM(124, iushr)           \
	__ENUM(125, lushr)           \
	__ENUM(126, iand)            \
	__ENUM(127, land)            \
	__ENUM(128, ior)             \
	__ENUM(129, lor)             \
	__ENUM(130, ixor)            \
	__ENUM(131, lxor)            \
	__ENUM(132, iinc)            \
	__ENUM(133, i2l)             \
	__ENUM(134, i2f)             \
	__ENUM(135, i2d)             \
	__ENUM(136, l2i)             \
	__ENUM(137, l2f)             \
	__ENUM(138, l2d)             \
	__ENUM(139, f2i)             \
	__ENUM(140, f2l)             \
	__ENUM(141, f2d)             \
	__ENUM(142, d2i)             \
	__ENUM(143, d2l)             \
	__ENUM(144, d2f)             \
	__ENUM(145, i2b)             \
	__ENUM(146, i2c)             \
	__ENUM(147, i2s)             \
	__ENUM(148, lcmp)            \
	__ENUM(149, fcmpl)           \
	__ENUM(150, fcmpg)           \
	__ENUM(151, dcmpl)           \
	__ENUM(152, dcmpg)           \
	__ENUM(153, ifeq)            \
	__ENUM(154, ifne)            \
	__ENUM(155, iflt)            \
	__ENUM(156, ifge)            \
	__ENUM(157, ifgt)            \
	__ENUM(158, ifle)            \
	__ENUM(159, if_icmpeq)       \
	__ENUM(160, if_icmpne)       \
	__ENUM(161, if_icmplt)       \
	__ENUM(162, if_icmpge)       \
	__ENUM(163, if_icmpgt)       \
	__ENUM(164, if_icmple)       \
	__ENUM(165, if_acmpeq)       \
	__ENUM(166, if_acmpne)       \
	__ENUM(167, goto)            \
	__ENUM(168, jsr)             \
	__ENUM(169, ret)             \
	__ENUM(170, tableswitch)     \
	__ENUM(171, lookupswitch)    \
	__ENUM(172, ireturn)         \
	__ENUM(173, lreturn)         \
	__ENUM(174, freturn)         \
	__ENUM(175, dreturn)         \
	__ENUM(176, areturn)         \
	__ENUM(177, return)          \
	__ENUM(178, getstatic)       \
	__ENUM(179, putstatic)       \
	__ENUM(180, getfield)        \
	__ENUM(181, putfield)        \
	__ENUM(182, invokevirtual)   \
	__ENUM(183, invokespecial)   \
	__ENUM(184, invokestatic)    \
	__ENUM(185, invokeinterface) \
	__ENUM(186, invokedynamic)   \
	__ENUM(187, new)             \
	__ENUM(188, newarray)        \
	__ENUM(189, anewarray)       \
	__ENUM(190, arraylength)     \
	__ENUM(191, athrow)          \
	__ENUM(192, checkcast)       \
	__ENUM(193, instanceof)      \
	__ENUM(194, monitorenter)    \
	__ENUM(195, monitorexit)     \
	__ENUM(196, wide)            \
	__ENUM(197, multianewarray)  \
	__ENUM(198, ifnull)          \
	__ENUM(199, ifnonnull)       \
	__ENUM(200, goto_w)          \
	__ENUM(201, jsr_w)           \
	__ENUM(202, breakpoint)      \
	__ENUM(254, impdep1)         \
	__ENUM(255, impdep2)

class Method;
class Class;
class Frame;
class VMThread;
class VM;

class Instructions {
public:
	static uint16_t execute(const uint8_t opcode, VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
		switch (opcode) {
#define __ENUM(opcode, name) \
	case opcode:             \
		return op$##name(vm, thread, frame, _class, method);
			__ENUMERATE_OPCODES
#undef __ENUM
		default:
			printf("Unknown instruction opcode 0x%x\n", opcode);
			assert(false);
		}
	}
	static const char* opcode_name(const uint8_t opcode) {
		switch (opcode) {
#define __ENUM(opcode, name) \
	case opcode:             \
		return #name;
			__ENUMERATE_OPCODES
#undef __ENUM
		default:
			return "???";
		}
	}

private:
#define __ENUM(opcode, name) static uint16_t op$##name(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method);
	__ENUMERATE_OPCODES
#undef __ENUM
};

#undef __ENUMERATE_OPCODES
