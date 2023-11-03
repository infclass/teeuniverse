/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverse.
 * 
 * TeeUniverse is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverse.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * THIS FILE HAS BEEN GENERATED BY A SCRIPT.
 * DO NOT EDIT MANUALLY!
 *
 * Please use the script "scripts/assets/assets.py" to regenerate it.
 *
 * Why this file is generated by a script?
 * Because there is more than 10 files that follow the same format.
 * In addition, each time a new member is added, enums, getter, setters,
 * copy/transfert functions and storage structure must be updated.
 * It's too much to avoid mistakes.
 */

#ifndef __CLIENT_ASSETS_CHARACTER__
#define __CLIENT_ASSETS_CHARACTER__

#include <shared/assets/asset.h>
#include <cassert>
#include <shared/tl/algorithm.h>
#include <shared/assets/assetpath.h>
#include <vector>

class CAsset_Character : public CAsset
{
public:
	static const int TypeId = 0;
	
	enum
	{
		TYPE_PART,
	};
	
	static inline CSubPath SubPath_Part(int Id0) { return CSubPath(TYPE_PART, Id0, 0, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		IDLEPATH,
		WALKPATH,
		CONTROLLEDJUMPPATH,
		UNCONTROLLEDJUMPPATH,
		PART_ARRAYSIZE,
		PART_PTR,
		PART_ARRAY,
		PART_NAME,
		PART_DEFAULTPATH,
		PART,
	};
	
	class CIteratorPart
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorPart() : m_Index(0), m_Reverse(false) {}
		CIteratorPart(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorPart& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_Part(m_Index); }
		bool operator==(const CIteratorPart& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorPart& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorPart BeginPart() const { return CIteratorPart(0, false); }
	CIteratorPart EndPart() const { return CIteratorPart(m_Part.size(), false); }
	CIteratorPart ReverseBeginPart() const { return CIteratorPart(m_Part.size()-1, true); }
	CIteratorPart ReverseEndPart() const { return CIteratorPart(-1, true); }
	
	class CPart
	{
	public:
		class CTuaType_0_2_0
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_2_0& TuaType);
		};
		
		class CTuaType_0_2_1
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_2_1& TuaType);
		};
		
		class CTuaType_0_2_2
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_2_2& TuaType);
		};
		
		class CTuaType_0_2_3
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_3& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_2_3& TuaType);
		};
		
		class CTuaType_0_2_4
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_4& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_2_4& TuaType);
		};
		
		class CTuaType_0_3_0
		{
		public:
			tua_stringid m_Name;
			CAssetPath::CTuaType m_DefaultPath;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_0& TuaType, CAsset_Character::CPart& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character::CPart& SysType, CTuaType_0_3_0& TuaType);
		};
		
	
	private:
		_dynamic_string<128> m_Name{};
		CAssetPath m_DefaultPath{};
	
	public:
		const char* GetName() const { return m_Name.buffer(); }
		
		CAssetPath GetDefaultPath() const { return m_DefaultPath; }
		
		void SetName(const char* Value) { m_Name = Value; }
		
		void SetDefaultPath(const CAssetPath& Value) { m_DefaultPath = Value; }
		
		void AssetPathOperation(const CAssetPath::COperation& Operation)
		{
			Operation.Apply(m_DefaultPath);
		}
		
	};
	class CTuaType_0_2_0 : public CAsset::CTuaType_0_2_0
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_2_0& TuaType);
	};
	
	class CTuaType_0_2_1 : public CAsset::CTuaType_0_2_1
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_2_1& TuaType);
	};
	
	class CTuaType_0_2_2 : public CAsset::CTuaType_0_2_2
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_2_2& TuaType);
	};
	
	class CTuaType_0_2_3 : public CAsset::CTuaType_0_2_3
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_3& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_2_3& TuaType);
	};
	
	class CTuaType_0_2_4 : public CAsset::CTuaType_0_2_4
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_4& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_2_4& TuaType);
	};
	
	class CTuaType_0_3_0 : public CAsset::CTuaType_0_3_0
	{
	public:
		CAssetPath::CTuaType m_IdlePath;
		CAssetPath::CTuaType m_WalkPath;
		CAssetPath::CTuaType m_ControlledJumpPath;
		CAssetPath::CTuaType m_UncontrolledJumpPath;
		CTuaArray m_Part;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_0& TuaType, CAsset_Character& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Character& SysType, CTuaType_0_3_0& TuaType);
	};
	

private:
	CAssetPath m_IdlePath{};
	CAssetPath m_WalkPath{};
	CAssetPath m_ControlledJumpPath{};
	CAssetPath m_UncontrolledJumpPath{};
	std::vector<CAsset_Character::CPart> m_Part{};

