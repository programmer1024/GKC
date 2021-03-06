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

////////////////////////////////////////////////////////////////////////////////
//internal header
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//definitions

typedef fixed_array<char_a, 64>  lcid_array;

//------------------------------------------------------------------------------
//OS

#if defined(GKC_OS_WINDOWS)
	#include "Windows/sys_types.h"
#elif defined(GKC_OS_LINUX)
	#include "Linux/sys_types.h"
#else
	#error Error OS type!
#endif

//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
