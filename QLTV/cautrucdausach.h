struct DauSach{
	char ISBN[11];
	char tensach[23];
	int sotrang;
	char tacgia[13];
	int nxb;
	char theloai[13];
	NodeSach *First = NULL;
	
	/*
	 * Cac thuoc tinh them
	 */
	int soluotmuon; 	// so luot muon sach
	int soluong;	// so luong sach cua dau sach
	
	DauSach(){
	}
	DauSach(char *isbn, char* ten, int st, char *tg, int xb, char* tl){
		strcpy(ISBN, isbn);
		strcpy(tensach, ten);
		sotrang = st;
		strcpy(tacgia, tg);
		nxb = xb;
		strcpy(theloai, tl);
		First = NULL;
		
		soluong = 0;
		soluotmuon = 0;
	}

};

struct DS_DauSach{
	int n;
	DauSach *nodes[MAX_SIZE_DAUSACH];
	
	DS_DauSach(){
		n = 0;
	}
	~DS_DauSach(){
		printf("Free memory dau sach + dms \n");
		while(n) {
			DeleteAllNodeSach(nodes[n-1]->First);
			delete nodes[--n];
		}
	}
};

int listIndexDauSachSearch[MAX_SIZE_DAUSACH];
int sizeListIndexDauSachSearch = 0;

void InsertDauSach(DS_DauSach &DSDS, DauSach *dausach, int position);
void AddDauSach(DS_DauSach &DSDS, DauSach *dausach);
void DeleteDauSach(DS_DauSach &DSDS, char* ISBN);
int ExistsDauSach(DS_DauSach &DSDS, char* ISBN);

/*
 * Them DauSach vao vi tri position trong DSDS
 */
void InsertDauSach(DS_DauSach &DSDS, DauSach *dausach, int position){
	if(position < 0){
		printf("Vi tri them dau sach khong hop le \n");
		return;
	}
	// neu position >= DSDS.n thi se Insert vao cuoi danh sach
	for(int i=DSDS.n; i>position; i--){
		DSDS.nodes[i] = DSDS.nodes[i-1];
	}
	DSDS.nodes[position] = dausach;
	DSDS.n++; 
}

/*
 * Them DauSach khi nguoi dung nhap
 * Ham AddDauSach se tu dong tim vi tri Insert thich hop
 */
void AddDauSach(DS_DauSach &DSDS, DauSach *dausach){
	if(DSDS.n > MAX_SIZE_DAUSACH)
		printf("DSDS day \n");
	else{
		for(int i=0; i<DSDS.n; i++){
			if(strcmp(dausach->theloai, DSDS.nodes[i]->theloai) < 0){
				InsertDauSach(DSDS, dausach, i);
				return;
			}
		
			if(strcmp(dausach->theloai, DSDS.nodes[i]->theloai) == 0){
				if(strcmp(dausach->tensach, DSDS.nodes[i]->tensach) <= 0){
					InsertDauSach(DSDS, dausach, i);
					return;
				}
			}
		}
		
		DSDS.nodes[DSDS.n++] = dausach;
	}
}

void InsertLastDauSach(DS_DauSach &DSDS, DauSach *dausach){
	// su dung khi doc file
	if(DSDS.n > MAX_SIZE_DAUSACH)
		printf("DSDS day \n");
	else{
		DSDS.nodes[DSDS.n++] = dausach;
	}
}


int ExistsDauSach(DS_DauSach &DSDS, char* ISBN){
	for(int i=0; i<DSDS.n; i++){
		if(strcmp(DSDS.nodes[i]->ISBN, ISBN) == 0){
			return i;
		}
	}
	return -1;
}

/*
 * Cap nhat Dau Sach tai vi tri i, noi dung la dausach
 */
void UpdateDauSach(DS_DauSach &DSDS, DauSach *dausach, int i){
	if(i >= DSDS.n || i < 0) printf("Khong the update dau sach");
	else {
		// Gan dia chi con tro DMS First vao dausach moi
		dausach->First = DSDS.nodes[i]->First;
		dausach->soluong = DSDS.nodes[i]->soluong;
		dausach->soluotmuon = DSDS.nodes[i]->soluotmuon;
		
		delete DSDS.nodes[i];
		for(int j=i; j<DSDS.n; j++){
			DSDS.nodes[j] = DSDS.nodes[j+1];
		}
		DSDS.n--;
		AddDauSach(DSDS, dausach);
	}
}

