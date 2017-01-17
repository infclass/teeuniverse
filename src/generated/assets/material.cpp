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

#include <generated/assets/material.h>
#include <shared/assets/assetssaveloadcontext.h>
#include <shared/archivefile.h>

CAsset_Material::CLabel::CLabel()
{
	m_Color = 1.0f;
	m_AngleStart = 0.0f;
	m_AngleEnd = 2.0f*Pi;
}

CAsset_Material::CSprite::CSprite()
{
	m_Size = 1.0f;
	m_Color = 1.0f;
	m_Flags = 0x0;
	m_Position = 0.0f;
	m_Alignment = SPRITEALIGN_LINE;
	m_Filling = SPRITEFILLING_SCALING;
	m_TileType = SPRITETILE_LINE;
	m_TileLabel0 = 0;
	m_TileLabel1 = 0;
}

CAsset_Material::CAsset_Material()
{
	m_TextureSize = 1.0f;
	m_TextureAngle = 0.0f;
	m_TextureSpacing = 0.0f;
	m_TextureEnabled = false;
}

void CAsset_Material::CLabel::CTuaType_0_1_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_Material::CLabel& SysType)
{
}


void CAsset_Material::CSprite::CTuaType_0_1_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_Material::CSprite& SysType)
{
}


void CAsset_Material::CLayer::CTuaType_0_1_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_Material::CLayer& SysType)
{
}


void CAsset_Material::CTuaType_0_1_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_1_0& TuaType, CAsset_Material& SysType)
{
	CAsset::CTuaType_0_1_0::Read(pLoadingContext, TuaType, SysType);

}


void CAsset_Material::CLabel::CTuaType_0_1_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLabel& SysType, CTuaType_0_1_0& TuaType)
{
}

void CAsset_Material::CSprite::CTuaType_0_1_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CSprite& SysType, CTuaType_0_1_0& TuaType)
{
}

void CAsset_Material::CLayer::CTuaType_0_1_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLayer& SysType, CTuaType_0_1_0& TuaType)
{
}

void CAsset_Material::CTuaType_0_1_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material& SysType, CTuaType_0_1_0& TuaType)
{
	CAsset::CTuaType_0_1_0::Write(pLoadingContext, SysType, TuaType);

}

void CAsset_Material::CLabel::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Material::CLabel& SysType)
{
	SysType.m_Color = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color);
	SysType.m_AngleStart = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_AngleStart);
	SysType.m_AngleEnd = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_AngleEnd);
}


void CAsset_Material::CSprite::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Material::CSprite& SysType)
{
	pLoadingContext->ReadAssetPath(TuaType.m_Path, SysType.m_Path);
	SysType.m_Size.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_X);
	SysType.m_Size.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_Y);
	SysType.m_Color = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color);
	SysType.m_Flags = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Flags);
	SysType.m_Position.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Position.m_X);
	SysType.m_Position.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Position.m_Y);
	SysType.m_Alignment = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Alignment);
	SysType.m_Filling = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Filling);
	SysType.m_TileType = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileType);
	SysType.m_TileLabel0 = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileLabel0);
	SysType.m_TileLabel1 = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileLabel1);
}


void CAsset_Material::CLayer::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Material::CLayer& SysType)
{
	{
		const CAsset_Material::CSprite::CTuaType_0_2_0* pData = (const CAsset_Material::CSprite::CTuaType_0_2_0*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Sprite.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Sprite.m_Size);
		SysType.m_Sprite.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CSprite::CTuaType_0_2_0::Read(pLoadingContext, pData[i], SysType.m_Sprite[i]);
		}
	}
	
}


