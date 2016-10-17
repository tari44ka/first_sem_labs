#ifndef LIST_H
#define LIST_H
struct Element{
	int value;
	Element *prev;
	Element *next;
};

class List{
	public:
		List();
		~List();
		void addInTail(int value);
		void moveHead(int position);
		void print();
	private:
		Element *head;
		Element *tail;		

		void moveForward(int position);
		void moveBack(int position);
};

#endif /*LIST_H*/
