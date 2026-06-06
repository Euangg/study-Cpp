
struct B;
struct A {
	int a{ 0 };
	void test(B b){}
};

struct B {
	int b{ 0 };
	void test(A a) {}
};


int main() {
	A a;
}