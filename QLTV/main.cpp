using namespace std; 

//#include <winbgim.h> 
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <string>
             
#include "datetime.h"
#include "define.h"
#include "queue.h"
#include "cautrucdanhmucsach.h"
#include "cautrucdausach.h"
#include "cautrucmuontra.h"
#include "cautrucdocgia.h"

#include "view.h"
#include "local.h"

#include "dausach.h"
#include "docgia.h"
#include "muontra.h"
#include "thongtin.h"
       
          
bool isExit = false;

void ReadDauSachFromFile(DS_DauSach &DSDS);
void ReadDocGiaFromFile(NodeDocGia* &TreeDG);
void WriteDauSachToFile(DS_DauSach &DSDS);
void WriteDocGiaToFile(NodeDocGia* &TreeDG);
void FreeMemory();

struct Writer{
	Writer(){
	}
	~Writer(){
		printf("Write file\n");
		WriteDauSachToFile(DSDS);
		WriteDocGiaToFile(TreeDocGia);
		
		printf("Free memory doc gia + ds muon tra\n");
		DeleteMemoryDocGia(TreeDocGia);
	}
};
Writer writer;
             
int main(int argc, char *argv[])
{
	srand(time(NULL));
	initwindow(w, h, AppTitle);
	ClearScreen();
	
	ReadDauSachFromFile(DSDS);
	ReadDocGiaFromFile(TreeDocGia);
	
	DrawMenu();
	
	while(true){
		Event();
		if(isExit) break;
		delay(50);
	}	
	
	closegraph();	
	return 0;
}

void ClearScreen(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(0, 0, w, h);  
}
    
void DrawMenu(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 7);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w/2-textwidth(AppTitle)/2, 100, AppTitle);
	
	btnQLDauSach.draw();
	btnQLDocGia.draw();
	btnQLSach.draw();
	btnThongTin.draw();
	btnThoat.draw();
} 

 
void Event(){
	mx = mousex(); my = mousey();
	KbEvent();
	
	if(curMenu == 0){
		MenuEvent();
	}else if(curMenu == btnQLDauSach.id){
		DauSachEvent();
	}else if(curMenu == btnQLDocGia.id){
		DocGiaEvent();
	}else if(curMenu == btnQLSach.id){
		MuonTraEvent();
	}else if(curMenu == btnThongTin.id){
		ThongTinEvent();
	}
} 


void ReadDauSachFromFile(DS_DauSach &DSDS){
	fstream fileDauSach, fileDMS;
	
	fileDauSach.open("data_dsds.txt", ios::in);
	fileDMS.open("data_dms.txt", ios::in);
	
	if(!fileDauSach.is_open() || ! fileDMS.is_open()){
		printf("Loi mo file de doc \n");
		return;
	}
	string line, lineDMS;

	DauSach dausach;
	
//	getline(fileDauSach, line);
//	int n = atoi(line.c_str());
	int n;
	fileDauSach >> n;
	fileDauSach.ignore();
	int m, slm;
		
	for(int i=0; i<n; i++){
		DauSach *dausach = new DauSach;
		
		getline(fileDauSach, line);		strcpy(dausach->ISBN, line.c_str());
		getline(fileDauSach, line);		strcpy(dausach->tensach, line.c_str());
		getline(fileDauSach, line);		dausach->sotrang = atoi(line.c_str());
		getline(fileDauSach, line);		strcpy(dausach->tacgia, line.c_str());
		getline(fileDauSach, line);		dausach->nxb = atoi(line.c_str());
		getline(fileDauSach, line);		strcpy(dausach->theloai, line.c_str());
		
		
		getline(fileDMS, lineDMS);
		slm = atoi(lineDMS.c_str());
		dausach->soluotmuon = slm;
		
		getline(fileDMS, lineDMS);
		m = atoi(lineDMS.c_str());
		dausach->soluong = m;
		
		for(int j=0; j<m; j++){
			Sach sach;
			
			getline(fileDMS, lineDMS);		strcpy(sach.MASACH, lineDMS.c_str());	
			getline(fileDMS, lineDMS);		sach.trangthai = atoi(lineDMS.c_str());
			getline(fileDMS, lineDMS);		strcpy(sach.vitri, lineDMS.c_str()); 
			
			InsertLast_NodeSach(dausach->First, sach);
		}
		InsertLastDauSach(DSDS, dausach);
	}

	fileDauSach.close();
	fileDMS.close();
}
 
void WriteDauSachToFile(DS_DauSach &DSDS){
//	printf("Write File \n");
	
	fstream fileDauSach, fileDMS;
	fileDauSach.open("data_dsds.txt", ios::out | ios::trunc);	
	fileDMS.open("data_dms.txt", ios::out | ios::trunc);
	
	fileDauSach << DSDS.n << endl;
	for(int i=0; i<DSDS.n; i++){
		fileDauSach << DSDS.nodes[i]->ISBN << endl;
		fileDauSach << DSDS.nodes[i]->tensach << endl;
		fileDauSach << DSDS.nodes[i]->sotrang << endl;
		fileDauSach << DSDS.nodes[i]->tacgia << endl;
		fileDauSach << DSDS.nodes[i]->nxb << endl;
		fileDauSach << DSDS.nodes[i]->theloai << endl;
		
//		fileDMS << SizeListNodeSach(DSDS.nodes[i]->First) << endl;
		fileDMS << DSDS.nodes[i]->soluotmuon << endl;
		fileDMS << DSDS.nodes[i]->soluong << endl;
		for(NodeSach* node = DSDS.nodes[i]->First; node != NULL; node = node->next){
			fileDMS << node->sach.MASACH << endl;
			fileDMS << node->sach.trangthai << endl;
			fileDMS << node->sach.vitri << endl;
		}
	}
	fileDauSach.close();
	fileDMS.close();
}
        
