#pragma once
#include"DataStruct.h"
#include<list>

// �ܵĵ�ַ�ռ�Ϊ64λ��������16λ��16��������ʾ��
#define STACK_START 0x7ff<<9 // ջ���ռ����ʼλ�ã�Ҳ������ߵ�ַ��
#define PAGE_SIZE 0x1<<12 // 4k

//enum class OPERATION {
//
//
//};

struct pgd; // ҳ��


// �����ڴ�Σ�һ��section��
struct vm_area_struct {
	unsigned long vm_start; // �͵�ַ
	unsigned long vm_end; // �ߵ�ַ��
	unsigned long used;
	// OPERATION type;


};

// ����һ���µ� vma �� mm_struct ��rbtree��list��
void insert_vma(struct mm_struct* mm, struct vm_area_struct* vma) {
	mm->mmap.push_back(vma);
	mm->rb_tree.insert(vma->vm_start, vma);
	mm->map_count++;
}


// ul�������������ͬ����ͬ��32λosΪ32λ��64λΪ64λ��
// �պ÷��������ַ�ռ�Ĵ�С�������ø���������Ϊ��ַ��ʾ��
struct mm_struct {
	unsigned long task_size; // ������������ռ���ܴ�С��
	unsigned long mmap_base; // �����ڴ�ӳ�����ʼ��ַ����ջһ��������ķ����ǴӸߵ�ַ��͵�ַ��
	unsigned long brk_start, brk_end;
	unsigned long stack_start, stack_end;
	unsigned long data_start, data_end;

	RedBlackTree<int, vm_area_struct*> rb_tree; // vm_area_struct�������key�����vm_start��val�����vm_area_struct��
	list<vm_area_struct*> mmap; // vm_area_struct����
	vm_area_struct* cache_vm_area; // ��ǰ���̸ոշ��ʵ������ַ�Σ�
	int map_count; // vm_area_struct��������

	pgd* page_table;
};


