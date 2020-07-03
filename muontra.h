struct SachMT{
	char MASACH[10];
	char TenSach[30];
	char NgayMuon[10];
	int TrangThai;
};
struct DSMuonTra{
	int n;
	SachMT *mt = new SachMT[3];
	
	DSMuonTra(){
		n = 0;
	}
	~DSMuonTra(){
		delete[] mt;
	}
};

DSMuonTra DSMT;
 
void RunMuonTra(){
	DrawBorderMuonTra();
	
	curMenuMuonTra = -1;
	btnMuonSach.isHover = true;
	btnMuonSach.isChoose = true;
	SetMenuMuonTraSelect(btnMuonSach.id);
	
	btnBackToMenu.draw();
	btnMuonSach.draw();
	btnTraSach.draw();
	btnTopTen.draw();
}

void MuonTraEvent(){
	if(curDGMT != NULL && curMenuMuonTra != btnTopTen.id) ItemMTEvent();
	
	ButtonEffect(btnBackToMenu);
	ButtonEffect(btnMuonSach);
	ButtonEffect(btnTraSach);
	ButtonEffect(btnTopTen);
	
	if(curMenuMuonTra == btnMuonSach.id){
		ButtonEffect(btnTimMaDG);
		if(curDGMT != NULL) ButtonEffect(btnTimMaSach);
		if(canMT) ButtonEffect(btnXacNhanMuonSach);
	}else if(curMenuMuonTra == btnTraSach.id){
		ButtonEffect(btnTimMaDG);
		if(curMT != -1) {
			if(subWindow == XAC_NHAN_TRA_SACH){
				ButtonEffect(btnXacNhanTraSach);
				ButtonEffect(btnLamMatSach);
			}else if(subWindow == XAC_NHAN_LAM_MAT_SACH){
				ButtonEffect(btnXacNhanLamMatSach);
				ButtonEffect(btnHuyLamMatSach);
			}
			
		}
	}else if(curMenuMuonTra == btnTopTen.id){
		
	}
	
	if(GetAsyncKeyState(VK_LBUTTON)){
		if(curMenuMuonTra == btnTraSach.id) ItemMTClick();
		
		if(btnBackToMenu.isMouseHover(mx, my)){
			SetMenuSelect(0);
		}else if(btnMuonSach.isMouseHover(mx, my)){
			SetMenuMuonTraSelect(btnMuonSach.id);
		}else if(btnTraSach.isMouseHover(mx, my)){
			SetMenuMuonTraSelect(btnTraSach.id);
		}else if(btnTopTen.isMouseHover(mx, my)){
			SetMenuMuonTraSelect(btnTopTen.id);
		}
		
		if(curMenuMuonTra == btnMuonSach.id){
			if(btnTimMaDG.isMouseHover(mx, my)){
				curDGMT = &SearchDocGia(TreeDocGia, edNhapMaDGMuonSach.toInt())->docgia;
				DrawThongTinDocGia();
			}
			
			if(edNhapMaDGMuonSach.isMouseHover(mx, my)){
				Edit = &edNhapMaDGMuonSach;
			}
			
			if(curDGMT != NULL){
				if(btnTimMaSach.isMouseHover(mx, my)){
					if(strlen(edNhapMaSachMuonSach.content) > 0){
						// tim Dau Sach co chua Ma Sach can tim
						curDSMT = GetDauSach(DSDS, edNhapMaSachMuonSach.content);
						if(curDSMT == NULL){
							curSachMT = NULL;
						}else{
							// curSachMT != NULL : always
							curSachMT = GetSach(curDSMT->First, edNhapMaSachMuonSach.content);
						}
						
						strcpy(edNhapNgayMuonSach.content, GetSystemDate());
						DrawThongTinSach();
					}
				}
				if(edNhapMaSachMuonSach.isMouseHover(mx, my)){
					Edit = &edNhapMaSachMuonSach;
				}
				if(curSachMT != NULL && canMT){
					if(edNhapNgayMuonSach.isMouseHover(mx, my)){
						Edit = &edNhapNgayMuonSach;
					}
					if(btnXacNhanMuonSach.isMouseHover(mx, my)){
						// Muon sach
						if(!CheckDate(edNhapNgayMuonSach.content)){
							strcpy(mess, "THONG BAO : Ngay muon khong hop le");
							DrawThongTinSach();
						}else if(CompareDate(edNhapNgayMuonSach.content, GetSystemDate()) > 0){
							strcpy(mess, "THONG BAO : Ngay muon khong the muon hon ngay hien tai");
							DrawThongTinSach();
						}else{
							// 0: DANG MUON
							MuonTra muon(curSachMT->MASACH, edNhapNgayMuonSach.content, "", 0);
							InsertLast_MuonTra(curDGMT->mt, muon);
							
							NodeSach *nodeSach = GetNodeSach(curDSMT->First, curSachMT->MASACH);
							Sach sach = nodeSach->sach;
							sach.trangthai = 1; 	// DA CHO MUON
							UpdateNodeSach(nodeSach, sach);
							
							// Tang so luot muon sach cua Dau Sach
							curDSMT->soluotmuon ++;
							
							curDSMT = NULL;
							curSachMT = NULL;
							canMT = false;
							
							memset(edNhapMaSachMuonSach.content, 0, sizeof(edNhapMaSachMuonSach.content));
							DrawThongTinDocGia();
						}
					}
				}
			}
			
		}else if(curMenuMuonTra == btnTraSach.id){
			if(btnTimMaDG.isMouseHover(mx, my)){
				curDGMT = &SearchDocGia(TreeDocGia, edNhapMaDGMuonSach.toInt())->docgia;
				DrawThongTinDocGia();
			}
			
			if(edNhapMaDGMuonSach.isMouseHover(mx, my)){
				Edit = &edNhapMaDGMuonSach;
			}
			
			if(curMT != -1 && curDGMT != NULL){
				if(edNhapNgayTraSach.isMouseHover(mx, my)){
					Edit = &edNhapNgayTraSach;
				}
				
				if(subWindow == XAC_NHAN_TRA_SACH){
					if(btnXacNhanTraSach.isMouseHover(mx, my)){
						if(!CheckDate(edNhapNgayTraSach.content)){
							strcpy(mess, "THONG BAO : Ngay nhap vao khong hop le");
							DrawThongTinSachTra(curMT);
						}else if(CompareDate(edNhapNgayTraSach.content, DSMT.mt[curMT].NgayMuon) < 0){
							strcpy(mess, "THONG BAO : Ngay tra sach khong the som hon ngay muon sach");
							DrawThongTinSachTra(curMT);
						}else if(CompareDate(edNhapNgayTraSach.content, GetSystemDate()) > 0){
							strcpy(mess, "THONG BAO : Ngay muon khong the muon hon ngay hien tai");
							DrawThongTinSach();
						}else{
							// 1: DA TRA 
							MuonTra tra(DSMT.mt[curMT].MASACH, DSMT.mt[curMT].NgayMuon, edNhapNgayTraSach.content, 1);
							Update_MuonTra(curDGMT->mt, tra);
							
							curDSMT = GetDauSach(DSDS, DSMT.mt[curMT].MASACH);
							
							NodeSach *nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
							Sach sach = nodeSach->sach;
							sach.trangthai = 0; 	// CHO MUON DUOC
							UpdateNodeSach(nodeSach, sach);
								
							// test
//							nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
//							printf("TT : %d \n", nodeSach->sach.trangthai);
							
							curDSMT = NULL;
							curMT = -1;
								
							memset(edNhapNgayTraSach.content, 0, sizeof(edNhapNgayTraSach.content));
							DrawThongTinDocGia();
						}
						
					}else if(btnLamMatSach.isMouseHover(mx, my)){
						subWindow = XAC_NHAN_LAM_MAT_SACH;
						DrawThongTinSachTra(curMT);
					}
					
				}else if(subWindow == XAC_NHAN_LAM_MAT_SACH){
					if(btnXacNhanLamMatSach.isMouseHover(mx, my)){
						// 2: LAM MAT
						MuonTra tra(DSMT.mt[curMT].MASACH, DSMT.mt[curMT].NgayMuon, "", 2);
						Update_MuonTra(curDGMT->mt, tra);
							
						curDSMT = GetDauSach(DSDS, DSMT.mt[curMT].MASACH);
							
						NodeSach *nodeSach = GetNodeSach(curDSMT->First, DSMT.mt[curMT].MASACH);
						Sach sach = nodeSach->sach;
						sach.trangthai = 2; 	// DA THANH LY
						UpdateNodeSach(nodeSach, sach);
								
						curDSMT = NULL;
						curMT = -1;
						
						curDGMT->trangthai = 0; // KHOA THE DOC GIA
						UpdateDocGia(TreeDocGia, *curDGMT);
								
						memset(edNhapNgayTraSach.content, 0, sizeof(edNhapNgayTraSach.content));
						DrawThongTinDocGia();
					}else if(btnHuyLamMatSach.isMouseHover(mx, my)){
						subWindow = XAC_NHAN_TRA_SACH;
						DrawThongTinSachTra(curMT);
					}
				}
				
			}
		}else if(curMenuMuonTra == btnTopTen.id){
			
		}
	}
}

