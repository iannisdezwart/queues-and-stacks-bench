#include <bits/stdc++.h>
#include <sys/time.h>

void
die(const char *s)
{
	std::cerr << "Error: " << s << std::endl;
	exit(1);
}

template <typename T>
struct LinkedListQueueNode
{
	LinkedListQueueNode *next;
	T data;

	LinkedListQueueNode(const T &data)
	{
		this->data = data;
		this->next = NULL;
	}

	LinkedListQueueNode(T &&data)
	{
		this->data = std::move(data);
		this->next = NULL;
	}
};

template <typename T>
struct LinkedListQueue
{
	LinkedListQueueNode<T> *head;
	LinkedListQueueNode<T> *tail;
	size_t size;

	LinkedListQueue() : head(NULL), tail(NULL), size(0) {}

	void
	print()
	{
		LinkedListQueueNode<T> *curr = head;

		while (curr != NULL)
		{
			std::cout << curr->data << " ";
			curr = curr->next;
		}

		std::cout << std::endl;
	}

	void
	push(const T &data)
	{
		if (size == 0)
		{
			head = new LinkedListQueueNode<T>(data);
			tail = head;
		}
		else
		{
			tail->next = new LinkedListQueueNode<T>(data);
			tail = tail->next;
		}

		size++;
	}

	void
	push(T &&data)
	{
		if (size == 0)
		{
			head = new LinkedListQueueNode<T>(std::move(data));
			tail = head;
		}
		else
		{
			tail->next = new LinkedListQueueNode<T>(std::move(data));
			tail = tail->next;
		}

		size++;
	}

	T
	pop()
	{
		if (size == 0)
		{
			die("Cannot pop an empty queue");
		}

		T data = head->data;
		LinkedListQueueNode<T> *temp = head;
		head = head->next;
		delete temp;
		size--;

		return data;
	}
};

template <typename T>
struct ArrayQueue
{
	T *array;
	size_t size;
	size_t head;
	size_t tail;
	size_t capacity;

	ArrayQueue(size_t init_capacity = 16)
		: capacity(init_capacity), array(new T[init_capacity]),
		  size(0), head(0), tail(0) {}

	void
	print()
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << array[(head + i) % capacity] << " ";
		}

		std::cout << std::endl;
	}

	void
	reallocate(size_t new_capacity)
	{
		T *new_array = new T[new_capacity];

		for (size_t i = 0; i < size; i++)
		{
			new_array[i] = array[(head + i) % size];
		}

		delete[] array;
		capacity = new_capacity;
		array = new_array;
		head = 0;
		tail = size % size;
	}

	void
	push(const T &data)
	{
		if (size == capacity)
		{
			reallocate(capacity * 2);
		}

		array[tail] = data;

		tail++;
		tail %= capacity;
		size++;
	}

	void
	push(T &&data)
	{
		if (size == capacity)
		{
			reallocate(capacity * 2);
		}

		array[tail] = std::move(data);

		tail++;
		tail %= capacity;
		size++;
	}

	T
	pop()
	{
		if (size == 0)
		{
			die("Cannot pop an empty queue");
		}

		T data = array[head];
		head++;
		head %= capacity;
		size--;

		return data;
	}
};

uint64_t
now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

struct Result
{
	uint64_t ll_push_time;
	uint64_t ll_pop_time;
	uint64_t arr_push_time;
	uint64_t arr_pop_time;
};

Result
benchmark(int bench_size)
{
	std::cout << "Benchmarking size " << bench_size << std::endl;

	Result result;



	LinkedListQueue<int> ll_queue;

	// LinkedListQueue Push

	uint64_t start = now();

	for (int i = 0; i < bench_size; i++)
	{
		ll_queue.push(i);
	}

	result.ll_push_time = now() - start;

	// LinkedListQueue Pop

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		ll_queue.pop();
	}

	result.ll_pop_time = now() - start;



	ArrayQueue<int> array_queue;

	// ArrayQueue Push

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		array_queue.push(i);
	}

	result.arr_push_time = now() - start;

	// ArrayQueue Pop

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		array_queue.pop();
	}

	result.arr_pop_time = now() - start;



	return result;
}

#define MIN_BENCH_SIZE 15
#define MAX_BENCH_SIZE 25

int
main()
{
	std::vector<Result> results;

	for (size_t i = MIN_BENCH_SIZE; i <= MAX_BENCH_SIZE; i++)
	{
		results.push_back(benchmark(1 << i));
	}

	std::cout << "GRAPH DATA: " << std::endl;

	for (size_t i = MIN_BENCH_SIZE; i <= MAX_BENCH_SIZE; i++)
	{
		std::cout << (1 << i);

		if (i == MAX_BENCH_SIZE)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}

	std::cout << "LinkedListQueue push" << std::endl;

	for (size_t i = 0; i < results.size(); i++)
	{
		std::cout << results[i].ll_push_time;

		if (i == results.size() - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}

	std::cout << "LinkedListQueue pop" << std::endl;

	for (size_t i = 0; i < results.size(); i++)
	{
		std::cout << results[i].ll_pop_time;

		if (i == results.size() - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}

	std::cout << "ArrayQueue push" << std::endl;

	for (size_t i = 0; i < results.size(); i++)
	{
		std::cout << results[i].arr_push_time;

		if (i == results.size() - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}

	std::cout << "ArrayQueue pop" << std::endl;

	for (size_t i = 0; i < results.size(); i++)
	{
		std::cout << results[i].arr_pop_time;

		if (i == results.size() - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}
}
