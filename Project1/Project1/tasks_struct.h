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
	// 进程状态；
	TASK_STRUCT_STATE task_state{TASK_STRUCT_STATE::NONE}; // 任务状态；

	// pid和pgid
	int pid, pgid;
	task_struct* group_leader;

	// 文件系统；
	//fs_struct fs; 

	// 文件描述符表；
	//file_struct f; 

	// 容器；
	//cgroup cg;

	// 命名空间；
	//namespace_struct sp;

	// 虚存；
	//mm_struct mm; 

	// 进程树：
	task_struct* parent;
	std::list<task_struct*> children, sibling;
	
	// 优先级：
	int dynamic_priority, static_priority, rt_priority, normal_priority;


};
