void RunDocGia(){
	strcpy(mess, "");
	ClearContentThemDocGia();
	
	DrawDanhSachDocGia();
	
	btnSapXepTen.isChoose = sortDGByName;
	btnSapXepMaThe.isChoose = !btnSapXepTen.isChoose; 
	
	btnSapXepTen.isHover = sortDGByName;
	btnSapXepMaThe.isHover = !sortDGByName;
	
	btnSapXepTen.draw();
	btnSapXepMaThe.draw();
	
	btnTatCaDocGia.isHover = true;
	btnTatCaDocGia.isChoose = true;
	btnDocGiaQuaHan.isChoose = false;
	btnDocGiaQuaHan.isHover = false;
	
	btnTatCaDocGia.draw();
	btnDocGiaQuaHan.draw();
	
//	DSDG.GetAllDocGia(TreeDocGia);
	
	DrawListDocGia(true);
	Window = THEM_DOC_GIA;
	if(btnTatCaDocGia.isChoose) DrawThemDocGia();
	
	setlinestyle(SOLID_LINE, 0, 1);
	line(XDG[6]+10, 0, XDG[6]+10, h);
}

void DocGiaEvent(){
	
	ButtonEffect(btnQuayVe);
	ButtonEffect(btnTatCaDocGia);
	ButtonEffect(btnDocGiaQuaHan);
	
	if(Window == THEM_DOC_GIA){
		ButtonEffect(btnThemDocGia);
	}else if(Window == HIEU_CHINH_DOC_GIA){
		ButtonEffect(btnHieuChinhDocGia);
		ButtonEffect(btnBackToThemDocGia);
	}else if(Window == XOA_DOC_GIA){
		if(curDG != -1){
			ButtonEffect(btnXacNhanXoaDocGia);
			ButtonEffect(btnHuyXoaDocGia);
		}
		ButtonEffect(btnBackToThemDocGia);
	}
	
	ItemDocGiaEvent();
	
	if(btnTatCaDocGia.isChoose){
		ButtonEffect(btnPrevDocGia);
		ButtonEffect(btnNextDocGia);
		ButtonEffect(btnSapXepTen);
		ButtonEffect(btnSapXepMaThe);
	}else{
		ButtonEffect(btnPrevDocGiaQH);
		ButtonEffect(btnNextDocGiaQH);
	}


	if(GetAsyncKeyState(VK_LBUTTON)){
		if(btnQuayVe.isMouseHover(mx, my)){
			SetMenuSelect(0);
		}
		// Switch
		ButtonSwitchClick();
		ItemDGLeftMouseClick();
		
		if(Window == THEM_DOC_GIA){
			if(btnThemDocGia.isMouseHover(mx, my)){
				if(CheckThemDocGia()){
					DocGia docgia(edThemMaTheDocGia.toInt(), 
								edThemHoDocGia.trim(), 
								edThemTenDocGia.trim(), 
								edThemPhaiDocGia.toInt(), 
								edThemTrangThaiTheDocGia.toInt());
								
					InsertDocGia(TreeDocGia, docgia);
					insertAfter_ID(nodeStart, edThemMaTheDocGia.toInt());
					
					strcpy(mess, "Them doc gia thanh cong!");
					ClearContentThemDocGia();
					ClearLayoutListDocGia();
					DrawListDocGia(true);
					DrawThemDocGia();
				}else{
					DrawThemDocGia(false);
				}
				
			}
				
			if(edThemHoDocGia.isMouseHover(mx, my)){
				Edit = &edThemHoDocGia;
			}else if(edThemTenDocGia.isMouseHover(mx, my)){
				Edit = &edThemTenDocGia;
			}else if(edThemPhaiDocGia.isMouseHover(mx, my)){
				Edit = &edThemPhaiDocGia;
			}else if(edThemTrangThaiTheDocGia.isMouseHover(mx, my)){
				Edit = &edThemTrangThaiTheDocGia;
			}
				
		}else if(Window == HIEU_CHINH_DOC_GIA){
			if(btnHieuChinhDocGia.isMouseHover(mx, my)){
				if(curDG != -1 && CheckHieuChinhDocGia()){
					DocGia docgia(edHieuChinhMaTheDocGia.toInt(), 
									edHieuChinhHoDocGia.trim(), 
									edHieuChinhTenDocGia.trim(), 
									edHieuChinhPhaiDocGia.toInt(), 
									edHieuChinhTrangThaiTheDocGia.toInt());
					UpdateDocGia(TreeDocGia, docgia);
					strcpy(mess, "Hieu chinh doc gia thanh cong!");
					ClearContentHieuChinhDocGia();
					ClearLayoutListDocGia();
					DrawListDocGia(true);
					curDG = -1;
				}
				DrawHieuChinhDocGia();
			}
				
			if(curDG != -1){
				if(edHieuChinhHoDocGia.isMouseHover(mx, my)){
					Edit = &edHieuChinhHoDocGia;
				}else if(edHieuChinhTenDocGia.isMouseHover(mx, my)){
					Edit = &edHieuChinhTenDocGia;
				}else if(edHieuChinhPhaiDocGia.isMouseHover(mx, my)){
					Edit = &edHieuChinhPhaiDocGia;
				}else if(edHieuChinhTrangThaiTheDocGia.isMouseHover(mx, my)){
					Edit = &edHieuChinhTrangThaiTheDocGia;
				}	
			}
				
		}else if(Window == XOA_DOC_GIA){
			if(btnXacNhanXoaDocGia.isMouseHover(mx, my) && curDG != -1){

				// neu doc gia k muon sach nao thi co the xoa
				if(DSDG.nodes[curDG]->mt.total == 0){
					delete_ID(DSDG.nodes[curDG]->MATHE);
					RemoveDocGia(TreeDocGia, DSDG.nodes[curDG]->MATHE);
					
					strcpy(mess, "Xoa doc gia thanh cong!");
					curDG = -1;
					ClearLayoutListDocGia();
					DrawListDocGia(true);
					ClearRightLayout();
					DrawXoaDocGia(curDG);
				}else{
					// Doc gia dang muon sach -> k the xoa
					strcpy(mess, "Doc gia da muon sach nen khong the xoa!");
					DrawXoaDocGia(curDG);
				}

			}else if(btnHuyXoaDocGia.isMouseHover(mx, my)){
				Window = THEM_DOC_GIA;
				ClearRightLayout();
				strcpy(mess, "");
				DrawThemDocGia();
			}
		}
		if(btnBackToThemDocGia.isMouseHover(mx, my) && Window != THEM_DOC_GIA){
			strcpy(mess, "");
			Window = THEM_DOC_GIA;
			ClearRightLayout();
			DrawThemDocGia();
		}
		
		if(btnTatCaDocGia.isChoose){
			// Tat ca Doc gia - MODE
		
			if(btnPrevDocGia.isMouseHover(mx, my)){
				if(curPageDG > 1){
					curPageDG--;
					ClearLayoutListDocGia();
					DrawListDocGia();
				}
			}else if(btnNextDocGia.isMouseHover(mx, my)){
				if(curPageDG < totalPageDG){
					curPageDG ++;
					ClearLayoutListDocGia();
					DrawListDocGia();
				}
			}
	 		
		}else{
			// Doc Gia Qua Han - MODE
			if(btnPrevDocGiaQH.isMouseHover(mx, my)){
				if(curPageDGQuaHan > 1){
					curPageDGQuaHan--;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}else if(btnNextDocGiaQH.isMouseHover(mx, my)){
				if(curPageDGQuaHan < totalPageDGQuaHan){
					curPageDGQuaHan ++;
					ClearLayoutListDocGiaQuaHan();
					DrawListDocGia();
				}
			}	
		}
		
	}else if(GetAsyncKeyState(VK_RBUTTON)){
		ItemDGRightMouseClick();
	}
}

void ButtonSwitchClick(){
	if(btnTatCaDocGia.isMouseHover(mx, my)){
		if(!btnTatCaDocGia.isChoose){
			btnDocGiaQuaHan.isChoose = false;
			btnTatCaDocGia.isChoose = true;
			curItemDG = -1;
			// Get list docgia
//			DSDG.GetAllDocGia(TreeDocGia);
			
			
			ClearLayoutListDocGiaQuaHan();
			DrawListDocGia(true);
//			Window = THEM_DOC_GIA;
//			DrawThemDocGia();
			DrawDanhSachDocGia();
			
			btnSapXepTen.isChoose = sortDGByName;
			btnSapXepMaThe.isChoose = !btnSapXepTen.isChoose; 
			
			btnSapXepTen.isHover = sortDGByName;
			btnSapXepMaThe.isHover = !sortDGByName;
			
			btnSapXepTen.draw();
			btnSapXepMaThe.draw();
		}
	}else if(btnDocGiaQuaHan.isMouseHover(mx, my)){
		if(!btnDocGiaQuaHan.isChoose){
			btnTatCaDocGia.isChoose = false;
			btnDocGiaQuaHan.isChoose = true;
			curItemDG = -1;
			// Get list docgia qua han
			DSDG.GetDocGiaQuaHan(TreeDocGia);
			
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(0, 70, 500, 500);
			ClearLayoutListDocGiaQuaHan();
			DrawListDocGia();
		}
	}
	
	if(btnSapXepTen.isMouseHover(mx, my)){
		if(!sortDGByName){
			sortDGByName = true;
			ClearLayoutListDocGia();
			DrawListDocGia();
		}
	}else if(btnSapXepMaThe.isMouseHover(mx, my)){
		if(sortDGByName){
			sortDGByName = false;
			ClearLayoutListDocGia();
			DrawListDocGia();
		}
	}
	btnSapXepTen.isChoose = sortDGByName;
	btnSapXepMaThe.isChoose = !sortDGByName;

}

void ItemDocGiaEvent(){
	if(mx > XDG[0] && mx < XDG[btnTatCaDocGia.isChoose?5:6] && my > 220-8 && my < 220+13*40-8){
		
		if(curItemDG != GetItemDocGiaPosition(my)){
			if(curItemDG != -1){
				// khoi phuc item
				setfillstyle(SOLID_FILL, BG_COLOR);
				bar(XDG[0], 220 + curItemDG*40 - 8, XDG[btnTatCaDocGia.isChoose?5:6], 220+(curItemDG+1)*40-8);
				
				setbkcolor(BG_COLOR);
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setcolor(TEXT_COLOR);
				
				if(btnTatCaDocGia.isChoose){
					DrawItemDocGia(*DSDG.nodes[(curPageDG-1)*13 + curItemDG], (curPageDG-1)*13 + curItemDG);
					DrawBorderDSDocGia();
				}
				else{
					DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan-1)*13 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan-1)*13 + curItemDG], (curPageDGQuaHan-1)*13 + curItemDG);
					DrawBorderDSDocGiaQuaHan();
				}
					
				
			}
			
			// Ve item hien tai
			curItemDG = GetItemDocGiaPosition(my);
			if(curItemDG != -1){
				setfillstyle(SOLID_FILL, LINE);
				bar(XDG[0], 220 + curItemDG*40 - 8, XDG[btnTatCaDocGia.isChoose?5:6], 220+(curItemDG+1)*40-8);
				
				settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
				setbkcolor(LINE);
				setcolor(TEXT_COLOR);
				
				if(btnTatCaDocGia.isChoose){
					DrawItemDocGia(*DSDG.nodes[(curPageDG-1)*13 + curItemDG], (curPageDG-1)*13 + curItemDG);
					DrawBorderDSDocGia();
				}
				else{
					DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan-1)*13 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan-1)*13 + curItemDG], (curPageDGQuaHan-1)*13 + curItemDG);
					DrawBorderDSDocGiaQuaHan();
				}
			}
		}
	}else{
		if(curItemDG != -1){
			// khoi phuc item
			setfillstyle(SOLID_FILL, BG_COLOR);
			bar(XDG[0], 220 + curItemDG*40 - 8, XDG[btnTatCaDocGia.isChoose?5:6], 220+(curItemDG+1)*40-8);
			setbkcolor(BG_COLOR);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
			setcolor(TEXT_COLOR);
			
			if(btnTatCaDocGia.isChoose){
				DrawItemDocGia(*DSDG.nodes[(curPageDG-1)*13 + curItemDG], (curPageDG-1)*13 + curItemDG);
				DrawBorderDSDocGia();
			}
			else{
				DrawItemDocGiaQuaHan(*DSDG.nodes[(curPageDGQuaHan-1)*13 + curItemDG], DSDG.soNgayQH[(curPageDGQuaHan-1)*13 + curItemDG], (curPageDGQuaHan-1)*13 + curItemDG);
				DrawBorderDSDocGiaQuaHan();
			}
			
			curItemDG = -1;
		}
	}
}

