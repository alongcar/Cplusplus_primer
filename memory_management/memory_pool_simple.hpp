#pragma once

#define MEM_PAGE_SIZE 0x1000 // 页面大小4k。1*8^3

typedef struct mempool_s {
public:
	int block_size;// 指块大小 如在一个4k的内存池上，固定每次分配一个32byte的块
	int free_count;// 指当前空闲块数目
	void* mem;// 指向内存池的初始位置
	void* ptr;// 指向下一次分配的块的位置
}mempool_t;

void test_memory_pool();