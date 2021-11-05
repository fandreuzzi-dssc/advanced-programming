#include <iostream>
#include <string>
#include <vector>

struct X {
	int val;

	void out(const std::string& s, int nv) {
		std::cout << this << " -> " << s << ": " << val << "(" << nv << ")" << std::endl;
	}

	X() { out("X()", 0); val=0; }
	X(int v) { val=v; out("X(int)", v); }
	X(const X& x) { val=x.val; out("X(X&)", x.val); }
	X& operator=(const X& a) {
		out("X::operator=()", a.val); val=a.val; return *this;
	}

	~X() { out("~X()", 0); }
};

X glob(2);
// 0x10daad160 -> X(int): 2(2)

X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

int main() {
	X loc {4}; // local variable
	// 0x7ffee2157398 -> X(int): 4(4)

	X loc2{loc}; // copy constructor
	// 0x7ffee2157390 -> X(X&): 4(4)

	loc = X{5}; // copy assignement
	// 0x7ffee2157380 -> X(int): 5(5)
	// 0x7ffee2157398 -> X::operator=(): 4(5)
	// 0x7ffee2157380 -> ~X(): 5(0)

	loc2 = copy(loc); // call by value and return
	// 0x7ffee2157370 -> X(X&): 5(5)
	// 0x7ffee2157378 -> X(X&): 5(5)
	// 0x7ffee2157390 -> X::operator=(): 4(5)
	// 0x7ffee2157378 -> ~X(): 5(0)
	// 0x7ffee2157370 -> ~X(): 5(0)

	loc2 = copy2(loc);
	// probably there have been several optimizations here, several steps are missing
	// 0x7ffee2157360 -> X(X&): 5(5) (passing loc to copy2)
	// 0x7ffee2157368 -> X(X&): 5(5) (passing the copy to the function operator=)
	// 0x7ffee2157390 -> X::operator=(): 5(5)
	// 0x7ffee2157368 -> ~X(): 5(0)
	// 0x7ffee2157360 -> ~X(): 5(0)

	X loc3{6};
	// 0x7ffee2157358 -> X(int): 6(6)

	X& r = ref_to(loc); // call by reference and return
	// nothing?

	delete make(7);
	// 0x7ffee2157278 -> X(int): 7(7)
	// 0x7f8c81c058c0 -> X(X&): 7(7) (created with new on the FS)
	// 0x7ffee2157278 -> ~X(): 7(0)
	// 0x7f8c81c058c0 -> ~X(): 7(0)

	delete make(8);
	// 0x7ffee2157278 -> X(int): 8(8)
	// 0x7f8c81c058c0 -> X(X&): 8(8)
	// 0x7ffee2157278 -> ~X(): 8(0)
	// 0x7f8c81c058c0 -> ~X(): 8(0)

	std::vector<X> v(4); // default values
	// 0x7f8c81c058c0 -> X(): 8(0)
	// 0x7f8c81c058c4 -> X(): 0(0)
	// 0x7f8c81c058c8 -> X(): 0(0)
	// 0x7f8c81c058cc -> X(): 0(0)

	XX loc4;
	// 0x7ffee2157330 -> X(): 0(0)
	// 0x7ffee2157334 -> X(): 0(0)

	X* p = new X{9}; // free store
	// 0x7f8c81c058d0 -> X(int): 9(9)

	delete p;
	// 0x7f8c81c058d0 -> ~X(): 9(0)

	X* pp = new X[5]; // array of X on free store
	// 0x7f8c81c058e8 -> X(): 0(0)
	// 0x7f8c81c058ec -> X(): 0(0)
	// 0x7f8c81c058f0 -> X(): 0(0)
	// 0x7f8c81c058f4 -> X(): 0(0)
	// 0x7f8c81c058f8 -> X(): 0(0)

	delete[] pp;
	// 0x7f8c81c058f8 -> ~X(): 0(0)
	// 0x7f8c81c058f4 -> ~X(): 0(0)
	// 0x7f8c81c058f0 -> ~X(): 0(0)
	// 0x7f8c81c058ec -> ~X(): 0(0)
	// 0x7f8c81c058e8 -> ~X(): 0(0)

	// 0x7ffee2157334 -> ~X(): 0(0) loc4.a
	// 0x7ffee2157330 -> ~X(): 0(0) loc4.b
	// 0x7f8c81c058cc -> ~X(): 0(0) (v[3])
	// 0x7f8c81c058c8 -> ~X(): 0(0) (v[2])
	// 0x7f8c81c058c4 -> ~X(): 0(0) (v[1])
	// 0x7f8c81c058c0 -> ~X(): 0(0) (v[0])
	// 0x7ffee2157358 -> ~X(): 6(0) (loc3)
	// 0x7ffee2157390 -> ~X(): 5(0) (loc2)
	// 0x7ffee2157398 -> ~X(): 5(0) (loc)
}

// 0x10daad160 -> ~X(): 2(0)
