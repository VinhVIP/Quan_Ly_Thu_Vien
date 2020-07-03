template <typename Type>
struct Queue{
	int n;
	int fr, rear;
	Type *nodes;	

	Queue(){
		n = 0;
		fr = 0; rear = 0;
		nodes = new Type[QUEUE_CAPACITY];
	}
	~Queue(){
		delete[] nodes;
	}	
	bool full(){
		if(n >= QUEUE_CAPACITY) return true;
		return false;
	}	
	bool empty(){
		return n == 0;
	}
	int size(){
		return n;
	}
	void clear(){
		n = 0;
	}
	Type front(){
		return nodes[fr];
	}	
	bool push(Type value){
		if(full()) return false;
		nodes[rear] = value;
		rear = (rear + 1) % QUEUE_CAPACITY;
		n++;
		return true;
	}	
	bool pop(){
		if(empty()) return false;
		else{
			fr = (fr+1) % QUEUE_CAPACITY;
			n--;
		}
		return true;
	}
};
