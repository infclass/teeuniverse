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

#ifndef __CLIENT_ASSETS_MAPLAYERTILES__
#define __CLIENT_ASSETS_MAPLAYERTILES__

#include <shared/assets/asset.h>
#include <shared/tl/array2d.h>
#include <shared/math/vector.h>
#include <shared/assets/assetpath.h>

class CAsset_MapLayerTiles : public CAsset
{
public:
	enum
	{
		TILEFLAG_VFLIP=1,
		TILEFLAG_HFLIP=2,
		TILEFLAG_OPAQUE=4,
		TILEFLAG_ROTATE=8,
	};
	
	static const int TypeId = 17;
	
	enum
	{
		TYPE_TILE,
	};
	
	static inline CSubPath SubPath_Tile(int Id0, int Id1) { return CSubPath(TYPE_TILE, Id0, Id1, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		PARENTPATH,
		IMAGEPATH,
		COLOR,
		TILE_WIDTH,
		TILE_HEIGHT,
		TILE_DEPTH,
		TILE_PTR,
		TILE_ARRAY,
		TILE_INDEX,
		TILE_FLAGS,
		TILE,
		VISIBILITY,
		POSITIONX,
		POSITIONY,
	};
	
	class CTile
	{
	public:
		class CTuaType_0_1_0
		{
		public:
			tua_uint8 m_Index;
			tua_uint8 m_Flags;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_MapLayerTiles::CTile& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles::CTile& SysType, CTuaType_0_1_0& TuaType);
		};
		
		class CTuaType_0_2_0
		{
		public:
			tua_uint8 m_Index;
			tua_uint8 m_Flags;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_MapLayerTiles::CTile& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles::CTile& SysType, CTuaType_0_2_0& TuaType);
		};
		
		class CTuaType_0_2_1
		{
		public:
			tua_uint8 m_Index;
			tua_uint8 m_Flags;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_MapLayerTiles::CTile& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles::CTile& SysType, CTuaType_0_2_1& TuaType);
		};
		
		class CTuaType_0_2_2
		{
		public:
			tua_uint8 m_Index;
			tua_uint8 m_Flags;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_MapLayerTiles::CTile& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles::CTile& SysType, CTuaType_0_2_2& TuaType);
		};
		
	
	private:
		uint8 m_Index;
		uint8 m_Flags;
	
	public:
		CTile();
		inline uint8 GetIndex() const { return m_Index; }
		
		inline uint8 GetFlags() const { return m_Flags; }
		
		inline void SetIndex(uint8 Value) { m_Index = Value; }
		
		inline void SetFlags(uint8 Value) { m_Flags = Value; }
		
		void AssetPathOperation(const CAssetPath::COperation& Operation)
		{
		}
		
	};
	class CTuaType_0_1_0 : public CAsset::CTuaType_0_1_0
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CAssetPath::CTuaType m_ImagePath;
		tua_uint32 m_Color;
		CTuaArray2d m_Tile;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_MapLayerTiles& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles& SysType, CTuaType_0_1_0& TuaType);
	};
	
	class CTuaType_0_2_0 : public CAsset::CTuaType_0_2_0
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CAssetPath::CTuaType m_ImagePath;
		tua_uint32 m_Color;
		CTuaArray2d m_Tile;
		tua_uint8 m_Visibility;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_MapLayerTiles& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles& SysType, CTuaType_0_2_0& TuaType);
	};
	
	class CTuaType_0_2_1 : public CAsset::CTuaType_0_2_1
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CAssetPath::CTuaType m_ImagePath;
		tua_uint32 m_Color;
		CTuaArray2d m_Tile;
		tua_uint8 m_Visibility;
		tua_int32 m_PositionX;
		tua_int32 m_PositionY;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_MapLayerTiles& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles& SysType, CTuaType_0_2_1& TuaType);
	};
	
	class CTuaType_0_2_2 : public CAsset::CTuaType_0_2_2
	{
	public:
		CAssetPath::CTuaType m_ParentPath;
		CAssetPath::CTuaType m_ImagePath;
		tua_uint32 m_Color;
		CTuaArray2d m_Tile;
		tua_uint8 m_Visibility;
		tua_int32 m_PositionX;
		tua_int32 m_PositionY;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_MapLayerTiles& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapLayerTiles& SysType, CTuaType_0_2_2& TuaType);
	};
	