void AutoGenMaDocGia(){
	nodeStart = Node_ID_Random();
	if(nodeStart != NULL){
		int ranID = rand()%(nodeStart->next->id - nodeStart->id - 1) + nodeStart->id + 1;
		itoa(ranID, edThemMaTheDocGia.content, 10);
	}else{
		strcpy(edThemMaTheDocGia.content, "OVERFLOW");
	}
	
}

bool CheckThemDocGia(){
	if(strcmp(edThemMaTheDocGia.content, "OVERFLOW") == 0){
		strcpy(mess, "So luong doc gia dat gioi han");
		return false;
	}
	
	if(strlen(edThemHoDocGia.content) == 0){
		strcpy(mess, "Ho va ten dem khong duoc bo trong");
		Edit = &edThemHoDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edThemTenDocGia.content) == 0){
		strcpy(mess, "Ten khong duoc bo trong");
		Edit = &edThemTenDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edThemPhaiDocGia.content) == 0){
		strcpy(mess, "Phai khong duoc bo trong");
		Edit = &edThemPhaiDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edThemTrangThaiTheDocGia.content) == 0){
		strcpy(mess, "Trang thai the khong duoc bo trong");
		Edit = &edThemTrangThaiTheDocGia;
		Edit->draw();
		return false;
	}

	return true;
}
 
