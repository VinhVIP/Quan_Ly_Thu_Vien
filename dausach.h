void RunDauSach(){
	strcpy(mess, "");
	ClearContentThemDauSach();
	
	setlinestyle(SOLID_LINE, 0 , 1);
	line(XDS[6]+10, 0, XDS[6]+10, h);
	
	DrawDanhSachDauSach();
	
	DrawList();
	Window = THEM_DAU_SACH;
	subWindow = NHAP_SACH;
	
	if(Window == THEM_DAU_SACH){
		DrawThemDauSach();
	}else if(Window == HIEU_CHINH_DAU_SACH){
		DrawHieuChinhDauSach();
	}else if(Window == DANH_MUC_SACH){
		DrawDanhMucSach();
		if(subWindow == NHAP_SACH){
			DrawNhapSach();
		}
	}
}

void DrawDanhSachDauSach(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDS[0]+XDS[6])/2-textwidth(DauSachTitle)/2, 15, DauSachTitle);
	
	btnQuayVe.draw();
	btnClearTimDauSach.draw();
	btnPrevDauSach.draw();
	btnNextDauSach.draw();
	
	edTimDauSach.draw();
}

void ClearRightLayout(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[6]+15, 0 , w, h);
}
  
void DrawDanhMucSach(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_COLOR);
	char t[50];
	sprintf(t, "%s: %s", DanhMucSach, DSDS.nodes[curDauSach]->tensach);
	outtextxy((XDMS[0] + XDMS[3])/2-textwidth(t)/2, 20, t);
	
	DrawBorderListSach();
	
	setcolor(TEXT_COLOR);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	char ch[3][20] = {"Ma sach", "Trang thai", "Vi tri"};
		
	for(int i=0; i < 3; i++){
		setbkcolor(BG_COLOR);
		outtextxy(XDMS[i] + (XDMS[i+1]-XDMS[i])/2 - textwidth(ch[i])/2, 102-textheight("V")/2, ch[i]);
	}

	totalPageSach = (DSDS.nodes[curDauSach]->soluong - 1) / 10 + 1;
	
	setcolor(TEXT_COLOR);
	NodeSach* node = GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1));
	for(int i = 0; node != NULL && i < 10; node = node->next){
		DrawItemSach(node->sach, i++);
	}

	
	// num page
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	char chPage[20];
	sprintf(chPage, "TRANG %d / %d", curPageSach, totalPageSach);
	outtextxy(XDMS[0] + (XDMS[3]-XDMS[0])/2 - textwidth(chPage)/2, 570, chPage);
	

	btnBackToThemDauSach.draw();
	btnPrevDanhMucSach.draw();
	btnNextDanhMucSach.draw();
	
	// tips
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	setlinestyle(SOLID_LINE, 0, 3);
	rectangle(XDMS[0], 880, XDMS[3], 980);
	outtextxy(XDMS[0] + 20, 890, "Click chuot trai: Hieu chinh sach");
}
 
void DrawNhapSach(){
	ClearLayoutSach();
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setbkcolor(BG_COLOR);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDMS[0]+XDMS[3])/2-textwidth(NhapSach)/2, 650, NhapSach);
	edNhapSoLuongSach.draw();
	btnNhapSoLuongSach.draw();
}

void DrawThemSach(){
	ClearLayoutSach();
	
	AutoCreateMaSach();
	strcpy(edThemTrangThaiSach.content, "0");
	
	btnThemSach.draw();
	edThemMaSach.draw();
	edThemTrangThaiSach.draw();
	edThemViTriSach.draw();
	
	
	char ch[30], c[3];
//	strcpy(ch, ThemSach);
//	itoa(curNhapSach, c, 10);
//	strcat(ch, c);
//	strcat(ch, " / ");
//	itoa(totalNhapSach, c, 10);
//	strcat(ch, c);
	sprintf(ch, "%s %d / %d", ThemSach, curNhapSach, totalNhapSach);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDMS[0]+XDMS[3])/2-textwidth(ch)/2, 610, ch);
	
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TIPS);
	rectangle(XDMS[0], 800, XDMS[3], 850);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0]+5, 805, XDMS[3]-5, 845);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	outtextxy(XDMS[0]+20, 825-textheight(ThongBao)/2, ThongBao);
	
	// Draw mess
	outtextxy(XDMS[0]+50 + textwidth(ThongBao), 825-textheight(ThongBao)/2, mess);
}
  
