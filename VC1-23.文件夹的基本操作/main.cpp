//文件夹的创建:CreateDirectory
//此API只能创建一层目录，比如想在C盘下的Temp目录下创建新目录为123；那么前提是Temp这个目录存在才可以

//文件夹删除:RemoveDirectory
//此API只能删除空目录

//文件夹属性信息获取：GetFileAttributes




#define _AFXDLL
#include<iostream>
#include<afx.h>
//其中已包含Windows.h，与Windows.h不能同时包含
//不能与atlstr.h同时包含



//删除非空文件夹
BOOL DeleteTargetFolder(LPCTSTR lpstrPath) {
	CString strRootPath(lpstrPath);
	if (strRootPath[strRootPath.GetLength() - 1] != '\\') {
		strRootPath = strRootPath + _T("\\");
	}//保证路径结尾为“\”，要遍历里面的内容

	CFileFind mFinder;
	BOOL bFind = mFinder.FindFile(strRootPath + _T("*.*"), 0);
	while (bFind)
	{
		bFind = mFinder.FindNextFile();
		if (mFinder.IsDots()) {
			continue;
		}
		else {
			if (mFinder.IsDirectory()) {//目标是目录
				DeleteTargetFolder(mFinder.GetFilePath());
			}
			else {//目标是文件
				DeleteFile(mFinder.GetFilePath());
			}
		}
	}
	mFinder.Close();
	RemoveDirectory(strRootPath);
	//一定要放到mFinder.Close();后面，否则会失败，提示文件夹正在被使用中 

	return true;
}

int main() {
	
	/*if (CreateDirectoryA("C:\\123", NULL)) {
		cout << "文件夹创建成功" << endl;



	}
	else {
		cout << "失败" << endl;
	}*/

	if (RemoveDirectoryA("C:\\123\\")) {
		std::cout << "文件夹移除成功" << std::endl;

	}
	else {
		std::cout << "移除失败" << std::endl;
	}

	
	//DeleteTargetFolder(_T("C:\\123"));
}