void DrawBorderDSMT(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(BORDER_COLOR);
	setbkcolor(BG_COLOR);
	char t[4][15] = {"Ma sach", "Ten sach", "Ngay muon", "Trang thai"};
	setfillstyle(SOLID_FILL, BORDER_COLOR);
	rectangle(XMT[0], 500, XMT[4], 725);
	int yline = 580;
//	setcolor(TEXT_COLOR);
	line(XMT[0], yline, XMT[4], yline);
	for(int i=0; i<4; i++){
		line(XMT[i], 500, XMT[i], 725);
		outtextxy((XMT[i]+XMT[i+1])/2 - textwidth(t[i])/2, (500+yline)/2-textheight(t[i])/2, t[i]);
	}
}

int GetItemMTPosition(int y){
	int pos = (y-600+8)/40;
	if(pos >= DSMT.n) return -1;
	return pos;
}

void ItemMTClick(){
	if(curItemMT != -1){
		subWindow = XAC_NHAN_TRA_SACH;
		strcpy(edNhapNgayTraSach.content, GetSystemDate());
		DrawThongTinSachTra(curItemMT);
	}
}

void ItemMTEvent(){
	if(mx > XMT[0] && mx < XMT[4] && my > 600-8 && my < 720-8){
		
		if(curItemMT != GetItemMTPosition(my)){
			if(curItemMT != -1){
				// khoi phuc item
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
				
				setbkcolor(BG_COLOR);
				DrawItemMT(curItemMT);
				
				DrawBorderDSMT();
			}
			
			// Ve item hien tai
			curItemMT = GetItemMTPosition(my);
			if(curItemMT != -1){
				setfillstyle(SOLID_FILL, LINE);
				bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
				
				setbkcolor(LINE);
				DrawItemMT(curItemMT);
				
				DrawBorderDSMT();
			}
		}
	}else{
		if(curItemMT != -1){
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XMT[0], 600 + curItemMT*40 - 8, XMT[4], 600+(curItemMT+1)*40-8);
			setbkcolor(BG_COLOR);
		
			DrawItemMT(curItemMT);
				
			DrawBorderDSMT();
			curItemMT = -1;
		}
	}
}

