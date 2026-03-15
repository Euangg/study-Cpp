//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//int main()
//{
//	int lj1[10000], lj2[10000], cp[10000] = { 0 }, r, i, j, k, n1, n2, b1, b2{0}, b11, b22, b3, b33, b4, b5, tui, temp, temp1, making;//cp1234
//	int max = 0;
//	srand(time(NULL));
//	i = 0;
//	while (i < 10000)
//	{
//		r = rand() % 10 + 1;
//		if (r = 1)
//		{
//			lj1[i] = 0;
//		}
//		else
//		{
//			lj1[i] = 1;
//		}
//		i++;
//	}
//	i = 0;
//	while (i < 10000)
//	{
//		r = rand() % 10 + 1;
//		if (r = 1)
//		{
//			lj2[i] = 0;
//		}
//		else
//		{
//			lj2[i] = 1;
//		}
//		i++;
//	}                //生成初始数组 
//
//	printf("%d"), lj1[10];
//	b1 = 0; b11 = 0; b22 = 0;
//	while (b1 < 10000)
//	{
//		b11 = 0; b22 = 0;
//		i = 0;
//		while (i < b1)
//		{
//			if (lj1[i] == 0)
//			{
//				b11++;
//			}
//		}         //统计不合格件数 
//		i = 0;
//		for (i = 0; i < b1; i++)
//		{
//			for (j = 0; j < b1 - i - 1; j++)
//			{
//				temp = lj1[j];
//				lj1[j] = lj1[j + 1];
//				lj1[j + 1] = temp;
//			}
//		}     //冒泡排序修正初始数组 
//		while (b2 < 10000)
//		{
//			i = 0;
//			while (i < b2)
//			{
//				if (lj2[i] == 0)
//				{
//					b22++;
//				}
//				i++;
//			}//统计不合格件数 
//			i = 0; j = 0;
//			for (i = 0; i < b2; i++)
//			{
//				for (j = 0; j < b2 - i - 1; j++)
//				{
//					temp = lj2[j];
//					lj2[j] = lj2[j + 1];
//					lj2[j + 1] = temp;
//				}
//			}//冒泡排序修正初始数组 
//			if (b11 <= b22)
//			{
//				temp = b22;
//			}
//			else
//			{
//				temp = b11;
//			}
//			i = 0;
//			while (i < temp)
//			{
//				cp[i] = 0;
//				i++;
//			}//无法组装为成品 
//			while (i < 10000)
//			{
//				r = rand() % 10 + 1;
//				if ((lj1[b1] == 0) || (lj2[b2] == 0) || (r == 1))
//				{
//					cp[b1] = 0;
//				}//产生次品 
//				else
//				{
//					cp[b1] = 1;
//				}//产生成品 
//				i++;
//			}
//			b3 = 0;
//			while (b3 + temp < 10000)
//			{
//				b33 = 0;
//				i = temp;
//				while (i < b3 + temp)
//				{
//					if (cp[i] == 0)
//					{
//						b33++;
//					}
//					i++;
//				}//统计不合格件数 
//				for (i = temp; i < b3 + temp; i++)
//				{
//					for (j = temp; j < b3 + temp - i - 1; j++)
//					{
//						temp1 = cp[j]; cp[j] = cp[j + 1]; cp[j + 1] = temp1;
//						temp1 = lj1[j]; lj1[j] = lj1[j + 1]; lj1[j + 1] = temp1;
//						temp1 = lj2[j]; lj2[j] = lj2[j + 1]; lj2[j + 1] = temp1;
//					}
//				}//冒泡排序修正初始数组 
//				b4 = 0; tui = 0;
//				while (b4 < b33)//拆解部分 
//				{
//					i = temp + b3;
//					while (i < 10000)
//					{
//						if (cp[i] == 0)
//						{
//							tui++;
//						}
//						i++;
//					}  //统计退回不合格件数 
//					for (i = temp + b33; i < 10000; i++)
//					{
//						for (j = temp + b33; j < 10000 - i - 1; j++)
//						{
//							temp1 = cp[j]; cp[j] = cp[j + 1]; cp[j + 1] = temp1;
//							temp1 = lj1[j]; lj1[j] = lj1[j + 1]; lj1[j + 1] = temp1;
//							temp1 = lj2[j]; lj2[j] = lj2[j + 1]; lj2[j + 1] = temp1;
//						}
//					}//冒泡排序修正初始数组
//
//
//					making = (-4) * 10000 + (-2) * b1 + (-3) * b2 + (-18) * 10000 + (-6) * (10000 - temp) + (-3) * b3 + 56 * (10000 - temp - b33) + (-5) * b4;
//					if (max <= making)
//					{
//						max = making;
//						printf("%d,%d,%d,%d,%d", b1, b2, b3, b4, making);
//					}
//
//					b4++;
//				}
//
//
//
//
//				b3++;
//			}
//
//
//			b2++;
//		}
//
//
//		b1++;
//	}
//
//
//
//
//
//	return 0;
//}
