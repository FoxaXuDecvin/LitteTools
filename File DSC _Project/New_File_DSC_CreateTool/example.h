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
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "无文件" << endl;
		return "ok";
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			buildbdsproj(newDir);//先遍历删除文件夹下的文件，再删除空的文件夹
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			Process_cache = file_path;
			Process_cache = ReplaceChar(Process_cache, path_select, "");
			//cout << file_path.c_str() << endl;
			_fileapi_write(outfile, ReplaceChar(Process_cache, "\\", "/"));
			_prtoutmsg("_添加文件 :  " + file_path);
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
	_prtoutmsg("BDS 配置文件创建工具");
	_prtoutmsg("---------------------------------------------------");
	_prtoutmsg("基于 OpenCLT ...   " + $codename + "(" + $version_msg + ")  " + $version_code_str);
	_prtoutmsg("Copyright FoxaXu  " + $year_message);
	_prtoutmsg("---------------------------------------------------");

	_prts("选择绑定的目录 / 或在此输入一个配置文件  >");
	path_select = _getline_type();
	if (check_file_existence(path_select)) {
		TaskName_ID = _load_sipcfg(path_select, "TaskName");
		Devlop_ID = _load_sipcfg(path_select, "Credits");
		Root_ID = _load_sipcfg(path_select, "root");

		_prts("已绑定配置文件 请选择绑定的目录  >");
		path_select = _getline_type();
		_pn();
	}
	else {
		_pn();
		_prts("给这个任务起一个名称  >");
		TaskName_ID = _getline_type();
		_pn();
		_prts("创建者名称  >");
		Devlop_ID = _getline_type();
		_pn();
		_prts("要绑定的服务器路径  >");
		Root_ID = _getline_type();
		_pn();
	}

	if (!_dapi_ExistFolder_check(path_select)) {
		_prtoutmsg("拒绝访问 - 请检查文件夹是否存在");
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
	_prtoutmsg("正在合成文件..     请稍等");
	_write_sipcfg(outfile, "TotalSize", to_string(wtoutf));
	_prtendl();


	_prtendl();
	_prtendl();
	_prtendl();
	_prtoutmsg("已完成包装");
	_prtoutmsg("你可以修改创建者信息，任务名称，服务器路径");
	_prtoutmsg("请不要在已经完成包装的配置文件里写入新的文件路径");
	_prtoutmsg("随意在完成包装的配置文件中写入数据可能会导致同步出错");
	_prtoutmsg("总文件量 :  " + to_string(wtoutf));
	_prtoutmsg("按Enter退出此工具");

	_pause();
	return 0;
}