void DrawItemMT(int i){
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_COLOR);
	
	outtextxy(XMT[0]+10, 600+i*40, DSMT.mt[i].MASACH);
	outtextxy(XMT[1]+10, 600+i*40, DSMT.mt[i].TenSach);
	outtextxy(XMT[2]+10, 600+i*40, DSMT.mt[i].NgayMuon);
	outtextxy(XMT[3]+10, 600+i*40, TTMuonTra[DSMT.mt[i].TrangThai]);
}

void DrawThongTinDocGia(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(255, 200, 250+(w-250)/2-5, h);
	ClearLayoutRightMuonTra();
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	if(curDGMT == NULL){
		setcolor(TIPS);
		outtextxy(280, 200, "Khong tim thay doc gia nay");
	}else{	
		char ch[30];
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_COLOR);
		outtextxy(300, 200, "Doc gia :");
		sprintf(ch, "%s %s", curDGMT->ho, curDGMT->ten);
		outtextxy(600, 200, ch);
		
		outtextxy(300, 250, "Ma the :");
		sprintf(ch, "%d", curDGMT->MATHE);
		outtextxy(600, 250, ch);
		
		outtextxy(300, 300, "Phai :");
		outtextxy(600, 300, PhaiDocGia[curDGMT->phai]);
		
		outtextxy(300, 350, "Trang thai the :");
		outtextxy(600, 350, TTTDocGia[curDGMT->trangthai]);
		
		settextstyle(BOLD_FONT, HORIZ_DIR, 3);
		setcolor(TEXT_TITLE_COLOR);
		outtextxy((XMT[0]+XMT[4])/2 - textwidth(DSDM)/2, 450, DSDM);
		
		DrawBorderDSMT();
		
		DSMT.n = 0;
		DauSach *ds;
		char chNow[15];
		strcpy(chNow, GetSystemDate());
		bool isQH = false;
		
//		for(NodeMuonTra *mt = curDGMT->mt.First; mt != NULL; mt = mt->next){
//			if(mt->muontra.trangthai != 1){
//				// Dang muon + Lam mat
//				ds = GetDauSach(DSDS, mt->muontra.MASACH);
//				strcpy(DSMT.mt[DSMT.n].MASACH, mt->muontra.MASACH);
//				strcpy(DSMT.mt[DSMT.n].TenSach, ds->tensach);
//				strcpy(DSMT.mt[DSMT.n].NgayMuon, mt->muontra.ngaymuon);
//				DSMT.mt[DSMT.n].TrangThai = mt->muontra.trangthai;
//				DrawItemMT(DSMT.n++);
//			}
//			if(mt->muontra.trangthai == 0){
//				// Muon sach qua 7 ngay
//				if(DiffTime(chNow, mt->muontra.ngaymuon) > 7*24*60*60){
//					isQH = true;
//				}
//			}
//		}
		if(curDGMT->mt.chuaTra > 0){
			DSMT.n = curDGMT->mt.chuaTra;
			int i = DSMT.n-1;
			for(NodeMuonTra *mt = curDGMT->mt.Last; mt != NULL; mt = mt->prev){
				if(mt->muontra.trangthai != 1){
					ds = GetDauSach(DSDS, mt->muontra.MASACH);
					strcpy(DSMT.mt[i].MASACH, mt->muontra.MASACH);
					strcpy(DSMT.mt[i].TenSach, ds->tensach);
					strcpy(DSMT.mt[i].NgayMuon, mt->muontra.ngaymuon);
					DSMT.mt[i].TrangThai = mt->muontra.trangthai;
					DrawItemMT(i--);
				}
				if(mt->muontra.trangthai == 0){
					if(DiffTime(chNow, mt->muontra.ngaymuon) > 7*24*60*60){
						isQH = true;
					}
				}
			}
		}
		
		
		if(curMenuMuonTra == btnMuonSach.id){
			setcolor(TIPS);
			settextstyle(BOLD_FONT, HORIZ_DIR, 3);
				
			if(curDGMT->trangthai == 0){
				// the bi khoa
				outtextxy(1200, 250, "THE DOC GIA DANG BI KHOA, KHONG THE MUON SACH");
				return;
			}
			if(DSMT.n >= 3){
				outtextxy(1200, 250, "SO LUONG SACH MUON DA DAT GIOI HAN !");
				outtextxy(1200, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI");
				return;
			}
			if(isQH){
				outtextxy(1200, 250, "DOC GIA DA MUON SACH QUA 7 NGAY ");
				outtextxy(1200, 300, "VUI LONG TRA SACH TRUOC KHI MUON SACH MOI");
				return;
			}

			edNhapMaSachMuonSach.draw();
			btnTimMaSach.draw();
			
		}else if(curMenuMuonTra == btnTraSach.id){
			
		}
	}
}

