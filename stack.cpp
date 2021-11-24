#include <bits/stdc++.h>
#include <sys/time.h>

void
die(const char *s)
{
	std::cerr << "Error: " << s << std::endl;
	exit(1);
}

template <typename T>
struct LinkedListStackNode
{
	LinkedListStackNode *prev;
	T data;

	LinkedListStackNode(T data)
	{
		this->data = data;
		this->prev = NULL;
	}
};

template <typename T>
struct LinkedListStack
{
	LinkedListStackNode<T> *top;
	size_t size;

	LinkedListStack() : top(NULL), size(0) {}

	void
	print()
	{
		LinkedListStackNode<T> *curr = top;

		while (curr != NULL) {
			std::cout << curr->data << " ";
			curr = curr->prev;
		}

		std::cout << std::endl;
	}

	void
	push(const T &data)
	{
		LinkedListStackNode<T> *node = new LinkedListStackNode<T>(data);

		node->prev = top;
		top = node;
		size++;
	}

	void
	push(T &&data)
	{
		LinkedListStackNode<T> *node = new LinkedListStackNode<T>(std::move(data));

		node->prev = top;
		top = node;
		size++;
	}

	T
	pop()
	{
		if (size == 0)
		{
			die("Stack is empty");
		}

		LinkedListStackNode<T> *node = top;
		top = top->prev;
		size--;

		T data = node->data;
		delete node;

		return data;
	}
};

template <typename T>
struct ArrayStack
{
	T *array;
	size_t size;
	size_t capacity;

	ArrayStack(size_t init_capacity = 16)
		: array(new T[init_capacity]), capacity(init_capacity),
		  size(0) {}

	void
	print()
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << array[i] << " ";
		}

		std::cout << std::endl;
	}

	void
	reallocate(size_t new_capacity)
	{
		T *new_array = new T[new_capacity];

		for (size_t i = 0; i < size; i++)
		{
			new_array[i] = array[i];
		}

		delete[] array;
		array = new_array;
		capacity = new_capacity;
	}

	void
	push(const T &data)
	{
		if (size == capacity)
		{
			reallocate(capacity * 2);
		}

		array[size++] = data;
	}

	void
	push(T &&data)
	{
		if (size == capacity)
		{
			reallocate(capacity * 2);
		}

		array[size++] = std::move(data);
	}

	T
	pop()
	{
		if (size == 0)
		{
			die("Stack is empty");
		}

		T data = array[--size];

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



	LinkedListStack<int> ll_stack;

	// LinkedListStack Push

	uint64_t start = now();

	for (int i = 0; i < bench_size; i++)
	{
		ll_stack.push(i);
	}

	result.ll_push_time = now() - start;

	// LinkedListStack Pop

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		ll_stack.pop();
	}

	result.ll_pop_time = now() - start;



	ArrayStack<int> array_stack;

	// ArrayStack Push

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		array_stack.push(i);
	}

	result.arr_push_time = now() - start;

	// ArrayStack Pop

	start = now();

	for (int i = 0; i < bench_size; i++)
	{
		array_stack.pop();
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

	std::cout << "LinkedListStack push" << std::endl;

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

	std::cout << "LinkedListStack pop" << std::endl;

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

	std::cout << "ArrayStack push" << std::endl;

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

	std::cout << "ArrayStack pop" << std::endl;

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