void CAsset_Material::CTuaType_0_2_0::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_0& TuaType, CAsset_Material& SysType)
{
	CAsset::CTuaType_0_2_0::Read(pLoadingContext, TuaType, SysType);

	{
		const CAsset_Material::CLabel::CTuaType_0_2_0* pData = (const CAsset_Material::CLabel::CTuaType_0_2_0*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Label.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Label.m_Size);
		SysType.m_Label.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CLabel::CTuaType_0_2_0::Read(pLoadingContext, pData[i], SysType.m_Label[i]);
		}
	}
	
	{
		const CAsset_Material::CLayer::CTuaType_0_2_0* pData = (const CAsset_Material::CLayer::CTuaType_0_2_0*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Layer.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Layer.m_Size);
		SysType.m_Layer.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CLayer::CTuaType_0_2_0::Read(pLoadingContext, pData[i], SysType.m_Layer[i]);
		}
	}
	
	pLoadingContext->ReadAssetPath(TuaType.m_TexturePath, SysType.m_TexturePath);
	SysType.m_TextureColor = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_TextureColor);
	SysType.m_TextureSize.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSize.m_X);
	SysType.m_TextureSize.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSize.m_Y);
	SysType.m_TextureAngle = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureAngle);
	SysType.m_TextureSpacing = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSpacing);
	SysType.m_TextureEnabled = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_TextureEnabled);
}


void CAsset_Material::CLabel::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLabel& SysType, CTuaType_0_2_0& TuaType)
{
	TuaType.m_Color = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color);
	TuaType.m_AngleStart = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_AngleStart);
	TuaType.m_AngleEnd = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_AngleEnd);
}

void CAsset_Material::CSprite::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CSprite& SysType, CTuaType_0_2_0& TuaType)
{
	pLoadingContext->WriteAssetPath(SysType.m_Path, TuaType.m_Path);
	TuaType.m_Size.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.x);
	TuaType.m_Size.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.y);
	TuaType.m_Color = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color);
	TuaType.m_Flags = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Flags);
	TuaType.m_Position.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Position.x);
	TuaType.m_Position.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Position.y);
	TuaType.m_Alignment = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Alignment);
	TuaType.m_Filling = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Filling);
	TuaType.m_TileType = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileType);
	TuaType.m_TileLabel0 = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileLabel0);
	TuaType.m_TileLabel1 = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileLabel1);
}

void CAsset_Material::CLayer::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLayer& SysType, CTuaType_0_2_0& TuaType)
{
	{
		TuaType.m_Sprite.m_Size = SysType.m_Sprite.size();
		CAsset_Material::CSprite::CTuaType_0_2_0* pData = new CAsset_Material::CSprite::CTuaType_0_2_0[SysType.m_Sprite.size()];
		for(int i=0; i<SysType.m_Sprite.size(); i++)
		{
			CAsset_Material::CSprite::CTuaType_0_2_0::Write(pLoadingContext, SysType.m_Sprite[i], pData[i]);
		}
		TuaType.m_Sprite.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CSprite::CTuaType_0_2_0)*SysType.m_Sprite.size());
		delete[] pData;
	}
}

void CAsset_Material::CTuaType_0_2_0::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material& SysType, CTuaType_0_2_0& TuaType)
{
	CAsset::CTuaType_0_2_0::Write(pLoadingContext, SysType, TuaType);

	{
		TuaType.m_Label.m_Size = SysType.m_Label.size();
		CAsset_Material::CLabel::CTuaType_0_2_0* pData = new CAsset_Material::CLabel::CTuaType_0_2_0[SysType.m_Label.size()];
		for(int i=0; i<SysType.m_Label.size(); i++)
		{
			CAsset_Material::CLabel::CTuaType_0_2_0::Write(pLoadingContext, SysType.m_Label[i], pData[i]);
		}
		TuaType.m_Label.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CLabel::CTuaType_0_2_0)*SysType.m_Label.size());
		delete[] pData;
	}
	{
		TuaType.m_Layer.m_Size = SysType.m_Layer.size();
		CAsset_Material::CLayer::CTuaType_0_2_0* pData = new CAsset_Material::CLayer::CTuaType_0_2_0[SysType.m_Layer.size()];
		for(int i=0; i<SysType.m_Layer.size(); i++)
		{
			CAsset_Material::CLayer::CTuaType_0_2_0::Write(pLoadingContext, SysType.m_Layer[i], pData[i]);
		}
		TuaType.m_Layer.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CLayer::CTuaType_0_2_0)*SysType.m_Layer.size());
		delete[] pData;
	}
	pLoadingContext->WriteAssetPath(SysType.m_TexturePath, TuaType.m_TexturePath);
	TuaType.m_TextureColor = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_TextureColor);
	TuaType.m_TextureSize.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSize.x);
	TuaType.m_TextureSize.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSize.y);
	TuaType.m_TextureAngle = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureAngle);
	TuaType.m_TextureSpacing = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSpacing);
	TuaType.m_TextureEnabled = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_TextureEnabled);
}

