﻿/*
** Copyright (c) 2014, Xin YUAN, courses of Zhejiang University
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
This file contains string classes.
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __GKC_STRING_H__
#define __GKC_STRING_H__
////////////////////////////////////////////////////////////////////////////////

#ifndef __GKC_ARRAY_H__
	#error GkcString.h requires GkcArray.h to be included first.
#endif

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

// classes

// FixedStringT<Tchar, t_size>
//   Tchar: CharA CharH CharL, CharS CharW

template <typename Tchar, uintptr t_size>
class FixedStringT : public FixedArray<Tchar, t_size, DefaultCompareTrait<Tchar>>
{
private:
	typedef FixedStringT<Tchar, t_size>  thisClass;
	typedef FixedArray<Tchar, t_size, DefaultCompareTrait<Tchar>>  baseClass;

public:
	FixStringT() throw() : m_uLength(0)
	{
		m_data[0] = 0;
	}
	FixedStringT(const thisClass& src) throw() : m_uLength(src.m_uLength)
	{
		assert( m_uLength < t_size );
		mem_copy(src.m_data, sizeof(Tchar) * (m_uLength + 1), m_data);
	}
	~FixedStringT() throw()
	{
	}

	//operators
	thisClass& operator=(const thisClass& src) throw()
	{
		if( this != &src ) {
			m_uLength = src.m_uLength;
			assert( m_uLength < t_size );
			mem_copy(src.m_data, sizeof(Tchar) * (m_uLength + 1), m_data);
		}
		return *this;
	}

	uintptr GetLength() const throw()
	{
		return m_uLength;
	}
	void SetLength(uintptr uLength) throw()
	{
		assert( uLength < t_size );
		m_uLength = uLength;
		m_data[m_uLength] = 0;
	}

	//iterators
	const Iterator GetEnd() const throw()
	{
		return Iterator(RefPtr<Tchar>(m_data + m_uLength));
	}
	Iterator GetEnd() throw()
	{
		return Iterator(RefPtr<Tchar>(m_data + m_uLength));
	}
	const ReverseIterator<Iterator> GetReverseBegin() const throw()
	{
		return ReverseIterator<Iterator>(GetEnd());
	}
	ReverseIterator<Iterator> GetReverseBegin() throw()
	{
		return ReverseIterator<Iterator>(GetEnd());
	}

	//methods
	void RecalcLength() throw()
	{
		m_uLength = calc_string_length(m_data);
	}

private:
	uintptr m_uLength;

private:
	//logical
	bool operator==(const thisClass& right) const throw();
	bool operator!=(const thisClass& right) const throw();
	bool operator<(const thisClass& right) const throw();
	bool operator>(const thisClass& right) const throw();
	bool operator<=(const thisClass& right) const throw();
	bool operator>=(const thisClass& right) const throw();
};

// FixedStringCompareTrait<T>

template <class T>
class FixedStringCompareTrait
{
public:
	static bool IsEQ(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) == 0;
	}
	static bool IsNE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) != 0;
	}
	static bool IsGT(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) > 0;
	}
	static bool IsLT(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) < 0;
	}
	static bool IsGE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) >= 0;
	}
	static bool IsLE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) <= 0;
	}
	static int Compare(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value()));
	}
};

// FixedStringCaseIgnoreCompareTrait<T>

template <class T>
class FixedStringCaseIgnoreCompareTrait
{
public:
	static bool IsEQ(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) == 0;
	}
	static bool IsNE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) != 0;
	}
	static bool IsGT(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) > 0;
	}
	static bool IsLT(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) < 0;
	}
	static bool IsGE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) >= 0;
	}
	static bool IsLE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) <= 0;
	}
	static int Compare(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value()));
	}
};

// StringT<Tchar>
//   Tchar: CharA CharH CharL, CharS CharW
template <typename Tchar>
class StringT : public SharedArray<Tchar>
{
private:
	typedef StringT<Tchar>  thisClass;
	typedef SharedArray<Tchar>  baseClass;

public:
	StringT() throw()
	{
	}
	StringT(const thisClass& src) throw() : baseClass(static_cast<const baseClass&>(src))
	{
	}
	StringT(thisClass&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
	}
	~StringT() throw()
	{
	}

	//operators
	thisClass& operator=(const thisClass& src) throw()
	{
		return baseClass::operator=(static_cast<const baseClass&>(src));
	}
	thisClass& operator=(thisClass&& src) throw()
	{
		return baseClass::operator=(rv_forward(static_cast<baseClass&>(src)));
	}

	uintptr GetLength() const throw()
	{
		return (m_pB == NULL) ? 0 : ((SharedArrayBlock*)m_pB)->GetLength() - 1;
	}
	bool IsEmpty() const throw()
	{
		return GetLength() == 0;
	}

	//iterators
	const Iterator GetEnd() const throw()
	{
		return Iterator(RefPtr<T>(m_pT + GetLength()));
	}
	Iterator GetEnd() throw()
	{
		return Iterator(RefPtr<T>(m_pT + GetLength()));
	}
	const Iterator GetReverseBegin() const throw()
	{
		return ReverseIterator<Iterator>(GetEnd());
	}
	Iterator GetReverseBegin() throw()
	{
		return ReverseIterator<Iterator>(GetEnd());
	}

	const Iterator GetAt(uintptr index) const throw()
	{
		assert( index < GetLength() );
		return Iterator(RefPtr<T>(m_pT + index));
	}
	Iterator GetAt(uintptr index) throw()
	{
		assert( index < GetLength() );
		return Iterator(RefPtr<T>(m_pT + index));
	}
	void SetAt(uintptr index, const T& t)  //may throw
	{
		assert( index < GetLength() );
		m_pT[index] = t;
	}
	void SetAt(uintptr index, T&& t)  //may throw
	{
		assert( index < GetLength() );
		m_pT[index] = rv_forward(t);
	}

	//methods
	void SetLength(uintptr uLength)
	{
		SetCount(uLength + 1);
		GetAt(uLength).get_Value() = 0;
	}
};

// StringX
typedef StringT<CharA>  StringA;
typedef StringT<CharH>  StringH;
typedef StringT<CharL>  StringL;
typedef StringT<CharS>  StringS;
typedef StringT<CharW>  StringW;

// StringCompareTrait<T>

template <class T>
class StringCompareTrait
{
public:
	static bool IsEQ(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) == 0;
	}
	static bool IsNE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) != 0;
	}
	static bool IsGT(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) > 0;
	}
	static bool IsLT(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) < 0;
	}
	static bool IsGE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) >= 0;
	}
	static bool IsLE(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) <= 0;
	}
	static int Compare(const T& t1, const T& t2) throw()
	{
		return compare_string(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value()));
	}
};

// StringCaseIgnoreCompareTrait<T>

template <class T>
class StringCaseIgnoreCompareTrait
{
public:
	static bool IsEQ(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) == 0;
	}
	static bool IsNE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) != 0;
	}
	static bool IsGT(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) > 0;
	}
	static bool IsLT(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) < 0;
	}
	static bool IsGE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) >= 0;
	}
	static bool IsLE(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value())) <= 0;
	}
	static int Compare(const T& t1, const T& t2) throw()
	{
		return compare_string_case_insensitive(&(t1.GetBegin().get_Value()), &(t2.GetBegin().get_Value()));
	}
};

// StringHelper

class StringHelper
{
public:
	//make string
	template <typename Tchar, uintptr t_size>
	static void MakeString(const ConstString<Tchar>& strSrc, FixedString<Tchar, t_size>& strDest) throw()
	{
		assert( !strSrc.IsNull() );
		uintptr uCount = strSrc.GetCount();
		if( uCount == 0 ) {
			strDest.SetLength(0);
			return ;
		}
		if( uCount > t_size - 1 )
			uCount = t_size - 1;
		strDest.SetLength(uCount);
		mem_copy(&(strSrc.GetBegin().get_Value()), uCount * sizeof(Tchar), &(strDest.GetBegin().get_Value()));
	}
	template <typename Tchar>
	static void MakeString(const ConstString<Tchar>& strSrc, StringT<Tchar>& strDest)
	{
		assert( !strSrc.IsNull() );
		uintptr uCount = strSrc.GetCount();
		strDest.SetLength(uCount);
		if( uCount == 0 ) {
			return ;
		}
		mem_copy(&(strSrc.GetBegin().get_Value()), uCount * sizeof(Tchar), &(strDest.GetBegin().get_Value()));
	}
	template <typename Tchar, uintptr t_size>
	static void MakeString(const FixedString<Tchar, t_size>& strSrc, StringT<Tchar>& strDest)
	{
		uintptr uCount = strSrc.GetLength();
		strDest.SetLength(uCount);
		if( uCount == 0 ) {
			return ;
		}
		mem_copy(&(strSrc.GetBegin().get_Value()), uCount * sizeof(Tchar), &(strDest.GetBegin().get_Value()));
	}
	template <typename Tchar, uintptr t_size>
	static void MakeString(const StringT<Tchar>& strSrc, FixedString<Tchar, t_size>& strDest) throw()
	{
		uintptr uCount = strSrc.GetLength();
		if( uCount == 0 ) {
			strDest.SetLength(0);
			return ;
		}
		if( uCount > t_size - 1 )
			uCount = t_size - 1;
		strDest.SetLength(uCount);
		mem_copy(&(strSrc.GetBegin().get_Value()), uCount * sizeof(Tchar), &(strDest.GetBegin().get_Value()));
	}

	//clone
	template <typename Tchar>
	static StringT<Tchar> Clone(const StringT<Tchar>& str)
	{
		StringT<Tchar> ret;
		uintptr uCount = str.GetLength();
		ret.SetLength(uCount);
		if( uCount == 0 ) {
			return ret;
		}
		mem_copy(&(str.GetBegin().get_Value()), uCount * sizeof(Tchar), &(ret.GetBegin().get_Value()));
		return ret;
	}
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif //__GKC_STRING_H__
////////////////////////////////////////////////////////////////////////////////
