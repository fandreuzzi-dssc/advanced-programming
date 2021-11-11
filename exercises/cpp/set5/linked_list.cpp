#include <memory>
#include <iostream>

#define DEBUG 1

enum class Insertion_method { push_back, push_front };

// we pre-declare the templated friend
// https://isocpp.org/wiki/faq/templates#template-friends
template<typename T> class List;
template<typename T> std::ostream& operator<< (std::ostream& o, const List<T>& x);

template <typename T>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method is used to fill the list
  int insert(const T& v, const Insertion_method m);

  // return the size of the list
  std::size_t size() const { return _size; }

  // delete all the nodes of the list
  void reset() { if(head) delete head.release(); }

  List() {
#if DEBUG
	std::cout << "[LL] " << this << " Initializing empty" << std::endl;
#endif
  }
  List(const T& v) {
	insert(v, Insertion_method::push_back);
#if DEBUG
	std::cout << "[LL] " << this << " Initializing with head=" << v << std::endl;
#endif
  }

  List(const List<T>& other) { // copy constructor
#if DEBUG
        std::cout << "[LL] " << this << " Copy-inizializing from " << other << std::endl;
#endif
	_size = other.size();

	if (other.size() > 0) {
		node *n = new node(*other.head.get());
		head = std::unique_ptr<node>(n);
	} else head = std::unique_ptr<node>(nullptr);
  }

  List(List<T>&& other) {
#if DEBUG
        std::cout << "[LL] " << this << " Move-inizializing from " << other << std::endl;
#endif

	_size = other.size();
	head = std::move(other.head);
  }

  List<T>& operator=(List<T>&& other) {
#if DEBUG
        std::cout << "[LL] " << this << " Move-assigning from " << other << std::endl;
#endif

	_size = other.size();

//	if (head) delete head.get();
	head = std::move(other.head);

	return *this;
  }

  ~List() {
#if DEBUG
        std::cout << "[LL] Destroying: " << this << std::endl;
#endif
	reset();
  }
 private:
  struct node {
    T value;
    std::unique_ptr<node> next = nullptr;

    node(const T& v): value(v) {
#if DEBUG
	std::cout << "[Node] " << this << " Initializing with value " << v << std::endl; 
#endif
    }

    // we can assume that nobody has the ownership of the node
    node(const T& v, std::unique_ptr<node>& ptr): value(v), next(std::move(ptr)) { 
#if DEBUG
	std::cout << "[Node] " << this << " Inizializing with value=" << value << ", next=" << next << std::endl;
#endif
    }

    // copy constructor
    // note that the order of the debug is going to be reversed since the output
    // happens at the end of the body of the recursive function
    node(const node& other) {
	value = other.value;
	// recursively construct a new hierarchy of linked nodes
	if (other.next)	next = std::unique_ptr<node>(new node(*other.next.get()));
#if DEBUG
        std::cout << "[Node] " << this << " Copy-inizializing with value=" << value << ", next=" << next << std::endl;
#endif
    }

    ~node() {
#if DEBUG
	std::cout << "[Node] " << this << " Destroying, value=" << value << ", next=" << next << std::endl;
#endif
        if (next) delete next.release();
    }
  };

  // we can assume that the list is not empty
  void push_back(const T& v) {
	node *n = head.get();
	while (n->next) n = n->next.get();
	n->next = std::unique_ptr<node>(new node(v));
  }

  void push_front(const T& v) {
	// this already points to the former front
	node *new_front = new node(v, head);
	head = std::unique_ptr<node>(new_front);
  }

  std::unique_ptr<node> head;
  std::size_t _size = 0;

  friend std::ostream& operator<< <>(std::ostream& os, const List<T>& l);
};

template <typename T>
int List<T>::insert(const T& v, const Insertion_method m) {
	if (!size()) head = std::unique_ptr<node>(new node(v));
	else {
		switch(m) {
			case Insertion_method::push_back: push_back(v);
				break;
			case Insertion_method::push_front: push_front(v);
				break;
			default: return -1;
		}
	}
	_size += 1;
	return 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
	os << "{";

	if (l.size() > 0) {
		auto n = l.head.get();
		os << n->value << " ";

		if (n->next) n = n->next.get();
		while (n->next) { os << "-> " << n->value << " "; n = n->next.get(); }

		os << (n != l.head.get() ? "-> " : "") << n->value;
	}

	return os << "}";
}

int main() {
	List<int> l;
	std::cout << "l: " << l << std::endl;

	std::cout << "Inserting items into the LL" << std::endl;
	for(int i = 3; i > 0; i--) l.insert(i, static_cast<Insertion_method>(i%2 == 0));
	std::cout << l << std::endl;

	std::cout << "Copy initialize: " << l << std::endl;
	List<int> l2 = l;
	std::cout << "l2: " << l2 << std::endl;

	std::cout << "We change a little bit the first list to perform several other marvelous experiments:" << std::endl;
	for(int i = 6; i > 2; i--) l.insert(i, static_cast<Insertion_method>(i%2 == 0));

	std::cout << "Move initialize: " << l << std::endl;
	l2 = std::move(l);
	std::cout << "Result: " << l2 << std::endl;
}
