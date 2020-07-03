
struct MuonTra{
	char MASACH[20];
	char ngaymuon[10];
	char ngaytra[10];
	int trangthai;
		/*
		 * 0: Dang muon
		 * 1: Da tra
		 * 2: Lam mat
		 */
	MuonTra(){
	}
	MuonTra(char* ms, char* muon, char* tra, int tt){
		strcpy(MASACH, ms);
		strcpy(ngaymuon, muon);
		strcpy(ngaytra, tra);
		trangthai = tt;
	}
};

struct NodeMuonTra{
	MuonTra muontra;
	NodeMuonTra *prev;
	NodeMuonTra *next;
};

struct DS_MuonTra{
	NodeMuonTra *First = NULL;
	NodeMuonTra *Last = NULL;
	
	/*
	 * thuoc tinh them 
	 */
	int total;	// tong so luong sach da muon
	int chuaTra;	// so luong sach dang muon + lam mat
	
	DS_MuonTra(){
		First = NULL;
		Last = NULL;
		total = 0;
		chuaTra = 0;
	}
	~DS_MuonTra(){
	}
};
 
NodeMuonTra* CreateNewNode_MuonTra(MuonTra &mt){
	NodeMuonTra *newNode = new NodeMuonTra;
	
	newNode->muontra = mt;
	newNode->prev = NULL;
	newNode->next = NULL;
	
	return newNode;
}
 
void InsertFirst_MuonTra(DS_MuonTra &DSMT, MuonTra &mt){
	NodeMuonTra *newNode = CreateNewNode_MuonTra(mt);
	newNode->next = DSMT.First;
	
	if(DSMT.First == NULL) DSMT.Last = newNode;
	else DSMT.First->prev = newNode;
	DSMT.First = newNode;
}

void InsertLast_MuonTra(DS_MuonTra &DSMT, MuonTra &mt){
	NodeMuonTra *newNode = CreateNewNode_MuonTra(mt);
	if(DSMT.First == NULL){
		DSMT.First = newNode;
		DSMT.Last = newNode;
	}else{
		DSMT.Last->next = newNode;
		newNode->prev = DSMT.Last;
		DSMT.Last = newNode;
	}
	
	DSMT.total++;
	if(mt.trangthai != 1) DSMT.chuaTra++;
}

// Tra sach + lam mat sach
void Update_MuonTra(DS_MuonTra &DSMT, MuonTra &mt){
	for(NodeMuonTra *node = DSMT.Last; node != NULL; node = node->prev){
		if(strcmp(node->muontra.MASACH, mt.MASACH) == 0 && strlen(node->muontra.ngaytra) == 0){
			node->muontra = mt;
			if(mt.trangthai == 1) DSMT.chuaTra--;
			return;
		}
	}	
}

void ClearList_MuonTra(DS_MuonTra &DSMT){
	NodeMuonTra *removeNode;
	while(DSMT.First != NULL){
		removeNode = DSMT.First;
		DSMT.First = removeNode->next;
		delete removeNode;
	}
}

void DeleteAllMuonTra(DS_MuonTra &DSMT){
	NodeMuonTra *removeNode;
	while(DSMT.First != NULL){
		removeNode = DSMT.First;
		DSMT.First = DSMT.First->next;
		delete removeNode;
	}
}
