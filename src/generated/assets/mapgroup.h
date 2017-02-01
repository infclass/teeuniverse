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

#ifndef __CLIENT_ASSETS_MAPGROUP__
#define __CLIENT_ASSETS_MAPGROUP__

#include <shared/assets/asset.h>
#include <cassert>
#include <vector>
#include <shared/math/vector.h>
#include <shared/assets/assetpath.h>
#include <shared/tl/algorithm.h>

class CAsset_MapGroup : public CAsset
{
public:
	static const int TypeId = 15;
	
	enum
	{
		TYPE_LAYER,
	};
	
	static inline CSubPath SubPath_Layer(int Id0) { return CSubPath(TYPE_LAYER, Id0, 0, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		PARENTPATH,
		LAYER_ARRAYSIZE,
		LAYER_PTR,
		LAYER_ARRAY,
		LAYER,
		POSITION_X,
		POSITION_Y,
		POSITION,
		HARDPARALLAX_X,
		HARDPARALLAX_Y,
		HARDPARALLAX,
		CLIPPING,
		CLIPPOSITION_X,
		CLIPPOSITION_Y,
		CLIPPOSITION,
		CLIPSIZE_X,
		CLIPSIZE_Y,
		CLIPSIZE,
		VISIBILITY,
	};
	
	class CIteratorLayer
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorLayer() : m_Index(0), m_Reverse(false) {}
		CIteratorLayer(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorLayer& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_Layer(m_Index); }
		bool operator==(const CIteratorLayer& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorLayer& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorLayer BeginLayer() const { return CIteratorLayer(0, false); }
	CIteratorLayer EndLayer() const { return CIteratorLayer(m_Layer.size(), false); }
	CIteratorLayer ReverseBeginLayer() const { return CIteratorLayer(m_Layer.size()-1, true); }
	CIteratorLayer ReverseEndLayer() const { return CIteratorLayer(-1, true); }
	
	class CTuaType_0_1_0 : public CAsset::CTuaType_0_1_0
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CTuaArray m_Layer;
		CTuaVec2 m_Position;
		CTuaVec2 m_HardParallax;
		tua_uint8 m_Clipping;
		CTuaVec2 m_ClipPosition;
		CTuaVec2 m_ClipSize;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_MapGroup& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapGroup& SysType, CTuaType_0_1_0& TuaType);
	};
	
	class CTuaType_0_2_0 : public CAsset::CTuaType_0_2_0
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CTuaArray m_Layer;
		CTuaVec2 m_Position;
		CTuaVec2 m_HardParallax;
		tua_uint8 m_Clipping;
		CTuaVec2 m_ClipPosition;
		CTuaVec2 m_ClipSize;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_MapGroup& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapGroup& SysType, CTuaType_0_2_0& TuaType);
	};
	
	class CTuaType_0_2_1 : public CAsset::CTuaType_0_2_1
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CTuaArray m_Layer;
		CTuaVec2 m_Position;
		CTuaVec2 m_HardParallax;
		tua_uint8 m_Clipping;
		CTuaVec2 m_ClipPosition;
		CTuaVec2 m_ClipSize;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_MapGroup& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapGroup& SysType, CTuaType_0_2_1& TuaType);
	};
	
	class CTuaType_0_2_2 : public CAsset::CTuaType_0_2_2
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CTuaArray m_Layer;
		CTuaVec2 m_Position;
		CTuaVec2 m_HardParallax;
		tua_uint8 m_Clipping;
		CTuaVec2 m_ClipPosition;
		CTuaVec2 m_ClipSize;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_MapGroup& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapGroup& SysType, CTuaType_0_2_2& TuaType);
	};
	

private:
	CAssetPath m_ParentPath;
	std::vector<CAssetPath> m_Layer;
	vec2 m_Position;
	vec2 m_HardParallax;
	bool m_Clipping;
	vec2 m_ClipPosition;
	vec2 m_ClipSize;
	bool m_Visibility;