bool CheckHieuChinhDocGia(){
	if(strlen(edHieuChinhHoDocGia.content) == 0){
		strcpy(mess, "Ho va ten dem khong duoc bo trong");
		Edit = &edHieuChinhHoDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhTenDocGia.content) == 0){
		strcpy(mess, "Ten khong duoc bo trong");
		Edit = &edHieuChinhTenDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhPhaiDocGia.content) == 0){
		strcpy(mess, "Phai khong duoc bo trong");
		Edit = &edHieuChinhPhaiDocGia;
		Edit->draw();
		return false;
	}else if(strlen(edHieuChinhTrangThaiTheDocGia.content) == 0){
		strcpy(mess, "Trang thai the khong duoc bo trong");
		Edit = &edHieuChinhTrangThaiTheDocGia;
		Edit->draw();
		return false;
	}
	
	return true;
}

void ClearContentThemDocGia(){
	memset(edThemMaTheDocGia.content, 0, sizeof(edThemMaTheDocGia.content));	
	memset(edThemHoDocGia.content, 0, sizeof(edThemHoDocGia.content));	
	memset(edThemTenDocGia.content, 0, sizeof(edThemTenDocGia.content));	
	memset(edThemPhaiDocGia.content, 0, sizeof(edThemPhaiDocGia.content));	
	memset(edThemTrangThaiTheDocGia.content, 0, sizeof(edThemTrangThaiTheDocGia.content));	
}

