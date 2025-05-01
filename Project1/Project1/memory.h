#pragma once
#include"DataStruct.h"
#include<list>

enum class OPERATION {


};

struct pgd; // ҳ��


// �����ڴ�Σ�
struct vm_area_struct {
	unsigned long vm_start;
	unsigned long used;
	OPERATION type;


};




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