private:
	CAssetPath m_ParentPath;
	CAssetPath m_ImagePath;
	vec4 m_Color;
	array2d< CTile > m_Tile;
	bool m_Visibility;
	int m_PositionX;
	int m_PositionY;

public:
	virtual ~CAsset_MapLayerTiles() {}
	
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
	
	CAsset_MapLayerTiles();
	inline CAssetPath GetParentPath() const { return m_ParentPath; }
	
	inline CAssetPath GetImagePath() const { return m_ImagePath; }
	
	inline vec4 GetColor() const { return m_Color; }
	
	inline int GetTileWidth() const { return m_Tile.get_width(); }
	
	inline int GetTileHeight() const { return m_Tile.get_height(); }
	
	inline int GetTileDepth() const { return m_Tile.get_depth(); }
	
	inline const CAsset_MapLayerTiles::CTile* GetTilePtr() const { return m_Tile.base_ptr(); }
	
	inline const array2d< CTile >& GetTileArray() const { return m_Tile; }
	inline array2d< CTile >& GetTileArray() { return m_Tile; }
	
	inline const CAsset_MapLayerTiles::CTile& GetTile(const CSubPath& SubPath) const { return m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()); }
	
	inline uint8 GetTileIndex(const CSubPath& SubPath) const { return m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).GetIndex(); }
	
	inline uint8 GetTileFlags(const CSubPath& SubPath) const { return m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).GetFlags(); }
	
	inline bool GetVisibility() const { return m_Visibility; }
	
	inline int GetPositionX() const { return m_PositionX; }
	
	inline int GetPositionY() const { return m_PositionY; }
	
	inline void SetParentPath(const CAssetPath& Value) { m_ParentPath = Value; }
	
	inline void SetImagePath(const CAssetPath& Value) { m_ImagePath = Value; }
	
	inline void SetColor(vec4 Value) { m_Color = Value; }
	
	inline void SetTileWidth(int Value) { m_Tile.resize_width(max(Value, 1)); }
	
	inline void SetTileHeight(int Value) { m_Tile.resize_height(max(Value, 1)); }
	
	inline void SetTileDepth(int Value) { m_Tile.resize_depth(max(Value, 1)); }
	
	inline void SetTile(const CSubPath& SubPath, const CAsset_MapLayerTiles::CTile& Value) { m_Tile.set_clamp(SubPath.GetId(), SubPath.GetId2(), Value); }
	
	inline void SetTileIndex(const CSubPath& SubPath, uint8 Value) { m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).SetIndex(Value); }
	
	inline void SetTileFlags(const CSubPath& SubPath, uint8 Value) { m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).SetFlags(Value); }
	
	inline void SetVisibility(bool Value) { m_Visibility = Value; }
	
	inline void SetPositionX(int Value) { m_PositionX = Value; }
	
	inline void SetPositionY(int Value) { m_PositionY = Value; }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_ParentPath);
		Operation.Apply(m_ImagePath);
		for(int i=0; i<m_Tile.get_linear_size(); i++)
		{
			m_Tile.linear_get_clamp(i).AssetPathOperation(Operation);
		}
	}
	
};

template<> int CAsset_MapLayerTiles::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const;
template<> bool CAsset_MapLayerTiles::SetValue(int ValueType, const CSubPath& SubPath, int Value);
template<> bool CAsset_MapLayerTiles::GetValue(int ValueType, const CSubPath& SubPath, bool DefaultValue) const;
template<> bool CAsset_MapLayerTiles::SetValue(int ValueType, const CSubPath& SubPath, bool Value);
template<> vec4 CAsset_MapLayerTiles::GetValue(int ValueType, const CSubPath& SubPath, vec4 DefaultValue) const;
template<> bool CAsset_MapLayerTiles::SetValue(int ValueType, const CSubPath& SubPath, vec4 Value);
template<> CAssetPath CAsset_MapLayerTiles::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const;
template<> bool CAsset_MapLayerTiles::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value);

#endif
