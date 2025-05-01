#pragma once
#include<string>

// struct file �ϸ�����������ṹ�岻�������ļ�ϵͳ��أ���Ҳ�ͽ�������������������ļ�ϵͳ���ԣ�������Ҫ��һ�㣬
// ���෴������ṹ��Խ��̹������Ҫ������¼�˽��̴��ļ��������ġ�
struct file {
	unsigned long long size;
	std::string path;
	int fd;
	int f_count; // ���ü�����

};

struct file_table {
	file** f;

};


struct files_struct {
	file_table* ft;
	int next_fd;


};