void ReadDocGiaFromFile(NodeDocGia* &TreeDG){
	fstream fileDocGia, fileMuonTra;
	fileDocGia.open("data_docgia.txt", ios::in);
	fileMuonTra.open("data_muontra.txt", ios::in);
	if(!fileDocGia.is_open() || !fileMuonTra.is_open()){
		printf("Loi mo file doc gia \n");
		AddRangeListID();
		return;
	}
	string line, lineMT;
	
//	getline(fileDocGia, line);
//	int n = atoi(line.c_str());
	int n;
	fileDocGia >> n;
	fileDocGia.ignore();
	int m;
	for(int i=0; i<n; i++){
		DocGia dg;
		
		getline(fileDocGia, line);		dg.MATHE = atoi(line.c_str());
		getline(fileDocGia, line);		strcpy(dg.ho, line.c_str());
		getline(fileDocGia, line);		strcpy(dg.ten, line.c_str());
		getline(fileDocGia, line);		dg.phai = atoi(line.c_str());
		getline(fileDocGia, line);		dg.trangthai = atoi(line.c_str());
		
		getline(fileMuonTra, lineMT);
		m = atoi(lineMT.c_str());
		for(int j=0; j<m; j++){
			MuonTra mt;
			getline(fileMuonTra, lineMT); 	strcpy(mt.MASACH, lineMT.c_str());
			getline(fileMuonTra, lineMT);	strcpy(mt.ngaymuon, lineMT.c_str());
			getline(fileMuonTra, lineMT);	strcpy(mt.ngaytra, lineMT.c_str());
			getline(fileMuonTra, lineMT);	mt.trangthai = atoi(lineMT.c_str());
			InsertLast_MuonTra(dg.mt, mt);
		}
		
		InsertDocGia(TreeDG, dg);
	}

	Duyet_DG_ID(TreeDG);
	AddRangeListID();
	
	fileMuonTra.close();
	fileDocGia.close();
}
 
void WriteDocGiaToFile(NodeDocGia* &TreeDG){
	if(TreeDocGia== NULL) return;
//	printf("Write File : Doc Gia \n");
	 
	fstream fileDocGia, fileMuonTra;
	fileDocGia.open("data_docgia.txt", ios::out | ios::trunc);
	fileMuonTra.open("data_muontra.txt", ios::out | ios::trunc);

	int i=0;
	Queue<NodeDocGia*> q;
	NodeDocGia *node;
	NodeMuonTra *nodeMT;
	q.push(TreeDG);
	
	fileDocGia << TotalDocGia(TreeDocGia) << endl;
	while(!q.empty()){
		// Lay tung doc gia ra - ghi du lieu
		node = q.front();	q.pop();
		
		fileDocGia << node->docgia.MATHE << endl;
		fileDocGia << node->docgia.ho << endl;
		fileDocGia << node->docgia.ten << endl;
		fileDocGia << node->docgia.phai << endl;
		fileDocGia << node->docgia.trangthai << endl;
		
		// ghi danh sach cac sach da muon 
		fileMuonTra << node->docgia.mt.total << endl;
		for(nodeMT = node->docgia.mt.First; nodeMT != NULL; nodeMT = nodeMT->next){
			fileMuonTra << nodeMT->muontra.MASACH << endl;
			fileMuonTra << nodeMT->muontra.ngaymuon << endl;
			fileMuonTra << nodeMT->muontra.ngaytra << endl;
			fileMuonTra << nodeMT->muontra.trangthai << endl;
		}
		
		if(node->left != NULL) q.push(node->left);
		if(node->right != NULL) q.push(node->right);
	}
	
	fileMuonTra.close();
	fileDocGia.close();
}
  
 
void MenuEvent(){
	ButtonEffect(btnQLDauSach);
	ButtonEffect(btnQLDocGia);
	ButtonEffect(btnQLSach);
	ButtonEffect(btnThongTin);
	ButtonEffect(btnThoat);	

	//Menu Click Event
	if(GetAsyncKeyState(VK_LBUTTON)){
		if(btnQLDauSach.isMouseHover(mx, my)){
			SetMenuSelect(btnQLDauSach.id);
		}else if(btnQLDocGia.isMouseHover(mx, my)){
			SetMenuSelect(btnQLDocGia.id);
		}else if(btnQLSach.isMouseHover(mx, my)){
			SetMenuSelect(btnQLSach.id);
		}else if(btnThongTin.isMouseHover(mx, my)){
			SetMenuSelect(btnThongTin.id);
		}else if(btnThoat.isMouseHover(mx, my)){
			isExit = true;
		}
	}
}
    
int TotalDocGia(NodeDocGia* &TreeDG){
	if(TreeDG == NULL) return 0;
	int cnt = 0;
	Queue<NodeDocGia> q;
	NodeDocGia node;
	q.push(*TreeDG);
	while(!q.empty()){
		node = q.front();	q.pop();
		cnt++;
		if(node.left != NULL) q.push(*node.left);
		if(node.right != NULL) q.push(*node.right);
	}
	return cnt;
}
   











