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
	int owner; // �������ļ����û���
	std::string path; // ��ǰ�ļ���·��
	dentry d;


};