void ClearContentHieuChinhDocGia(){
	memset(edHieuChinhMaTheDocGia.content, 0, sizeof(edHieuChinhMaTheDocGia.content));	
	memset(edHieuChinhHoDocGia.content, 0, sizeof(edHieuChinhHoDocGia.content));	
	memset(edHieuChinhTenDocGia.content, 0, sizeof(edHieuChinhTenDocGia.content));	
	memset(edHieuChinhPhaiDocGia.content, 0, sizeof(edHieuChinhPhaiDocGia.content));	
	memset(edHieuChinhTrangThaiTheDocGia.content, 0, sizeof(edHieuChinhTrangThaiTheDocGia.content));	
}
 
void DrawDanhSachDocGia(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDG[0]+XDG[5])/2-textwidth(DocGiaTitle)/2, 15, DocGiaTitle);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	outtextxy(20, 100, "Sap xep theo:");
	
	btnQuayVe.draw();
	btnTatCaDocGia.draw();
	btnDocGiaQuaHan.draw();
	btnPrevDocGia.draw();
	btnNextDocGia.draw();
	btnSapXepTen.draw();
	btnSapXepMaThe.draw();
}

void ClearLayoutListDocGia(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDG[0]-5, 150-5, XDG[5]+5, 820);
}

void ClearLayoutListDocGiaQuaHan(){
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDG[0]-5, 150-5, XDG[6]+5, 820);
}