void CAsset_Material::CLabel::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Material::CLabel& SysType)
{
	SysType.m_Color = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color);
	SysType.m_AngleStart = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_AngleStart);
	SysType.m_AngleEnd = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_AngleEnd);
}


void CAsset_Material::CSprite::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Material::CSprite& SysType)
{
	pLoadingContext->ReadAssetPath(TuaType.m_Path, SysType.m_Path);
	SysType.m_Size.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_X);
	SysType.m_Size.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Size.m_Y);
	SysType.m_Color = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_Color);
	SysType.m_Flags = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Flags);
	SysType.m_Position.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Position.m_X);
	SysType.m_Position.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_Position.m_Y);
	SysType.m_Alignment = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Alignment);
	SysType.m_Filling = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_Filling);
	SysType.m_TileType = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileType);
	SysType.m_TileLabel0 = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileLabel0);
	SysType.m_TileLabel1 = pLoadingContext->ArchiveFile()->ReadInt32(TuaType.m_TileLabel1);
}


void CAsset_Material::CLayer::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Material::CLayer& SysType)
{
	{
		const CAsset_Material::CSprite::CTuaType_0_2_1* pData = (const CAsset_Material::CSprite::CTuaType_0_2_1*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Sprite.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Sprite.m_Size);
		SysType.m_Sprite.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CSprite::CTuaType_0_2_1::Read(pLoadingContext, pData[i], SysType.m_Sprite[i]);
		}
	}
	
}


void CAsset_Material::CTuaType_0_2_1::Read(CAssetsSaveLoadContext* pLoadingContext, const CTuaType_0_2_1& TuaType, CAsset_Material& SysType)
{
	CAsset::CTuaType_0_2_1::Read(pLoadingContext, TuaType, SysType);

	{
		const CAsset_Material::CLabel::CTuaType_0_2_1* pData = (const CAsset_Material::CLabel::CTuaType_0_2_1*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Label.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Label.m_Size);
		SysType.m_Label.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CLabel::CTuaType_0_2_1::Read(pLoadingContext, pData[i], SysType.m_Label[i]);
		}
	}
	
	{
		const CAsset_Material::CLayer::CTuaType_0_2_1* pData = (const CAsset_Material::CLayer::CTuaType_0_2_1*) pLoadingContext->ArchiveFile()->GetData(TuaType.m_Layer.m_Data);
		uint32 Size = pLoadingContext->ArchiveFile()->ReadUInt32(TuaType.m_Layer.m_Size);
		SysType.m_Layer.resize(Size);
		for(uint32 i=0; i<Size; i++)
		{
			CAsset_Material::CLayer::CTuaType_0_2_1::Read(pLoadingContext, pData[i], SysType.m_Layer[i]);
		}
	}
	
	pLoadingContext->ReadAssetPath(TuaType.m_TexturePath, SysType.m_TexturePath);
	SysType.m_TextureColor = pLoadingContext->ArchiveFile()->ReadColor(TuaType.m_TextureColor);
	SysType.m_TextureSize.x = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSize.m_X);
	SysType.m_TextureSize.y = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSize.m_Y);
	SysType.m_TextureAngle = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureAngle);
	SysType.m_TextureSpacing = pLoadingContext->ArchiveFile()->ReadFloat(TuaType.m_TextureSpacing);
	SysType.m_TextureEnabled = pLoadingContext->ArchiveFile()->ReadBool(TuaType.m_TextureEnabled);
}


void CAsset_Material::CLabel::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLabel& SysType, CTuaType_0_2_1& TuaType)
{
	TuaType.m_Color = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color);
	TuaType.m_AngleStart = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_AngleStart);
	TuaType.m_AngleEnd = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_AngleEnd);
}

