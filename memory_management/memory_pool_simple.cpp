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
	// 使用头插法将当前释放的块放到待分配内存块的首位，并使它指向当前ptr所在的块。
	*(char**)ptr = static_cast<char*>(mp->ptr);
	mp->ptr = ptr;
	mp->free_count++;
	std::cout << "free\n";
	std::cout << "mp->ptr：" << mp->ptr << "\n";
	
}

// mempool_s* mp = nullptr;// 兼容

int memInit(mempool_t* mp, size_t block_size) {
	// 如果mp页为空，返回-1
	if (!mp) return -1;
	// 将mp所指内存清空置零，分配的块由于频繁调用，每次分配出来的并不一定是崭新的块，所以对于堆上分配的内存一定要记得清空。
	// memset(mp, 0, sizeof(mempool_t));

	mp->block_size = block_size;
	mp->free_count = MEM_PAGE_SIZE / block_size;
	mp->mem = malloc(MEM_PAGE_SIZE);
	if (!mp->mem) return -1;
	
	mp->ptr = mp->mem;

	char* q = static_cast<char*>(mp->ptr);
	for (int i = 0; i < mp->free_count; i++) {
		// q转化为char指针的指针，并对这个指针的指针解引用，结果是*q为char的指针，该指针指向下一个块的指针域。即q中存的是指向下一个指针域的指针
		*(char**)q = q + block_size;
		// 将q后移，继续对之后的指针域执行，使它们指向下一个指针域
		q += block_size;
	}
	*(char**)q = nullptr;// 最后一个空闲块的指针域指空
}

#define malloc(mp, size) _malloc(mp, size)
#define free(mp, ptr) _free(mp, ptr)

void test_memory_pool() {
	mempool_t mempool;
	mempool_t* mp = &mempool;
	memInit(mp, 32);

	void* p1 = malloc(mp, 5);
	std::cout << "p1：" << p1 << "\n";
	void* p2 = malloc(mp, 10);
	std::cout << "p2：" << p2 << "\n";
	void* p3 = malloc(mp, 15);
	std::cout << "p3：" << p3 << "\n";
	void* p4 = malloc(mp, 20);
	std::cout << "p4：" << p4 << "\n";

	free(mp, p2);
	
	free(mp, p4);

	void* p5 = malloc(mp, 20);
	std::cout << "p5：" << p5 << "\n";
	void* p6 = malloc(mp, 20);
	std::cout << "p6：" << p6 << "\n";

}