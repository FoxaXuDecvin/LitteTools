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

string casename;
int lv_s, lv_a, lv_b, lv_c, lv_d, lv_e, lv_f;
int sgAN, sgBN, sgCN;
int cs_randseed;
string userloadprofile;

string opcs;

int openapi_abr;
string openapi_abr_full;
string openapi_abr_tag;
int openapi_st, openapi_st_g;
string openapi_gwname;
int openapi_skinborad;
string openapi_gtLv;

string cweap;

int wpls_max;
int wpls_rg;
string wpls_rgname;
string statTrackID;

bool fastopen = false;

void ColorRefresh() {
	if (openapi_gtLv == "s") {
		system("color 67");
	}
	if (openapi_gtLv == "a") {
		system("color 47");
	}
	if (openapi_gtLv == "b") {
		system("color c7");
	}
	if (openapi_gtLv == "c") {
		system("color d7");
	}
	if (openapi_gtLv == "d") {
		system("color 17");
	}
	if (openapi_gtLv == "e") {
		system("color 97");
	}
	if (openapi_gtLv == "f") {
		system("color f0");
	}
	return;
}

string GetWeaponRand(string gt_level) {
	openapi_gtLv = gt_level;
	wpls_max = atoi(_load_sipcfg(userloadprofile, "wp_" + gt_level + "_max").c_str());

	wpls_rg = _get_random(1, wpls_max);

	openapi_gwname = wpls_rgname = _load_sipcfg(userloadprofile, "wp_" + gt_level + "_" + to_string(wpls_rg));

	openapi_st_g = atoi(_load_sipcfg(userloadprofile, "wp_" + gt_level + "_" + to_string(wpls_rg) + "_st").c_str());

	openapi_skinborad = _get_random(1, 1000);

	if (openapi_st_g == 1) {
		if (_get_random(1, 10) == 1) {
			openapi_st = 1;
		}
		else {
			openapi_st = 0;
		}
	}
	else {
		if (openapi_st_g == 2) {
			openapi_st = 2;
		}
		else {
			openapi_st = 0;
		}
	}

	openapi_abr = _get_random(atoi(_load_sipcfg(userloadprofile, "wp_" + gt_level + "_" + to_string(wpls_rg) + "_abr_min").c_str()),
		atoi(_load_sipcfg(userloadprofile, "wp_" + gt_level + "_" + to_string(wpls_rg) + "_abr_max").c_str()));

	openapi_abr_tag = "ո�³��� ";

	if (openapi_abr > 699999) {
		openapi_abr_tag = "����ĥ�� ";
	}

	if (openapi_abr > 1499999) {
		openapi_abr_tag = "�þ�ɳ�� ";
	}

	if (openapi_abr > 3799999) {
		openapi_abr_tag = "���𲻿� ";
	}

	if (openapi_abr > 4499999) {
		openapi_abr_tag = "ս������ ";
	}

	openapi_abr = openapi_abr + 100000000;

	openapi_abr_full = to_string(openapi_abr);

	openapi_abr_full[0] = '0';
	openapi_abr_full[1] = '.';

	if (gt_level == "s") {
		wpls_rgname = " ?????????????????";
	}

	if (openapi_st == 1) {
		return wpls_rgname + "   [StatTrack]";
	}
	else {
		if (openapi_st == 2) {
			return wpls_rgname + "   [����Ʒ]";
		}
		else {
			return wpls_rgname;
		}
	}

		return "Error";
}

void randGetWeapList() {
	cs_randseed = _get_random(1, 100000);

	ColorRefresh();

	if (lv_s >= cs_randseed) {
		_prtoutmsg("[���亱��]" + GetWeaponRand("s"));
		return;
	}

	if (lv_a >= cs_randseed) {
		_prtoutmsg("[����]" + GetWeaponRand("a"));
		return;
	}

	if (lv_b >= cs_randseed) {
		_prtoutmsg("[����]" + GetWeaponRand("b"));
		return;
	}

	if (lv_c >= cs_randseed) {
		_prtoutmsg("[����]" + GetWeaponRand("c"));
		return;
	}

	if (lv_d >= cs_randseed) {
		_prtoutmsg("[����]" + GetWeaponRand("d"));
		return;
	}

	if (lv_e >= cs_randseed) {
		_prtoutmsg("[��ҵ]" + GetWeaponRand("e"));
		return;
	}

	if (lv_f >= cs_randseed) {
		_prtoutmsg("[����]" + GetWeaponRand("f"));
		return;
	}

	return;
}