void DrawHieuChinhSach(){
	ClearLayoutSach();
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	setbkcolor(BG_COLOR);
	outtextxy((XDMS[0]+XDMS[3])/2-textwidth(HieuChinhSach)/2, 610, HieuChinhSach);
	
	btnHieuChinhSach.draw();
	edHieuChinhMaSach.draw();
	edHieuChinhTrangThaiSach.draw();
	edHieuChinhViTriSach.draw();
	btnBackToNhapSach.draw();
	
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(TIPS);
	rectangle(XDMS[0], 800, XDMS[3], 850);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0]+5, 805, XDMS[3]-5, 845);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	outtextxy(XDMS[0]+20, 825-textheight(ThongBao)/2, ThongBao);
	
	// Draw mess
	outtextxy(XDMS[0]+50 + textwidth(ThongBao), 825-textheight(ThongBao)/2, mess);
}

void DrawThemDauSach(){
	setbkcolor(BG_COLOR);
	setfillstyle(WIDE_DOT_FILL, GREEN);
	bar(XDS[6]+15, 210, w-15, 280);
	
	setcolor(BORDER_COLOR);
	setlinestyle(SOLID_FILL, 0, 3);
	rectangle(XDS[6]+20, 210, w-15, 700);
	line(XDS[6]+20, 280, w-15, 280);
	line(XDS[6]+20, 650, w-15, 650);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w-15+XDS[6]+20)/2 - textwidth(ThemDauSach)/2, 245 - textheight(ThemDauSach)/2, ThemDauSach);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	outtextxy(XDS[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	outtextxy(XDS[6]+50+20 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);
	
	edThemISBN.draw();
	edThemTenSach.draw();
	edThemSoTrang.draw();
	edThemTacGia.draw();
	edThemNXB.draw();
	edThemTheLoai.draw();
	
	btnThemDauSach.draw();
} 
 
void DrawHieuChinhDauSach(){
	setbkcolor(BG_COLOR);
	setfillstyle(WIDE_DOT_FILL, GREEN);
	bar(XDS[6]+15, 210, w-15, 280);
	
	setcolor(BORDER_COLOR);
	setlinestyle(SOLID_FILL, 0, 3);
	rectangle(XDS[6]+20, 210, w-15, 700);
	line(XDS[6]+20, 280, w-15, 280);
	line(XDS[6]+20, 650, w-15, 650);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((w-15+XDS[6]+20)/2 - textwidth(HieuChinhDauSach)/2, 245 - textheight(HieuChinhDauSach)/2, HieuChinhDauSach);

	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	outtextxy(XDS[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	outtextxy(XDS[6]+50+20 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);
		
	edHieuChinhISBN.draw();
	edHieuChinhTenSach.draw();
	edHieuChinhSoTrang.draw();
	edHieuChinhTacGia.draw();
	edHieuChinhNXB.draw();
	edHieuChinhTheLoai.draw();
	
	btnBackToThemDauSach.draw();
	btnHieuChinhDauSach.draw();
}
 
void ClearContentThemSach(){
	memset(edThemMaSach.content, 0, sizeof(edThemMaSach.content));
	memset(edThemTrangThaiSach.content, 0, sizeof(edThemTrangThaiSach.content));
//	memset(edThemViTriSach.content, 0, sizeof(edThemViTriSach.content));
}

void ClearContentHieuChinhSach(){
	memset(edHieuChinhMaSach.content, 0, sizeof(edHieuChinhMaSach.content));
	memset(edHieuChinhTrangThaiSach.content, 0, sizeof(edHieuChinhTrangThaiSach.content));
	memset(edHieuChinhViTriSach.content, 0, sizeof(edHieuChinhViTriSach.content));
}
 
void ClearContentNhapSoLuongSach(){
	memset(edNhapSoLuongSach.content, 0, sizeof(edNhapSoLuongSach.content));
}
 
void ClearContentThemDauSach(){	
	memset(edThemISBN.content, 0, sizeof(edThemISBN.content));
	memset(edThemTenSach.content, 0, sizeof(edThemTenSach.content));
	memset(edThemSoTrang.content, 0, sizeof(edThemSoTrang.content));
	memset(edThemTacGia.content, 0, sizeof(edThemTacGia.content));
	memset(edThemNXB.content, 0, sizeof(edThemNXB.content));
	memset(edThemTheLoai.content, 0, sizeof(edThemTheLoai.content));
}

void ClearContentHieuChinhDauSach(){
	memset(edHieuChinhISBN.content, 0, sizeof(edHieuChinhISBN.content));
	memset(edHieuChinhTenSach.content, 0, sizeof(edHieuChinhTenSach.content));
	memset(edHieuChinhSoTrang.content, 0, sizeof(edHieuChinhSoTrang.content));
	memset(edHieuChinhTacGia.content, 0, sizeof(edHieuChinhTacGia.content));
	memset(edHieuChinhNXB.content, 0, sizeof(edHieuChinhNXB.content));
	memset(edHieuChinhTheLoai.content, 0, sizeof(edHieuChinhTheLoai.content));
}

void AutoCreateMaSach(){
	if(curNhapSach == 1) startIndexSach = DSDS.nodes[curDauSach]->soluong;
	else startIndexSach++;
	
	char id[20];
	sprintf(id, "%s-%d", DSDS.nodes[curDauSach]->ISBN, startIndexSach);
	strcpy(edThemMaSach.content, id);
}

bool CheckSach(){
	if(strlen(edThemTrangThaiSach.content) == 0 ||
		strlen(edThemViTriSach.content) == 0){
		
		strcpy(mess, "Khong duoc bo trong bat ki truong nao");
		return false;	
	}
	if(edThemTrangThaiSach.toInt() == 1){
		strcpy(mess, "Trang thai sach ban dau khong the la: DA CHO MUON");
		return false;
	}
	return true;
}

bool CheckHieuChinhSach(){
	if(strlen(edHieuChinhTrangThaiSach.content) == 0 ||
		strlen(edHieuChinhViTriSach.content) == 0){
		
		strcpy(mess, "Khong duoc bo trong bat ki truong nao");
		return false;	
	}
	if(canEditTrangThai && edHieuChinhTrangThaiSach.toInt() == 1){
		strcpy(mess, "Trang thai sach khong the la: DA CHO MUON");
		return false;
	}
	return true;
}

bool CheckSoLuongSach(){
	if(strlen(edNhapSoLuongSach.content) == 0){
		strcpy(mess, "Hay nhap so luong sach them");
		return false;
	}
	return true;
}

bool CheckDauSach(){
	if(strlen(edThemISBN.content) == 0) {
		strcpy(mess, "ISBN khong duoc bo trong");
		Edit = &edThemISBN;
		Edit->draw();
		return false;
	}else if(strlen(edThemTenSach.content) == 0) {
		strcpy(mess, "Ten sach khong duoc bo trong");
		Edit = &edThemTenSach;
		Edit->draw();
		return false;
	}else if(strlen(edThemSoTrang.content) == 0) {
		strcpy(mess, "So trang khong duoc bo trong");
		Edit = &edThemSoTrang;
		Edit->draw();
		return false;
	}else if(strlen(edThemTacGia.content) == 0) {
		strcpy(mess, "Tac gia khong duoc bo trong");
		Edit = &edThemTacGia;
		Edit->draw();
		return false;
	}else if(strlen(edThemNXB.content) == 0) {
		strcpy(mess, "NXB khong duoc bo trong");
		Edit = &edThemNXB;
		Edit->draw();
		return false;
	}else if(strlen(edThemTheLoai.content) == 0) {
		strcpy(mess, "The loai khong duoc bo trong");
		Edit = &edThemTheLoai;
		Edit->draw();
		return false;
	}
	
	if(ExistsDauSach(DSDS, edThemISBN.content) != -1){
		strcpy(mess, "ISBN da ton tai");
		Edit = &edThemISBN;
		Edit->draw();
		return false;
	}
	
	char chDate[11];
	strcpy(chDate, GetSystemDate());
	int *d = SplitDate(chDate);
	int year = d[2];
	delete[] d;
	int y = edThemNXB.toInt();
	if(y > year){
		strcpy(mess, "NXB khong the lon hon nam hien tai");
		Edit = &edThemNXB;
		Edit->draw();
		return false;
	}

	return true;
}
 
bool CheckHieuChinhDauSach(){
	if(strlen(edHieuChinhISBN.content) == 0) {
		strcpy(mess, "ISBN khong duoc bo trong");
		Edit = &edHieuChinhISBN;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhTenSach.content) == 0) {
		strcpy(mess, "Ten sach khong duoc bo trong");
		Edit = &edHieuChinhTenSach;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhSoTrang.content) == 0) {
		strcpy(mess, "So trang khong duoc bo trong");
		Edit = &edHieuChinhSoTrang;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhTacGia.content) == 0) {
		strcpy(mess, "Tac gia khong duoc bo trong");
		Edit = &edHieuChinhTacGia;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhNXB.content) == 0) {
		strcpy(mess, "NXB khong duoc bo trong");
		Edit = &edHieuChinhNXB;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhTheLoai.content) == 0) {
		strcpy(mess, "The loai khong duoc bo trong");
		Edit = &edHieuChinhTheLoai;
		Edit->draw();
		return false;
	}
	
	char chDate[11];
	strcpy(chDate, GetSystemDate());
	int *d = SplitDate(chDate);
	int year = d[2];
	delete[] d;
	int y = edHieuChinhNXB.toInt();
	if(y > year){
		strcpy(mess, "NXB khong the lon hon nam hien tai");
		Edit = &edHieuChinhNXB;
		Edit->draw();
		return false;
	}

	return true;
}

