#pragma once
#include<string>
#include<atomic>

// 物理内存：开机之后先会通过内存固件进行物理内存的检测，查看内存的范围等进行构建 e820_table 存储所有的物理内存；
// 之后进行粗粒度映射的初始化(memblock(最小单位为memory_region))；
// 最后再进行细粒度映射的初始化(mem_section[N][M](最小单位为page))

/* --------------------------------------------------------------- */
// 物理内存探测，e820_table初始化；
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

// 探测物理内存，初始化e820_table；
void detect_memory() {
	// detect_memory_e820();
}

void e820_memory_setup(){
	detect_memory();
}

/* --------------------------------------------------------------- */
// memblock粗粒度物理内存初始化；
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

// 表示全部物理内存
struct MemBlock {
	Memory_Type usable;
	Memory_Type reserved;
};

// 初始化memory_block
void e820_memory_block_init() {

}



/* --------------------------------------------------------------- */

// 物理页
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
	std::atomic<int> _refcount; // 引用计数
};

struct mem_section {
	Page** section;
	std::string usage;
};

extern mem_section mem_sections;


/* --------------------------------------------------------------- */
// 机器初始化程序，调用上面的几个函数；
void setup_arch(char** cmdline_p) {
		// 保存物理内存检测结果
		e820_memory_setup();
		// memblock内存分配器初始化
		e820_memory_block_init();
}