void DrawThongTinSachTra(int itemMT){
	if(itemMT != -1){
		curMT = itemMT;
		
		setfillstyle(SOLID_FILL, BG_COLOR);
		bar(250+(w-250)/2+5, 110, w, h);
		
		settextstyle(BOLD_FONT, HORIZ_DIR, 3);
		setcolor(TEXT_TITLE_COLOR);
		outtextxy(1300, 150, "THONG TIN SACH");
		
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_COLOR);
		
		outtextxy(1200, 200, "Ma sach :");	
		outtextxy(1500, 200, DSMT.mt[curMT].MASACH);
		
		outtextxy(1200, 250, "Ten sach : ");
		outtextxy(1500, 250, DSMT.mt[curMT].TenSach);
		
		outtextxy(1200, 300, "Ngay muon :");
		outtextxy(1500, 300, DSMT.mt[curMT].NgayMuon);
		
		setfillstyle(SOLID_FILL, BG_COLOR);
		bar(1100, 400, w,h);
		
		if(subWindow == XAC_NHAN_TRA_SACH){
//			strcpy(edNhapNgayTraSach.content, GetSystemDate());
			edNhapNgayTraSach.draw();
			btnXacNhanTraSach.draw();
			btnLamMatSach.draw();
			
			settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			setcolor(TIPS);
			outtextxy(250+(w-250)/2 + 30, 700, mess);
			
		}else if(subWindow == XAC_NHAN_LAM_MAT_SACH){
			DrawLamMatSach();
		}
		
	}
}
 