void GetHieuChinhDauSach(int i){
	curDauSach = i;
	ClearContentHieuChinhDauSach();
	
	char ch[10];
	strcpy(edHieuChinhISBN.content, DSDS.nodes[i]->ISBN);
	strcpy(edHieuChinhTenSach.content, DSDS.nodes[i]->tensach);
	itoa(DSDS.nodes[i]->sotrang, ch, 10);
	strcpy(edHieuChinhSoTrang.content, ch);
	strcpy(edHieuChinhTacGia.content, DSDS.nodes[i]->tacgia);
	itoa(DSDS.nodes[i]->nxb, ch, 10);
	strcpy(edHieuChinhNXB.content, ch);
	strcpy(edHieuChinhTheLoai.content, DSDS.nodes[i]->theloai);
	
	ClearRightLayout();
	DrawHieuChinhDauSach();
}
 
void DauSachEvent(){
	ItemEvent();
	
	ButtonEffect(btnQuayVe);
	ButtonEffect(btnClearTimDauSach);
	ButtonEffect(btnPrevDauSach);
	ButtonEffect(btnNextDauSach);
	
	if(Window == THEM_DAU_SACH){
		ButtonEffect(btnThemDauSach);
	}else if(Window == HIEU_CHINH_DAU_SACH){
		ButtonEffect(btnHieuChinhDauSach);
		ButtonEffect(btnBackToThemDauSach);
	}else if(Window == DANH_MUC_SACH){
		ButtonEffect(btnBackToThemDauSach);
		ButtonEffect(btnPrevDanhMucSach);
		ButtonEffect(btnNextDanhMucSach);
		if(subWindow == NHAP_SACH){
			ButtonEffect(btnNhapSoLuongSach);
		}else if(subWindow == THEM_SACH){
			ButtonEffect(btnThemSach);
		}else if(subWindow == HIEU_CHINH_SACH){
			ButtonEffect(btnHieuChinhSach);
			ButtonEffect(btnBackToNhapSach);
		}
		
	}

	// Su kien Click chuot trai 
	if(GetAsyncKeyState(VK_LBUTTON)){
		ItemLeftMouseClick();
		
		if(Edit != NULL){
			int n = strlen(Edit->content);
			Edit->content[n] = ' ';
			Edit->draw();
			Edit->content[n] = '\0';
		}
		
		if(curMenu == btnQLDauSach.id){
			
			if(edTimDauSach.isMouseHover(mx, my)){
				Edit = &edTimDauSach;
			}else if(btnPrevDauSach.isMouseHover(mx, my)){
				if(curPageDauSach > 1){
					--curPageDauSach;
					ClearLayoutListDauSach();
					DrawList();
				}
			}else if(btnNextDauSach.isMouseHover(mx, my)){
				if(curPageDauSach < totalPageDauSach){
					++curPageDauSach;
					ClearLayoutListDauSach();
					DrawList();
				}
			}else if(btnClearTimDauSach.isMouseHover(mx, my)){
				memset(edTimDauSach.content, 0 , sizeof(edTimDauSach.content));
				edTimDauSach.draw();
				DrawList();
			}
			
			// man hinh Them dau sach
			if(Window == THEM_DAU_SACH){
				
				if(btnThemDauSach.isMouseHover(mx, my)){
					// Them dau sach
					// check truoc khi add
					if(CheckDauSach()){
						DauSach *dausach = new DauSach(edThemISBN.trim(), 
									edThemTenSach.trim(), 
									edThemSoTrang.toInt(), 
									edThemTacGia.trim(), 
									edThemNXB.toInt(), 
									edThemTheLoai.trim());
					
						AddDauSach(DSDS, dausach);
						ClearLayoutListDauSach();
						
						if(strlen(edTimDauSach.content) > 0){
							GetListNodes(DSDS, edTimDauSach.content, sizeListIndexDauSachSearch);
						}
						
						DrawList();
						ClearContentThemDauSach();
						strcpy(mess, "Them dau sach thanh cong!");
					}
					DrawThemDauSach();
				}
				
				if(edThemISBN.isMouseHover(mx, my)){
					Edit = &edThemISBN;
				}else if(edThemTenSach.isMouseHover(mx, my)){
					Edit = &edThemTenSach;
				}else if(edThemSoTrang.isMouseHover(mx, my)){
					Edit = &edThemSoTrang;
				}else if(edThemTacGia.isMouseHover(mx, my)){
					Edit = &edThemTacGia;
				}else if(edThemNXB.isMouseHover(mx, my)){
					Edit = &edThemNXB;
				}else if(edThemTheLoai.isMouseHover(mx, my)){
					Edit = &edThemTheLoai;
				}
				
				
			}else if(Window == HIEU_CHINH_DAU_SACH){
				if(btnHieuChinhDauSach.isMouseHover(mx, my)){
					// Hieu chinh dau sach
					if(CheckHieuChinhDauSach()){
						DauSach *dausach = new DauSach(edHieuChinhISBN.content, 
									edHieuChinhTenSach.trim(), 
									edHieuChinhSoTrang.toInt(), 
									edHieuChinhTacGia.trim(), 
									edHieuChinhNXB.toInt(), 
									edHieuChinhTheLoai.trim());
						UpdateDauSach(DSDS, dausach, curDauSach);
						ClearLayoutListDauSach();
						
						if(strlen(edTimDauSach.content) > 0){
							GetListNodes(DSDS, edTimDauSach.content, sizeListIndexDauSachSearch);
						}
						
						DrawList();
						ClearContentHieuChinhDauSach();
						curDauSach = -1;
						strcpy(mess, "Hieu chinh dau sach thanh cong!");
					}
					DrawHieuChinhDauSach();
				}
				
				if(curDauSach != -1){
					if(edHieuChinhISBN.isMouseHover(mx, my)){
						// khong cho phep chinh sua ISBN
//						Edit = &edHieuChinhISBN;
					}else if(edHieuChinhTenSach.isMouseHover(mx, my)){
						Edit = &edHieuChinhTenSach;
					}else if(edHieuChinhSoTrang.isMouseHover(mx, my)){
						Edit = &edHieuChinhSoTrang;
					}else if(edHieuChinhTacGia.isMouseHover(mx, my)){
						Edit = &edHieuChinhTacGia;
					}else if(edHieuChinhNXB.isMouseHover(mx, my)){
						Edit = &edHieuChinhNXB;
					}else if(edHieuChinhTheLoai.isMouseHover(mx, my)){
						Edit = &edHieuChinhTheLoai;
					}
				}

				
			}else if(Window == DANH_MUC_SACH){
				if(btnPrevDanhMucSach.isMouseHover(mx, my)){
					if(curPageSach > 1){
						--curPageSach;
						ClearLayoutDanhMucSach();
						DrawDanhMucSach();
					}
				}else if(btnNextDanhMucSach.isMouseHover(mx, my)){
					if(curPageSach < totalPageSach){
						++curPageSach;
						ClearLayoutDanhMucSach();
						DrawDanhMucSach();
					}
				}
				
				if(subWindow == NHAP_SACH){
					if(btnNhapSoLuongSach.isMouseHover(mx, my)){
						if(CheckSoLuongSach()){
							totalNhapSach = edNhapSoLuongSach.toInt();
							curNhapSach = 1;
							subWindow = THEM_SACH;
							memset(edThemViTriSach.content, 0, sizeof(edThemViTriSach.content));
							strcpy(mess, "");
							DrawThemSach();
						}
					}
					
					if(edNhapSoLuongSach.isMouseHover(mx, my)){
						Edit = &edNhapSoLuongSach;
					}
					
				}else if(subWindow == THEM_SACH){
					if(btnThemSach.isMouseHover(mx, my)){
						// Check them sach
						if(CheckSach()){
							Sach sach(edThemMaSach.content, edThemTrangThaiSach.toInt(), edThemViTriSach.content);
							InsertLast_NodeSach(DSDS.nodes[curDauSach]->First, sach);
							DSDS.nodes[curDauSach]->soluong ++;
//							printf("So luong: %d \n", DSDS.nodes[curDauSach]->soluong);
							
							ClearContentThemSach();
							ClearRightLayout();
							++curNhapSach;
							
							strcpy(mess, "Them sach thanh cong!");
							DrawThemSach();
							
							if(curNhapSach > totalNhapSach){
								ClearContentNhapSoLuongSach();
								subWindow = NHAP_SACH;
								curNhapSach = -1;
								totalNhapSach = 0;
								DrawNhapSach();
							}
							
						}else{
							DrawThemSach();
						}
						
						DrawDanhMucSach();
					}
					
					if(edThemTrangThaiSach.isMouseHover(mx, my)){
						Edit = &edThemTrangThaiSach;
					}else if(edThemViTriSach.isMouseHover(mx, my)){
						Edit = &edThemViTriSach;
					}
					
				}else if(subWindow == HIEU_CHINH_SACH){
					if(btnHieuChinhSach.isMouseHover(mx, my)){
						if(CheckHieuChinhSach()){
							// update
							NodeSach *nodeSelect = GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1) + curSach);
							Sach sach(edHieuChinhMaSach.content, edHieuChinhTrangThaiSach.toInt(), edHieuChinhViTriSach.content);
							UpdateNodeSach(nodeSelect, sach);
							ClearRightLayout();
							strcpy(mess, "Hieu chinh sach thanh cong!");
							DrawDanhMucSach();
						}
						DrawHieuChinhSach();
					}else if(btnBackToNhapSach.isMouseHover(mx, my)){
						subWindow = NHAP_SACH;
						DrawNhapSach();
					}
					
					
					if(edHieuChinhTrangThaiSach.isMouseHover(mx, my) && canEditTrangThai){
						Edit = &edHieuChinhTrangThaiSach;
					}else if(edHieuChinhViTriSach.isMouseHover(mx, my)){
						Edit = &edHieuChinhViTriSach;
					}
				}

			}
		}
		
		if(btnBackToThemDauSach.isMouseHover(mx, my)){
			Window = THEM_DAU_SACH;
			ClearRightLayout();
			ClearContentThemDauSach();
			strcpy(mess, "");
			DrawThemDauSach();
		}else if(btnQuayVe.isMouseHover(mx, my)){
			SetMenuSelect(0);
		}else if(btnQLSach.isMouseHover(mx, my)){
			
		}else if(btnThongTin.isMouseHover(mx, my)){
			
		}else if(btnThoat.isMouseHover(mx, my)){
			
		}
	}else if(GetAsyncKeyState(VK_RBUTTON)){
		ItemRightMouseClick();
	}
	
}