/*
 * Xoa Dau Sach theo ISBN
 */
//void DeleteDauSach(DS_DauSach &DSDS, char* ISBN){
//	// Tim vi tri Dau sach muon xoa
//	int i = ExistsDauSach(DSDS, ISBN);
//	if(i == -1){
//		printf("Khong the xoa \n");
//	}else{
//		for(;i<DSDS.n-1; i++){
//			DSDS.nodes[i] = DSDS.nodes[i+1];
//		}
//		DSDS.n--;
//	}
//}

bool IsPrefix(const char* pre, const char* str){
//	return strncmp(pre, str, strlen(pre)) == 0;
	if(strlen(pre) > strlen(str)) return false;
	for(int i=0; i<strlen(pre); i++){
		if(pre[i] != str[i]) return false;
	}
	return true;
}

/*
 * Loc danh sach cac Dau Sach co ten bat dau la: strFind
 * Luu vi tri cua cac Dau Sach vao 1 mang: listIndexDauSachSearch[]
 * Size cua list se duoc luu vao bien: m
 */
void GetListNodes(DS_DauSach &DSDS, const char* strFind, int &m){
	m = 0;
	for(int i=0; i<DSDS.n; i++){
		if(IsPrefix(strFind, DSDS.nodes[i]->tensach)){
			listIndexDauSachSearch[m++] = i;
		}
	}
}

int GetSepPosition(char *s){
	int n = strlen(s);
	for(int i=0; i<n; i++){
		if(s[i] == '-') return i;
	}
	return -1;
}

/*
 * Tim DauSach theo masach
 * Tra ve node cua DauSach can tim
 */
DauSach* GetDauSach(DS_DauSach &DSDS, char* masach){
	NodeSach *node;
	
	int sepPos = GetSepPosition(masach);
	char isbn[sepPos+1];
	int indexSach=0;
	for(int i=0; i<sepPos; i++) isbn[i] = masach[i];
	isbn[sepPos] = '\0';
	for(int i=sepPos+1; i<strlen(masach); i++){
		indexSach = indexSach*10 + (masach[i]-'0');
	}

	for(int i=0; i<DSDS.n; i++){
		if(strcmp(DSDS.nodes[i]->ISBN, isbn) == 0){
			if(indexSach < DSDS.nodes[i]->soluong) return DSDS.nodes[i];
			else break;
		}
	
	}
	return NULL;
}

/*
 * Tim DauSach theo masach
 * Tra ve index cua DauSach can tim
 */
int GetIndexDauSach(DS_DauSach &DSDS, char* masach){
	int sepPos = GetSepPosition(masach);
	char isbn[sepPos+1];
	for(int i=0; i<sepPos; i++) isbn[i] = masach[i];
	isbn[sepPos] = '\0';
	
	for(int i=0; i<DSDS.n; i++){	
		if(strcmp(DSDS.nodes[i]->ISBN, isbn) == 0){
			return i;
		}
	}
	return -1;
}

/*
 * Struct thong ke so luot muon sach cua moi Dau Sach
 */
struct LuotMuonSach{
	int indexDS;	// vi tri cua DauSach
	int cnt;		// so luot muon
};	

struct TopSach{
	int n;
	LuotMuonSach *list;
	
	TopSach(DS_DauSach &DSDS){
		n = DSDS.n;
		list = new LuotMuonSach[n];
		for(int i=0; i<n; i++){
			list[i].indexDS = i;
			list[i].cnt = DSDS.nodes[i]->soluotmuon;
		}
		sort();
	}
	~TopSach(){
		delete[] list;
	}
	
	// Phan doan
	void partition(int low, int high){
		int i = low, j = high;
		LuotMuonSach tmp;
		int pivot = list[(low+high)/2].cnt;
		do{
			while(list[i].cnt > pivot) i++;
			while(list[j].cnt < pivot) j--;
			if(i <= j){
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
				i++; j--;
			}
		}while(i <= j);
		
		if(low < j) partition(low, j);
		if(i < high) partition(i, high);
	}
	void sort(){
		// Sap xep theo thu tu cnt giam dan
		// Su dung QuickSort
		partition(0, n-1);
	}
};