void CAsset_Material::CSprite::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CSprite& SysType, CTuaType_0_2_1& TuaType)
{
	pLoadingContext->WriteAssetPath(SysType.m_Path, TuaType.m_Path);
	TuaType.m_Size.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.x);
	TuaType.m_Size.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Size.y);
	TuaType.m_Color = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_Color);
	TuaType.m_Flags = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Flags);
	TuaType.m_Position.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Position.x);
	TuaType.m_Position.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_Position.y);
	TuaType.m_Alignment = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Alignment);
	TuaType.m_Filling = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_Filling);
	TuaType.m_TileType = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileType);
	TuaType.m_TileLabel0 = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileLabel0);
	TuaType.m_TileLabel1 = pLoadingContext->ArchiveFile()->WriteInt32(SysType.m_TileLabel1);
}

void CAsset_Material::CLayer::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material::CLayer& SysType, CTuaType_0_2_1& TuaType)
{
	{
		TuaType.m_Sprite.m_Size = SysType.m_Sprite.size();
		CAsset_Material::CSprite::CTuaType_0_2_1* pData = new CAsset_Material::CSprite::CTuaType_0_2_1[SysType.m_Sprite.size()];
		for(int i=0; i<SysType.m_Sprite.size(); i++)
		{
			CAsset_Material::CSprite::CTuaType_0_2_1::Write(pLoadingContext, SysType.m_Sprite[i], pData[i]);
		}
		TuaType.m_Sprite.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CSprite::CTuaType_0_2_1)*SysType.m_Sprite.size());
		delete[] pData;
	}
}

void CAsset_Material::CTuaType_0_2_1::Write(CAssetsSaveLoadContext* pLoadingContext, const CAsset_Material& SysType, CTuaType_0_2_1& TuaType)
{
	CAsset::CTuaType_0_2_1::Write(pLoadingContext, SysType, TuaType);

	{
		TuaType.m_Label.m_Size = SysType.m_Label.size();
		CAsset_Material::CLabel::CTuaType_0_2_1* pData = new CAsset_Material::CLabel::CTuaType_0_2_1[SysType.m_Label.size()];
		for(int i=0; i<SysType.m_Label.size(); i++)
		{
			CAsset_Material::CLabel::CTuaType_0_2_1::Write(pLoadingContext, SysType.m_Label[i], pData[i]);
		}
		TuaType.m_Label.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CLabel::CTuaType_0_2_1)*SysType.m_Label.size());
		delete[] pData;
	}
	{
		TuaType.m_Layer.m_Size = SysType.m_Layer.size();
		CAsset_Material::CLayer::CTuaType_0_2_1* pData = new CAsset_Material::CLayer::CTuaType_0_2_1[SysType.m_Layer.size()];
		for(int i=0; i<SysType.m_Layer.size(); i++)
		{
			CAsset_Material::CLayer::CTuaType_0_2_1::Write(pLoadingContext, SysType.m_Layer[i], pData[i]);
		}
		TuaType.m_Layer.m_Data = pLoadingContext->ArchiveFile()->AddData((uint8*) pData, sizeof(CAsset_Material::CLayer::CTuaType_0_2_1)*SysType.m_Layer.size());
		delete[] pData;
	}
	pLoadingContext->WriteAssetPath(SysType.m_TexturePath, TuaType.m_TexturePath);
	TuaType.m_TextureColor = pLoadingContext->ArchiveFile()->WriteColor(SysType.m_TextureColor);
	TuaType.m_TextureSize.m_X = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSize.x);
	TuaType.m_TextureSize.m_Y = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSize.y);
	TuaType.m_TextureAngle = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureAngle);
	TuaType.m_TextureSpacing = pLoadingContext->ArchiveFile()->WriteFloat(SysType.m_TextureSpacing);
	TuaType.m_TextureEnabled = pLoadingContext->ArchiveFile()->WriteBool(SysType.m_TextureEnabled);
}

