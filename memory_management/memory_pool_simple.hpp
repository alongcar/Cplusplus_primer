#pragma once

#define MEM_PAGE_SIZE 0x1000 // ҳ���С4k��1*8^3

typedef struct mempool_s {
public:
	int block_size;// ָ���С ����һ��4k���ڴ���ϣ��̶�ÿ�η���һ��32byte�Ŀ�
	int free_count;// ָ��ǰ���п���Ŀ
	void* mem;// ָ���ڴ�صĳ�ʼλ��
	void* ptr;// ָ����һ�η���Ŀ��λ��
}mempool_t;

void test_memory_pool();