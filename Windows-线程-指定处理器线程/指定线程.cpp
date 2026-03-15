//一个程序指定到单独的一个CPU会比不指定CPU运行时快，主要有两个原因：
//1.CPU切换时损耗性能
//2.Intel的自动降频技术、windows平衡负载，二者冲突。
//Intel技术SpeedStep：当一个CPU没有满负荷运行时自动降频从而达到节能减排目的
//Windows平衡负载：将一个线程在不同时间分配到不同CPU，从而使每一个CPU不“过累”
//Windows平衡负载会让Intel降频、Intel降频会让Windows觉得CPU累了、进而导致每个CPU降频
//因此将线程（进程）绑定到指定CPU核心，不让Windows自作主张分散任务，从而提高单线程效率

//1.任务管理器，详细信息，右击，设置相关性
//2.SetThreadAffinityMask
//第一个参数为线程句柄
//第二个参数为一个mask，可取值为0~2^31(32位）和0~2^63（64位），每一位代表每一个CPU是否使用
//如果要指定多个CPU：比如第0、1个：mask = 0×03，第1、2个：mask = 0×06

#include<Windows.h>
#include<stdio.h>
int main() {
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	printf("Number of processors: %d.\n", info.dwNumberOfProcessors);
	//输出的是逻辑核心数量，比如i3处理器就是双核心四线程，输出4。i5处理器是四核心四线程，输出也是4。
}