//Put Code Here
int _HeadMainLoad() {
ReturnMainUI:
	opcs = "";
	cleanConsole();
	SetConsoleTitle("CS Case Simulator");
	_prtoutmsg("����λ�� AllCase ����������ļ�.");
	_prtoutmsg("���� RecoilCase.txt");
	_prtendl();
	cout << "open case file  >";
	getline(cin, userloadprofile);

	userloadprofile = _$GetSelfPath + "/AllCase/" + userloadprofile;

	if (!check_file_existenceA(userloadprofile)) {
		_prtoutmsg("δ�ҵ��ҵ� :  " + userloadprofile);
		_pause();
		goto ReturnMainUI;
	}

	_prtoutmsg("���ڼ���  " + userloadprofile);

	casename = _load_sipcfg(userloadprofile, "CaseName");

	//Load Case Data
	lv_s = atoi(_load_sipcfg(userloadprofile, "Level_S").c_str());
	lv_a = atoi(_load_sipcfg(userloadprofile, "Level_A").c_str());
	lv_b = atoi(_load_sipcfg(userloadprofile, "Level_B").c_str());
	lv_c = atoi(_load_sipcfg(userloadprofile, "Level_C").c_str());
	lv_d = atoi(_load_sipcfg(userloadprofile, "Level_D").c_str());
	lv_e = atoi(_load_sipcfg(userloadprofile, "Level_E").c_str());
	lv_f = atoi(_load_sipcfg(userloadprofile, "Level_F").c_str());
	sgAN = atoi(_load_sipcfg(userloadprofile, "StageANum").c_str());
	sgBN = atoi(_load_sipcfg(userloadprofile, "StageBNum").c_str());
	sgCN = atoi(_load_sipcfg(userloadprofile, "StageCNum").c_str());

	OpenCase:
	cleanConsole();
	SetConsoleTitle(casename.c_str());
	_prtoutmsg("ȷ�ϴ� :   " + casename);
	_prtoutmsg("���������� exit");
	_prtoutmsg("�������� fs ���ÿ��ٿ���");
	_prtoutmsg("�� Enter �� " + casename);
	_prtendl();
	cout << casename << "  -OpenCase >";
	getline(cin, opcs);
	if (opcs == "exit")goto ReturnMainUI;
	if (opcs == "fs") {
		fastopen = true;
	}

	if (fastopen == true) goto OutputResult;
	cleanConsole();
	sleepapi(1);

	cleanConsole();

	_prtoutmsg("���ڴ� :  " + casename);
	openapi_gtLv = "null";

	for (int autolist = 0; autolist != sgAN; autolist++) {
		randGetWeapList();
	}
	for (int autolist = 0; autolist != sgBN; autolist++) {
		randGetWeapList();
	}
	for (int autolist = 0; autolist != sgCN; autolist++) {
		randGetWeapList();
	}

	//Make Sure
	Sleep(100);
OutputResult:
	randGetWeapList();

	ColorRefresh();

	if (fastopen == false) {
		Sleep(300);
		_prtoutmsg("Stop ....");
		Sleep(800);
	}

	if (lv_s >= cs_randseed) {
		cweap = "[���亱��]";
		goto LoadResultCase;
	}

	if (lv_a >= cs_randseed) {
		cweap = "[����]";
		goto LoadResultCase;
	}

	if (lv_b >= cs_randseed) {
		cweap = "[����]";
		goto LoadResultCase;
	}

	if (lv_c >= cs_randseed) {
		cweap = "[����]";
		goto LoadResultCase;
	}

	if (lv_d >= cs_randseed) {
		cweap = "[����]";
		goto LoadResultCase;
	}

	if (lv_e >= cs_randseed) {
		cweap = "[��ҵ]";
		goto LoadResultCase;
	}

	if (lv_f >= cs_randseed) {
		cweap = "[����]";
		goto LoadResultCase;
	}

	LoadResultCase:

	Sleep(1000);

	cleanConsole();
	if (openapi_st == 1) {
		statTrackID = "[StatTrack]";
	}
	else {
		if (openapi_st == 2) {
			statTrackID = "[����Ʒ]";
		}
		else {
			statTrackID = "";
		}
		
	}

	system("color F7 ");
	Sleep(150);

	_fileapi_write(_$GetSelfPath + "/Case.log", "-------------------------------------------------------------");
	_fileapi_write(_$GetSelfPath + "/Case.log", "����Ʒ    :   " + cweap + " " + statTrackID + " " + openapi_gwname);
	_fileapi_write(_$GetSelfPath + "/Case.log", "ģ��      :    " + to_string(openapi_skinborad));
	_fileapi_write(_$GetSelfPath + "/Case.log", "ĥ���    :    " + openapi_abr_tag + " ( " + openapi_abr_full + ")");
	_fileapi_write(_$GetSelfPath + "/Case.log", "�������� :  " + to_string(cs_randseed));

	_fileapi_write(_$GetSelfPath + "/Total.log", casename + "  - " + cweap + " " + statTrackID + " " + openapi_gwname);

	ColorRefresh();
	_prtoutmsg("-------------------------------------------------------------");
	_prtoutmsg("����Ʒ    :   " + cweap + " " + statTrackID + " " + openapi_gwname);
	Sleep(200);
	_prtoutmsg("ģ��      :    " + to_string(openapi_skinborad));
	_prtoutmsg("ĥ���    :    " +  openapi_abr_tag + " ( " + openapi_abr_full + ")");
	_prtendl();
	_prtoutmsg("�������� :  " + to_string(cs_randseed));
	_prtoutmsg("����Ѿ���¼���� Total.log");
	_prtoutmsg("�����¼�ѱ��浽 Case.log");
	_prtoutmsg("-------------------------------------------------------------");
	_prtendl();
	_prtoutmsg("��Enter������һ����");
	_pause();
	system("color 07");
	goto OpenCase;
}