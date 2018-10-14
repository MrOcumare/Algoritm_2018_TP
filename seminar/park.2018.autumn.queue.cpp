#include <cassert>
#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////////
// Queue.h

class Queue {
public:
	Queue() = default;
	Queue(const Queue& other) = delete;
	Queue(Queue&& other) { *this = std::move(other); }
	~Queue();

	Queue& operator=(const Queue& other) = delete;
	Queue& operator=(Queue&& other);
	
	Queue MakeCopy() const;

	void Push(int value);
	int Pop();

	bool IsEmpty() const { return !head; }

private:
	struct Node;

	Node* head = nullptr;
	Node* tail = nullptr;

	void clean();
};

////////////////////////////////////////////////////////////////////////
// Queue.cpp

struct Queue::Node {
	int Value = 0;
	Node* Next = nullptr;

	Node() = default;
	Node(int value) : Value(value) {}
};

Queue::~Queue()
{
	clean();
}

Queue& Queue::operator=(Queue&& queue)
{
	clean();

	std::swap(head, queue.head);
	std::swap(tail, queue.tail);

	return *this;
}

void Queue::clean()
{
	while (head) {
		Node* node = head;
		head = head->Next;
		delete node;
	}

	tail = nullptr;
}

Queue Queue::MakeCopy() const
{
	Queue copy;
	Node* node = head;
	while (node) {
		copy.Push(node->Value);
		node = node->Next;
	}

	return copy;
}

void Queue::Push(int value)
{
	Node* node = new Node(value);

	if (IsEmpty()) {
		head = tail = node;
		return;
	}

	tail->Next = node;
	tail = node;
}

int Queue::Pop()
{
	assert(!IsEmpty());

	int result = head->Value;

	Node* node = head;
	if (head != tail) {
		head = head->Next;
	} else {
		head = tail = nullptr;
	}

	delete node;
	return result;
}

Queue create_queue()
{
	Queue queue;
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);

	return queue;
}

void test()
{
	auto queue = create_queue();

	assert(queue.Pop() == 3);
	assert(queue.Pop() == 4);
	assert(!queue.IsEmpty());
	assert(queue.Pop() == 5);
	assert(queue.IsEmpty());
}


//////////////////////////////////////////////////////////////////
//main.cpp

struct Operation {
	int Code = 0;
	int Value = 0;
};

bool do_operation(Queue& queue, Operation op)
{
	switch (op.Code) {
	case 3:
		queue.Push(op.Value);
		return true;
	case 2: {
			const int result = !queue.IsEmpty() ? queue.Pop() : -1;
			return result == op.Value;
		}
	}

	assert(false);
	return false;
}

int main()
{
	int n = 0;
	std::cin >> n;

	Queue queue;
	for (int i = 0; i < n; i++) {
		Operation op;
		std::cin >> op.Code >> op.Value;
		if (!do_operation(queue, op)) {
			std::cout << "NO";
			return 0;
		}
	}

	std::cout << "YES";

	return 0;
}