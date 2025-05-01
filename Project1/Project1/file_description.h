#pragma once
#include<string>

// struct file 严格来讲，这个结构体不仅仅和文件系统相关，它也和进程相关联。对于虚拟文件系统而言，它的重要性一般，
// 而相反，这个结构体对进程管理更重要，它记录了进程打开文件的上下文。
struct file {
	unsigned long long size;
	std::string path;
	int fd;
	int f_count; // 引用计数；

};

struct file_table {
	file** f;

};


struct files_struct {
	file_table* ft;
	int next_fd;


};