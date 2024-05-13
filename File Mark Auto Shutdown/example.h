#pragma once

#include"../shload.h"
#include<ShlObj.h>

//Args API
string buffer;
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	argsSetExit = true;
	if (args$api == "-install") {
		if (IsUserAnAdmin()) {
			buffer = "reg add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"FileMarkAutoShutdown_AutoRun\" /t REG_SZ /d \"" + _$GetSelfFull + "\"";
			_str_system(buffer);
			//_fileapi_createmark("temp~command.txt", buffer);
			MessageBox(0, "Software is register .Complete", "FMAS Notification", MB_OK);
			return;
		}
		else {
			MessageBox(0, "Please Runas Administrator", "FMAS Notification", MB_OK);
			return;
		}
		
		return;
	}
	if (args$api == "-uninstall") {
		if (IsUserAnAdmin()) {
			buffer = "reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v \"FileMarkAutoShutdown_AutoRun\" /f";
			_str_system(buffer);
			//_fileapi_createmark("temp~command.txt", buffer);
			MessageBox(0, "Software is unregister .Complete", "FMAS Notification", MB_OK);
			return;
		}
		else {
			MessageBox(0, "Please Runas Administrator", "FMAS Notification", MB_OK);
			return;
		}

		return;
	}

	_prtoutmsg("Unknown Args :  " + args$api);
	return;
}

const string runprofile = _$GetSelfPath + "/FMAS_config.cfg";
string monfile, checktime_str,syscmd_str;
int checktime;
//Put Code Here
int _HeadMainLoad() {
	//main
	if (!check_file_existence(runprofile)) {
		_soildwrite_open(runprofile);
		_soildwrite_write("//File Mark Auto Shutdown_For Server (Configuration File)");
		_soildwrite_write("$MonitorFile={Null};");
		_soildwrite_write("$CheckExistenceFreq=10;");
		_soildwrite_write("$SystemCommand=shutdown -s -t 0;");
		_soildwrite_close();
	}

	monfile = _load_sipcfg(runprofile, "MonitorFile");
	checktime_str = _load_sipcfg(runprofile, "CheckExistenceFreq");
	syscmd_str = _load_sipcfg(runprofile, "SystemCommand");

	checktime = atoi(checktime_str.c_str());

	if (monfile == "{Null}") {
		MessageBox(0, "Monitor File is not set", "FMAS Notification", MB_OK);
		return 0;
	}

	while (true) {
		sleepapi(checktime);
		if (check_file_existence(monfile)) {
			_fileapi_del(monfile);
			_str_system(syscmd_str);
			return 0;
		}
	}

	return 0;
}