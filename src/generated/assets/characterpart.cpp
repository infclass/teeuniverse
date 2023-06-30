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

#include <generated/assets/characterpart.h>
#include <shared/assets/assetssaveloadcontext.h>
#include <shared/archivefile.h>


void CAsset_CharacterPart::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_2_0::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_2_0& TuaType)
{
	CAsset::CTuaType_0_2_0::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_2_1::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_2_1& TuaType)
{
	CAsset::CTuaType_0_2_1::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_2_2::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_2& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_2_2::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_2_2::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_2_2& TuaType)
{
	CAsset::CTuaType_0_2_2::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_2_3::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_3& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_2_3::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_2_3::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_2_3& TuaType)
{
	CAsset::CTuaType_0_2_3::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_2_4::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_4& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_2_4::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_2_4::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_2_4& TuaType)
{
	CAsset::CTuaType_0_2_4::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_3_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_0& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_3_0::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_3_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_3_0& TuaType)
{
	CAsset::CTuaType_0_3_0::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

void CAsset_CharacterPart::CTuaType_0_3_3::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_3_3& TuaType, CAsset_CharacterPart& SysType)
{
	CAsset::CTuaType_0_3_3::Read(pLoadingContext, TuaType, SysType);

	pLoadingContext->ReadAssetPath(TuaType.m_CharacterPath, SysType.m_CharacterPath);
	CSubPath::CTuaType::Read(pLoadingContext->ArchiveFile(), TuaType.m_CharacterPart, SysType.m_CharacterPart);
	pLoadingContext->ReadAssetPath(TuaType.m_SkeletonSkinPath, SysType.m_SkeletonSkinPath);
}


void CAsset_CharacterPart::CTuaType_0_3_3::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_CharacterPart& SysType, CTuaType_0_3_3& TuaType)
{
	CAsset::CTuaType_0_3_3::Write(pLoadingContext, SysType, TuaType);

	pLoadingContext->WriteAssetPath(SysType.m_CharacterPath, TuaType.m_CharacterPath);
	CSubPath::CTuaType::Write(pLoadingContext->ArchiveFile(), SysType.m_CharacterPart, TuaType.m_CharacterPart);
	pLoadingContext->WriteAssetPath(SysType.m_SkeletonSkinPath, TuaType.m_SkeletonSkinPath);
}

template<>
CAssetPath CAsset_CharacterPart::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const
{
	switch(ValueType)
	{
		case CHARACTERPATH:
			return GetCharacterPath();
		case SKELETONSKINPATH:
			return GetSkeletonSkinPath();
	}
	return CAsset::GetValue<CAssetPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_CharacterPart::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value)
{
	switch(ValueType)
	{
		case CHARACTERPATH:
			SetCharacterPath(Value);
			return true;
		case SKELETONSKINPATH:
			SetSkeletonSkinPath(Value);
			return true;
	}
	return CAsset::SetValue<CAssetPath>(ValueType, SubPath, Value);
}

template<>
CSubPath CAsset_CharacterPart::GetValue(int ValueType, const CSubPath& SubPath, CSubPath DefaultValue) const
{
	switch(ValueType)
	{
		case CHARACTERPART:
			return GetCharacterPart();
	}
	return CAsset::GetValue<CSubPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_CharacterPart::SetValue(int ValueType, const CSubPath& SubPath, CSubPath Value)
{
	switch(ValueType)
	{
		case CHARACTERPART:
			SetCharacterPart(Value);
			return true;
	}
	return CAsset::SetValue<CSubPath>(ValueType, SubPath, Value);
}

int CAsset_CharacterPart::AddSubItem(int Type, const CSubPath& SubPath)
{
	return -1;
}

int CAsset_CharacterPart::AddSubItemAt(int Type, const CSubPath& SubPath, int Index)
{
	return -1;
}

void CAsset_CharacterPart::DeleteSubItem(const CSubPath& SubPath)
{
}

void CAsset_CharacterPart::RelMoveSubItem(CSubPath& SubPath, int RelMove)
{
}