void ItemLeftMouseClick(){
	if(curItem != -1){
		Window = HIEU_CHINH_DAU_SACH;
		strcpy(mess, "");
		if(strlen(edTimDauSach.content) == 0) GetHieuChinhDauSach(13*(curPageDauSach-1) + curItem);
		else GetHieuChinhDauSach(listIndexDauSachSearch[13*(curPageDauSach-1) + curItem]);
	}
	if(Window == DANH_MUC_SACH){
		if(curItemSach != -1){
			subWindow = HIEU_CHINH_SACH;
			curSach = curItemSach;
			strcpy(mess, "");
			
			ClearContentHieuChinhSach();
			
			NodeSach *nodeSelect = GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1) + curSach);
			strcpy(edHieuChinhMaSach.content, nodeSelect->sach.MASACH);
			char ch[2];
			itoa(nodeSelect->sach.trangthai, ch, 10);
			strcpy(edHieuChinhTrangThaiSach.content, ch);
			strcpy(edHieuChinhViTriSach.content, nodeSelect->sach.vitri);
			
			if(nodeSelect->sach.trangthai == 0){
				canEditTrangThai = true;
			}else{
				canEditTrangThai = false;
			}
	
			DrawHieuChinhSach();
		}
	}
}

void ItemRightMouseClick(){
	if(curItem != -1){
		Window = DANH_MUC_SACH;
		subWindow = NHAP_SACH;
		Edit = NULL;
		
		if(strlen(edTimDauSach.content) == 0) curDauSach = 13*(curPageDauSach-1) + curItem;
		else curDauSach = listIndexDauSachSearch[13*(curPageDauSach-1) + curItem];
		
		curPageSach = 1;
		Edit = NULL;
		memset(mess, 0, sizeof(mess));
		ClearRightLayout();
		ClearContentNhapSoLuongSach();
		AutoCreateMaSach();
		DrawDanhMucSach();
		DrawNhapSach();
	}
}