public:
	virtual ~CAsset_MapGroup() {}
	
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
	
	void RelMoveSubItem(const CSubPath& SubPath, int RelMove);
	
	CAsset_MapGroup();
	inline CAssetPath GetParentPath() const { return m_ParentPath; }
	
	inline int GetLayerArraySize() const { return m_Layer.size(); }
	
	inline const CAssetPath* GetLayerPtr() const { return &(m_Layer.front()); }
	
	inline const std::vector<CAssetPath>& GetLayerArray() const { return m_Layer; }
	inline std::vector<CAssetPath>& GetLayerArray() { return m_Layer; }
	
	inline CAssetPath GetLayer(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_Layer.size());
		{
			return m_Layer[SubPath.GetId()];
		}
	}
	
	inline vec2 GetPosition() const { return m_Position; }
	
	inline float GetPositionX() const { return m_Position.x; }
	
	inline float GetPositionY() const { return m_Position.y; }
	
	inline vec2 GetHardParallax() const { return m_HardParallax; }
	
	inline float GetHardParallaxX() const { return m_HardParallax.x; }
	
	inline float GetHardParallaxY() const { return m_HardParallax.y; }
	
	inline bool GetClipping() const { return m_Clipping; }
	
	inline vec2 GetClipPosition() const { return m_ClipPosition; }
	
	inline float GetClipPositionX() const { return m_ClipPosition.x; }
	
	inline float GetClipPositionY() const { return m_ClipPosition.y; }
	
	inline vec2 GetClipSize() const { return m_ClipSize; }
	
	inline float GetClipSizeX() const { return m_ClipSize.x; }
	
	inline float GetClipSizeY() const { return m_ClipSize.y; }
	
	inline bool GetVisibility() const { return m_Visibility; }
	
	inline void SetParentPath(const CAssetPath& Value) { m_ParentPath = Value; }
	
	inline void SetLayerArraySize(int Value) { m_Layer.resize(Value); }
	
	inline void SetLayer(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_Layer.size())
		{
			m_Layer[SubPath.GetId()] = Value;
		}
	}
	
	inline void SetPosition(vec2 Value) { m_Position = Value; }
	
	inline void SetPositionX(float Value) { m_Position.x = Value; }
	
	inline void SetPositionY(float Value) { m_Position.y = Value; }
	
	inline void SetHardParallax(vec2 Value) { m_HardParallax = Value; }
	
	inline void SetHardParallaxX(float Value) { m_HardParallax.x = Value; }
	
	inline void SetHardParallaxY(float Value) { m_HardParallax.y = Value; }
	
	inline void SetClipping(bool Value) { m_Clipping = Value; }
	
	inline void SetClipPosition(vec2 Value) { m_ClipPosition = Value; }
	
	inline void SetClipPositionX(float Value) { m_ClipPosition.x = Value; }
	
	inline void SetClipPositionY(float Value) { m_ClipPosition.y = Value; }
	
	inline void SetClipSize(vec2 Value) { m_ClipSize = Value; }
	
	inline void SetClipSizeX(float Value) { m_ClipSize.x = Value; }
	
	inline void SetClipSizeY(float Value) { m_ClipSize.y = Value; }
	
	inline void SetVisibility(bool Value) { m_Visibility = Value; }
	
	inline int AddLayer()
	{
		int Id = m_Layer.size();
		m_Layer.emplace_back();
		return Id;
	}
	
	inline void AddAtLayer(int Index) { m_Layer.insert(m_Layer.begin() + Index, CAssetPath()); }
	
	inline void DeleteLayer(const CSubPath& SubPath) { m_Layer.erase(m_Layer.begin() + SubPath.GetId()); }
	
	inline void RelMoveLayer(const CSubPath& SubPath, int RelMove) { relative_move(m_Layer, SubPath.GetId(), RelMove); }
	
	inline bool IsValidLayer(const CSubPath& SubPath) const { return (SubPath.IsNotNull() && SubPath.GetId() < m_Layer.size()); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_ParentPath);
		{
			int Shift = 0;
			for(unsigned int i=0; i<m_Layer.size(); i++)
			{
				if(Operation.MustBeDeleted(m_Layer[i]))
					Shift++;
				else if(Shift > 0)
					m_Layer[i-Shift] = m_Layer[i];
			}
			m_Layer.resize(m_Layer.size()-Shift);
		}
		for(unsigned int i=0; i<m_Layer.size(); i++)
		{
			Operation.Apply(m_Layer[i]);
		}
	}
	
};

template<> int CAsset_MapGroup::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const;
template<> bool CAsset_MapGroup::SetValue(int ValueType, const CSubPath& SubPath, int Value);
template<> bool CAsset_MapGroup::GetValue(int ValueType, const CSubPath& SubPath, bool DefaultValue) const;
template<> bool CAsset_MapGroup::SetValue(int ValueType, const CSubPath& SubPath, bool Value);
template<> float CAsset_MapGroup::GetValue(int ValueType, const CSubPath& SubPath, float DefaultValue) const;
template<> bool CAsset_MapGroup::SetValue(int ValueType, const CSubPath& SubPath, float Value);
template<> vec2 CAsset_MapGroup::GetValue(int ValueType, const CSubPath& SubPath, vec2 DefaultValue) const;
template<> bool CAsset_MapGroup::SetValue(int ValueType, const CSubPath& SubPath, vec2 Value);
template<> CAssetPath CAsset_MapGroup::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const;
template<> bool CAsset_MapGroup::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value);

#endif
