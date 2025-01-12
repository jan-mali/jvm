#pragma once

class Method;
class Class;
class Frame;
class VMThread;
class VM;

class NativeClass {
public:
	virtual ~NativeClass() = default;

	virtual bool execute_function(const char* name, const char* descriptor, VM* vm, VMThread* thread, Frame& frame, Class* _class, Method* method) = 0;

	[[nodiscard]] const char* name() const { return m_name; }

protected:
	void set_name(const char* name) { m_name = name; }

private:
	const char* m_name = "<NativeClass>";
	// TODO: Fields, etc
};
