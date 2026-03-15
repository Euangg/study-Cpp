class base {
public:
	base() {};
	//base() = delete;
	//~base() = delete;

	base(const base&) = delete;
	base& operator=(const base&) = delete;
};

int main() {
	base b1;
	//¿½±´¹¹Ôì
	//base b2(b1);
	//base b2 = b1;

	//¿½±´¸³Öµ
	/*base b2;
	b2 = b1;*/
}