void DrawBorderDSDocGia(){	
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(BORDER_COLOR);
	rectangle(XDG[0], 150, XDG[5], 750);
	line(XDG[0], 150 + 25 + 2*20, XDG[5], 150 + 25 + 2*20);
	for(int i=0; i < 5; i++){
		line(XDG[i+1], 150, XDG[i+1], 750);
	}
	
	char ch[6][20] = {"Ma the", "Ho", "Ten", "Phai", "Trang thai the"};
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	for(int i=0; i < 5; i++){
		setbkcolor(BG_COLOR);
		outtextxy(XDG[i] + (XDG[i+1]-XDG[i])/2 - textwidth(ch[i])/2, 170, ch[i]);
	}
}

void DrawBorderDSDocGiaQuaHan(){
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(BORDER_COLOR);
	rectangle(XDG[0], 150, XDG[6], 750);
	line(XDG[0], 150 + 25 + 2*20, XDG[6], 150 + 25 + 2*20);
	for(int i=0; i < 6; i++){
		line(XDG[i+1], 150, XDG[i+1], 750);
	}
	
	char ch[7][20] = {"Ma the", "Ho", "Ten", "Phai", "Trang thai the", "So ngay qua han"};
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	for(int i=0; i < 6; i++){
		setbkcolor(BG_COLOR);
		outtextxy(XDG[i] + (XDG[i+1]-XDG[i])/2 - textwidth(ch[i])/2, 170, ch[i]);
	}
}
 
void DrawListDocGia(bool reload){
	char chPage[20];
	
	if(reload && btnTatCaDocGia.isChoose) DSDG.GetAllDocGia(TreeDocGia);
	
	if(btnTatCaDocGia.isChoose){

		DrawBorderDSDocGia();
	
		if(sortDGByName){
			DSDG.SortTenDocGia();
		}else{
			DSDG.SortMaTheDocGia();	
		}
		totalPageDG = (DSDG.n-1)/13 + 1;
		for(int i=13*(curPageDG-1); i < 13*curPageDG; i++){
			if(i >= DSDG.n) break;
			DrawItemDocGia(*DSDG.nodes[i], i);
		}
		
		// num page
		
		sprintf(chPage, "TRANG %d / %d", curPageDG, totalPageDG);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		outtextxy((XDG[5]+XDG[0])/2 - textwidth(chPage)/2, 785, chPage);
		
		btnPrevDocGia.draw();
		btnNextDocGia.draw();
		
	}else if(btnDocGiaQuaHan.isChoose){
		DrawBorderDSDocGiaQuaHan();
//		DSDG.GetDocGiaQuaHan(TreeDocGia);
		
		totalPageDGQuaHan = (DSDG.n-1)/13 + 1;
		for(int i=13*(curPageDGQuaHan-1); i < 13*curPageDGQuaHan; i++){
			if(i >= DSDG.n) break;
			DrawItemDocGiaQuaHan(*DSDG.nodes[i], DSDG.soNgayQH[i], i);
		}
		
		// num page
		sprintf(chPage, "TRANG %d / %d", curPageDGQuaHan, totalPageDGQuaHan);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		outtextxy((XDG[0]+XDG[6])/2 - textwidth(chPage)/2, 785, chPage);
		
		
		btnPrevDocGiaQH.draw();
		btnNextDocGiaQH.draw();
	}
	
	setcolor(TIPS);
	rectangle(10, 850, XDG[5], 950);
	outtextxy(20, 870, "Click chuot trai: Hieu chinh doc gia");
	outtextxy(20, 900, "Click chuot phai: Xoa doc gia");
}

