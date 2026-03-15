//互斥
//针对问题：多线程下代码或资源的共享使用
//实现：1.创建互斥
//			HANDLE CreateMutex(
//				LPSECURITY_ATTRIBUTES lpMutexAttributes,//安全属性
//				BOOL bInitialOwner,						//初始拥有者 TRUE/FALSE，TRUE哪个线程创建互斥，哪个线程就拥有互斥
//				LPCTSTR lpName							//命名，可以置空
//			);创建成功返回互斥句柄，是一个可等候句柄
//			在任何一个时间点上，只能有一个线程拥有互斥，具有独占性和排他性
//			当互斥不被任何线程拥有时，有信号；互斥被任意线程拥有时，无信号


