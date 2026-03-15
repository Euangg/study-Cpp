class TimeKeeper {
public:
	TimeKeeper();
	virtual ~TimeKeeper();
};
//防止基类指针指向子类对象时【多态】，销毁不干净
//任何class只要带有virtual函数，几乎确定也应该有个virtual析构函数
