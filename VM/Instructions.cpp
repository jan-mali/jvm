#include "Instructions.h"

#include "Class.h"
#include "Frame.h"
#include "Method.h"
#include "VM.h"
#include "VMThread.h"
#include "../ClassFile/ConstantPool.h"
#include "../Utils/DescriptorTools.h"

#define TODO(opcode, name) \
	uint16_t Instructions::op$##name(VM*, VMThread*, Frame&, Class*, Method*) { printf("TODO: Implement opcode: " #name "\n"); assert(false); }

struct MethodSearchResult {
	Class* _class;
	Method* method;
};

static MethodSearchResult find_method(uint16_t cp_methodref_index, VM* vm, Class* _class) {
	MethodSearchResult result {};

	ConstantPool::ConstantPoolEntry methodref_entry = _class->constant_pool()->get_jvm_index(cp_methodref_index);
	assert(methodref_entry.tag == ConstantPool::Tag::Methodref);

	uint16_t class_index = methodref_entry.method_ref.class_index;
	uint16_t name_and_type_index = methodref_entry.method_ref.name_and_type_index;

	ConstantPool::ConstantPoolEntry class_entry = _class->constant_pool()->get_jvm_index(class_index);
	assert(class_entry.tag == ConstantPool::Tag::Class);

	ConstantPool::ConstantPoolEntry name_and_type_entry = _class->constant_pool()->get_jvm_index(name_and_type_index);
	assert(name_and_type_entry.tag == ConstantPool::Tag::NameAndType);

	uint16_t class_name_index = class_entry._class.name_index;
	ConstantPool::ConstantPoolEntry class_name_entry = _class->constant_pool()->get_jvm_index(class_name_index);
	assert(class_name_entry.tag == ConstantPool::Tag::Utf8);

	uint16_t method_name_index = name_and_type_entry.name_and_type.name_index;
	ConstantPool::ConstantPoolEntry method_name_entry = _class->constant_pool()->get_jvm_index(method_name_index);
	assert(method_name_entry.tag == ConstantPool::Tag::Utf8);

	uint16_t method_descriptor_index = name_and_type_entry.name_and_type.descriptor_index;
	ConstantPool::ConstantPoolEntry method_descriptor_entry = _class->constant_pool()->get_jvm_index(method_descriptor_index);
	assert(method_descriptor_entry.tag == ConstantPool::Tag::Utf8);

	const char* class_name = class_name_entry.utf8.bytes;
	const char* method_name = method_name_entry.utf8.bytes;
	const char* method_descriptor = method_descriptor_entry.utf8.bytes;

	printf("find_method: %s.%s%s\n", class_name, method_name, method_descriptor);

	Class* target_class = vm->get_class(class_name);
	assert(target_class);

	Method* target_method = target_class->find_method(method_name, method_descriptor);
	assert(target_method);

	result._class = target_class;
	result.method = target_method;

	return result;
}

