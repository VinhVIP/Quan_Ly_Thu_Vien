struct Sach{
	char MASACH[15];
	int trangthai;
		/*
		 * 0: Cho muon duoc
		 * 1: Da cho muon
		 * 2: Da thanh ly
		 */
	char vitri[20];
	
	Sach(){
	}
	Sach(char ms[20], int tt, char vt[30]){
		strcpy(MASACH, ms);
		trangthai = tt;
		strcpy(vitri, vt);
	}
};

// NODE Sach - DSLK don
struct NodeSach{
	Sach sach;
	NodeSach *next;
};


void InsertFirst_NodeSach(NodeSach* &First, Sach &sach);
void InsertAfter_NodeSach(NodeSach* &node, Sach &sach);
void InsertLast_NodeSach(NodeSach* &First, Sach &sach);

/*
 * Cap phat bo nho cho Node moi
 */
NodeSach* CreateNodeSach(Sach &sach){
	NodeSach *node = new NodeSach;
	node->sach = sach;
	return node;
}

void InsertFirst_NodeSach(NodeSach* &First, Sach &sach){
	NodeSach *newNode = CreateNodeSach(sach);
	
	newNode->next = First;
	First = newNode;
}

void InsertAfter_NodeSach(NodeSach* &node, Sach &sach){
	NodeSach *newNode = CreateNodeSach(sach);
	
	newNode->next = node->next;
	node->next = newNode;
}

void InsertLast_NodeSach(NodeSach* &First, Sach &sach){
	if(First == NULL) InsertFirst_NodeSach(First, sach);
	else{
		NodeSach *last;
		for(last = First; last->next != NULL; last = last->next);
		InsertAfter_NodeSach(last, sach);
	}
}

/*
 * Lay NodeSach tai vi tri position
 */
NodeSach* GetNodeSach(NodeSach* First, int position){
	NodeSach* node = First;
	for(int i=0; node != NULL; node = node->next){
		if(i == position) break;
		++i;
	}
	return node;
}

/*
 * Lay NodeSach theo masach
 */
NodeSach* GetNodeSach(NodeSach *First, char* masach){
	for(NodeSach *node = First; node != NULL; node = node->next){
		if(strcmp(node->sach.MASACH, masach) == 0) return node;
	}
	return NULL;
}


void UpdateNodeSach(NodeSach* &node, Sach &sach){
	if(node == NULL) printf("K the update");
	else{
		node->sach = sach;
	}
}

Sach* GetSach(NodeSach *First, char* masach){
	for(NodeSach *node = First; node != NULL; node = node->next){
		if(strcmp(node->sach.MASACH, masach) == 0) return &node->sach;
	}
	return NULL;
}

void DeleteAllNodeSach(NodeSach* &First){
	NodeSach *removeNode;
	while(First != NULL){
		removeNode = First;
		First = First->next;
		delete removeNode;
	}
}



