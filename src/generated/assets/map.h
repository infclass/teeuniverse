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

#ifndef __CLIENT_ASSETS_MAP__
#define __CLIENT_ASSETS_MAP__

#include <shared/assets/asset.h>
#include <shared/tl/array.h>
#include <shared/math/vector.h>

class CAsset_Map : public CAsset
{
public:
	static const int TypeId = 14;
	
	enum
	{
		TYPE_BGGROUP,
		TYPE_FGGROUP,
		TYPE_ZONELAYER,
		TYPE_ENTITYLAYER,
	};
	
	static inline CSubPath SubPath_BgGroup(int Id0) { return CSubPath(TYPE_BGGROUP, Id0, 0, 0); }
	static inline CSubPath SubPath_FgGroup(int Id0) { return CSubPath(TYPE_FGGROUP, Id0, 0, 0); }
	static inline CSubPath SubPath_ZoneLayer(int Id0) { return CSubPath(TYPE_ZONELAYER, Id0, 0, 0); }
	static inline CSubPath SubPath_EntityLayer(int Id0) { return CSubPath(TYPE_ENTITYLAYER, Id0, 0, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		BGGROUP_ARRAYSIZE,
		BGGROUP_PTR,
		BGGROUP_ARRAY,
		BGGROUP,
		FGGROUP_ARRAYSIZE,
		FGGROUP_PTR,
		FGGROUP_ARRAY,
		FGGROUP,
		ZONELAYER_ARRAYSIZE,
		ZONELAYER_PTR,
		ZONELAYER_ARRAY,
		ZONELAYER,
		ENTITYLAYER_ARRAYSIZE,
		ENTITYLAYER_PTR,
		ENTITYLAYER_ARRAY,
		ENTITYLAYER,
		CAMERAPOSITION_X,
		CAMERAPOSITION_Y,
		CAMERAPOSITION,
		CAMERAZOOM,
		SHOWENTITIES,
		SHOWZONES,
	};
	
	class CIteratorBgGroup
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorBgGroup() : m_Index(0), m_Reverse(false) {}
		CIteratorBgGroup(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorBgGroup& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_BgGroup(m_Index); }
		bool operator==(const CIteratorBgGroup& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorBgGroup& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorBgGroup BeginBgGroup() const { return CIteratorBgGroup(0, false); }
	CIteratorBgGroup EndBgGroup() const { return CIteratorBgGroup(m_BgGroup.size(), false); }
	CIteratorBgGroup ReverseBeginBgGroup() const { return CIteratorBgGroup(m_BgGroup.size()-1, true); }
	CIteratorBgGroup ReverseEndBgGroup() const { return CIteratorBgGroup(-1, true); }
	
	class CIteratorFgGroup
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorFgGroup() : m_Index(0), m_Reverse(false) {}
		CIteratorFgGroup(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorFgGroup& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_FgGroup(m_Index); }
		bool operator==(const CIteratorFgGroup& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorFgGroup& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorFgGroup BeginFgGroup() const { return CIteratorFgGroup(0, false); }
	CIteratorFgGroup EndFgGroup() const { return CIteratorFgGroup(m_FgGroup.size(), false); }
	CIteratorFgGroup ReverseBeginFgGroup() const { return CIteratorFgGroup(m_FgGroup.size()-1, true); }
	CIteratorFgGroup ReverseEndFgGroup() const { return CIteratorFgGroup(-1, true); }
	
	class CIteratorZoneLayer
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorZoneLayer() : m_Index(0), m_Reverse(false) {}
		CIteratorZoneLayer(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorZoneLayer& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_ZoneLayer(m_Index); }
		bool operator==(const CIteratorZoneLayer& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorZoneLayer& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorZoneLayer BeginZoneLayer() const { return CIteratorZoneLayer(0, false); }
	CIteratorZoneLayer EndZoneLayer() const { return CIteratorZoneLayer(m_ZoneLayer.size(), false); }
	CIteratorZoneLayer ReverseBeginZoneLayer() const { return CIteratorZoneLayer(m_ZoneLayer.size()-1, true); }
	CIteratorZoneLayer ReverseEndZoneLayer() const { return CIteratorZoneLayer(-1, true); }
	
	class CIteratorEntityLayer
	{
	protected:
		int m_Index;
		bool m_Reverse;
	public:
		CIteratorEntityLayer() : m_Index(0), m_Reverse(false) {}
		CIteratorEntityLayer(int Index, bool Reverse) : m_Index(Index), m_Reverse(Reverse) {}
		CIteratorEntityLayer& operator++() { if(m_Reverse) m_Index--; else m_Index++; return *this; }
		CSubPath operator*() { return SubPath_EntityLayer(m_Index); }
		bool operator==(const CIteratorEntityLayer& Iter2) { return Iter2.m_Index == m_Index; }
		bool operator!=(const CIteratorEntityLayer& Iter2) { return Iter2.m_Index != m_Index; }
	};
	
	CIteratorEntityLayer BeginEntityLayer() const { return CIteratorEntityLayer(0, false); }
	CIteratorEntityLayer EndEntityLayer() const { return CIteratorEntityLayer(m_EntityLayer.size(), false); }
	CIteratorEntityLayer ReverseBeginEntityLayer() const { return CIteratorEntityLayer(m_EntityLayer.size()-1, true); }
	CIteratorEntityLayer ReverseEndEntityLayer() const { return CIteratorEntityLayer(-1, true); }
	
	class CTuaType_0_1_0 : public CAsset::CTuaType_0_1_0
	{
	public:
		CTuaArray m_BgGroup;
		CTuaArray m_FgGroup;
		CTuaArray m_ZoneLayer;
		CTuaArray m_EntityLayer;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_Map& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Map& SysType, CTuaType_0_1_0& TuaType);
	};
	
	class CTuaType_0_2_0 : public CAsset::CTuaType_0_2_0
	{
	public:
		CTuaArray m_BgGroup;
		CTuaArray m_FgGroup;
		CTuaArray m_ZoneLayer;
		CTuaArray m_EntityLayer;
		CTuaVec2 m_CameraPosition;
		tua_float m_CameraZoom;
		tua_uint8 m_ShowEntities;
		tua_uint8 m_ShowZones;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Map& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_Map& SysType, CTuaType_0_2_0& TuaType);
	};
	

private:
	array< CAssetPath, allocator_default<CAssetPath> > m_BgGroup;
	array< CAssetPath, allocator_default<CAssetPath> > m_FgGroup;
	array< CAssetPath, allocator_default<CAssetPath> > m_ZoneLayer;
	array< CAssetPath, allocator_default<CAssetPath> > m_EntityLayer;
	vec2 m_CameraPosition;
	float m_CameraZoom;
	bool m_ShowEntities;
	bool m_ShowZones;

public:
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
	
	CAsset_Map();
	void copy(const CAsset_Map& Item)
	{
		CAsset::copy(Item);
		m_BgGroup.copy(Item.m_BgGroup);
		m_FgGroup.copy(Item.m_FgGroup);
		m_ZoneLayer.copy(Item.m_ZoneLayer);
		m_EntityLayer.copy(Item.m_EntityLayer);
		m_CameraPosition = Item.m_CameraPosition;
		m_CameraZoom = Item.m_CameraZoom;
		m_ShowEntities = Item.m_ShowEntities;
		m_ShowZones = Item.m_ShowZones;
	}
	
	void transfert(CAsset_Map& Item)
	{
		CAsset::transfert(Item);
		m_BgGroup.transfert(Item.m_BgGroup);
		m_FgGroup.transfert(Item.m_FgGroup);
		m_ZoneLayer.transfert(Item.m_ZoneLayer);
		m_EntityLayer.transfert(Item.m_EntityLayer);
		m_CameraPosition = Item.m_CameraPosition;
		m_CameraZoom = Item.m_CameraZoom;
		m_ShowEntities = Item.m_ShowEntities;
		m_ShowZones = Item.m_ShowZones;
	}
	
	inline int GetBgGroupArraySize() const { return m_BgGroup.size(); }
	
	inline const CAssetPath* GetBgGroupPtr() const { return m_BgGroup.base_ptr(); }
	
	inline const array< CAssetPath, allocator_default<CAssetPath> >& GetBgGroupArray() const { return m_BgGroup; }
	inline array< CAssetPath, allocator_default<CAssetPath> >& GetBgGroupArray() { return m_BgGroup; }
	
	inline CAssetPath GetBgGroup(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_BgGroup.size());
		return m_BgGroup[SubPath.GetId()];
	}
	
	inline int GetFgGroupArraySize() const { return m_FgGroup.size(); }
	
	inline const CAssetPath* GetFgGroupPtr() const { return m_FgGroup.base_ptr(); }
	
	inline const array< CAssetPath, allocator_default<CAssetPath> >& GetFgGroupArray() const { return m_FgGroup; }
	inline array< CAssetPath, allocator_default<CAssetPath> >& GetFgGroupArray() { return m_FgGroup; }
	
	inline CAssetPath GetFgGroup(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_FgGroup.size());
		return m_FgGroup[SubPath.GetId()];
	}
	
