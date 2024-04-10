#pragma once

#include"../shload.h"

//Args API
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == args$api) {
		_prtoutmsg("Args = " + args$api);
		return;
	}

	_prtoutmsg("Unknown Args :  " + args$api);
	return;
}

string path_select, outfile;

int wtoutf = 1;

string buildbdsproj(string dir) {
	//��Ŀ¼�������"\\*.*"���е�һ������
	string newDir = dir + "\\*.*";
	//���ڲ��ҵľ��
	intptr_t handle;
	struct _finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "���ļ�" << endl;
		return "ok";
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//���Ϊ�ļ��У������ļ���·�����ٴα���
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			newDir = dir + "\\" + fileinfo.name;
			buildbdsproj(newDir);//�ȱ���ɾ���ļ����µ��ļ�����ɾ���յ��ļ���
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			//cout << file_path.c_str() << endl;
			_fileapi_write(outfile,file_path);
			_prtoutmsg("_Find File :  " + file_path);
			wtoutf++;
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	return "ok";
}

//Put Code Here
int _HeadMainLoad() {
	_prtendl();
	_prtoutmsg("BDS Create Tools");
	_prtoutmsg("By FoxaXu        sign : " + to_string(aaa));
	_prtendl();
	_prtoutmsg("---------------------------------------------------");
	_prtoutmsg("Based on OpenCLT ...   " + $codename + "(" + $version_msg + ")  " + $version_code_str);
    _prtoutmsg("Copyright FoxaXu  " + $year_message);
	_prtoutmsg("---------------------------------------------------");

	_prts("Choose path to output  >");
	path_select = _getline_type();

	if (!_dapi_ExistFolder_check(path_select)) {
		_prtoutmsg("Failed. Access denied - Directory not exist");
		_pause();
		return 0;
	}

	_prts("Output file  >");
	outfile = _getline_type();

	_fileapi_del(outfile);

	_fileapi_createmark(outfile, "BDS CREATE TOOL    -Batch Download Script");
	_write_sipcfg(outfile, "TaskName", "BDS-Project");
	_write_sipcfg(outfile, "auther", "(- v -)");
	_write_sipcfg(outfile, "root", "(Write URL Here)");

	_write_sipcfg(outfile, "TotalSize", "-1");

	_write_sipcfg(outfile, "startdownload", "go");
	//Start output
	
	buildbdsproj(path_select);

	wtoutf--;
	_prtendl();
	_prtendl();
	_prtoutmsg("Compositing file..     Please wait");
	_write_sipcfg(outfile, "TotalSize", to_string(wtoutf));
	_prtendl();


	_prtendl();
	_prtendl();
	_prtendl();
	_prtoutmsg("One Step");
	_prtoutmsg("Now. You just need write your data . taskname auther.");
	_prtoutmsg("Before use. Please set root server on your file");
	_prtoutmsg("total find file :  " + to_string(wtoutf));
	_prtoutmsg("Press Enter to Exit");

	_pause();
	return 0;
}