public:
	virtual ~CAsset_Character() {}
	
	template<typename T>
	T GetValue(int ValueType, const CSubPath& SubPath, T DefaultValue) const
	{
		return CAsset::GetValue<T>(ValueType, SubPath, DefaultValue);
	}
	
	template<typename T>
	bool SetValue(int ValueType, const CSubPath& SubPath, T Value)
	{
		return CAsset::SetValue<T>(ValueType, SubPath, Value);
	}
	
	int AddSubItem(int Type, const CSubPath& SubPath);
	
	int AddSubItemAt(int Type, const CSubPath& SubPath, int Index);
	
	void DeleteSubItem(const CSubPath& SubPath);
	
	void RelMoveSubItem(CSubPath& SubPath, int RelMove);
	
	CAssetPath GetIdlePath() const { return m_IdlePath; }
	
	CAssetPath GetWalkPath() const { return m_WalkPath; }
	
	CAssetPath GetControlledJumpPath() const { return m_ControlledJumpPath; }
	
	CAssetPath GetUncontrolledJumpPath() const { return m_UncontrolledJumpPath; }
	
	int GetPartArraySize() const { return m_Part.size(); }
	
	const CAsset_Character::CPart* GetPartPtr() const { return &(m_Part.front()); }
	
	const std::vector<CAsset_Character::CPart>& GetPartArray() const { return m_Part; }
	std::vector<CAsset_Character::CPart>& GetPartArray() { return m_Part; }
	
	const CAsset_Character::CPart& GetPart(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_Part.size());
		{
			return m_Part[SubPath.GetId()];
		}
	}
	
	const char* GetPartName(const CSubPath& SubPath) const
	{
		if(SubPath.GetId() < m_Part.size())
			return m_Part[SubPath.GetId()].GetName();
		else return NULL;
	}
	
	CAssetPath GetPartDefaultPath(const CSubPath& SubPath) const
	{
		if(SubPath.GetId() < m_Part.size())
			return m_Part[SubPath.GetId()].GetDefaultPath();
		else return CAssetPath::Null();
	}
	
	void SetIdlePath(const CAssetPath& Value) { m_IdlePath = Value; }
	
	void SetWalkPath(const CAssetPath& Value) { m_WalkPath = Value; }
	
	void SetControlledJumpPath(const CAssetPath& Value) { m_ControlledJumpPath = Value; }
	
	void SetUncontrolledJumpPath(const CAssetPath& Value) { m_UncontrolledJumpPath = Value; }
	
	void SetPartArraySize(int Value) { m_Part.resize(Value); }
	
	void SetPart(const CSubPath& SubPath, const CAsset_Character::CPart& Value)
	{
		if(SubPath.GetId() < m_Part.size())
		{
			m_Part[SubPath.GetId()] = Value;
		}
	}
	
	void SetPartName(const CSubPath& SubPath, const char* Value)
	{
		if(SubPath.GetId() < m_Part.size())
			m_Part[SubPath.GetId()].SetName(Value);
	}
	
	void SetPartDefaultPath(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_Part.size())
			m_Part[SubPath.GetId()].SetDefaultPath(Value);
	}
	
	int AddPart()
	{
		int Id = m_Part.size();
		m_Part.emplace_back();
		return Id;
	}
	
	void AddAtPart(int Index) { m_Part.insert(m_Part.begin() + Index, CAsset_Character::CPart()); }
	
	void DeletePart(const CSubPath& SubPath) { m_Part.erase(m_Part.begin() + SubPath.GetId()); }
	
	void RelMovePart(CSubPath& SubPath, int RelMove)
	{
		int NewId = relative_move(m_Part, SubPath.GetId(), RelMove);
		SubPath.SetId(NewId);
	}
	
	bool IsValidPart(const CSubPath& SubPath) const { return (SubPath.IsNotNull() && SubPath.GetId() < m_Part.size()); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_IdlePath);
		Operation.Apply(m_WalkPath);
		Operation.Apply(m_ControlledJumpPath);
		Operation.Apply(m_UncontrolledJumpPath);
		for(unsigned int i=0; i<m_Part.size(); i++)
		{
			m_Part[i].AssetPathOperation(Operation);
		}
	}
	
};

template<> int CAsset_Character::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const;
template<> bool CAsset_Character::SetValue(int ValueType, const CSubPath& SubPath, int Value);
template<> const char* CAsset_Character::GetValue(int ValueType, const CSubPath& SubPath, const char* DefaultValue) const;
template<> bool CAsset_Character::SetValue(int ValueType, const CSubPath& SubPath, const char* Value);
template<> CAssetPath CAsset_Character::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const;
template<> bool CAsset_Character::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value);

#endif