void ItemEvent(){
	if(mx > XDS[0] && mx < XDS[6] && my > 230-8 && my < 230+13*40-8){
		
		if(curItem != GetItemPosition(my)){
			if(curItem != -1){
				// khoi phuc item
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XDS[0], 230 + curItem*40 - 8, XDS[6], 230+(curItem+1)*40-8);
				
				setbkcolor(BG_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_COLOR);
				
				if(strlen(edTimDauSach.content) == 0){
					DrawItemDauSach((curPageDauSach-1)*13 + curItem, -1);
				}else{
					DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach-1)*13 + curItem], curItem);
				}
				
				DrawBorderList();
			}
			
			// Ve item hien tai
			curItem = GetItemPosition(my);
			if(curItem != -1){
				setfillstyle(SOLID_FILL, LINE);
				bar(XDS[0], 230 + curItem*40 - 8, XDS[6], 230+(curItem+1)*40-8);
				
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(TEXT_COLOR);
				
				if(strlen(edTimDauSach.content) == 0){
					DrawItemDauSach((curPageDauSach-1)*13 + curItem, -1);
				}else{
					DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach-1)*13 + curItem], curItem);
				}
				
				DrawBorderList();
			}
		}
	}else{
		if(curItem != -1){
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XDS[0], 230 + curItem*40 - 8, XDS[6], 230+(curItem+1)*40-8);
			setbkcolor(BG_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_COLOR);
			
			if(strlen(edTimDauSach.content) == 0){
				DrawItemDauSach((curPageDauSach-1)*13 + curItem, -1);
			}else{
				DrawItemDauSach(listIndexDauSachSearch[(curPageDauSach-1)*13 + curItem], curItem);
			}
				
			DrawBorderList();
			curItem = -1;
		}
	}
	
	// important
	if(Window != DANH_MUC_SACH) return;
	
	if(mx > XDMS[0] && mx < XDMS[3] && my > 140-8 && my < 140+10*40-8){
		
		if(curItemSach != GetItemSachPosition(my)){
			if(curItemSach != -1){
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XDMS[0], 140 + curItemSach*40 - 8, XDMS[3], 140+(curItemSach+1)*40-8);
				
				setbkcolor(BG_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_COLOR);
				DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1) + curItemSach)->sach, curItemSach);
				DrawBorderListSach();
			}
			curItemSach = GetItemSachPosition(my);
			if(curItemSach != -1){
				setfillstyle(SOLID_FILL, LINE);
				bar(XDMS[0], 140 + curItemSach*40 - 8, XDMS[3], 140+(curItemSach+1)*40-8);
				
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(TEXT_COLOR);
				DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1) + curItemSach)->sach, curItemSach);
				DrawBorderListSach();
			}
		}
	}else{
		if(curItemSach != -1){
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XDMS[0], 140 + curItemSach*40 - 8, XDMS[3], 140+(curItemSach+1)*40-8);
				
			setbkcolor(BG_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_COLOR);
			DrawItemSach(GetNodeSach(DSDS.nodes[curDauSach]->First, 10*(curPageSach-1) + curItemSach)->sach, curItemSach);
			DrawBorderListSach();
			curItemSach = -1;
		}
	}
}
  
