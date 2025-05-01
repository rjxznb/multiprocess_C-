#pragma once
#include<string>
#include<thread>
#include<list>

struct inode {


};


struct dentry {
	std::string name;
	std::chrono::time_point create_time;
	dentry* parent;
	std::list<dentry*> children;


};


struct fs_struct {
	int owner; // 创建该文件的用户；
	std::string path; // 当前文件的路径
	dentry d;


};
