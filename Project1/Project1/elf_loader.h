#pragma once
#include<iostream>
#include "memory.h"
#include "file_description.h"

struct binary_prm {
	struct file_header; // 可执行文件头，包括如：elf等，后续通过该参数调用对应的加载器；
	struct program_header_table; // 可执行文件的segment table；
	struct sction_header_table;	 // 可执行文件的section table；
	std::string path; // 文件路径；
	std::string env; // 环境变量；
	mm_struct* mm; // mm；
	unsigned long mm_stack; // mm_struct的栈区最高地址；
	int arg_count;
	const char* arg[]; // 启动参数；
};

// 为binary_prm初始化一个mm_struct对象，一般会在exec函数中执行；
// 在初始化的时候只会分配一个vma对象，就是1页4k栈空间；
void binary_prm_mm_init(mm_struct* mm) {
	vm_area_struct* vma = new vm_area_struct{ STACK_START - PAGE_SIZE, STACK_START, 0 };
	mm->stack_start = vma->vm_start;
	mm->stack_end = vma->vm_end;
	insert_vma(mm, vma);
	mm->map_count = 1;
}


// 初始化一个binary_prm对象，并且申请一个新的虚拟内存空间留给新的进程使用；
struct binary_prm* alloc_binary_prm(){
	binary_prm* bprm = new binary_prm;
	mm_struct* mm = new mm_struct;
	binary_prm_mm_init(mm);
	bprm->mm = mm;
	bprm->mm_stack = mm->stack_end;
}

// 初始化binary_prm对象之后，需要查看文件头的信息，从而判断二进制文件的类型，从而调用对应的加载器
void load_file_header(struct binary_prm* bprm) {
	bprm->file_header
}


// elf加载器实例的函数
void elf_load_binary(struct binary_prm* ) {
	// 1.先读文件头，读到一个buf里；
	// 2.再读program header table
	// 3.释放原来进程的mm_struct
	// 4.重新设置mm_struct为binprm里的mm_struct，并加载可执行文件的load segment；
	// 5.分配数据段和brk的虚拟地址空间；
	// 6.加载动态库，进入libc_start_main函数；
}

void elf_load_shlib(struct file*) {

}

void elf_load_coredump(struct coredump_prm*) {
	
}

// 加载器类；
struct bin_loader {
	void(*load_binary)(struct binary_prm*);
	void(*load_shlib)(struct file*);
	void(*load_coredump)(struct coredump_prm*);
};


// 注册elf加载器对象；
struct bin_loader elf_bin_loader {
	.load_binary = elf_load_binary,
	.load_shlib = elf_load_shlib,
	.load_coredump = elf_load_coredump
};

// 执行进程函数，该函数会调用elf加载器的加载二进制文件的回调函数来载入进程；
void exec(std::string path, const char* arg[], int arg_count, std::string env) {
	struct binary_prm* bprm = alloc_binary_prm();
	bprm->path = path;
	bprm->env = env;
	bprm->arg_count = arg_count;

}


