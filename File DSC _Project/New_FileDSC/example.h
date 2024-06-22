#pragma once

#include"../shload.h"
#include"../Code/_sdk_URLCodec.h"

//Create EmptyPath
// -4 == Not Found
int FindCharLineA(int startline, string file, string charData) {
	//cout << "GoRoll. in " << startline << endl;
	while (true) {
		//cout << "A" << endl;
		readbufferA = LineReader_noerror(file, startline);
		//cout << "B" << endl;
		readbufferA = HeadSpaceCleanA(readbufferA);
		//cout << "Roll :  " << startline << "  INFO :  " << readbufferA << endl;
		if (readbufferA == "overline") {
			return -4;
		}
		if (readbufferA == "LineError") {
			return -4;
		}
		if (readbufferA == "FileNotExist") {
			//cout << "File NULL" << endl;
			return -4;
		}

		if (readbufferA == charData) {
			//cout << "EndRoll :  " << startline << endl;
			return startline;
		}
		startline++;
	}
}

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

bool PreLaunchLoad(void) {
	//Put Preload code here
	//
	__settings_displaylaunchscreen = false;

	//End
	return true;
}

bool useDebug = true;
bool NoErrorType = false;
//Args API
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == "-sync") {
		_sync_mode = true;
		return;
	}
	if (args$api == "-nodebug") {
		useDebug = false;
		return;
	}
	if (args$api == "-noerror") {
		NoErrorType = true;
		__settings_throwErrorMode = false;
		return;
	}


	if (argsSign == 1) {
		argsSign++;
		if (args$api == "-local") {
			DSh = "local";
			return;
		}
		if (args$api == "-url") {
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


//Put Code Here
int _HeadMainLoad() {
	url_bds = "LatestSync.bds";
	if (argsSign == 4) {
		_pn();
		_prtoutmsg("File Download and Sync (��Batch Download��Ŀ�޸�����)");
		_prtoutmsg("��Ҫͬ���������ļ� :  " + DScript);
		_prtoutmsg("��Ҫͬ����Ŀ¼ :  " + DSPath);
		_prtendl();
		_prtoutmsg("���ڻ�ȡͬ����Ϣ...        ���Ե�");

		//Load Script Data;
		if (check_file_existence("outdate_bdsfile.txt")) {
			if (check_file_existence(url_bds)) {
				_fileapi_del("outdate_bdsfile.txt");
			}
		}
		if (DSh == "url") {
			if (check_file_existence(url_bds)) {
				_fileapi_CpFile(url_bds, "outdate_bdsfile.txt");
			}
			if (!_urldown_api_nocache(DScript, url_bds)) {
				_prtoutmsg("�޷���������ַ��ȡ���������ļ� :   " + DScript);
				return 0;
			}
			DScript = url_bds;
		}
		if (check_file_existence("Modify.log")) {
			_fileapi_del("Modify.log");
		}
		_soildwrite_open("Modify.log");

		if (_sync_mode == true) {
			if (!check_file_existence("outdate_bdsfile.txt")) {
				_p("�ڵ�ǰĿ¼����δ�ҵ�ĩ��ͬ����Ϣ��������ǳ���ͬ�������������Ϣ���벻Ҫ����ɾ���κ�Ŀ¼�µ� bds�ļ�");
				goto SkipCheckDelete;
			}
			_pn();
			_p("���ڲ�����Ҫ��ɾ�����ļ�");
			pitA = FindCharLine(1, DScript, "$startdownload=go;");
			pitB = FindCharLine(1, "outdate_bdsfile.txt", "$startdownload=go;");

			_soildwrite_write("�ѱ�ɾ�����ļ�");
			while (true) {
				if (useDebug == true) {
					_p("���������� " + to_string(pitB) + " ���ļ�");
				}
				tempcacheN = LineReader("outdate_bdsfile.txt", pitB);
				if (tempcacheN == "overline") {
					break;
				}
				if (tempcacheN == "ReadFailed") {
					_p("�ļ��𻵣��޷��ж��ļ��޸����");
					break;
				}
				if (FindCharLineA(pitA, DScript, tempcacheN) == -4) {
					_fileapi_del(DSPath + "/" + tempcacheN);
					_soildwrite_write("��ɾ�� :  " + tempcacheN);
					_p("���ڴ��� :  " + tempcacheN);
					pitB++;
				}
				else {
					pitA++;
					pitB++;
				}
				
			}
			_p("����ͬ���µ��ļ�");
			_fileapi_del("outdate_bdsfile.txt");
		}

		SkipCheckDelete:

		taskname = _load_sipcfg(DScript, "TaskName");
		Devlop = _load_sipcfg(DScript, "Credits");
		totalsize = _load_sipcfg(DScript, "TotalSize");

		bds_rootsrv = _load_sipcfg(DScript, "root");

		totalsize_i = atoi(totalsize.c_str());

		if (totalsize_i == -1) {
			totalsize_i = INT_MAX;
		}

		//Output
		_prtendl();

		_prtoutmsg("�������� :   " + taskname);
		_prtoutmsg("�����ļ������� :   " + Devlop);
		_prtoutmsg("���ļ����� :   " + totalsize);

		_prtendl();
		_prtendl();
		_prtoutmsg("��ʼ�����ļ�");
		_prtendl();

		bds_total_fail = bds_total_succ = bds_total_skip = 0;

		bds_startDown = FindCharLine(1, DScript, "$startdownload=go;");

		_soildwrite_write("");
		_soildwrite_write("��ȡ�������ļ�");
		
		_fileapi_createmark("Fail.log", "��ȡʧ�ܵ��ļ�");

		for (int downid = 1; true; downid++) {
			if (downid > totalsize_i)break;
			bds_startDown++;
			did_str = to_string(downid);

			dlbuffer = _fileapi_textread(DScript, bds_startDown);

			if (dlbuffer == "overline")break;

			craftURL = bds_rootsrv + dlbuffer;
			craftURL = UTF8Url::Encode(craftURL);
			craftAddres = DSPath + "/" + dlbuffer;

			creatpath(craftAddres);
			if (check_file_existence(craftAddres)) {
				if (useDebug == true) {
					_prtoutmsg("_����(�Ѵ���)  [��" + did_str + "���ļ�/�ܹ�" + totalsize + "���ļ�] URL��ַ :  " + craftURL);
				}
				bds_total_skip++;
				continue;
			}			
			else {
				_prtoutmsg("_��������  [��" + did_str + "���ļ�/�ܹ�" + totalsize + "���ļ�] URL��ַ :  " + craftURL);
			}
			if (!_urldown_api_vc_nocache(craftURL, craftAddres)) {
				if (NoErrorType == false) {
					_prtoutmsg("�޷��������  =  [��" + did_str + "���ļ� / �ܹ�" + totalsize + "���ļ�] URL��ַ :  " + craftURL);
				}
				_fileapi_write("Fail.log", craftURL);
				bds_total_fail++;
				continue;
			}
			_soildwrite_write(craftURL);

			bds_total_succ++;
			continue;
		}

		_soildwrite_close();

		_prtendl();
		_prtendl();
		_prtoutmsg("�ɹ������������");
		_prtoutmsg("�ܹ� " + totalsize+"���ļ�");
		_prtoutmsg("��ϸ��Ϣ -  ���سɹ����� :  " + to_string(bds_total_succ) + "  ����ʧ������ :  " + to_string(bds_total_fail) + "  �������ļ����� :  " + to_string(bds_total_skip));
		_prtoutmsg("�����˳�");
		_pause();
		_str_system("start Modify.log");
		return 0;
	}
	else {
		_prtendl();
		_prtoutmsg("File Download and Sync");
		_prtendl();
		_prtoutmsg("---------------------------------------------------");
		_p("����Ŀ����Batch Download �޸Ķ���");
		_prtoutmsg("Based on OpenCLT ...   " + $codename + "(" + $version_msg + ")  " + $version_code_str);
		_prtoutmsg("Copyright FoxaXu  " + $year_message);
		_prtoutmsg("Command : ");
		_prtoutmsg("                        [BDS] <-local/-url> <%rollscript%> <path> </-sync> </-nodebug>");
		_prtoutmsg("Example : ");
		_prtoutmsg("                        [BDS] -local \"autodown.bds\" D:\\Example");
		_prtoutmsg("                        [BDS] -url \"https://www.foxaxu.com/example.bds\" D:\\Example");
		_prtoutmsg("                        [BDS] -url \"https://www.foxaxu.com/example.bds\" D:\\Example -sync");
		_prtoutmsg("                        [BDS] -url \"https://www.foxaxu.com/example.bds\" D:\\Example -sync -nodebug");
		_prtoutmsg("---------------------------------------------------");
		_prtoutmsg($version_msg);
		_pause();
		return 0;
	}
}