#include "Instructions.h"

#include "Frame.h"
#include "Method.h"
#include "VMThread.h"

#define TODO(opcode, name) \
	uint16_t Instructions::op$##name(VM*, VMThread*, Frame&, Class*, Method*) { printf("TODO: Implement opcode: " #name); assert(false); }

TODO(0, nop);
TODO(1, aconst_null);
uint16_t Instructions::op$iconst_m1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, -1 });
	return 1;
}
uint16_t Instructions::op$iconst_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 0 });
	return 1;
}
uint16_t Instructions::op$iconst_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 1 });
	return 1;
}
uint16_t Instructions::op$iconst_2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 2 });
	return 1;
}
uint16_t Instructions::op$iconst_3(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 3 });
	return 1;
}
uint16_t Instructions::op$iconst_4(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 4 });
	return 1;
}
uint16_t Instructions::op$iconst_5(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Int, 5 });
	return 1;
}
TODO(9, lconst_0);
TODO(10, lconst_1);
TODO(11, fconst_0);
TODO(12, fconst_1);
TODO(13, fconst_2);
TODO(14, dconst_0);
TODO(15, dconst_1);
TODO(16, bipush);
TODO(17, sipush);
TODO(18, ldc);
TODO(19, ldc_w);
TODO(20, ldc2_w);
TODO(21, iload);
TODO(22, lload);
TODO(23, fload);
TODO(24, dload);
TODO(25, aload);
uint16_t Instructions::op$iload_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(0);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$iload_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(1);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$iload_2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(2);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$iload_3(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(3);
	frame.push_operand(value);
	return 1;
}
TODO(30, lload_0);
TODO(31, lload_1);
TODO(32, lload_2);
TODO(33, lload_3);
TODO(34, fload_0);
TODO(35, fload_1);
TODO(36, fload_2);
TODO(37, fload_3);
TODO(38, dload_0);
TODO(39, dload_1);
TODO(40, dload_2);
TODO(41, dload_3);
TODO(42, aload_0);
TODO(43, aload_1);
TODO(44, aload_2);
TODO(45, aload_3);
TODO(46, iaload);
TODO(47, laload);
TODO(48, faload);
TODO(49, daload);
TODO(50, aaload);
TODO(51, baload);
TODO(52, caload);
TODO(53, saload);
TODO(54, istore);
TODO(55, lstore);
TODO(56, fstore);
TODO(57, dstore);
TODO(58, astore);
uint16_t Instructions::op$istore_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(0, value);
	return 1;
}
uint16_t Instructions::op$istore_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(1, value);
	return 1;
}
uint16_t Instructions::op$istore_2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(2, value);
	return 1;
}
uint16_t Instructions::op$istore_3(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(3, value);
	return 1;
}
TODO(63, lstore_0);
TODO(64, lstore_1);
TODO(65, lstore_2);
TODO(66, lstore_3);
TODO(67, fstore_0);
TODO(68, fstore_1);
TODO(69, fstore_2);
TODO(70, fstore_3);
TODO(71, dstore_0);
TODO(72, dstore_1);
TODO(73, dstore_2);
TODO(74, dstore_3);
TODO(75, astore_0);
TODO(76, astore_1);
TODO(77, astore_2);
TODO(78, astore_3);
TODO(79, iastore);
TODO(80, lastore);
TODO(81, fastore);
TODO(82, dastore);
TODO(83, aastore);
TODO(84, bastore);
TODO(85, castore);
TODO(86, sastore);
TODO(87, pop);
TODO(88, pop2);
TODO(89, dup);
TODO(90, dup_x1);
TODO(91, dup_x2);
TODO(92, dup2);
TODO(93, dup2_x1);
TODO(94, dup2_x2);
TODO(95, swap);
uint16_t Instructions::op$iadd(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value + value2.value };
	frame.push_operand(result);
	return 1;
}
TODO(97, ladd);
TODO(98, fadd);
TODO(99, dadd);
uint16_t Instructions::op$isub(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value - value2.value };
	frame.push_operand(result);
	return 1;
}
TODO(101, lsub);
TODO(102, fsub);
TODO(103, dsub);
uint16_t Instructions::op$imul(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value * value2.value };
	frame.push_operand(result);
	return 1;
}
TODO(105, lmul);
TODO(106, fmul);
TODO(107, dmul);
TODO(108, idiv);
TODO(109, ldiv);
TODO(110, fdiv);
TODO(111, ddiv);
TODO(112, irem);
TODO(113, lrem);
TODO(114, frem);
TODO(115, drem);
TODO(116, ineg);
TODO(117, lneg);
TODO(118, fneg);
TODO(119, dneg);
TODO(120, ishl);
TODO(121, lshl);
TODO(122, ishr);
TODO(123, lshr);
TODO(124, iushr);
TODO(125, lushr);
TODO(126, iand);
TODO(127, land);
TODO(128, ior);
TODO(129, lor);
TODO(130, ixor);
TODO(131, lxor);
uint16_t Instructions::op$iinc(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	uint8_t _const = method->code_attribute().code[thread->pc().instruction + 2];
	Variable value = frame.read_local(index);
	value.value += _const;
	frame.store_local(index, value);
	return 3;
}
TODO(133, i2l);
TODO(134, i2f);
TODO(135, i2d);
TODO(136, l2i);
TODO(137, l2f);
TODO(138, l2d);
TODO(139, f2i);
TODO(140, f2l);
TODO(141, f2d);
TODO(142, d2i);
TODO(143, d2l);
TODO(144, d2f);
TODO(145, i2b);
TODO(146, i2c);
TODO(147, i2s);
TODO(148, lcmp);
TODO(149, fcmpl);
TODO(150, fcmpg);
TODO(151, dcmpl);
TODO(152, dcmpg);
TODO(153, ifeq);
TODO(154, ifne);
TODO(155, iflt);
TODO(156, ifge);
TODO(157, ifgt);
TODO(158, ifle);
TODO(159, if_icmpeq);
TODO(160, if_icmpne);
TODO(161, if_icmplt);
TODO(162, if_icmpge);
TODO(163, if_icmpgt);
TODO(164, if_icmple);
TODO(165, if_acmpeq);
TODO(166, if_acmpne);
TODO(167, goto);
TODO(168, jsr);
TODO(169, ret);
TODO(170, tableswitch);
TODO(171, lookupswitch);
TODO(172, ireturn);
TODO(173, lreturn);
TODO(174, freturn);
TODO(175, dreturn);
TODO(176, areturn);
TODO(177, return);
TODO(178, getstatic);
TODO(179, putstatic);
TODO(180, getfield);
TODO(181, putfield);
TODO(182, invokevirtual);
TODO(183, invokespecial);
TODO(184, invokestatic);
TODO(185, invokeinterface);
TODO(186, invokedynamic);
TODO(187, new);
TODO(188, newarray);
TODO(189, anewarray);
TODO(190, arraylength);
TODO(191, athrow);
TODO(192, checkcast);
TODO(193, instanceof);
TODO(194, monitorenter);
TODO(195, monitorexit);
TODO(196, wide);
TODO(197, multianewarray);
TODO(198, ifnull);
TODO(199, ifnonnull);
TODO(200, goto_w);
TODO(201, jsr_w);
TODO(202, breakpoint);
TODO(254, impdep1);
TODO(255, impdep2);

#undef TODO