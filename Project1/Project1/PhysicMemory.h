#pragma once
#include<string>
#include<atomic>

// �����ڴ棺����֮���Ȼ�ͨ���ڴ�̼����������ڴ�ļ�⣬�鿴�ڴ�ķ�Χ�Ƚ��й��� e820_table �洢���е������ڴ棻
// ֮����д�����ӳ��ĳ�ʼ��(memblock(��С��λΪmemory_region))��
// ����ٽ���ϸ����ӳ��ĳ�ʼ��(mem_section[N][M](��С��λΪpage))

/* --------------------------------------------------------------- */
// �����ڴ�̽�⣬e820_table��ʼ����
#define E820_MAX_ENTRY 128

enum class e820_type {

};

struct e820_table_entry {
	unsigned long base;
	unsigned long size;
	enum e820_type t;
};

struct e820_table {
	int entry_cnt;
	e820_table_entry table[E820_MAX_ENTRY];
};

extern struct e820_table _e820_table;

// ̽�������ڴ棬��ʼ��e820_table��
void detect_memory() {
	// detect_memory_e820();
}

void e820_memory_setup(){
	detect_memory();
}

/* --------------------------------------------------------------- */
// memblock�����������ڴ��ʼ����
#define MEMORY_REGION_NUM 128


extern Memory_Region Usable[MEMORY_REGION_NUM];
extern Memory_Region Reserved[MEMORY_REGION_NUM];


enum class Memory_Flag {


};

struct Memory_Region {
	unsigned long base;
	unsigned long size;
	enum Memory_Flag flag;
};

struct Memory_Type {
	int cnt;
	int max;
	unsigned long totle_size;
	Memory_Region* region;
};

// ��ʾȫ�������ڴ�
struct MemBlock {
	Memory_Type usable;
	Memory_Type reserved;
};

// ��ʼ��memory_block
void e820_memory_block_init() {

}



/* --------------------------------------------------------------- */

// ����ҳ
struct Page {
	unsigned long flag;
	union {
		struct {
			union {

			};
		};


	};
	union {

	};
	std::atomic<int> _refcount; // ���ü���
};

struct mem_section {
	Page** section;
	std::string usage;
};

extern mem_section mem_sections;


/* --------------------------------------------------------------- */
// ������ʼ�����򣬵�������ļ���������
void setup_arch(char** cmdline_p) {
		// ���������ڴ�����
		e820_memory_setup();
		// memblock�ڴ��������ʼ��
		e820_memory_block_init();
}