template<>
int CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, int DefaultValue) const
{
	switch(ValueType)
	{
		case LABEL_ARRAYSIZE:
			return GetLabelArraySize();
		case LAYER_ARRAYSIZE:
			return GetLayerArraySize();
		case LAYER_SPRITE_ARRAYSIZE:
			return GetLayerSpriteArraySize(SubPath);
		case LAYER_SPRITE_FLAGS:
			return GetLayerSpriteFlags(SubPath);
		case LAYER_SPRITE_ALIGNMENT:
			return GetLayerSpriteAlignment(SubPath);
		case LAYER_SPRITE_FILLING:
			return GetLayerSpriteFilling(SubPath);
		case LAYER_SPRITE_TILETYPE:
			return GetLayerSpriteTileType(SubPath);
		case LAYER_SPRITE_TILELABEL0:
			return GetLayerSpriteTileLabel0(SubPath);
		case LAYER_SPRITE_TILELABEL1:
			return GetLayerSpriteTileLabel1(SubPath);
	}
	return CAsset::GetValue<int>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, int Value)
{
	switch(ValueType)
	{
		case LABEL_ARRAYSIZE:
			SetLabelArraySize(Value);
			return true;
		case LAYER_ARRAYSIZE:
			SetLayerArraySize(Value);
			return true;
		case LAYER_SPRITE_ARRAYSIZE:
			SetLayerSpriteArraySize(SubPath, Value);
			return true;
		case LAYER_SPRITE_FLAGS:
			SetLayerSpriteFlags(SubPath, Value);
			return true;
		case LAYER_SPRITE_ALIGNMENT:
			SetLayerSpriteAlignment(SubPath, Value);
			return true;
		case LAYER_SPRITE_FILLING:
			SetLayerSpriteFilling(SubPath, Value);
			return true;
		case LAYER_SPRITE_TILETYPE:
			SetLayerSpriteTileType(SubPath, Value);
			return true;
		case LAYER_SPRITE_TILELABEL0:
			SetLayerSpriteTileLabel0(SubPath, Value);
			return true;
		case LAYER_SPRITE_TILELABEL1:
			SetLayerSpriteTileLabel1(SubPath, Value);
			return true;
	}
	return CAsset::SetValue<int>(ValueType, SubPath, Value);
}

template<>
bool CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, bool DefaultValue) const
{
	switch(ValueType)
	{
		case TEXTUREENABLED:
			return GetTextureEnabled();
	}
	return CAsset::GetValue<bool>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, bool Value)
{
	switch(ValueType)
	{
		case TEXTUREENABLED:
			SetTextureEnabled(Value);
			return true;
	}
	return CAsset::SetValue<bool>(ValueType, SubPath, Value);
}

template<>
float CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, float DefaultValue) const
{
	switch(ValueType)
	{
		case LABEL_ANGLESTART:
			return GetLabelAngleStart(SubPath);
		case LABEL_ANGLEEND:
			return GetLabelAngleEnd(SubPath);
		case LAYER_SPRITE_SIZE_X:
			return GetLayerSpriteSizeX(SubPath);
		case LAYER_SPRITE_SIZE_Y:
			return GetLayerSpriteSizeY(SubPath);
		case LAYER_SPRITE_POSITION_X:
			return GetLayerSpritePositionX(SubPath);
		case LAYER_SPRITE_POSITION_Y:
			return GetLayerSpritePositionY(SubPath);
		case TEXTURESIZE_X:
			return GetTextureSizeX();
		case TEXTURESIZE_Y:
			return GetTextureSizeY();
		case TEXTUREANGLE:
			return GetTextureAngle();
		case TEXTURESPACING:
			return GetTextureSpacing();
	}
	return CAsset::GetValue<float>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, float Value)
{
	switch(ValueType)
	{
		case LABEL_ANGLESTART:
			SetLabelAngleStart(SubPath, Value);
			return true;
		case LABEL_ANGLEEND:
			SetLabelAngleEnd(SubPath, Value);
			return true;
		case LAYER_SPRITE_SIZE_X:
			SetLayerSpriteSizeX(SubPath, Value);
			return true;
		case LAYER_SPRITE_SIZE_Y:
			SetLayerSpriteSizeY(SubPath, Value);
			return true;
		case LAYER_SPRITE_POSITION_X:
			SetLayerSpritePositionX(SubPath, Value);
			return true;
		case LAYER_SPRITE_POSITION_Y:
			SetLayerSpritePositionY(SubPath, Value);
			return true;
		case TEXTURESIZE_X:
			SetTextureSizeX(Value);
			return true;
		case TEXTURESIZE_Y:
			SetTextureSizeY(Value);
			return true;
		case TEXTUREANGLE:
			SetTextureAngle(Value);
			return true;
		case TEXTURESPACING:
			SetTextureSpacing(Value);
			return true;
	}
	return CAsset::SetValue<float>(ValueType, SubPath, Value);
}

