#include"memory_primitives.hpp"
#include<stdlib.h>
#include<memory>
#include<iostream>

//void example1() {
//	// 一个较为低阶的内存分配的例子：使用malloc和free来分配，以下分配了512byte内存
//	void* p1 = malloc(512); // 512bytes
//	free(p1);
//
//	complex<int>* p2 = new complex<int>;
//	delete p2;
//
//	// 以下调用全局的函数operator new 
//	void* p3 = ::operator new(512);
//	::operator delete(p3);
//
//// 以下使用C++标准库的分配方式：现有3种标准接口规格，
//#ifdef _MSC_VER
//	// allocate和deallocate都不是static的，要通过对象来调用，下面的语句分配了3个int类型的空间。
//	int* p4 = std::allocator<int>().allocate(3, (int*)0);
//	std::allocator<int>().deallocate(p4, 3);
//#endif
//
//#ifdef __BORLANDC__
//	// 以下函数不是static的，分配5个int大小的内存
//	int* p4 = std::allocator<int>().allocate(5;
//	std::allocator<int>().deallocate(p4, 5);
//#endif
//
//#ifdef __GNUC__
//	// 以下函数是static的,分配512byte的内存,gnuc也是有上面的非静态的分配的。
//	int* p4 = std::alloc::allocate(512);
//	alloc::deallocate(p4, 512);
//
//	// 以下函数是非静态的，通过对象调用。以下分配9个内存
//	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
//	__gnu_cxx::__pool_alloc<int>.deallocate((int*)p5, 9);
//#endif
//
//}
//
//void* myAlloc(size_t size) {
//	return malloc(size);
//}
//
//void myFree(void* ptr) {
//	return free(ptr);
//}

//void* operator new(size_t size) {
//	std::cout << "using overloading global operator new() \n";
//	return myAlloc(size);
//}
//
//void* operator new[](size_t size) {
//	std::cout << "using overloading global operator new[]() \n";
//	return myAlloc(size);
//}
//
//void operator delete(void* ptr) {
//	std::cout << "using overloading global operator delete() \n";
//	myFree(ptr);
//}
//
//void operator delete[](void* ptr) {
//	std::cout << "using overloading global operator delete[]() \n";
//	myFree(ptr);
//}

//template<typename T>
//complex<T>::complex() {
//	std::cout << "调用次数+1" << "现调用次数：" << ++cnt
//		<< "本次调用目标创建地址为" << this << std::endl;
//}
//
//template<typename T>
//complex<T>::~complex() {
//	std::cout << "调用析构，本次调用析构地址为" << this << std::endl;
//}
//
//void try_to_overload_operator() {
//	complex<int>* c = new complex<int>();
//	delete c;
//	complex<int>* ac = new complex<int>[5]();
//	delete[] ac;
//}

void* operator new(size_t size, std::nothrow_t& _THROW0) {
	void* p;
	while ((p = malloc(size)) == 0) {
		_TRY_BEGIN
			if (_callnewh(size) == 0) break;
		_CATCH(std::bad_alloc) return(0);
		_CATCH_END
	}
	return (p);
}

//void __cdecl operator delete(void* p) _THROW0()
//{
//	// free an allocated object
//	free(p);
//}