﻿/*
** Copyright (c) 2018, Xin YUAN, courses of Zhejiang University
** All rights reserved.
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the 2-Clause BSD License.
**
** Author contact information:
**   yxxinyuan@zju.edu.cn
**
*/

/*
Internal Header
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __TXT_BASE_H__
#define __TXT_BASE_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

// _Delete_Output_File

inline void _Delete_Output_File(const ConstStringS& strFile, ShareCom<IByteStream> spStream, ShareCom<ITextStream> spText = ShareCom<ITextStream>()) throw()
{
	spStream.Release();
	spText.Release();
	thread_sleep(10);
	bool bRet = FileManagementHelper::DeleteFile(strFile);
	(void)bRet;
	assert( bRet );
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
