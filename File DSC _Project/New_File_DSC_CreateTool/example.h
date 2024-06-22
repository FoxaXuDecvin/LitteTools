#pragma once

#include"../shload.h"

bool PreLaunchLoad(void) {
	//Put Preload code here
	//

	__settings_displaylaunchscreen = false;

	//End
	return true;
}

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
			Process_cache = file_path;
			Process_cache = ReplaceChar(Process_cache, path_select, "");
			//cout << file_path.c_str() << endl;
			_fileapi_write(outfile, ReplaceChar(Process_cache, "\\", "/"));
			_prtoutmsg("_����ļ� :  " + file_path);
			wtoutf++;
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	return "ok";
}

//Put Code Here
int _HeadMainLoad() {
	//main
	_prtendl();
	_prtoutmsg("BDS �����ļ���������");
	_prtoutmsg("---------------------------------------------------");
	_prtoutmsg("���� OpenCLT ...   " + $codename + "(" + $version_msg + ")  " + $version_code_str);
	_prtoutmsg("Copyright FoxaXu  " + $year_message);
	_prtoutmsg("---------------------------------------------------");

	_prts("ѡ��󶨵�Ŀ¼ / ���ڴ�����һ�������ļ�  >");
	path_select = _getline_type();
	if (check_file_existence(path_select)) {
		TaskName_ID = _load_sipcfg(path_select, "TaskName");
		Devlop_ID = _load_sipcfg(path_select, "Credits");
		Root_ID = _load_sipcfg(path_select, "root");

		_prts("�Ѱ������ļ� ��ѡ��󶨵�Ŀ¼  >");
		path_select = _getline_type();
		_pn();
	}
	else {
		_pn();
		_prts("�����������һ������  >");
		TaskName_ID = _getline_type();
		_pn();
		_prts("����������  >");
		Devlop_ID = _getline_type();
		_pn();
		_prts("Ҫ�󶨵ķ�����·��  >");
		Root_ID = _getline_type();
		_pn();
	}

	if (!_dapi_ExistFolder_check(path_select)) {
		_prtoutmsg("�ܾ����� - �����ļ����Ƿ����");
		_pause();
		return 0;
	}

	_prts("Output file  >");
	outfile = _getline_type();

	_fileapi_del(outfile);

	_fileapi_createmark(outfile, "BDS CREATE TOOL    -Batch Download Script");
	_write_sipcfg(outfile, "TaskName", TaskName_ID);
	_write_sipcfg(outfile, "Credits", Devlop_ID);
	_write_sipcfg(outfile, "root", Root_ID);

	_write_sipcfg(outfile, "TotalSize", "-1");

	_write_sipcfg(outfile, "startdownload", "go");
	//Start output

	buildbdsproj(path_select);

	wtoutf--;
	_prtendl();
	_prtendl();
	_prtoutmsg("���ںϳ��ļ�..     ���Ե�");
	_write_sipcfg(outfile, "TotalSize", to_string(wtoutf));
	_prtendl();


	_prtendl();
	_prtendl();
	_prtendl();
	_prtoutmsg("����ɰ�װ");
	_prtoutmsg("������޸Ĵ�������Ϣ���������ƣ�������·��");
	_prtoutmsg("�벻Ҫ���Ѿ���ɰ�װ�������ļ���д���µ��ļ�·��");
	_prtoutmsg("��������ɰ�װ�������ļ���д�����ݿ��ܻᵼ��ͬ������");
	_prtoutmsg("���ļ��� :  " + to_string(wtoutf));
	_prtoutmsg("��Enter�˳��˹���");

	_pause();
	return 0;
}