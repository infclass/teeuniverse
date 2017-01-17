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

#include <generated/assets/guicomboboxstyle.h>
#include <shared/assets/assetssaveloadcontext.h>
#include <shared/archivefile.h>


void CAsset_GuiComboBoxStyle::CTuaType_0_1_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_GuiComboBoxStyle& SysType)
{
	CAsset::CTuaType_0_1_0::Read(pLoadingContext, TuaType, SysType);

}


void CAsset_GuiComboBoxStyle::CTuaType_0_1_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiComboBoxStyle& SysType, CTuaType_0_1_0& TuaType)
{
	CAsset::CTuaType_0_1_0::Write(pLoadingContext, SysType, TuaType);

}

void CAsset_GuiComboBoxStyle::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_GuiComboBoxStyle& SysType)
{
	CAsset::CTuaType_0_2_0::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_ButtonPath, SysType.m_ButtonPath);
	pLoadingContext->ReadAssetPath(TuaType.m_PopupPath, SysType.m_PopupPath);
	pLoadingContext->ReadAssetPath(TuaType.m_EnumPath, SysType.m_EnumPath);
}


void CAsset_GuiComboBoxStyle::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiComboBoxStyle& SysType, CTuaType_0_2_0& TuaType)
{
	CAsset::CTuaType_0_2_0::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_ButtonPath, TuaType.m_ButtonPath);
	pLoadingContext->WriteAssetPath(SysType.m_PopupPath, TuaType.m_PopupPath);
	pLoadingContext->WriteAssetPath(SysType.m_EnumPath, TuaType.m_EnumPath);
}

void CAsset_GuiComboBoxStyle::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_GuiComboBoxStyle& SysType)
{
	CAsset::CTuaType_0_2_1::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_ButtonPath, SysType.m_ButtonPath);
	pLoadingContext->ReadAssetPath(TuaType.m_PopupPath, SysType.m_PopupPath);
	pLoadingContext->ReadAssetPath(TuaType.m_EnumPath, SysType.m_EnumPath);
}


void CAsset_GuiComboBoxStyle::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiComboBoxStyle& SysType, CTuaType_0_2_1& TuaType)
{
	CAsset::CTuaType_0_2_1::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_ButtonPath, TuaType.m_ButtonPath);
	pLoadingContext->WriteAssetPath(SysType.m_PopupPath, TuaType.m_PopupPath);
	pLoadingContext->WriteAssetPath(SysType.m_EnumPath, TuaType.m_EnumPath);
}

template<>
CAssetPath CAsset_GuiComboBoxStyle::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const
{
	switch(ValueType)
	{
		case BUTTONPATH:
			return GetButtonPath();
		case POPUPPATH:
			return GetPopupPath();
		case ENUMPATH:
			return GetEnumPath();
	}
	return CAsset::GetValue<CAssetPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_GuiComboBoxStyle::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value)
{
	switch(ValueType)
	{
		case BUTTONPATH:
			SetButtonPath(Value);
			return true;
		case POPUPPATH:
			SetPopupPath(Value);
			return true;
		case ENUMPATH:
			SetEnumPath(Value);
			return true;
	}
	return CAsset::SetValue<CAssetPath>(ValueType, SubPath, Value);
}

int CAsset_GuiComboBoxStyle::AddSubItem(int Type, const CSubPath& SubPath)
{
	return -1;
}

int CAsset_GuiComboBoxStyle::AddSubItemAt(int Type, const CSubPath& SubPath, int Index)
{
	return -1;
}

void CAsset_GuiComboBoxStyle::DeleteSubItem(const CSubPath& SubPath)
{
}

void CAsset_GuiComboBoxStyle::RelMoveSubItem(const CSubPath& SubPath, int RelMove)
{
}


