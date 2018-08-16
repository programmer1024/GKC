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
#ifndef __MDP_DEF_H__
#define __MDP_DEF_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

//output types

#define MDP_TYPE_CHM     (0)
#define MDP_TYPE_EPUB    (1)

//------------------------------------------------------------------------------
//strings

// g_cover_htm_body

DECLARE_STATIC_CONST_STRING(g_cover_htm_body, CharA)

// g_chm_content_body

DECLARE_STATIC_CONST_STRING(g_chm_content_body, CharA)

// g_chm_content_folder

DECLARE_STATIC_CONST_STRING(g_chm_content_folder, CharA)

// g_chm_content_node

DECLARE_STATIC_CONST_STRING(g_chm_content_node, CharA)

// g_chm_index_body

DECLARE_STATIC_CONST_STRING(g_chm_index_body, CharA)

// g_epub_mimetype_body

DECLARE_STATIC_CONST_STRING(g_epub_mimetype_body, CharA)

// g_epub_container_body

DECLARE_STATIC_CONST_STRING(g_epub_container_body, CharA)

// g_epub_css_body

DECLARE_STATIC_CONST_STRING(g_epub_css_body, CharA)

// g_epub_opf_body

DECLARE_STATIC_CONST_STRING(g_epub_opf_body, CharA)

// g_epub_opf_item

DECLARE_STATIC_CONST_STRING(g_epub_opf_item, CharA)

// g_epub_opf_itemref

DECLARE_STATIC_CONST_STRING(g_epub_opf_itemref, CharA)

// g_epub_opf_guide

DECLARE_STATIC_CONST_STRING(g_epub_opf_guide, CharA)

// g_epub_ncx_body

DECLARE_STATIC_CONST_STRING(g_epub_ncx_body, CharA)

// g_epub_ncx_node

DECLARE_STATIC_CONST_STRING(g_epub_ncx_node, CharA)

// g_epub_ncx_node_tail

DECLARE_STATIC_CONST_STRING(g_epub_ncx_node_tail, CharA)

//------------------------------------------------------------------------------
//functions

// create the destination file tree
inline bool _Create_Output_FileTree(int iType, const ConstStringS& strDest,
									StringS& strDestRoot)
{
	StringS strDir(StringHelper::MakeEmptyString<CharS>(MemoryHelper::GetCrtMemoryManager()));  //may throw
	StringUtilHelper::MakeString(strDest, strDir);  //may throw
	FsPathHelper::AppendSeparator(strDir);  //may throw
	StringUtilHelper::Append(DECLARE_TEMP_CONST_STRING(ConstStringS, _S("doc")), strDir);  //may throw
	FsPathHelper::ConvertPathStringToPlatform(strDir);
	//create directory
	if( !FileManagementHelper::CheckDirectoryExists(StringUtilHelper::To_ConstString(strDir))
		&& !FileManagementHelper::CreateDirectory(StringUtilHelper::To_ConstString(strDir))
		)
		return false;
	//epub
	if( iType == MDP_TYPE_EPUB ) {
		FsPathHelper::AppendSeparator(strDir);  //may throw
		//META-INF
		StringS strTemp(StringHelper::Clone(strDir));  //may throw
		StringUtilHelper::Append(DECLARE_TEMP_CONST_STRING(ConstStringS, _S("META-INF")), strTemp);  //may throw
		FsPathHelper::ConvertPathStringToPlatform(strTemp);
		//create directory
		if( !FileManagementHelper::CheckDirectoryExists(StringUtilHelper::To_ConstString(strTemp))
			&& !FileManagementHelper::CreateDirectory(StringUtilHelper::To_ConstString(strTemp))
			)
			return false;
		//OEBPS
		strTemp = StringHelper::Clone(strDir);  //may throw
		StringUtilHelper::Append(DECLARE_TEMP_CONST_STRING(ConstStringS, _S("OPBPS")), strTemp);  //may throw
		FsPathHelper::ConvertPathStringToPlatform(strTemp);
		//create directory
		if( !FileManagementHelper::CheckDirectoryExists(StringUtilHelper::To_ConstString(strTemp))
			&& !FileManagementHelper::CreateDirectory(StringUtilHelper::To_ConstString(strTemp))
			)
			return false;
		strDir = strTemp;
	}
	strDestRoot = strDir;
	return true;
}

//get html ext name
inline ConstStringA _Get_Html_Ext_Name(int iType) throw()
{
	if( iType == MDP_TYPE_CHM )
		return DECLARE_TEMP_CONST_STRING(ConstStringA, ".htm");
	else if( iType == MDP_TYPE_EPUB )
		return DECLARE_TEMP_CONST_STRING(ConstStringA, ".xhtml");
	return ConstStringA();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