template<>
vec2 CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, vec2 DefaultValue) const
{
	switch(ValueType)
	{
		case LAYER_SPRITE_SIZE:
			return GetLayerSpriteSize(SubPath);
		case LAYER_SPRITE_POSITION:
			return GetLayerSpritePosition(SubPath);
		case TEXTURESIZE:
			return GetTextureSize();
	}
	return CAsset::GetValue<vec2>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, vec2 Value)
{
	switch(ValueType)
	{
		case LAYER_SPRITE_SIZE:
			SetLayerSpriteSize(SubPath, Value);
			return true;
		case LAYER_SPRITE_POSITION:
			SetLayerSpritePosition(SubPath, Value);
			return true;
		case TEXTURESIZE:
			SetTextureSize(Value);
			return true;
	}
	return CAsset::SetValue<vec2>(ValueType, SubPath, Value);
}

template<>
vec4 CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, vec4 DefaultValue) const
{
	switch(ValueType)
	{
		case LABEL_COLOR:
			return GetLabelColor(SubPath);
		case LAYER_SPRITE_COLOR:
			return GetLayerSpriteColor(SubPath);
		case TEXTURECOLOR:
			return GetTextureColor();
	}
	return CAsset::GetValue<vec4>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, vec4 Value)
{
	switch(ValueType)
	{
		case LABEL_COLOR:
			SetLabelColor(SubPath, Value);
			return true;
		case LAYER_SPRITE_COLOR:
			SetLayerSpriteColor(SubPath, Value);
			return true;
		case TEXTURECOLOR:
			SetTextureColor(Value);
			return true;
	}
	return CAsset::SetValue<vec4>(ValueType, SubPath, Value);
}

template<>
CAssetPath CAsset_Material::GetValue(int ValueType, const CSubPath& SubPath, CAssetPath DefaultValue) const
{
	switch(ValueType)
	{
		case LAYER_SPRITE_PATH:
			return GetLayerSpritePath(SubPath);
		case TEXTUREPATH:
			return GetTexturePath();
	}
	return CAsset::GetValue<CAssetPath>(ValueType, SubPath, DefaultValue);
}

template<>
bool CAsset_Material::SetValue(int ValueType, const CSubPath& SubPath, CAssetPath Value)
{
	switch(ValueType)
	{
		case LAYER_SPRITE_PATH:
			SetLayerSpritePath(SubPath, Value);
			return true;
		case TEXTUREPATH:
			SetTexturePath(Value);
			return true;
	}
	return CAsset::SetValue<CAssetPath>(ValueType, SubPath, Value);
}

int CAsset_Material::AddSubItem(int Type, const CSubPath& SubPath)
{
	switch(Type)
	{
		case TYPE_LABEL:
			return AddLabel();
		case TYPE_LAYER:
			return AddLayer();
		case TYPE_LAYER_SPRITE:
			return AddLayerSprite(SubPath);
	}
	return -1;
}

int CAsset_Material::AddSubItemAt(int Type, const CSubPath& SubPath, int Index)
{
	switch(Type)
	{
		case TYPE_LABEL:
			AddAtLabel(Index);
			return Index;
		case TYPE_LAYER:
			AddAtLayer(Index);
			return Index;
		case TYPE_LAYER_SPRITE:
			AddAtLayerSprite(SubPath, Index);
			return Index;
	}
	return -1;
}

void CAsset_Material::DeleteSubItem(const CSubPath& SubPath)
{
	switch(SubPath.GetType())
	{
		case TYPE_LABEL:
			DeleteLabel(SubPath);
			break;
		case TYPE_LAYER:
			DeleteLayer(SubPath);
			break;
		case TYPE_LAYER_SPRITE:
			DeleteLayerSprite(SubPath);
			break;
	}
}

void CAsset_Material::RelMoveSubItem(const CSubPath& SubPath, int RelMove)
{
	switch(SubPath.GetType())
	{
		case TYPE_LABEL:
			RelMoveLabel(SubPath, RelMove);
			break;
		case TYPE_LAYER:
			RelMoveLayer(SubPath, RelMove);
			break;
		case TYPE_LAYER_SPRITE:
			RelMoveLayerSprite(SubPath, RelMove);
			break;
	}
}