int GetItemPosition(int y){
	int pos = (y-230+8)/40;
	int i = 13*(curPageDauSach-1) + pos;
	if(strlen(edTimDauSach.content) == 0){
		if(i >= DSDS.n) return -1;
	}else{
		if(i >= sizeListIndexDauSachSearch) return -1;
	}
	return pos;
}

int GetItemSachPosition(int y){
	int pos = (y-140+8)/40;
	int i = 10*(curPageSach-1) + pos;
	if(i >= DSDS.nodes[curDauSach]->soluong) return -1;
	else return pos;
}

void ClearLayoutListDauSach(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDS[0], 150, XDS[6], 750);
}

void ClearLayoutSach(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0]-2, 610, w, 880);
}

void ClearLayoutDanhMucSach(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDMS[0]-2, 70, w, 535);
}

void DrawBorderList(){
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(BORDER_COLOR);
	rectangle(XDS[0], 150, XDS[6], 750);
	line(XDS[0], 150 + 25 + 2*20, XDS[6], 150 + 25 + 2*20);
	for(int i=0; i < 6; i++){
		line(XDS[i+1], 150, XDS[i+1], 750);
	}
}
 
void DrawBorderListSach(){
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(BORDER_COLOR);
	rectangle(XDMS[0], 70, XDMS[3], 535);
	line(XDMS[0], 135, XDMS[3], 135);
	line(XDMS[1], 70, XDMS[1], 535);
	line(XDMS[2], 70, XDMS[2], 535);
} 