void DrawLamMatSach(){
	setcolor(TEXT_TITLE_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	outtextxy(1350, 500, "LAM MAT SACH ?");
	setcolor(TIPS);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	outtextxy(1200, 550, "The doc gia se bi khoa");
	outtextxy(1200, 600, "Sach se chuyen qua trang thai: DA THANH LY");
	outtextxy(1200, 650, "Doc gia phai den sach moi co the tiep tuc muon sach");
	outtextxy(1200, 700, "Xac nhan lam mat sach ??");
	
	btnXacNhanLamMatSach.draw();
	btnHuyLamMatSach.draw();
}

void DrawThongTinSach(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(250+(w-250)/2+5, 200, w, h);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TEXT_COLOR);
	
	if(curSachMT != NULL){
		outtextxy(1200, 200, "Ma sach :");	
		outtextxy(1500, 200, curSachMT->MASACH);
		
		outtextxy(1200, 250, "Ten sach : ");
		outtextxy(1500, 250, curDSMT->tensach);
		
		outtextxy(1200, 300, "Trang thai :");
		outtextxy(1500, 300, TrangThaiSach[curSachMT->trangthai]);
		
		outtextxy(1200, 350, "Vi tri :");
		outtextxy(1500, 350, curSachMT->vitri);
		
		if(curSachMT->trangthai == 0){
			outtextxy(1300, 400, "=> DOC GIA CO THE MUON CUON SACH NAY !");
			canMT = true;	// Co the muon sach
		}else if(curSachMT->trangthai == 1){
			setcolor(TIPS);
			outtextxy(1300, 400, "=> DA CO NGUOI MUON CUON SACH NAY !");
			return;
		}else{
			setcolor(TIPS);
			outtextxy(1300, 400, "=> SACH DA THANH LY, KHONG THE MUON !");
			return;
		}
		
//		strcpy(edNhapNgayMuonSach.content, GetSystemDate());
		edNhapNgayMuonSach.draw();
		btnXacNhanMuonSach.draw();
		
		setfillstyle(SOLID_FILL, BG_COLOR);
		bar(1200, 740, w, h);
		setcolor(TIPS);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		outtextxy(250+(w-250)/2 + 30, 750, mess);
//		outtextxy(1200 + textwidth(ThongBao) + 40, 750, mess);
	}else{
		setcolor(TIPS);
		outtextxy(1300, 250, "Khong tim thay sach nay!");
	}
}

void SetMenuButtonSwitch(int menuID){
	btnMuonSach.isChoose = false;
	btnTraSach.isChoose = false;
	btnTopTen.isChoose = false;
	
	if(menuID == btnMuonSach.id){
		btnMuonSach.isChoose = true;
	}else if(menuID == btnTraSach.id){
		btnTraSach.isChoose = true;
	}else if(menuID == btnTopTen.id){
		btnTopTen.isChoose = true;
	}
}
 
