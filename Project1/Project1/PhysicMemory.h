#pragma once
#include<string>
#include<vector>
#include<atomic>
#include "DataStruct.h"

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



/* ---------------------------SPARSEMEM模型------------------------------------ */

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

#define PAGE_SIZE 1<<12 // 4K页面大小；
#define SECTION_PER_ROOTS PAGE_SIZE/sizeof(struct mem_section) // 一个mem_section*指针内部存储了多少个mem_section对象；
#define SECTION_SIZE 2<<27 // 一个mem_section负责管理多大的物理内存；128M
#define PAGES_PER_SECTION SECTION_SIZE/PAGE_SIZE // 一个mem_section内部存储了多少个struct page对象；


struct mem_section {
	Page** section;
	std::string usage;
};

// 全局mem_map，是一个二维数组；
extern mem_section** mem_sections;

// 工具函数，如何根据页帧号pfn找到所在mem_section对象；
struct mem_section pfn_to_section(unsigned long pfn) {
	return mem_sections[pfn / SECTION_SIZE / SECTION_PER_ROOTS][(pfn * PAGE_SIZE) % SECTION_PER_ROOTS];
}

/*----------------------------------buddy system--------------------------------------*/
#define MAX_FREE_AREA_SIZE 11 // 一个buddy数组有11中不同size的空闲链表，从4KB开始，挨个乘2；
#define MIGRATE_TYPES 3

enum class Migrate_Type{
	MOVABLE, // 可移动
	UNMOVABLE, // 不可移动
	RECLAIMABLE // 可回收
};


// 一个尺寸的链表，分为三种类型，可移动，不可移动和可回收类型；
struct free_area {
	ListHead<Page>* free_list[MIGRATE_TYPES]; // 存储不同大小内存块的空闲链表；
	unsigned long long nr_free; // 当前freelist的空闲页个数；
};

// 通过zone来管理内存；
enum class ZONE_TYPE{
	ZONE_DMA, // DMA使用的内存空间；
	ZONE_NORMAL, // 正常可使用的内存空间；
	ZONE_MOVABLE,
	ZONE_DEVICE, // 外设寄存器映射到内存的区域，如：GPU等；
	MAX_ZONE_TYPE // 用于定义一个pglist_data的zone数组大小，表示一个节点最多可以有多少个ZONE；
};
// 每一个zone都有一个自己的伙伴系统，就是对应着free_area数组；
struct zone {
	pglist_data* zone_pgdata; // 当前zone所在的node的pglist_data;
	int zone_start_pfn; // 该zone管理的起始页框号；
	ZONE_TYPE type;
	struct free_area free_area[MAX_FREE_AREA_SIZE];
};

#define MAX_NR_ZONES (int)ZONE_TYPE::MAX_ZONE_TYPE // 一个节点最多有几个zones；
#define MAX_NUMANODES 8 // 一个服务器最多的节点个数；
#define MAX_ZONES_PER_ZONELIST MAX_NUMANODES * MAX_NR_ZONES // 表示所有node可能的最多zone数。

// 在numa架构下每一个cpu都被作为一个node来看待，这里的pglist_data就对应一个node；
typedef struct pglist_data {
	struct zone node_zone[(int)ZONE_TYPE::MAX_ZONE_TYPE]; // 本节点管理的zone数组；
	struct zone global_node_zone[MAX_ZONES_PER_ZONELIST];
	int nr_zones; // 当前节点拥有的zone数量；
	unsigned long long node_id;
	ListHead<zone>* zonelist; // 存储当前cpu对应的所有zone的链表；
}pg_data_t;

// 初始化一个zone的伙伴系统；
void init_zone_free_area() {

}

// 当前主机的cpu个数
#define NR_CPU 1
// 定义全局的pglist_data，存储了每一个cpu对应的pglist_data结构体
pg_data_t pglists[NR_CPU];

/*--------------------------page compact碎片整理-------------------------*/

// 碎片整理的上下文参数结构体；
struct compact_control {
	// 在从后向前扫描zone时，存储空闲页；
	ListHead<Page>* freepages;
	// 在从前向后扫描zone时，存储待迁移的movable/reclaimable/页；
	ListHead<Page>* migratepages;
	// 空闲页数；
	unsigned long nr_free;
	// movable页数；
	unsigned long nr_movable;
	// 当前扫描的zone;
	struct zone zone;
	// 当前需要分配的内存大小；
	unsigned long order;
};

// 对一个zone执行碎片整理；
void compact_page() {


}

// 碎片整理操作；
void __alloc_page_compact(int preferred_nid ,std::vector<int> nodemask) {
	compact_control cc={
		.nr_free=0,
		.nr_movable=0,
	}

	for (zone : zonelist) {
		// 对每个zone执行碎片整理操作；
		compact_page()；
	}
	
}


























/* --------------------------------------------------------------- */
// 机器初始化程序，调用上面的几个函数；
void setup_arch(char** cmdline_p) {
		// 保存物理内存检测结果
		e820_memory_setup();
		// memblock内存分配器初始化
		e820_memory_block_init();
}