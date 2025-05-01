#pragma once
#include"DataStruct.h"
#include<list>

enum class OPERATION {


};

struct pgd; // 页表；


// 虚拟内存段；
struct vm_area_struct {
	unsigned long vm_start;
	unsigned long used;
	OPERATION type;


};




// ul类型是随机器不同而不同，32位os为32位，64位为64位，
// 刚好符合虚拟地址空间的大小，所以用该类型来作为地址表示；
struct mm_struct {
	unsigned long task_size; // 任务所用虚拟空间的总大小；
	unsigned long mmap_base; // 共享内存映射的起始地址，和栈一样，扩充的方向都是从高地址向低地址；
	unsigned long brk_start, brk_end;
	unsigned long stack_start, stack_end;
	unsigned long data_start, data_end;


	RedBlackTree<int, vm_area_struct*> rb_tree; // vm_area_struct红黑树；key存的是vm_start，val存的是vm_area_struct；
	list<vm_area_struct*> mmap; // vm_area_struct链表；
	vm_area_struct* cache_vm_area; // 当前进程刚刚访问的虚拟地址段；
	int map_count; // vm_area_struct的数量；

	pgd* page_table;

};


