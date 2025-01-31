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

#ifndef __CLIENT_ASSETS_GUISCROLLBARSTYLE__
#define __CLIENT_ASSETS_GUISCROLLBARSTYLE__

#include <shared/assets/asset.h>
#include <shared/assets/assetpath.h>

class CAsset_GuiScrollbarStyle : public CAsset
{
public:
	static const int TypeId = 9;
	
	enum
	{
		NAME = CAsset::NAME,
		RECTPATH,
		DEFAULTRAILPATH,
		DEFAULTSLIDERPATH,
		MOUSEOVERSLIDERPATH,
		MARGIN,
		PADDING,
	};
	
	class CTuaType_0_2_0 : public CAsset::CTuaType_0_2_0
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_2_0& TuaType);
	};
	
	class CTuaType_0_2_1 : public CAsset::CTuaType_0_2_1
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_2_1& TuaType);
	};
	
	class CTuaType_0_2_2 : public CAsset::CTuaType_0_2_2
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_2_2& TuaType);
	};
	
	class CTuaType_0_2_3 : public CAsset::CTuaType_0_2_3
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_3& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_2_3& TuaType);
	};
	
	class CTuaType_0_2_4 : public CAsset::CTuaType_0_2_4
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_4& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_2_4& TuaType);
	};
	
	class CTuaType_0_3_0 : public CAsset::CTuaType_0_3_0
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_0& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_3_0& TuaType);
	};
	
	class CTuaType_0_3_3 : public CAsset::CTuaType_0_3_3
	{
	public:
		CAssetPath::CTuaType m_RectPath;
		CAssetPath::CTuaType m_DefaultRailPath;
		CAssetPath::CTuaType m_DefaultSliderPath;
		CAssetPath::CTuaType m_MouseOverSliderPath;
		tua_int32 m_Margin;
		tua_int32 m_Padding;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_3& TuaType, CAsset_GuiScrollbarStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiScrollbarStyle& SysType, CTuaType_0_3_3& TuaType);
	};
	

private:
	CAssetPath m_RectPath{};
	CAssetPath m_DefaultRailPath{};
	CAssetPath m_DefaultSliderPath{};
	CAssetPath m_MouseOverSliderPath{};
	int m_Margin{};
	int m_Padding{};

public:
	virtual ~CAsset_GuiScrollbarStyle() {}
	
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
	
	CAsset_GuiScrollbarStyle();
	CAssetPath GetRectPath() const { return m_RectPath; }
	
	CAssetPath GetDefaultRailPath() const { return m_DefaultRailPath; }
	
	CAssetPath GetDefaultSliderPath() const { return m_DefaultSliderPath; }
	
	CAssetPath GetMouseOverSliderPath() const { return m_MouseOverSliderPath; }
	
	int GetMargin() const { return m_Margin; }
	
	int GetPadding() const { return m_Padding; }
	
	void SetRectPath(const CAssetPath& Value) { m_RectPath = Value; }
	
	void SetDefaultRailPath(const CAssetPath& Value) { m_DefaultRailPath = Value; }
	
	void SetDefaultSliderPath(const CAssetPath& Value) { m_DefaultSliderPath = Value; }
	
	void SetMouseOverSliderPath(const CAssetPath& Value) { m_MouseOverSliderPath = Value; }
	
	void SetMargin(int Value) { m_Margin = Value; }
	
	void SetPadding(int Value) { m_Padding = Value; }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_RectPath);
		Operation.Apply(m_DefaultRailPath);
		Operation.Apply(m_DefaultSliderPath);
		Operation.Apply(m_MouseOverSliderPath);
	}
	
};

template<> int CAsset_GuiScrollbarStyle::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const;
template<> bool CAsset_GuiScrollbarStyle::SetValue(int ValueType, const CSubPath& SubPath, int Value);
template<> CAssetPath CAsset_GuiScrollbarStyle::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const;
template<> bool CAsset_GuiScrollbarStyle::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value);

#endif
