#include"memory_pool_simple.hpp"
#include<iostream>
#include<cstdlib>
#include<string>


void* _malloc(mempool_t *mp, size_t size) {
	if (!mp || mp->free_count <=0 || size > mp->block_size) return NULL;
	void* ptr = mp->ptr;
	mp->ptr = *(char**)ptr;
	mp->free_count--;
	std::cout << "malloc\n";
	return ptr;
}

void _free(mempool_t *mp, void* ptr) {
	if (!mp) return;
	// ʹ��ͷ�巨����ǰ�ͷŵĿ�ŵ��������ڴ�����λ����ʹ��ָ��ǰptr���ڵĿ顣
	*(char**)ptr = static_cast<char*>(mp->ptr);
	mp->ptr = ptr;
	mp->free_count++;
	std::cout << "free\n";
	std::cout << "mp->ptr��" << mp->ptr << "\n";
	
}

// mempool_s* mp = nullptr;// ����

int memInit(mempool_t* mp, size_t block_size) {
	// ���mpҳΪ�գ�����-1
	if (!mp) return -1;
	// ��mp��ָ�ڴ�������㣬����Ŀ�����Ƶ�����ã�ÿ�η�������Ĳ���һ����ո�µĿ飬���Զ��ڶ��Ϸ�����ڴ�һ��Ҫ�ǵ���ա�
	// memset(mp, 0, sizeof(mempool_t));

	mp->block_size = block_size;
	mp->free_count = MEM_PAGE_SIZE / block_size;
	mp->mem = malloc(MEM_PAGE_SIZE);
	if (!mp->mem) return -1;
	
	mp->ptr = mp->mem;

	char* q = static_cast<char*>(mp->ptr);
	for (int i = 0; i < mp->free_count; i++) {
		// qת��Ϊcharָ���ָ�룬�������ָ���ָ������ã������*qΪchar��ָ�룬��ָ��ָ����һ�����ָ���򡣼�q�д����ָ����һ��ָ�����ָ��
		*(char**)q = q + block_size;
		// ��q���ƣ�������֮���ָ����ִ�У�ʹ����ָ����һ��ָ����
		q += block_size;
	}
	*(char**)q = nullptr;// ���һ�����п��ָ����ָ��
}

#define malloc(mp, size) _malloc(mp, size)
#define free(mp, ptr) _free(mp, ptr)

void test_memory_pool() {
	mempool_t mempool;
	mempool_t* mp = &mempool;
	memInit(mp, 32);

	void* p1 = malloc(mp, 5);
	std::cout << "p1��" << p1 << "\n";
	void* p2 = malloc(mp, 10);
	std::cout << "p2��" << p2 << "\n";
	void* p3 = malloc(mp, 15);
	std::cout << "p3��" << p3 << "\n";
	void* p4 = malloc(mp, 20);
	std::cout << "p4��" << p4 << "\n";

	free(mp, p2);
	
	free(mp, p4);

	void* p5 = malloc(mp, 20);
	std::cout << "p5��" << p5 << "\n";
	void* p6 = malloc(mp, 20);
	std::cout << "p6��" << p6 << "\n";

}