void DrawThemDocGia(bool genNewID){
	setbkcolor(BG_COLOR);
	setfillstyle(WIDE_DOT_FILL, GREEN);
	bar(XDG[6]+15, 210, w-15, 280);
	
	setcolor(BORDER_COLOR);
	setlinestyle(SOLID_FILL, 0, 3);
	rectangle(XDG[6]+20, 210, w-15, 700);
	line(XDG[6]+20, 280, w-15, 280);
	line(XDG[6]+20, 650, w-15, 650);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDG[6]+20+w-15)/2 - textwidth(ThemDauSach)/2, 245 - textheight(ThemDocGia)/2, ThemDocGia);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	outtextxy(XDG[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDG[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	outtextxy(XDG[6]+70 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);
	
	if(genNewID) AutoGenMaDocGia();
	strcpy(edThemTrangThaiTheDocGia.content, "1");
	
	edThemMaTheDocGia.draw();
	edThemHoDocGia.draw();
	edThemTenDocGia.draw();
	edThemPhaiDocGia.draw();
	edThemTrangThaiTheDocGia.draw();
	
	btnThemDocGia.draw();
} 
 
void GetHieuChinhDocGia(int i){
	curDG = i;
	ClearContentHieuChinhDocGia();
	
	char ch[10];
	itoa(DSDG.nodes[i]->MATHE, ch, 10);
	strcpy(edHieuChinhMaTheDocGia.content, ch);
	strcpy(edHieuChinhHoDocGia.content, DSDG.nodes[i]->ho);
	strcpy(edHieuChinhTenDocGia.content, DSDG.nodes[i]->ten);
	itoa(DSDG.nodes[i]->phai, ch, 10);
	strcpy(edHieuChinhPhaiDocGia.content, ch);
	itoa(DSDG.nodes[i]->trangthai, ch, 10);
	strcpy(edHieuChinhTrangThaiTheDocGia.content, ch);
	// Clear
	ClearRightLayout();
	DrawHieuChinhDocGia();
}
 
void DrawHieuChinhDocGia(){
	setbkcolor(BG_COLOR);
	setfillstyle(WIDE_DOT_FILL, GREEN);
	bar(XDG[6]+15, 210, w-15, 280);
	
	setcolor(BORDER_COLOR);
	setlinestyle(SOLID_FILL, 0, 3);
	rectangle(XDG[6]+20, 210, w-15, 700);
	line(XDG[6]+20, 280, w-15, 280);
	line(XDG[6]+20, 650, w-15, 650);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDG[6]+20+w-14)/2 - textwidth(HieuChinhDocGia)/2, 245 - textheight(HieuChinhDocGia)/2, HieuChinhDocGia);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(TIPS);
	outtextxy(XDG[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDG[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	outtextxy(XDG[6]+70 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);
	
	edHieuChinhMaTheDocGia.draw();
	edHieuChinhHoDocGia.draw();
	edHieuChinhTenDocGia.draw();
	edHieuChinhPhaiDocGia.draw();
	edHieuChinhTrangThaiTheDocGia.draw();
	
	btnHieuChinhDocGia.draw();
	btnBackToThemDocGia.draw();
} 

void DrawXoaDocGia(int i){
	setbkcolor(BG_COLOR);
	setfillstyle(WIDE_DOT_FILL, GREEN);
	bar(XDG[6]+20, 210, w-15, 280);
	
	setcolor(BORDER_COLOR);
	setlinestyle(SOLID_FILL, 0, 3);
	rectangle(XDG[6]+20, 210, w-15, 700);
	line(XDG[6]+20, 280, w-15, 280);
	line(XDG[6]+20, 650, w-15, 650);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy((XDG[6]+20+w-15)/2 - textwidth(XoaDocGia)/2, 245 - textheight(XoaDocGia)/2, XoaDocGia);
	
	if(i != -1){
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_COLOR);
		curDG = i;
		
		char ch[50];
		sprintf(ch, "%s %s", DSDG.nodes[i]->ho, DSDG.nodes[i]->ten);
		outtextxy(XDG[6]+100, 300, "Doc gia :");
		outtextxy(XDG[6]+400, 300, ch);
		
		itoa(DSDG.nodes[i]->MATHE, ch, 10);
		outtextxy(XDG[6]+100, 340, "Ma the :");
		outtextxy(XDG[6]+400, 340, ch);
		
		outtextxy(XDG[6]+100, 380, "Phai :");
		outtextxy(XDG[6]+400, 380, PhaiDocGia[DSDG.nodes[i]->phai]);
		
		outtextxy(XDG[6]+100, 420, "Trang thai the :");
		outtextxy(XDG[6]+400, 420, TTTDocGia[DSDG.nodes[i]->trangthai]);
		
		outtextxy(XDG[6]+100, 460, "So sach dang muon :");
		itoa(DSDG.nodes[i]->mt.chuaTra, ch, 10);
//		itoa(SoSachDangMuon(TreeDocGia, DSDG.nodes[i]->MATHE), ch, 10);
		outtextxy(XDG[6]+400, 460, ch);
		
		outtextxy(XDG[6]+100, 500, "Tong so sach da muon :");
		itoa(DSDG.nodes[i]->mt.total, ch, 10);
//		itoa(SoSachDaMuon(TreeDocGia, DSDG.nodes[i]->MATHE), ch, 10);
		outtextxy(XDG[6]+400, 500, ch);
		
		btnXacNhanXoaDocGia.draw();
		btnHuyXoaDocGia.draw();
	}
	
	setcolor(TIPS);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	outtextxy(XDG[6]+50, 675-textheight(ThongBao)/2, ThongBao);
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(XDG[6]+50 + textwidth(ThongBao), 675-textheight(ThongBao)/2, w-20, 675+textheight(ThongBao)/2);
	outtextxy(XDG[6]+70 + textwidth(ThongBao), 675-textheight(ThongBao)/2, mess);
	
	btnBackToThemDocGia.draw();
}

void ItemDGLeftMouseClick(){
	if(curItemDG != -1){
		strcpy(mess, "");
		Window = HIEU_CHINH_DOC_GIA;
		if(btnTatCaDocGia.isChoose)
			GetHieuChinhDocGia(13*(curPageDG-1) + curItemDG);
		else
			GetHieuChinhDocGia(13*(curPageDGQuaHan-1) + curItemDG);
	}
}

void ItemDGRightMouseClick(){
	if(curItemDG != -1){
		strcpy(mess, "");
		Window = XOA_DOC_GIA;
		ClearRightLayout();
		if(btnTatCaDocGia.isChoose)
			DrawXoaDocGia(13*(curPageDG-1) + curItemDG);
		else
			DrawXoaDocGia(13*(curPageDGQuaHan-1) + curItemDG);
		
	}
}
 
int GetItemDocGiaPosition(int y){
	int pos = (y-220+8)/40;
	int i;
	if(btnTatCaDocGia.isChoose){
		i = 13*(curPageDG-1) + pos;
	}else{
		i = 13*(curPageDGQuaHan-1) + pos;
	}
	if(i >= DSDG.n) return -1;
	return pos;
}

void DrawItemDocGia(DocGia &docgia, int i){
	setcolor(TEXT_COLOR);
	i %= 13;
	char ch[6];
	itoa(docgia.MATHE, ch, 10);
	outtextxy(XDG[0] + 10, 220 + i*40, ch);
	outtextxy(XDG[1] + 10, 220 + i*40, docgia.ho);
	outtextxy(XDG[2] + 10, 220 + i*40, docgia.ten);
	outtextxy(XDG[3] + 30, 220 + i*40, PhaiDocGia[docgia.phai]);
	outtextxy(XDG[4] + 10, 220 + i*40, TTTDocGia[docgia.trangthai]);
}

void DrawItemDocGiaQuaHan(DocGia &docgia, int soNgayQH, int i){
	DrawItemDocGia(docgia, i);
	char ch[4];
	sprintf(ch, "%d", soNgayQH);
	outtextxy(XDG[5]+50, 220 + i*40, ch);
}