void SetMenuMuonTraSelect(int menuID){
	if(curMenuMuonTra != menuID){
		curMenuMuonTra = menuID;
		curDGMT = NULL;
		curDSMT = NULL;
		Edit = NULL;
		strcpy(mess, "");
		ClearLayoutMainMuonTra();
		SetMenuButtonSwitch(curMenuMuonTra);
		
		if(curMenuMuonTra == btnMuonSach.id){
			DrawMuonSach();
		}else if(curMenuMuonTra == btnTraSach.id){
			DrawTraSach();
		}else if(curMenuMuonTra == btnTopTen.id){
			DrawTopTen();
		}
		
	}
}

void ClearLayoutLeftMuonTra(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(255, 105, 250+(w-250)/2-5, h);
} 

void ClearLayoutRightMuonTra(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(250+(w-250)/2+5, 105, w, h);
}

void ClearLayoutMainMuonTra(){
	// xoa title
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(255, 0, w, 95);
	// xoa content
	ClearLayoutLeftMuonTra();
	ClearLayoutRightMuonTra();
}


void DrawBorderMuonTra(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(250, 100, w, h);
	
	setlinestyle(SOLID_LINE, 0, 3);
	line(250, 0, 250, h);
	line(250, 100, w, 100);
	
}

void DrawMuonSach(){
	DrawBorderMuonTra();
	line((w+250)/2, 100, 250+(w-250)/2, h);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w+250)/2 - textwidth(MuonSach)/2, 50, MuonSach);
	
	memset(edNhapMaDGMuonSach.content, 0, sizeof(edNhapMaDGMuonSach.content));
	edNhapMaDGMuonSach.draw();
	btnTimMaDG.draw();
	
}

void DrawTraSach(){
	DrawBorderMuonTra();
	line((w+250)/2, 100, 250+(w-250)/2, h);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w+250)/2 - textwidth(TraSach)/2, 50, TraSach);
	
	memset(edNhapMaDGMuonSach.content, 0, sizeof(edNhapMaDGMuonSach.content));
	edNhapMaDGMuonSach.draw();
	btnTimMaDG.draw();
}
 
void DrawTopTen(){
	DrawBorderMuonTra();

	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w+250)/2 - textwidth(TopTen)/2, 50, TopTen);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(255, 105, w, h);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	
	char t[][20] = {"STT", "ISBN", "Ten sach", "So trang", "Tac gia", "NXB", "The loai", "So luot muon"};
	
	setlinestyle(SOLID_LINE,0, 3);
	setcolor(BORDER_COLOR);
	rectangle(XTT[0], 200, XTT[8], 880);
	line(XTT[0], 280, XTT[8], 280);
	for(int i=0; i<8; i++){
		line(XTT[i], 200, XTT[i], 880);
		outtextxy((XTT[i+1]+XTT[i])/2 - textwidth(t[i])/2, 240-textheight(t[i])/2, t[i]);
	}
	
	TopSach topsach(DSDS);
//	DuyetDocGia(TreeDocGia, topsach);
//	topsach.sort();
	char ch[20];
	for(int i=0; i < (topsach.n < 10 ? topsach.n : 10); i++){
		itoa(i+1, ch, 10);
		outtextxy((XTT[0]+XTT[1])/2-textwidth(ch)/2, 300 + i*50, ch);
		outtextxy(XTT[1]+10, 300 + i*50, DSDS.nodes[topsach.list[i].indexDS]->ISBN);
		outtextxy(XTT[2]+10, 300 + i*50, DSDS.nodes[topsach.list[i].indexDS]->tensach);
		itoa(DSDS.nodes[topsach.list[i].indexDS]->sotrang, ch, 10);
		outtextxy(XTT[3]+20, 300 + i*50, ch);
		outtextxy(XTT[4]+10, 300 + i*50, DSDS.nodes[topsach.list[i].indexDS]->tacgia);
		itoa(DSDS.nodes[topsach.list[i].indexDS]->nxb, ch, 10);
		outtextxy((XTT[5]+XTT[6])/2-textwidth(ch)/2, 300 + i*50, ch);
		outtextxy(XTT[6]+10, 300 + i*50, DSDS.nodes[topsach.list[i].indexDS]->theloai);
		itoa(topsach.list[i].cnt, ch, 10);
		outtextxy((XTT[7]+XTT[8])/2-textwidth(ch)/2, 300 + i*50, ch);
	} 
}












