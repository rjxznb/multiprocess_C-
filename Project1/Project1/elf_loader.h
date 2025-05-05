#pragma once
#include<iostream>
#include "memory.h"
#include "file_description.h"

struct binary_prm {
	struct file_header; // ��ִ���ļ�ͷ�������磺elf�ȣ�����ͨ���ò������ö�Ӧ�ļ�������
	struct program_header_table; // ��ִ���ļ���segment table��
	struct sction_header_table;	 // ��ִ���ļ���section table��
	std::string path; // �ļ�·����
	std::string env; // ����������
	mm_struct* mm; // mm��
	unsigned long mm_stack; // mm_struct��ջ����ߵ�ַ��
	int arg_count;
	const char* arg[]; // ����������
};

// Ϊbinary_prm��ʼ��һ��mm_struct����һ�����exec������ִ�У�
// �ڳ�ʼ����ʱ��ֻ�����һ��vma���󣬾���1ҳ4kջ�ռ䣻
void binary_prm_mm_init(mm_struct* mm) {
	vm_area_struct* vma = new vm_area_struct{ STACK_START - PAGE_SIZE, STACK_START, 0 };
	mm->stack_start = vma->vm_start;
	mm->stack_end = vma->vm_end;
	insert_vma(mm, vma);
	mm->map_count = 1;
}


// ��ʼ��һ��binary_prm���󣬲�������һ���µ������ڴ�ռ������µĽ���ʹ�ã�
struct binary_prm* alloc_binary_prm(){
	binary_prm* bprm = new binary_prm;
	mm_struct* mm = new mm_struct;
	binary_prm_mm_init(mm);
	bprm->mm = mm;
	bprm->mm_stack = mm->stack_end;
}

// ��ʼ��binary_prm����֮����Ҫ�鿴�ļ�ͷ����Ϣ���Ӷ��ж϶������ļ������ͣ��Ӷ����ö�Ӧ�ļ�����
void load_file_header(struct binary_prm* bprm) {
	bprm->file_header
}


// elf������ʵ���ĺ���
void elf_load_binary(struct binary_prm* ) {
	// 1.�ȶ��ļ�ͷ������һ��buf�
	// 2.�ٶ�program header table
	// 3.�ͷ�ԭ�����̵�mm_struct
	// 4.��������mm_structΪbinprm���mm_struct�������ؿ�ִ���ļ���load segment��
	// 5.�������ݶκ�brk�������ַ�ռ䣻
	// 6.���ض�̬�⣬����libc_start_main������
}

void elf_load_shlib(struct file*) {

}

void elf_load_coredump(struct coredump_prm*) {
	
}

// �������ࣻ
struct bin_loader {
	void(*load_binary)(struct binary_prm*);
	void(*load_shlib)(struct file*);
	void(*load_coredump)(struct coredump_prm*);
};


// ע��elf����������
struct bin_loader elf_bin_loader {
	.load_binary = elf_load_binary,
	.load_shlib = elf_load_shlib,
	.load_coredump = elf_load_coredump
};

// ִ�н��̺������ú��������elf�������ļ��ض������ļ��Ļص�������������̣�
void exec(std::string path, const char* arg[], int arg_count, std::string env) {
	struct binary_prm* bprm = alloc_binary_prm();
	bprm->path = path;
	bprm->env = env;
	bprm->arg_count = arg_count;

}