	inline int GetZoneLayerArraySize() const { return m_ZoneLayer.size(); }
	
	inline const CAssetPath* GetZoneLayerPtr() const { return m_ZoneLayer.base_ptr(); }
	
	inline const array< CAssetPath, allocator_default<CAssetPath> >& GetZoneLayerArray() const { return m_ZoneLayer; }
	inline array< CAssetPath, allocator_default<CAssetPath> >& GetZoneLayerArray() { return m_ZoneLayer; }
	
	inline CAssetPath GetZoneLayer(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_ZoneLayer.size());
		return m_ZoneLayer[SubPath.GetId()];
	}
	
	inline int GetEntityLayerArraySize() const { return m_EntityLayer.size(); }
	
	inline const CAssetPath* GetEntityLayerPtr() const { return m_EntityLayer.base_ptr(); }
	
	inline const array< CAssetPath, allocator_default<CAssetPath> >& GetEntityLayerArray() const { return m_EntityLayer; }
	inline array< CAssetPath, allocator_default<CAssetPath> >& GetEntityLayerArray() { return m_EntityLayer; }
	
	inline CAssetPath GetEntityLayer(const CSubPath& SubPath) const
	{
		assert(SubPath.GetId() < m_EntityLayer.size());
		return m_EntityLayer[SubPath.GetId()];
	}
	
	inline vec2 GetCameraPosition() const { return m_CameraPosition; }
	
	inline float GetCameraPositionX() const { return m_CameraPosition.x; }
	
	inline float GetCameraPositionY() const { return m_CameraPosition.y; }
	
	inline float GetCameraZoom() const { return m_CameraZoom; }
	
	inline bool GetShowEntities() const { return m_ShowEntities; }
	
	inline bool GetShowZones() const { return m_ShowZones; }
	
	inline void SetBgGroupArraySize(int Value) { m_BgGroup.resize(Value); }
	
	inline void SetBgGroup(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_BgGroup.size())
		{
			m_BgGroup[SubPath.GetId()] = Value;
		}
	}
	
	inline void SetFgGroupArraySize(int Value) { m_FgGroup.resize(Value); }
	
	inline void SetFgGroup(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_FgGroup.size())
		{
			m_FgGroup[SubPath.GetId()] = Value;
		}
	}
	
	inline void SetZoneLayerArraySize(int Value) { m_ZoneLayer.resize(Value); }
	
	inline void SetZoneLayer(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_ZoneLayer.size())
		{
			m_ZoneLayer[SubPath.GetId()] = Value;
		}
	}
	
	inline void SetEntityLayerArraySize(int Value) { m_EntityLayer.resize(Value); }
	
	inline void SetEntityLayer(const CSubPath& SubPath, const CAssetPath& Value)
	{
		if(SubPath.GetId() < m_EntityLayer.size())
		{
			m_EntityLayer[SubPath.GetId()] = Value;
		}
	}
	
	inline void SetCameraPosition(vec2 Value) { m_CameraPosition = Value; }
	
	inline void SetCameraPositionX(float Value) { m_CameraPosition.x = Value; }
	
	inline void SetCameraPositionY(float Value) { m_CameraPosition.y = Value; }
	
	inline void SetCameraZoom(float Value) { m_CameraZoom = Value; }
	
	inline void SetShowEntities(bool Value) { m_ShowEntities = Value; }
	
	inline void SetShowZones(bool Value) { m_ShowZones = Value; }
	
	inline int AddBgGroup()
	{
		int Id = m_BgGroup.size();
		m_BgGroup.increment();
		return Id;
	}
	
	inline int AddFgGroup()
	{
		int Id = m_FgGroup.size();
		m_FgGroup.increment();
		return Id;
	}
	
	inline int AddZoneLayer()
	{
		int Id = m_ZoneLayer.size();
		m_ZoneLayer.increment();
		return Id;
	}
	
	inline int AddEntityLayer()
	{
		int Id = m_EntityLayer.size();
		m_EntityLayer.increment();
		return Id;
	}
	
	inline void AddAtBgGroup(int Index) { m_BgGroup.insertat_and_init(Index); }
	
	inline void AddAtFgGroup(int Index) { m_FgGroup.insertat_and_init(Index); }
	
	inline void AddAtZoneLayer(int Index) { m_ZoneLayer.insertat_and_init(Index); }
	
	inline void AddAtEntityLayer(int Index) { m_EntityLayer.insertat_and_init(Index); }
	
	inline void DeleteBgGroup(const CSubPath& SubPath) { m_BgGroup.remove_index(SubPath.GetId()); }
	
	inline void DeleteFgGroup(const CSubPath& SubPath) { m_FgGroup.remove_index(SubPath.GetId()); }
	
	inline void DeleteZoneLayer(const CSubPath& SubPath) { m_ZoneLayer.remove_index(SubPath.GetId()); }
	
	inline void DeleteEntityLayer(const CSubPath& SubPath) { m_EntityLayer.remove_index(SubPath.GetId()); }
	
	inline void RelMoveBgGroup(const CSubPath& SubPath, int RelMove) { m_BgGroup.relative_move(SubPath.GetId(), RelMove); }
	
	inline void RelMoveFgGroup(const CSubPath& SubPath, int RelMove) { m_FgGroup.relative_move(SubPath.GetId(), RelMove); }
	
	inline void RelMoveZoneLayer(const CSubPath& SubPath, int RelMove) { m_ZoneLayer.relative_move(SubPath.GetId(), RelMove); }
	
	inline void RelMoveEntityLayer(const CSubPath& SubPath, int RelMove) { m_EntityLayer.relative_move(SubPath.GetId(), RelMove); }
	
	inline bool IsValidBgGroup(const CSubPath& SubPath) const { return (SubPath.GetId() < m_BgGroup.size()); }
	
	inline bool IsValidFgGroup(const CSubPath& SubPath) const { return (SubPath.GetId() < m_FgGroup.size()); }
	
	inline bool IsValidZoneLayer(const CSubPath& SubPath) const { return (SubPath.GetId() < m_ZoneLayer.size()); }
	
	inline bool IsValidEntityLayer(const CSubPath& SubPath) const { return (SubPath.GetId() < m_EntityLayer.size()); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		{
			int Shift = 0;
			for(int i=0; i<m_BgGroup.size(); i++)
			{
				if(Operation.MustBeDeleted(m_BgGroup[i]))
					Shift++;
				else if(Shift > 0)
					m_BgGroup[i-Shift] = m_BgGroup[i];
			}
			m_BgGroup.resize(m_BgGroup.size()-Shift);
		}
		for(int i=0; i<m_BgGroup.size(); i++)
		{
			Operation.Apply(m_BgGroup[i]);
		}
		{
			int Shift = 0;
			for(int i=0; i<m_FgGroup.size(); i++)
			{
				if(Operation.MustBeDeleted(m_FgGroup[i]))
					Shift++;
				else if(Shift > 0)
					m_FgGroup[i-Shift] = m_FgGroup[i];
			}
			m_FgGroup.resize(m_FgGroup.size()-Shift);
		}
		for(int i=0; i<m_FgGroup.size(); i++)
		{
			Operation.Apply(m_FgGroup[i]);
		}
		{
			int Shift = 0;
			for(int i=0; i<m_ZoneLayer.size(); i++)
			{
				if(Operation.MustBeDeleted(m_ZoneLayer[i]))
					Shift++;
				else if(Shift > 0)
					m_ZoneLayer[i-Shift] = m_ZoneLayer[i];
			}
			m_ZoneLayer.resize(m_ZoneLayer.size()-Shift);
		}
		for(int i=0; i<m_ZoneLayer.size(); i++)
		{
			Operation.Apply(m_ZoneLayer[i]);
		}
		{
			int Shift = 0;
			for(int i=0; i<m_EntityLayer.size(); i++)
			{
				if(Operation.MustBeDeleted(m_EntityLayer[i]))
					Shift++;
				else if(Shift > 0)
					m_EntityLayer[i-Shift] = m_EntityLayer[i];
			}
			m_EntityLayer.resize(m_EntityLayer.size()-Shift);
		}
		for(int i=0; i<m_EntityLayer.size(); i++)
		{
			Operation.Apply(m_EntityLayer[i]);
		}
	}
	
};

template<> int CAsset_Map::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const;
template<> bool CAsset_Map::SetValue(int ValueType, const CSubPath& SubPath, int Value);
template<> bool CAsset_Map::GetValue(int ValueType, const CSubPath& SubPath, bool DefaultValue) const;
template<> bool CAsset_Map::SetValue(int ValueType, const CSubPath& SubPath, bool Value);
template<> float CAsset_Map::GetValue(int ValueType, const CSubPath& SubPath, float DefaultValue) const;
template<> bool CAsset_Map::SetValue(int ValueType, const CSubPath& SubPath, float Value);
template<> vec2 CAsset_Map::GetValue(int ValueType, const CSubPath& SubPath, vec2 DefaultValue) const;
template<> bool CAsset_Map::SetValue(int ValueType, const CSubPath& SubPath, vec2 Value);
template<> CAssetPath CAsset_Map::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const;
template<> bool CAsset_Map::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value);

#endif
