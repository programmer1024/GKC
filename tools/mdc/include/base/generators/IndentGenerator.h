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
#ifndef __INDENT_GENERATOR_H__
#define __INDENT_GENERATOR_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

// _IndentGenerator

class _IndentGenerator : public _IHtmlGenerator
{
public:
// _IHtmlGenerator methods
	virtual CallResult Generate(bool bOpen, ShareCom<ICplMetaData>& spMeta, const CplMetaDataPosition& posData, ShareCom<ITextStream>& spText)
	{
		CallResult cr;
		cr = spText.Deref().PutLineA(DECLARE_TEMP_CONST_STRING(ConstStringA, "<p>o</p>"));
		return cr;
	}
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