void DrawList(){
	ClearLayoutListDauSach();
	DrawBorderList();
	char ch[6][20] = {"ISBN", "Ten sach", "So trang", "Tac gia", "NXB", "The loai"};
		
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	for(int i=0; i < 6; i++){
		setbkcolor(BG_COLOR);
		outtextxy(XDS[i] + (XDS[i+1]-XDS[i])/2 - textwidth(ch[i])/2, 170, ch[i]);
	}
	
	// caculate Total Page 
	// Num per page = 13
	
	
	setcolor(TEXT_COLOR);
	if(strlen(edTimDauSach.content) == 0){
		totalPageDauSach = (DSDS.n-1) / 13 + 1;
		for(int i = 13*(curPageDauSach-1); i < 13*curPageDauSach ; i++){
			if (i >= DSDS.n) break;
			DrawItemDauSach(i, -1);
		}
	}else{
		totalPageDauSach = (sizeListIndexDauSachSearch-1) / 13 + 1;
		int j = 0;
		for(int i = 13*(curPageDauSach-1); i < 13*curPageDauSach ; i++){
			if (i >= sizeListIndexDauSachSearch) break;
			DrawItemDauSach(listIndexDauSachSearch[i], j++);
		}
	}
	
	// num page
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	char chPage[20];
	sprintf(chPage, "TRANG %d / %d", curPageDauSach, totalPageDauSach);
	outtextxy((XDS[0]+XDS[6])/2 - textwidth(chPage)/2, 785, chPage);
	
	// tips
	setcolor(TIPS);
	rectangle(XDS[0], 880, XDS[6], 980);
	outtextxy(30, 890, "Click chuot trai: Hieu chinh dau sach");
	outtextxy(30, 920, "Click chuot phai: Xem thong tin, danh muc sach");
}
   
