#include"memory_primitives.hpp"
#include<stdlib.h>
#include<memory>
#include<iostream>

//void example1() {
//	// һ����Ϊ�ͽ׵��ڴ��������ӣ�ʹ��malloc��free�����䣬���·�����512byte�ڴ�
//	void* p1 = malloc(512); // 512bytes
//	free(p1);
//
//	complex<int>* p2 = new complex<int>;
//	delete p2;
//
//	// ���µ���ȫ�ֵĺ���operator new 
//	void* p3 = ::operator new(512);
//	::operator delete(p3);
//
//// ����ʹ��C++��׼��ķ��䷽ʽ������3�ֱ�׼�ӿڹ��
//#ifdef _MSC_VER
//	// allocate��deallocate������static�ģ�Ҫͨ�����������ã��������������3��int���͵Ŀռ䡣
//	int* p4 = std::allocator<int>().allocate(3, (int*)0);
//	std::allocator<int>().deallocate(p4, 3);
//#endif
//
//#ifdef __BORLANDC__
//	// ���º�������static�ģ�����5��int��С���ڴ�
//	int* p4 = std::allocator<int>().allocate(5;
//	std::allocator<int>().deallocate(p4, 5);
//#endif
//
//#ifdef __GNUC__
//	// ���º�����static��,����512byte���ڴ�,gnucҲ��������ķǾ�̬�ķ���ġ�
//	int* p4 = std::alloc::allocate(512);
//	alloc::deallocate(p4, 512);
//
//	// ���º����ǷǾ�̬�ģ�ͨ��������á����·���9���ڴ�
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
//	std::cout << "���ô���+1" << "�ֵ��ô�����" << ++cnt
//		<< "���ε���Ŀ�괴����ַΪ" << this << std::endl;
//}
//
//template<typename T>
//complex<T>::~complex() {
//	std::cout << "�������������ε���������ַΪ" << this << std::endl;
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