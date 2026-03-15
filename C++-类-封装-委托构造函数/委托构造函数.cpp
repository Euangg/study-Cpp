//让构造函数调用其他的构造函数
//同一个类中，一个构造函数调用其他的构造函数

class Test {
public:
	Test() {};
	Test(int max) { 
		this->m_max = max > 0 ? max : 100; 
	};
	Test(int max, int min) {
		this->m_max = max > 0 ? max : 100;
		this->m_min = min > 0 && min < max ? min : 1;
	}
	Test(int max, int min, int mid) {
		this->m_max = max > 0 ? max : 100;
		this->m_min = min > 0 && min < max ? min : 1;
		this->m_middle = mid<max&& mid>min ? mid : 50;
	}

private:
	int m_max;
	int m_min;
	int m_middle;
};

class Test2 {
public:
	Test2() {};
	Test2(int max) {
		this->m_max = max > 0 ? max : 100;
	};
	Test2(int max, int min):Test2(max) {
		this->m_min = min > 0 && min < max ? min : 1;
	}
	Test2(int max, int min, int mid):Test2(max,min) {//链状调用
		this->m_middle = mid<max&& mid>min ? mid : 50;
	}

private:
	int m_max;
	int m_min;
	int m_middle;
};

