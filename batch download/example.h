#pragma once

#include"../shload.h"

bool allowLoad = false;
int argsSign = 1;
string DSh, DScript, DSPath;

//Create EmptyPath

bool cp_true = false;

bool creatpath(string fileaddress) {
	string tempdata, outdata;

	if (checkChar(fileaddress, "/")) cp_true = true;
	if (checkChar(fileaddress, "\\")) cp_true = true;

	if (cp_true == false) {
		return false;
	}

	fileaddress = ReplaceChar(fileaddress, "\\", "/");

	int numbuffer = fileaddress.size();
	int baseNum = -1;

	while (true) {
		tempdata = fileaddress[numbuffer];
		if (tempdata == "/") break;
		numbuffer--;
	}
	numbuffer--;
	while (baseNum != numbuffer) {
		baseNum++;
		outdata = outdata + fileaddress[baseNum];
	};

	if (checkChar(outdata, "/")) creatpath(outdata);
	_dapi_mkdir(outdata);
	return true;

}

//Args API
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (argsSign == 1) {
		argsSign++;
		if (args$api == "local") {
			DSh = "local";
			return;
		}
		if (args$api == "url") {
			DSh = "url";
			return;
		}

		_prtoutmsg("Unknown Work status :  " + args$api);
		argsSetExit = true;
		return;
	}
	if (argsSign == 2) {
		argsSign++;
		if (DSh == "url") {
			DScript = args$api;
			return;
		}
		if (!check_file_existence(args$api)) {
			_prtoutmsg("BDS Script Not Found :  " + args$api);
			argsSetExit = true;
			return;
		}
		DScript = args$api;
		return;
	}
	if (argsSign == 3) {
		argsSign++;
		DSPath = args$api;
		return;
	}

	_prtoutmsg("Unknown Args :  " + args$api);
	return;
}

string taskname, auther, totalsize;

int totalsize_i;

string bds_rootsrv;

string did_str;

string dlbuffer;

int bds_total_succ, bds_total_fail,bds_startDown;

string url_bds;

//Put Code Here
int _HeadMainLoad() {
	url_bds = _get_random_s(1,1000000) + "~temp.bds";
	if (argsSign == 4) {
		_prtoutmsg("Start Batch Download");
		_prtoutmsg("Script :  " + DScript);
		_prtoutmsg("SavePath :  " + DSPath);
		_prtendl();
		_prtoutmsg("Reading File Message...        Please wait");

		//Load Script Data;
		if (DSh == "url") {
			if (!_urldown_api_nocache(DScript,url_bds)) {
				_prtoutmsg("Failed get script from :   " + DScript);
				return 0;
			}
			DScript = url_bds;
		}
		
		taskname = _load_sipcfg(DScript, "TaskName");
		auther = _load_sipcfg(DScript, "auther");
		totalsize = _load_sipcfg(DScript, "TotalSize");

		bds_rootsrv = _load_sipcfg(DScript, "root");

		totalsize_i = atoi(totalsize.c_str());

		//Output
		_prtendl();

		_prtoutmsg("taskid :       " + taskname);
		_prtoutmsg("auther :      " + auther);
		_prtoutmsg("Total File :  " + totalsize);

		_prtendl();
		_prtendl();
		_prtoutmsg("Start Download File");
		_prtendl();

		bds_total_fail = bds_total_succ = 0;

		bds_startDown = FindCharLine(1, DScript, "$startdownload=go;");

		for (int downid = 1; true; downid++) {
			if (downid > totalsize_i)break;
			bds_startDown++;
			did_str = to_string(downid);

			dlbuffer = _fileapi_textread(DScript, bds_startDown);

			if (dlbuffer == "overline")break;

			_prtoutmsg("_downloading  [" + did_str + "/" + totalsize + "] URL :  " + bds_rootsrv + dlbuffer);
			creatpath(DSPath + "/" + dlbuffer);
			if (check_file_existence(DSPath + "/" + dlbuffer))continue;
			if (!_urldown_api_nocache(bds_rootsrv + dlbuffer, DSPath + "/" + dlbuffer)) {
				_prtoutmsg("Failed Download  =  [" + did_str + " / " + totalsize + "] URL :  " + bds_rootsrv + dlbuffer);
				bds_total_fail++;
				continue;
			}

			bds_total_succ++;
			continue;
		}

		_prtendl();
		_prtendl();
		_prtoutmsg("Complete Download");
		_prtoutmsg("Total " + totalsize);
		_prtoutmsg("Download -  Succeed :  " + to_string(bds_total_succ) + "  Failed :  " + to_string(bds_total_fail));
		_prtoutmsg("process exit");
		_fileapi_del(url_bds);
		return 0;
	}
	else {
		_prtendl();
		_prtoutmsg("Batch Download Script");
		_prtoutmsg("By FoxaXu        sign : " + to_string(aaa));
		_prtendl();
		_prtoutmsg("---------------------------------------------------");
		_prtoutmsg("Based on OpenCLT ...   " + $codename + "(" + $version_msg + ")  " + $version_code_str);
		_prtoutmsg("Copyright FoxaXu  " + $year_message);
		_prtoutmsg("Command : ");
		_prtoutmsg("                        [BDS] <local/url> <%rollscript%> <path> ");
		_prtoutmsg("Example : ");
		_prtoutmsg("                        [BDS] local \"autodown.bds\" D:\\Example");
		_prtoutmsg("                        [BDS] url \"https://www.foxaxu.com/example.bds\" D:\\Example");
		_prtoutmsg("---------------------------------------------------");
		_prtoutmsg($version_msg);
		_pause();
		return 0;
	}
}