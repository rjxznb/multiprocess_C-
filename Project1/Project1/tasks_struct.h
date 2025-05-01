#pragma once
#include<list>

enum class TASK_STRUCT_STATE {
	NONE,
	TASK_STRUCT_STATE_SLEEP,
	TASK_STRUCT_STATE_INTERRUPT,
	TASK_STRUCT_STATE_UNINTERRUPT,
	TASK_STRUCT_STATE_RUNNING,
	TASK_STRUCT_STATE_DEAD,
	TASK_STRUCT_STATE_ZOMBIE,
};

struct cgroup;
struct fs_struct;
struct file_struct;
struct namespace_struct;
struct mm_struct;


struct task_struct {
	// ����״̬��
	TASK_STRUCT_STATE task_state{TASK_STRUCT_STATE::NONE}; // ����״̬��

	// pid��pgid
	int pid, pgid;
	task_struct* group_leader;

	// �ļ�ϵͳ��
	//fs_struct fs; 

	// �ļ���������
	//file_struct f; 

	// ������
	//cgroup cg;

	// �����ռ䣻
	//namespace_struct sp;

	// ��棻
	//mm_struct mm; 

	// ��������
	task_struct* parent;
	std::list<task_struct*> children, sibling;
	
	// ���ȼ���
	int dynamic_priority, static_priority, rt_priority, normal_priority;


};
