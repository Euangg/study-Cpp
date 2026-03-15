//打破循环shared_ptr的引用

#include<memory>
#include<iostream>
using std::cout;
using std::endl;

auto sptr = std::make_shared<int>(54);
//auto uptr = std::make_unique<int>(98);
//std::weak_ptr<int> wptr1_u = uptr;//weak_ptr不能指unique_ptr
int main() {
	cout << sptr.use_count() << endl;
	std::weak_ptr<int> wptr1 = sptr;//不增加使用记数
	cout << sptr.use_count() << endl;
	cout << *(wptr1.lock()) << endl;//检查对象是否存活，并访问修改
	cout << sptr.use_count() << endl;//lock也不会增加使用计数
	wptr1.lock().reset();//无效操作，不影响原shared_ptr的使用计数
	cout << sptr.use_count() << endl;//lock也不会增加使用计数
	sptr.reset();
	cout << wptr1.lock() << endl;//死了就是0000000
}