uint16_t Instructions::op$nop(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	return 1;
}
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
uint16_t Instructions::op$lconst_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Long, 0 });
	return 1;
}
uint16_t Instructions::op$lconst_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.push_operand({ Variable::Type::Long, 1 });
	return 1;
}
TODO(11, fconst_0);
TODO(12, fconst_1);
TODO(13, fconst_2);
TODO(14, dconst_0);
TODO(15, dconst_1);
uint16_t Instructions::op$bipush(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t byte = method->code_attribute().code[thread->pc().instruction + 1];
	const Variable value = { Variable::Type::Int, byte };
	frame.push_operand(value);
	return 2;
}
uint16_t Instructions::op$sipush(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t byte1 = method->code_attribute().code[thread->pc().instruction + 1];
	const uint8_t byte2 = method->code_attribute().code[thread->pc().instruction + 2];
	const Variable value = { Variable::Type::Int, (byte1 << 8) | byte2 };
	frame.push_operand(value);
	return 3;
}
TODO(18, ldc);
TODO(19, ldc_w);
uint16_t Instructions::op$ldc2_w(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t indexbyte1 = method->code_attribute().code[thread->pc().instruction + 1];
	const uint8_t indexbyte2 = method->code_attribute().code[thread->pc().instruction + 2];
	const uint16_t index = static_cast<uint16_t>((indexbyte1 << 8) | indexbyte2);
	auto entry = _class->constant_pool()->get_jvm_index(index);
	if (entry.tag == ConstantPool::Tag::Long) {
		int64_t value = entry._long.value();
		frame.push_operand({ Variable::Type::Long, value });
	} else {
		// TODO: Implement other cases (double, symbolic reference)
		assert(false);
	}
	return 3;
}
uint16_t Instructions::op$iload(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	const Variable value = frame.read_local(index);
	frame.push_operand(value);
	return 2;
}
uint16_t Instructions::op$lload(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	const Variable value = frame.read_local(index);
	frame.push_operand(value);
	return 2;
}
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
uint16_t Instructions::op$lload_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(0);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$lload_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(1);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$lload_2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(2);
	frame.push_operand(value);
	return 1;
}
uint16_t Instructions::op$lload_3(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.read_local(3);
	frame.push_operand(value);
	return 1;
}
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
uint16_t Instructions::op$istore(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	const Variable value = frame.pop_operand();
	frame.store_local(index, value);
	return 2;
}
uint16_t Instructions::op$lstore(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	const Variable value = frame.pop_operand();
	frame.store_local(index, value);
	// Both n & n+1 are set to the value because we are dealing with a long
	frame.store_local(index + 1, value);
	return 2;
}
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
uint16_t Instructions::op$lstore_0(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(0, value);
	// Both n & n+1 are set to the value because we are dealing with a long
	frame.store_local(1, value);
	return 1;
}
uint16_t Instructions::op$lstore_1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(1, value);
	// Both n & n+1 are set to the value because we are dealing with a long
	frame.store_local(2, value);
	return 1;
}
uint16_t Instructions::op$lstore_2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(2, value);
	// Both n & n+1 are set to the value because we are dealing with a long
	frame.store_local(3, value);
	return 1;
}
uint16_t Instructions::op$lstore_3(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	frame.store_local(3, value);
	// Both n & n+1 are set to the value because we are dealing with a long
	frame.store_local(4, value);
	return 1;
}
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
uint16_t Instructions::op$pop(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	frame.pop_operand();
	return 1;
}
TODO(88, pop2);
TODO(89, dup);
TODO(90, dup_x1);
TODO(91, dup_x2);
TODO(92, dup2);
TODO(93, dup2_x1);
TODO(94, dup2_x2);
uint16_t Instructions::op$swap(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value1 = frame.pop_operand();
	const Variable value2 = frame.pop_operand();
	frame.push_operand(value1);
	frame.push_operand(value2);
	return 1;
}
uint16_t Instructions::op$iadd(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value + value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$ladd(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value + value2.value };
	frame.push_operand(result);
	return 1;
}
TODO(98, fadd);
TODO(99, dadd);
uint16_t Instructions::op$isub(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value - value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$lsub(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value - value2.value };
	frame.push_operand(result);
	return 1;
}
TODO(102, fsub);
TODO(103, dsub);
uint16_t Instructions::op$imul(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value * value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$lmul(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value * value2.value };
	frame.push_operand(result);
	return 1;
}
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
uint16_t Instructions::op$ineg(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Int, -value.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$lneg(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Long, -value.value };
	frame.push_operand(result);
	return 1;
}
TODO(118, fneg);
TODO(119, dneg);
TODO(120, ishl);
TODO(121, lshl);
TODO(122, ishr);
TODO(123, lshr);
TODO(124, iushr);
TODO(125, lushr);
uint16_t Instructions::op$iand(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value & value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$land(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value & value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$ior(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value | value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$lor(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value | value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$ixor(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value1.value ^ value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$lxor(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value2 = frame.pop_operand();
	const Variable value1 = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value1.value ^ value2.value };
	frame.push_operand(result);
	return 1;
}
uint16_t Instructions::op$iinc(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	uint8_t index = method->code_attribute().code[thread->pc().instruction + 1];
	uint8_t _const = method->code_attribute().code[thread->pc().instruction + 2];
	Variable value = frame.read_local(index);
	value.value += _const;
	frame.store_local(index, value);
	return 3;
}
uint16_t Instructions::op$i2l(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Long, value.value };
	frame.push_operand(result);
	return 1;
}
TODO(134, i2f);
TODO(135, i2d);
uint16_t Instructions::op$l2i(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Int, static_cast<int32_t>(value.value & 0xFFFFFFFF) };
	frame.push_operand(result);
	return 1;
}
TODO(137, l2f);
TODO(138, l2d);
TODO(139, f2i);
TODO(140, f2l);
TODO(141, f2d);
TODO(142, d2i);
TODO(143, d2l);
TODO(144, d2f);
uint16_t Instructions::op$i2b(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value.value & 0xFF };
	frame.push_operand(result);
	return 1;
}
TODO(146, i2c);
uint16_t Instructions::op$i2s(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const Variable value = frame.pop_operand();
	const Variable result = { Variable::Type::Int, value.value & 0xFFFF };
	frame.push_operand(result);
	return 1;
}
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
uint16_t Instructions::op$ireturn(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	// TODO: Handle monitors
	if (method->access_flags().is_synchronized()) {
		printf("TODO: Don't know how to handle synchronized methods\n");
		assert(false);
	}
	const Variable value = frame.pop_operand();
	thread->handle_return();
	if (!thread->is_terminating())
		thread->current_frame().push_operand(value);
	// Don't increment the PC because it has already been replaced
	return 0;
}
TODO(173, lreturn);
TODO(174, freturn);
TODO(175, dreturn);
TODO(176, areturn);
uint16_t Instructions::op$return(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	// TODO: Handle monitors
	if (method->access_flags().is_synchronized()) {
		printf("TODO: Don't know how to handle synchronized methods\n");
		assert(false);
	}
	thread->handle_return();
	// Don't increment the PC because it has already been replaced
	return 0;
}
TODO(178, getstatic);
TODO(179, putstatic);
TODO(180, getfield);
TODO(181, putfield);
TODO(182, invokevirtual);
TODO(183, invokespecial);
uint16_t Instructions::op$invokestatic(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	const uint8_t indexbyte1 = method->code_attribute().code[thread->pc().instruction + 1];
	const uint8_t indexbyte2 = method->code_attribute().code[thread->pc().instruction + 2];
	const uint16_t index = indexbyte1 << 8 | indexbyte2;

	auto [target_class, target_method] = find_method(index, vm, _class);
	assert(target_class);
	assert(target_method);

	assert(target_method->access_flags().is_static());
	assert(!target_method->access_flags().is_abstract());

	if (target_method->access_flags().is_synchronized()) {
		printf("Synchronized methods are not supported yet\n");
		assert(false);
	}

	MethodDescriptor md = DescriptorTools::parse_method(target_method->descriptor());
	const int argument_count = md.params.size();

	auto arguments = std::vector<Variable>(argument_count, Variable());
	for (int i = argument_count - 1; i >= 0; --i) {
		arguments[i] = frame.pop_operand();
	}

	Frame new_frame = target_method->access_flags().is_native() ? Frame::create_native() : Frame::create(target_method->code_attribute());

	for (int i = 0; i < argument_count; ++i) {
		new_frame.store_local(i, arguments[i]);
	}

	const CodeAddress new_pc = { target_class, target_method, 0 };

	thread->prepare_invocation(new_pc, new_frame);

	return 3;
}
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
uint16_t Instructions::op$breakpoint(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	return 1;
}
uint16_t Instructions::op$impdep1(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	return 1;
}
uint16_t Instructions::op$impdep2(VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) {
	return 1;
}

#undef TODO