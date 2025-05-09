#pragma once
#include"DataStruct.h"
#include<list>

// 总的地址空间为64位，所以用16位的16进制来表示；
#define STACK_START 0x7ff<<9 // 栈区空间的起始位置，也就是最高地址；
#define PAGE_SIZE 0x1<<12 // 4k

//enum class OPERATION {
//
//
//};

struct pgd; // 页表；


// 虚拟内存段；一个section；
struct vm_area_struct {
	unsigned long vm_start; // 低地址
	unsigned long vm_end; // 高地址；
	unsigned long used;
	// OPERATION type;


};

// 插入一个新的 vma 到 mm_struct 的rbtree和list；
void insert_vma(struct mm_struct* mm, struct vm_area_struct* vma) {
	mm->mmap.push_back(vma);
	mm->rb_tree.insert(vma->vm_start, vma);
	mm->map_count++;
}


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


