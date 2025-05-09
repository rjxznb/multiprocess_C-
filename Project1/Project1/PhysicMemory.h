#pragma once
#include<string>
#include<vector>
#include<atomic>
#include "DataStruct.h"

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



/* ---------------------------SPARSEMEMģ��------------------------------------ */

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

#define PAGE_SIZE 1<<12 // 4Kҳ���С��
#define SECTION_PER_ROOTS PAGE_SIZE/sizeof(struct mem_section) // һ��mem_section*ָ���ڲ��洢�˶��ٸ�mem_section����
#define SECTION_SIZE 2<<27 // һ��mem_section���������������ڴ棻128M
#define PAGES_PER_SECTION SECTION_SIZE/PAGE_SIZE // һ��mem_section�ڲ��洢�˶��ٸ�struct page����


struct mem_section {
	Page** section;
	std::string usage;
};

// ȫ��mem_map����һ����ά���飻
extern mem_section** mem_sections;

// ���ߺ�������θ���ҳ֡��pfn�ҵ�����mem_section����
struct mem_section pfn_to_section(unsigned long pfn) {
	return mem_sections[pfn / SECTION_SIZE / SECTION_PER_ROOTS][(pfn * PAGE_SIZE) % SECTION_PER_ROOTS];
}

/*----------------------------------buddy system--------------------------------------*/
#define MAX_FREE_AREA_SIZE 11 // һ��buddy������11�в�ͬsize�Ŀ���������4KB��ʼ��������2��
#define MIGRATE_TYPES 3

enum class Migrate_Type{
	MOVABLE, // ���ƶ�
	UNMOVABLE, // �����ƶ�
	RECLAIMABLE // �ɻ���
};


// һ���ߴ��������Ϊ�������ͣ����ƶ��������ƶ��Ϳɻ������ͣ�
struct free_area {
	ListHead<Page>* free_list[MIGRATE_TYPES]; // �洢��ͬ��С�ڴ��Ŀ�������
	unsigned long long nr_free; // ��ǰfreelist�Ŀ���ҳ������
};

// ͨ��zone�������ڴ棻
enum class ZONE_TYPE{
	ZONE_DMA, // DMAʹ�õ��ڴ�ռ䣻
	ZONE_NORMAL, // ������ʹ�õ��ڴ�ռ䣻
	ZONE_MOVABLE,
	ZONE_DEVICE, // ����Ĵ���ӳ�䵽�ڴ�������磺GPU�ȣ�
	MAX_ZONE_TYPE // ���ڶ���һ��pglist_data��zone�����С����ʾһ���ڵ��������ж��ٸ�ZONE��
};
// ÿһ��zone����һ���Լ��Ļ��ϵͳ�����Ƕ�Ӧ��free_area���飻
struct zone {
	pglist_data* zone_pgdata; // ��ǰzone���ڵ�node��pglist_data;
	int zone_start_pfn; // ��zone�������ʼҳ��ţ�
	ZONE_TYPE type;
	struct free_area free_area[MAX_FREE_AREA_SIZE];
};

#define MAX_NR_ZONES (int)ZONE_TYPE::MAX_ZONE_TYPE // һ���ڵ�����м���zones��
#define MAX_NUMANODES 8 // һ�����������Ľڵ������
#define MAX_ZONES_PER_ZONELIST MAX_NUMANODES * MAX_NR_ZONES // ��ʾ����node���ܵ����zone����

// ��numa�ܹ���ÿһ��cpu������Ϊһ��node�������������pglist_data�Ͷ�Ӧһ��node��
typedef struct pglist_data {
	struct zone node_zone[(int)ZONE_TYPE::MAX_ZONE_TYPE]; // ���ڵ�����zone���飻
	struct zone global_node_zone[MAX_ZONES_PER_ZONELIST];
	int nr_zones; // ��ǰ�ڵ�ӵ�е�zone������
	unsigned long long node_id;
	ListHead<zone>* zonelist; // �洢��ǰcpu��Ӧ������zone������
}pg_data_t;

// ��ʼ��һ��zone�Ļ��ϵͳ��
void init_zone_free_area() {

}

// ��ǰ������cpu����
#define NR_CPU 1
// ����ȫ�ֵ�pglist_data���洢��ÿһ��cpu��Ӧ��pglist_data�ṹ��
pg_data_t pglists[NR_CPU];

/*--------------------------page compact��Ƭ����-------------------------*/

// ��Ƭ����������Ĳ����ṹ�壻
struct compact_control {
	// �ڴӺ���ǰɨ��zoneʱ���洢����ҳ��
	ListHead<Page>* freepages;
	// �ڴ�ǰ���ɨ��zoneʱ���洢��Ǩ�Ƶ�movable/reclaimable/ҳ��
	ListHead<Page>* migratepages;
	// ����ҳ����
	unsigned long nr_free;
	// movableҳ����
	unsigned long nr_movable;
	// ��ǰɨ���zone;
	struct zone zone;
	// ��ǰ��Ҫ������ڴ��С��
	unsigned long order;
};

// ��һ��zoneִ����Ƭ����
void compact_page() {


}

// ��Ƭ���������
void __alloc_page_compact(int preferred_nid ,std::vector<int> nodemask) {
	compact_control cc={
		.nr_free=0,
		.nr_movable=0,
	}

	for (zone : zonelist) {
		// ��ÿ��zoneִ����Ƭ���������
		compact_page()��
	}
	
}


























/* --------------------------------------------------------------- */
// ������ʼ�����򣬵�������ļ���������
void setup_arch(char** cmdline_p) {
		// ���������ڴ�����
		e820_memory_setup();
		// memblock�ڴ��������ʼ��
		e820_memory_block_init();
}