void DrawItemDauSach(int i, int j){
	char chs[10];
	outtextxy(XDS[0]+5, 230 + (j!=-1?j:(i%13)) *40, DSDS.nodes[i]->ISBN);
	outtextxy(XDS[1]+5, 230 + (j!=-1?j:(i%13)) *40, DSDS.nodes[i]->tensach);
	if(DSDS.nodes[i]->sotrang > 0){
		itoa(DSDS.nodes[i]->sotrang, chs, 10);
		outtextxy(XDS[2]+20, 230 + (j!=-1?j:(i%13)) *40, chs);
	}
	outtextxy(XDS[3]+5, 230 + (j!=-1?j:(i%13)) *40, DSDS.nodes[i]->tacgia);
	if(DSDS.nodes[i]->nxb > 0){
		itoa(DSDS.nodes[i]->nxb, chs, 10);
		outtextxy(XDS[4]+20, 230 + (j!=-1?j:(i%13)) *40, chs);
	}
	outtextxy(XDS[5]+5, 230 + (j!=-1?j:(i%13)) *40, DSDS.nodes[i]->theloai);
}

void DrawItemSach(Sach &sach, int i){
	outtextxy(XDMS[0] + 30, 140 + (i%10)*40, sach.MASACH);
	outtextxy(XDMS[1] + 30, 140 + (i%10)*40, TrangThaiSach[sach.trangthai]);
	outtextxy(XDMS[2] + 30, 140 + (i%10)*40, sach.vitri);
}



