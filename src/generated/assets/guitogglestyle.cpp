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

#include <generated/assets/guitogglestyle.h>
#include <shared/assets/assetssaveloadcontext.h>
#include <shared/archivefile.h>

CAsset_GuiToggleStyle::CAsset_GuiToggleStyle()
{
	m_SwitchIcon = false;
}

void CAsset_GuiToggleStyle::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_2_0::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_2_0& TuaType)
{
	CAsset::CTuaType_0_2_0::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_2_1::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_2_1& TuaType)
{
	CAsset::CTuaType_0_2_1::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_2_2::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_2_2::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_2_2::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_2_2& TuaType)
{
	CAsset::CTuaType_0_2_2::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_2_3::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_3& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_2_3::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_2_3::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_2_3& TuaType)
{
	CAsset::CTuaType_0_2_3::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_2_4::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_4& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_2_4::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_2_4::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_2_4& TuaType)
{
	CAsset::CTuaType_0_2_4::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_3_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_0& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_3_0::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_3_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_3_0& TuaType)
{
	CAsset::CTuaType_0_3_0::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

void CAsset_GuiToggleStyle::CTuaType_0_3_3::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_3& TuaType, CAsset_GuiToggleStyle& SysType)
{
	CAsset::CTuaType_0_3_3::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_IdleTrueStylePath, SysType.m_IdleTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverTrueStylePath, SysType.m_MouseOverTrueStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconTruePath, SysType.m_IconTruePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IdleFalseStylePath, SysType.m_IdleFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_MouseOverFalseStylePath, SysType.m_MouseOverFalseStylePath);
	pLoadingContext->ReadAssetPath(TuaType.m_IconFalsePath, SysType.m_IconFalsePath);
	SysType.m_SwitchIcon = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_SwitchIcon);
}


void CAsset_GuiToggleStyle::CTuaType_0_3_3::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiToggleStyle& SysType, CTuaType_0_3_3& TuaType)
{
	CAsset::CTuaType_0_3_3::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_IdleTrueStylePath, TuaType.m_IdleTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverTrueStylePath, TuaType.m_MouseOverTrueStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconTruePath, TuaType.m_IconTruePath);
	pLoadingContext->WriteAssetPath(SysType.m_IdleFalseStylePath, TuaType.m_IdleFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_MouseOverFalseStylePath, TuaType.m_MouseOverFalseStylePath);
	pLoadingContext->WriteAssetPath(SysType.m_IconFalsePath, TuaType.m_IconFalsePath);
	TuaType.m_SwitchIcon = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_SwitchIcon);
}

template<>
bool CAsset_GuiToggleStyle::GetValue(int ValueType, const CSubPath& SubPath, bool DefaultValue) const
{
	switch(ValueType)
	{
		case SWITCHICON:
			return GetSwitchIcon();
	}
	return CAsset::GetValue<bool>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_GuiToggleStyle::SetValue(int ValueType, const CSubPath& SubPath, bool Value)
{
	switch(ValueType)
	{
		case SWITCHICON:
			SetSwitchIcon(Value);
			return true;
	}
	return CAsset::SetValue<bool>(ValueType, SubPath, Value);
}

template<>
CAssetPath CAsset_GuiToggleStyle::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const
{
	switch(ValueType)
	{
		case IDLETRUESTYLEPATH:
			return GetIdleTrueStylePath();
		case MOUSEOVERTRUESTYLEPATH:
			return GetMouseOverTrueStylePath();
		case ICONTRUEPATH:
			return GetIconTruePath();
		case IDLEFALSESTYLEPATH:
			return GetIdleFalseStylePath();
		case MOUSEOVERFALSESTYLEPATH:
			return GetMouseOverFalseStylePath();
		case ICONFALSEPATH:
			return GetIconFalsePath();
	}
	return CAsset::GetValue<CAssetPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_GuiToggleStyle::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value)
{
	switch(ValueType)
	{
		case IDLETRUESTYLEPATH:
			SetIdleTrueStylePath(Value);
			return true;
		case MOUSEOVERTRUESTYLEPATH:
			SetMouseOverTrueStylePath(Value);
			return true;
		case ICONTRUEPATH:
			SetIconTruePath(Value);
			return true;
		case IDLEFALSESTYLEPATH:
			SetIdleFalseStylePath(Value);
			return true;
		case MOUSEOVERFALSESTYLEPATH:
			SetMouseOverFalseStylePath(Value);
			return true;
		case ICONFALSEPATH:
			SetIconFalsePath(Value);
			return true;
	}
	return CAsset::SetValue<CAssetPath>(ValueType, SubPath, Value);
}

int CAsset_GuiToggleStyle::AddSubItem(int Type, const CSubPath& SubPath)
{
	return -1;
}

int CAsset_GuiToggleStyle::AddSubItemAt(int Type, const CSubPath& SubPath, int Index)
{
	return -1;
}

void CAsset_GuiToggleStyle::DeleteSubItem(const CSubPath& SubPath)
{
}

void CAsset_GuiToggleStyle::RelMoveSubItem(CSubPath& SubPath, int RelMove)
{
}


