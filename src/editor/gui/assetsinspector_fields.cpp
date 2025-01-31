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

#include <editor/gui/assetsinspector.h>
#include <editor/gui/image_picker.h>
#include <editor/components/gui.h>
#include <shared/components/assetsmanager.h>
#include <client/components/assetsrenderer.h>
#include <client/gui/text-edit.h>
#include <client/gui/integer-edit.h>
#include <client/gui/duration-edit.h>
#include <client/gui/float-edit.h>
#include <client/gui/color-edit.h>
#include <client/gui/toggle.h>
#include <client/gui/combobox.h>
#include <client/gui/popup.h>
#include <client/gui/expand.h>
#include <shared/components/localization.h>
#include <shared/geometry/linetesselation.h>
#include <shared/imageprocessing/dilate.h>
#include <shared/imageprocessing/addborder.h>
#include <shared/autolayer.h>

void CAssetsInspector::AddField(gui::CVListLayout* pList, gui::CWidget* pWidget, const CLocalizableString& Text)
{
	gui::CHListLayout* pLayout = new gui::CHListLayout(Context());
	pList->Add(pLayout, false);
	
	gui::CLabel* pLabel = new gui::CLabel(Context(), Text);
	pLayout->Add(pLabel, true);
	
	pLayout->Add(pWidget, true);
}

void CAssetsInspector::AddField(gui::CVListLayout* pList, gui::CWidget* pWidget)
{
	pList->Add(pWidget, false);
}

class CAssetNameEdit : public gui::CAbstractTextEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	
	void SaveFromTextBuffer() override
	{
		AssetsManager()->TryChangeAssetName(m_pAssetsEditor->GetEditedAssetPath(), GetText(), -1);
	}
	
	void CopyToTextBuffer() override
	{
		const char* pName = AssetsManager()->GetAssetValue<const char*>(
			m_pAssetsEditor->GetEditedAssetPath(),
			CSubPath::Null(),
			CAsset::NAME,
			nullptr
		);
		
		if(pName)
		{
			if(m_Text != pName)
				SetText(pName);
		}
		else
			SetText("");
	}
	
public:
	CAssetNameEdit(CGuiEditor* pAssetsEditor) :
		gui::CAbstractTextEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor)
	{ }
	
	void Update(bool ParentEnabled) override
	{
		if(IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
		}
		
		gui::CAbstractTextEdit::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_AssetProperties(gui::CVScrollLayout* pTab)
{
	AddField(pTab, new CAssetNameEdit(AssetsEditor()), _LSTRING("Name"));
	
	pTab->AddSeparator();
}

/* TEXT EDIT **********************************************************/

class CMemberTextEdit : public gui::CAbstractTextEdit
{
public:
	CMemberTextEdit(CGuiEditor *pAssetsEditor, int Member);
	void Update(bool ParentEnabled) override;

protected:
	void SaveFromTextBuffer() override;
	void CopyToTextBuffer() override;

	CGuiEditor* m_pAssetsEditor;
	int m_Member;
};

CMemberTextEdit::CMemberTextEdit(CGuiEditor *pAssetsEditor, int Member) :
	gui::CAbstractTextEdit(pAssetsEditor),
	m_pAssetsEditor(pAssetsEditor),
	m_Member(Member)
{
}

void CMemberTextEdit::Update(bool ParentEnabled)
{
	if(IsEnabled() && ParentEnabled)
	{
		if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
			Editable(false);
		else
			Editable(true);
	}

	gui::CAbstractTextEdit::Update(ParentEnabled);
}

void CMemberTextEdit::SaveFromTextBuffer()
{
	int Token = AssetsManager()->GenerateToken();
	for(unsigned int i = 0; i < m_pAssetsEditor->GetEditedSubPathes().size(); i++)
	{
		AssetsManager()->SetAssetValue<const char *>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPathes()[i],
			m_Member,
			GetText(),
			Token);
	}

	CAssetState *pState = AssetsManager()->GetAssetState(m_pAssetsEditor->GetEditedAssetPath());
	pState->m_NumUpdates++;
}

void CMemberTextEdit::CopyToTextBuffer()
{
	const char *pName = AssetsManager()->GetAssetValue<const char *>(
		m_pAssetsEditor->GetEditedAssetPath(),
		m_pAssetsEditor->GetFirstEditedSubPath(),
		m_Member,
		nullptr);

	if(pName)
	{
		if(m_Text != pName)
			SetText(pName);
	}
	else
		SetText("");
}

void CAssetsInspector::AddField_Text(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	gui::CWidget *pWidget = new CMemberTextEdit(m_pAssetsEditor, Member);
	AddField(pList, pWidget, Text);
}

/* INTEGER EDIT *******************************************************/
	
class CMemberIntegerEdit : public gui::CAbstractIntegerEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	bool m_NoEdit;
	bool m_Unsigned = false;
	
	int GetValue() const override
	{
		if(m_Unsigned)
		{
			return m_pAssetsEditor->AssetsManager()->GetAssetValue<uint32_t>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_Member,
				0u
			);
		}
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		);
	}
	
	void SetValue(int Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			if(m_Unsigned)
			{
				uint32_t V = Value;
				m_pAssetsEditor->AssetsManager()->SetAssetValue<uint32_t>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_Member,
					V,
					Token
				);
				continue;
			}
			m_pAssetsEditor->AssetsManager()->SetAssetValue<int>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value,
				Token
			);
		}
	}
	
public:
	CMemberIntegerEdit(CGuiEditor* pAssetsEditor, int Member, bool NoEdit = false) :
		gui::CAbstractIntegerEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member),
		m_NoEdit(NoEdit)
	{
		if(m_NoEdit)
			Editable(false);
	}

	void SetUnsigned(bool Unsigned)
	{
		m_Unsigned = Unsigned;
	}
	
	void Update(bool ParentEnabled) override
	{
		if(!m_NoEdit && IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
		}
		
		gui::CAbstractIntegerEdit::Update(ParentEnabled);
	}
};

class CMemberIntegerEdit_MapLayerTiles_NoSource : public CMemberIntegerEdit
{	
public:
	CMemberIntegerEdit_MapLayerTiles_NoSource(CGuiEditor* pAssetsEditor, int Member, bool NoEdit = false) :
		CMemberIntegerEdit(pAssetsEditor, Member, NoEdit)
	{
		
	}
	
	void Update(bool ParentEnabled) override
	{
		if(!m_NoEdit && IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
		}
		
		if(IsEditable() && IsEnabled() && ParentEnabled)
		{
			const CAsset_MapLayerTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerTiles>(m_pAssetsEditor->GetEditedAssetPath());
			if(!pLayer || pLayer->GetSourcePath().IsNotNull())
				Editable(false);
		}
		
		gui::CAbstractIntegerEdit::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_Integer(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberIntegerEdit* pWidget = new CMemberIntegerEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_UInteger(gui::CVListLayout *pList, int Member, const CLocalizableString &Text)
{
	CMemberIntegerEdit* pWidget = new CMemberIntegerEdit(
		m_pAssetsEditor,
		Member
	);

	pWidget->SetUnsigned(true);
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_Integer_MapLayerTiles_NoSource(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberIntegerEdit_MapLayerTiles_NoSource* pWidget = new CMemberIntegerEdit_MapLayerTiles_NoSource(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_Integer_NoEdit(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberIntegerEdit* pWidget = new CMemberIntegerEdit(
		m_pAssetsEditor,
		Member,
		true
	);
	
	AddField(pList, pWidget, Text);
}

/* INTEGER EDIT *******************************************************/

class CMemberSeedEdit : public gui::CHListLayout
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
public:
	class CButton : public gui::CButton
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_Member;
	
	protected:
		void MouseClickAction() override
		{
			int Token = AssetsManager()->GenerateToken();
			for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
			{
				m_pAssetsEditor->AssetsManager()->SetAssetValue<int>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_Member,
					rand(),
					Token
				);
			}
		}
		
	public:
		CButton(CGuiEditor* pAssetsEditor, int Member) :
			gui::CButton(pAssetsEditor, pAssetsEditor->m_Path_Sprite_IconSystem),
			m_pAssetsEditor(pAssetsEditor),
			m_Member(Member)
		{
			
		}
	};
	
	class CTextEdit : public gui::CAbstractTextEdit
	{
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_Member;
		
	protected:
		void SaveFromTextBuffer() override
		{
			const char* pText = GetText();
			pText = str_skip_whitespaces((char*) pText);
            
            uint32_t Value = str_to_int_base(pText, 16);
			
			int Token = AssetsManager()->GenerateToken();
			for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
			{
				m_pAssetsEditor->AssetsManager()->SetAssetValue<int>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_Member,
					Value,
					Token
				);
			}
		}
		
		void CopyToTextBuffer() override
		{
            uint32_t Value = m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_Member,
				0
			);
			
			char aBuf[16];
			str_format(aBuf, sizeof(aBuf), "%08X", Value);
			SetText(aBuf);
		}
		
		void Update(bool ParentEnabled) override
		{
			if(IsEnabled() && ParentEnabled)
			{
				if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
					Editable(false);
				else
					Editable(true);
			}
			
			gui::CAbstractTextEdit::Update(ParentEnabled);
		}
		
	public:
		CTextEdit(CGuiEditor* pAssetsEditor, int Member) :
			gui::CAbstractTextEdit(pAssetsEditor),
			m_pAssetsEditor(pAssetsEditor),
			m_Member(Member)
		{
			
		}
	};

public:
	CMemberSeedEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CHListLayout(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{
		Add(new CTextEdit(m_pAssetsEditor, m_Member), true);
		Add(new CButton(m_pAssetsEditor, m_Member), false);
	}
};

void CAssetsInspector::AddField_Seed(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberSeedEdit* pWidget = new CMemberSeedEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

/* BOOL EDIT **********************************************************/
	
class CMemberBoolEdit : public gui::CAbstractToggle
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	bool GetValue() override
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<bool>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		);
	}
	
	void SetValue(bool Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<bool>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value,
				Token
			);
		}
	}
	
public:
	CMemberBoolEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractToggle(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Bool(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberBoolEdit* pWidget = new CMemberBoolEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

/* FLAG EDIT **********************************************************/
	
class CMemberFlagEdit : public gui::CAbstractToggle
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	int m_Mask;
	
	bool GetValue() override
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		) & m_Mask;
	}
	
	void SetValue(bool Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			int Flags = m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				0x0
			);
			
			if(Value)
				Flags |= m_Mask;
			else
				Flags &= ~m_Mask;
			
			m_pAssetsEditor->AssetsManager()->SetAssetValue<int>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Flags,
				Token
			);
		}
	}
	
public:
	CMemberFlagEdit(CGuiEditor* pAssetsEditor, int Member, int Mask) :
		gui::CAbstractToggle(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member),
		m_Mask(Mask)
	{ }
};

void CAssetsInspector::AddField_Flag(gui::CVListLayout* pList, int Member, int Mask, const CLocalizableString& Text)
{
	CMemberFlagEdit* pWidget = new CMemberFlagEdit(
		m_pAssetsEditor,
		Member,
		Mask
	);
	
	AddField(pList, pWidget, Text);
}

/* FLOAT EDIT *********************************************************/
	
class CMemberFloatEdit : public gui::CAbstractFloatEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	float GetValue() const override
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		);
	}
	
	void SetValue(float Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<float>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value,
				Token
			);
		}
	}
	
public:
	CMemberFloatEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractFloatEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
	
	void Update(bool ParentEnabled) override
	{
		if(IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
		}
		
		gui::CAbstractFloatEdit::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_Float(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberFloatEdit* pWidget = new CMemberFloatEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_Vec2(gui::CVListLayout* pList, int Member, int Member2, const CLocalizableString& Text)
{
	gui::CHListLayout* pLayout = new gui::CHListLayout(Context());
	
	pLayout->Add(new CMemberFloatEdit(
		m_pAssetsEditor,
		Member
	), true);
	pLayout->Add(new CMemberFloatEdit(
		m_pAssetsEditor,
		Member2
	), true);
	
	AddField(pList, pLayout, Text);
}

/* ANGLE EDIT *********************************************************/
	
class CMemberAngleEdit : public gui::CAbstractFloatEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	float GetValue() const override
	{
		return 180.0f*m_pAssetsEditor->AssetsManager()->GetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		)/Pi;
	}
	
	void SetValue(float Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<float>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value * Pi/180.0f,
				Token
			);
		}
	}
	
public:
	CMemberAngleEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractFloatEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Angle(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberAngleEdit* pWidget = new CMemberAngleEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

/* TIME EDIT **********************************************************/
	
class CMemberDurationEdit : public gui::CAbstractDurationEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	int64_t GetValue() const override
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<int64_t>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			0
		);
	}
	
	void SetValue(int64_t Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<int64_t>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value,
				Token
			);
		}
	}
	
public:
	CMemberDurationEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractDurationEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Duration(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberDurationEdit* pWidget = new CMemberDurationEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

/* COLOR EDIT *********************************************************/
	
class CMemberColorEdit : public gui::CAbstractColorEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	vec4 GetValue() const override
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<vec4>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			vec4(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}
	
	void SetValue(vec4 Value) override
	{
		int Token = AssetsManager()->GenerateToken();
		for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<vec4>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPathes()[i],
				m_Member,
				Value,
				Token
			);
		}
	}
	
public:
	CMemberColorEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractColorEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Color(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberColorEdit* pWidget = new CMemberColorEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, Text);
}

/* ASSET EDIT *********************************************************/

class CMemberAssetEdit : public gui::CButton
{
public:
	enum class EMode
	{
		TypeId=0,
		ImageTile,
		TilelayerStyle,
		MapgroupParent,
		Animation,
	};

	CMemberAssetEdit(CGuiEditor* pAssetsEditor, int Member, int AssetType, EMode Mode);
	void Update(bool ParentEnabled) override;

public:
	class CPopup : public gui::CPopup
	{
	public:
		class CItem : public gui::CButton
		{
		protected:
			CAssetPath m_AssetPath;
			CPopup* m_pPopup;
		
		protected:
			void MouseClickAction() override
			{
				m_pPopup->SetValue(m_AssetPath);
			}
			
		public:
			CItem(CPopup* pPopup, CAssetPath AssetPath, EMode Mode) :
				gui::CButton(pPopup->Context(), ""),
				m_AssetPath(AssetPath),
				m_pPopup(pPopup)
			{
				if(m_AssetPath.IsNull())
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconNone);
					SetText(_LSTRING("None"));
				}
				else
				{
					SetIcon(m_pPopup->m_pAssetsEditor->GetItemIcon(m_AssetPath, CSubPath::Null()));
					SetText(m_pPopup->m_pAssetsEditor->GetItemName(m_AssetPath, CSubPath::Null()));
				}
				
				if(Mode == EMode::ImageTile)
				{
					const CAsset_Image* pImage = AssetsManager()->GetAsset<CAsset_Image>(m_AssetPath);
					if(!pImage || !pImage->GetTilingEnabled())
						Editable(false);
				}
			}
			
			void Update(bool ParentEnabled) override
			{
				if(ParentEnabled)
				{
					if(m_pPopup->GetValue() == m_AssetPath)
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItemHL);
					else
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItem);
				}
				
				gui::CButton::Update(ParentEnabled);
			}
		};
	
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_Member;
		int m_AssetType;
		EMode m_Mode;
	
	protected:
		void ShowPackage(gui::CVScrollLayout* pLayout, int PackageId)
		{
			#define MACRO_ASSETTYPE(Name) case CAsset_##Name::TypeId:\
				for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_##Name>(PackageId); i++)\
					pExpand->Add(new CItem(this, CAssetPath(CAsset_##Name::TypeId, PackageId, i), m_Mode));\
				break;
			
			gui::CExpand* pExpand = new gui::CExpand(Context());
			pLayout->Add(pExpand);
			pExpand->SetTitle(new gui::CLabel(Context(), AssetsManager()->GetPackageName(PackageId), m_pAssetsEditor->m_Path_Sprite_IconFolder));
			
			if(m_Mode == EMode::TilelayerStyle)
			{
				for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_Image>(PackageId); i++)
					pExpand->Add(new CItem(this, CAssetPath(CAsset_Image::TypeId, PackageId, i), EMode::ImageTile));
				for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_TilingMaterial>(PackageId); i++)
					pExpand->Add(new CItem(this, CAssetPath(CAsset_TilingMaterial::TypeId, PackageId, i), m_Mode));
			}
			else if(m_Mode == EMode::Animation)
			{
				for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_SkeletonAnimation>(PackageId); i++)
				{
					CAssetPath AssetPath = CAssetPath(CAsset_SkeletonAnimation::TypeId, PackageId, i);
					const CAsset_SkeletonAnimation* pAnimation = AssetsManager()->GetAsset<CAsset_SkeletonAnimation>(AssetPath);
					if(pAnimation && pAnimation->GetSkeletonPath().IsNull())
					{
						pExpand->Add(new CItem(this, AssetPath, m_Mode));
					}
				}
			}
			else
			{
				switch(m_AssetType)
				{
					#include <generated/assets/assetsmacro.h>
				}
			}
		}
	
	public:
		CPopup(CGuiEditor* pAssetsEditor, int Member, int AssetType, gui::CRect ParentRect, EMode Mode) :
			gui::CPopup(pAssetsEditor, ParentRect, 250, 400, gui::CPopup::ALIGNMENT_SIDE),
			m_pAssetsEditor(pAssetsEditor),
			m_Member(Member),
			m_AssetType(AssetType),
			m_Mode(Mode)
		{
			
			gui::CVScrollLayout* pLayout = new gui::CVScrollLayout(Context());
			Add(pLayout);
			
			SetBoxStyle(m_pAssetsEditor->m_Path_Box_Dialog);
			pLayout->Add(new CItem(this, CAssetPath::Null(), m_Mode), false);
			
			ShowPackage(pLayout, m_pAssetsEditor->GetEditedPackageId());
			for(int p=0; p<AssetsManager()->GetNumPackages(); p++)
			{
				if(p != m_pAssetsEditor->GetEditedPackageId() && str_comp(AssetsManager()->GetPackageName(p), "gui_editor") != 0)
					ShowPackage(pLayout, p);
			}
		}
		
		CAssetPath GetValue()
		{
			return AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_Member,
				CAssetPath::Null()
			);
		}
		
		void SetValue(CAssetPath Value)
		{
			int Token = AssetsManager()->GenerateToken();
			if(m_Mode == EMode::MapgroupParent)
			{
				bool Changes = false;
				for(unsigned int i=0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
				{
					CAssetPath OldValue = AssetsManager()->GetAssetValue<CAssetPath>(
						m_pAssetsEditor->GetEditedAssetPath(),
						m_pAssetsEditor->GetEditedSubPathes()[i],
						m_Member,
						CAssetPath::Null()
					);
					
					if(OldValue != Value)
					{
						
						//Search the layer in the group
						const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(OldValue);
						if(pGroup)
						{
							CAsset_MapGroup::CIteratorLayer Iter;
							for(Iter = pGroup->ReverseBeginLayer(); Iter != pGroup->ReverseEndLayer(); ++Iter)
							{
								if(pGroup->GetLayer(*Iter) == m_pAssetsEditor->GetEditedAssetPath())
								{
									AssetsManager()->DeleteSubItem(OldValue, *Iter, Token);
									
									//We don't use a break here so all instance of the layer will be removed.
									//This can be used to cleanup corrupted maps
								}
							}
						}
						
						CSubPath LayerSubPath = CAsset_MapGroup::SubPath_Layer(AssetsManager()->AddSubItem(Value, CSubPath::Null(), CAsset_MapGroup::TYPE_LAYER, Token));
						AssetsManager()->SetAssetValue<CAssetPath>(Value, LayerSubPath, CAsset_MapGroup::LAYER, m_pAssetsEditor->GetEditedAssetPath(), Token);
						
						AssetsManager()->SetAssetValue<CAssetPath>(
							m_pAssetsEditor->GetEditedAssetPath(),
							m_pAssetsEditor->GetEditedSubPathes()[i],
							m_Member,
							Value,
							Token
						);
						
						Changes = true;
					}
				}
				
				if(Changes)
					m_pAssetsEditor->RefreshAssetsTree();
			}
			else
			{
				for(unsigned int i=0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
				{
					AssetsManager()->SetAssetValue<CAssetPath>(
						m_pAssetsEditor->GetEditedAssetPath(),
						m_pAssetsEditor->GetEditedSubPathes()[i],
						m_Member,
						Value
					);
				}
			}
		}
	
		int GetInputToBlock() override { return CGui::BLOCKEDINPUT_ALL; }
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	int m_AssetType;
	EMode m_Mode;
	
protected:
	void MouseClickAction() override
	{
		Context()->DisplayPopup(new CPopup(m_pAssetsEditor, m_Member, m_AssetType, m_DrawRect, m_Mode));
	}
};

CMemberAssetEdit::CMemberAssetEdit(CGuiEditor *pAssetsEditor, int Member, int AssetType, EMode Mode) :
	gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
	m_pAssetsEditor(pAssetsEditor),
	m_Member(Member),
	m_AssetType(AssetType),
	m_Mode(Mode)
{
}

void CMemberAssetEdit::Update(bool ParentEnabled)
{
	if(IsEnabled() && ParentEnabled)
	{
		if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
			Editable(false);
		else
			Editable(true);

		CAssetPath Value = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_Member,
			CAssetPath::Null());

		if(Value.IsNull())
		{
			SetIcon(m_pAssetsEditor->m_Path_Sprite_IconNone);
			SetText(_LSTRING("None"));
		}
		else
		{
			SetIcon(m_pAssetsEditor->GetItemIcon(Value, CSubPath::Null()));
			SetText(m_pAssetsEditor->GetItemName(Value, CSubPath::Null()));
		}
	}

	gui::CButton::Update(ParentEnabled);
}

void CAssetsInspector::AddField_Asset(gui::CVListLayout* pList, int Member, int AssetType, const CLocalizableString& Text)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		AssetType,
		CMemberAssetEdit::EMode::TypeId
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_TileLayerStyle(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		CAsset_Image::TypeId,
		CMemberAssetEdit::EMode::TilelayerStyle
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_ImageTiles(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		CAsset_Image::TypeId,
		CMemberAssetEdit::EMode::ImageTile
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_MapGroups(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		CAsset_MapGroup::TypeId,
		CMemberAssetEdit::EMode::MapgroupParent
	);
	
	AddField(pList, pWidget, Text);
}

void CAssetsInspector::AddField_Animations(gui::CVListLayout* pList, int Member, const CLocalizableString& Text)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		CAsset_MapGroup::TypeId,
		CMemberAssetEdit::EMode::Animation
	);
	
	AddField(pList, pWidget, Text);
}

class CZoneTypeEdit : public gui::CButton
{
public:
	CZoneTypeEdit(CGuiEditor* pAssetsEditor, int IndexMember, int ZonePathMember);
	void Update(bool ParentEnabled) override;

public:
	class CPopup : public gui::CPopup
	{
	public:
		class CItem : public gui::CButton
		{
		public:
			CItem(CPopup* pPopup, CAssetPath ZoneTypePath, CSubPath ZoneTypeIndex);
			void Update(bool ParentEnabled) override;

		protected:
			void MouseClickAction() override
			{
				m_pPopup->SetZoneTypeIndex(m_ZoneTypeIndex.GetId());
			}

			CAssetPath m_AssetPath;
			CPopup* m_pPopup;
			CSubPath m_ZoneTypeIndex;
		};

	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_Member;
		CAssetPath m_ZoneTypeAssetPath;

	public:
		CPopup(CGuiEditor* pAssetsEditor, int Member, CAssetPath ZoneTypeAssetPath, gui::CRect ParentRect) :
			gui::CPopup(pAssetsEditor, ParentRect, 250, 400, gui::CPopup::ALIGNMENT_SIDE),
			m_pAssetsEditor(pAssetsEditor),
			m_Member(Member),
			m_ZoneTypeAssetPath(ZoneTypeAssetPath)
		{
			gui::CVScrollLayout *pLayout = new gui::CVScrollLayout(Context());
			Add(pLayout);

			SetBoxStyle(m_pAssetsEditor->m_Path_Box_Dialog);

			const CAsset_ZoneType *pZoneType = AssetsManager()->GetAsset<CAsset_ZoneType>(m_ZoneTypeAssetPath);

			CAsset_ZoneType::CIteratorIndex Iter;
			for(Iter = pZoneType->BeginIndex(); Iter != pZoneType->EndIndex(); ++Iter)
			{
				pLayout->Add(new CItem(this, m_ZoneTypeAssetPath, *Iter), false);
			}
		}

		int GetZoneTypeIndex()
		{
			return AssetsManager()->GetAssetValue<int>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_Member,
				0);
		}

		void SetZoneTypeIndex(int Index)
		{
			int Token = AssetsManager()->GenerateToken();
			for(unsigned int i = 0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
			{
				AssetsManager()->SetAssetValue<int>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_Member,
					Index,
					Token);
			}
		}

		int GetInputToBlock() override { return CGui::BLOCKEDINPUT_ALL; }
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_IndexMember;
	int m_ZonePathMember;
	CAssetPath m_ZoneTypeAssetPath;

protected:
	void MouseClickAction() override
	{
		Context()->DisplayPopup(new CPopup(m_pAssetsEditor, m_IndexMember, m_ZoneTypeAssetPath, m_DrawRect));
	}
};

CZoneTypeEdit::CZoneTypeEdit(CGuiEditor *pAssetsEditor, int IndexMember, int ZonePathMember) :
	gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
	m_pAssetsEditor(pAssetsEditor),
	m_IndexMember(IndexMember),
	m_ZonePathMember(ZonePathMember)
{
}

void CZoneTypeEdit::Update(bool ParentEnabled)
{
	if(IsEnabled() && ParentEnabled)
	{
		if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
			Editable(false);
		else
			Editable(true);

		int Index = m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_IndexMember,
			0);

		m_ZoneTypeAssetPath = AssetsManager()->GetAssetValue<CAssetPath>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetFirstEditedSubPath(),
			m_ZonePathMember,
			CAssetPath::Null());

		const CAsset_ZoneType *pZoneType = AssetsManager()->GetAsset<CAsset_ZoneType>(m_ZoneTypeAssetPath);
		const CSubPath SubPath = CAsset_ZoneType::SubPath_Index(Index);
		if(pZoneType && pZoneType->IsValidIndex(SubPath) && pZoneType->GetIndexUsed(SubPath))
		{
			const char *pTitle = pZoneType->GetIndexTitle(SubPath);
			SetText(pTitle);
		}
		else
		{
			SetText(_LSTRING("None"));
		}
	}

	gui::CButton::Update(ParentEnabled);
}

CZoneTypeEdit::CPopup::CItem::CItem(CPopup *pPopup, CAssetPath ZoneTypePath, CSubPath ZoneTypeIndex) :
	gui::CButton(pPopup->Context(), ""),
	m_AssetPath(ZoneTypePath),
	m_pPopup(pPopup),
	m_ZoneTypeIndex(ZoneTypeIndex)
{
	if(m_AssetPath.IsNull())
	{
		SetText(_LSTRING("None"));
	}
	else
	{
		const CAsset_ZoneType *pZoneType = AssetsManager()->GetAsset<CAsset_ZoneType>(m_AssetPath);
		if(pZoneType && pZoneType->IsValidIndex(m_ZoneTypeIndex))
		{
			const char *pTitle = pZoneType->GetIndexTitle(m_ZoneTypeIndex);
			SetText(pTitle);
		}
	}
}

void CZoneTypeEdit::CPopup::CItem::Update(bool ParentEnabled)
{
	if(ParentEnabled)
	{
		if(m_pPopup->GetZoneTypeIndex() == m_ZoneTypeIndex.GetId())
			SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItemHL);
		else
			SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItem);
	}

	gui::CButton::Update(ParentEnabled);
}

void CAssetsInspector::AddField_ZoneIndex(gui::CVListLayout *pList, int Member, int ZonePathMember, const CLocalizableString &Text)
{
	CZoneTypeEdit *pWidget = new CZoneTypeEdit(m_pAssetsEditor, Member, ZonePathMember);
	AddField(pList, pWidget, Text);
}

/* BONE EDIT **********************************************************/

class CMemberBoneEdit : public gui::CButton
{
public:
	class CPopup : public gui::CPopup
	{
	public:
		class CItem : public gui::CButton
		{
		protected:
			CAssetPath m_AssetPath;
			CSubPath m_BonePath;
			CPopup* m_pPopup;
		
		protected:
			void MouseClickAction() override
			{
				m_pPopup->SetValue(m_BonePath);
			}
			
		public:
			CItem(CPopup* pPopup, CAssetPath AssetPath, CSubPath BonePath) :
				gui::CButton(pPopup->Context(), ""),
				m_AssetPath(AssetPath),
				m_BonePath(BonePath),
				m_pPopup(pPopup)
			{
				if(m_AssetPath.IsNull())
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconNone);
					SetText(_LSTRING("None"));
				}
				else
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconBone);
					SetText(AssetsManager()->GetAssetValue(m_AssetPath, m_BonePath, CAsset_Skeleton::BONE_NAME, ""));
				}
			}
			
			void Update(bool ParentEnabled) override
			{
				if(ParentEnabled)
				{
					if(m_pPopup->GetValue() == m_BonePath)
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItemHL);
					else
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItem);
				}
				
				gui::CButton::Update(ParentEnabled);
			}
		};
	
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_MemberBone;
		int m_AssetType;
	
	public:
		CPopup(CGuiEditor* pAssetsEditor, int MemberSkeleton, int MemberBone, gui::CRect ParentRect) :
			gui::CPopup(pAssetsEditor, ParentRect, 250, 400, gui::CPopup::ALIGNMENT_SIDE),
			m_pAssetsEditor(pAssetsEditor),
			m_MemberBone(MemberBone)
		{
			
			gui::CVScrollLayout* pLayout = new gui::CVScrollLayout(Context());
			Add(pLayout);
			
			SetBoxStyle(m_pAssetsEditor->m_Path_Box_Dialog);
			pLayout->Add(new CItem(this, CAssetPath::Null(), CSubPath::Null()), false);
			
			CAssetPath SkeletonPath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				MemberSkeleton,
				CAssetPath::Null()
			);
			
			const CAsset_Skeleton* pSkeleton = AssetsManager()->GetAsset<CAsset_Skeleton>(SkeletonPath);
			if(pSkeleton)
			{
				CAsset_Skeleton::CIteratorBone BoneIter;
				for(BoneIter = pSkeleton->BeginBone(); BoneIter != pSkeleton->EndBone(); ++BoneIter)
				{
					pLayout->Add(new CItem(this, SkeletonPath, *BoneIter), false);
				}
			}
		}
		
		CSubPath GetValue()
		{
			return AssetsManager()->GetAssetValue<CSubPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberBone,
				CSubPath::Null()
			);
		}
		
		void SetValue(CSubPath Value)
		{
			int Token = AssetsManager()->GenerateToken();
			
			for(unsigned int i=0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
			{
				AssetsManager()->SetAssetValue<CSubPath>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_MemberBone,
					Value,
					Token
				);
			}
		}
	
		int GetInputToBlock() override { return CGui::BLOCKEDINPUT_ALL; }
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_MemberSkeleton;
	int m_MemberBone;
	
protected:
	void MouseClickAction() override
	{
		Context()->DisplayPopup(new CPopup(m_pAssetsEditor, m_MemberSkeleton, m_MemberBone, m_DrawRect));
	}

public:
	CMemberBoneEdit(CGuiEditor* pAssetsEditor, int MemberSkeleton, int MemberBone) :
		gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
		m_pAssetsEditor(pAssetsEditor),
		m_MemberSkeleton(MemberSkeleton),
		m_MemberBone(MemberBone)
	{
		
	}
	
	void Update(bool ParentEnabled) override
	{
		if(IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
				
			CAssetPath Value = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberSkeleton,
				CAssetPath::Null()
			);
			
			CSubPath BonePath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CSubPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberBone,
				CSubPath::Null()
			);
			
			if(Value.IsNull() || BonePath.IsNull())
			{
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconNone);
				SetText(_LSTRING("None"));
			}
			else
			{
				CSubPath BonePath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CSubPath>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetFirstEditedSubPath(),
					m_MemberBone,
					CSubPath::Null()
				);
				
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconBone);
				SetText(AssetsManager()->GetAssetValue(Value, BonePath, CAsset_Skeleton::BONE_NAME, ""));
			}
		}
		
		gui::CButton::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_Bone(gui::CVListLayout* pList, int MemberSkeleton, int MemberBone, const CLocalizableString& Text)
{
	CMemberBoneEdit* pWidget = new CMemberBoneEdit(
		m_pAssetsEditor,
		MemberSkeleton,
		MemberBone
	);
	
	AddField(pList, pWidget, Text);
}

/* LAYER EDIT *********************************************************/

class CMemberLayerEdit : public gui::CButton
{
public:
	class CPopup : public gui::CPopup
	{
	public:
		class CItem : public gui::CButton
		{
		protected:
			CAssetPath m_AssetPath;
			CSubPath m_LayerPath;
			CPopup* m_pPopup;
		
		protected:
			void MouseClickAction() override
			{
				m_pPopup->SetValue(m_LayerPath);
			}
			
		public:
			CItem(CPopup* pPopup, CAssetPath AssetPath, CSubPath LayerPath) :
				gui::CButton(pPopup->Context(), ""),
				m_AssetPath(AssetPath),
				m_LayerPath(LayerPath),
				m_pPopup(pPopup)
			{
				if(m_AssetPath.IsNull())
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconNone);
					SetText(_LSTRING("None"));
				}
				else
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconLayer);
					SetText(AssetsManager()->GetAssetValue(m_AssetPath, m_LayerPath, CAsset_Skeleton::LAYER_NAME, ""));
				}
			}
			
			void Update(bool ParentEnabled) override
			{
				if(ParentEnabled)
				{
					if(m_pPopup->GetValue() == m_LayerPath)
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItemHL);
					else
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItem);
				}
				
				gui::CButton::Update(ParentEnabled);
			}
		};
	
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_MemberLayer;
		int m_AssetType;
	
	public:
		CPopup(CGuiEditor* pAssetsEditor, int MemberSkeleton, int MemberLayer, gui::CRect ParentRect) :
			gui::CPopup(pAssetsEditor, ParentRect, 250, 400, gui::CPopup::ALIGNMENT_SIDE),
			m_pAssetsEditor(pAssetsEditor),
			m_MemberLayer(MemberLayer)
		{
			
			gui::CVScrollLayout* pLayout = new gui::CVScrollLayout(Context());
			Add(pLayout);
			
			SetBoxStyle(m_pAssetsEditor->m_Path_Box_Dialog);
			pLayout->Add(new CItem(this, CAssetPath::Null(), CSubPath::Null()), false);
			
			CAssetPath SkeletonPath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				MemberSkeleton,
				CAssetPath::Null()
			);
			
			const CAsset_Skeleton* pSkeleton = AssetsManager()->GetAsset<CAsset_Skeleton>(SkeletonPath);
			if(pSkeleton)
			{
				CAsset_Skeleton::CIteratorLayer LayerIter;
				for(LayerIter = pSkeleton->BeginLayer(); LayerIter != pSkeleton->EndLayer(); ++LayerIter)
				{
					pLayout->Add(new CItem(this, SkeletonPath, *LayerIter), false);
				}
			}
		}
		
		CSubPath GetValue()
		{
			return AssetsManager()->GetAssetValue<CSubPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberLayer,
				CSubPath::Null()
			);
		}
		
		void SetValue(CSubPath Value)
		{
			int Token = AssetsManager()->GenerateToken();
			
			for(unsigned int i=0; i<m_pAssetsEditor->GetEditedSubPathes().size(); i++)
			{
				AssetsManager()->SetAssetValue<CSubPath>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetEditedSubPathes()[i],
					m_MemberLayer,
					Value,
					Token
				);
			}
		}
	
		int GetInputToBlock() override { return CGui::BLOCKEDINPUT_ALL; }
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_MemberSkeleton;
	int m_MemberLayer;
	
protected:
	void MouseClickAction() override
	{
		Context()->DisplayPopup(new CPopup(m_pAssetsEditor, m_MemberSkeleton, m_MemberLayer, m_DrawRect));
	}

public:
	CMemberLayerEdit(CGuiEditor* pAssetsEditor, int MemberSkeleton, int MemberLayer) :
		gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
		m_pAssetsEditor(pAssetsEditor),
		m_MemberSkeleton(MemberSkeleton),
		m_MemberLayer(MemberLayer)
	{
		
	}
	
	void Update(bool ParentEnabled) override
	{
		if(IsEnabled() && ParentEnabled)
		{
			if(!AssetsManager()->IsValidPackage(m_pAssetsEditor->GetEditedPackageId()) || AssetsManager()->IsReadOnlyPackage(m_pAssetsEditor->GetEditedPackageId()))
				Editable(false);
			else
				Editable(true);
				
			CAssetPath Value = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberSkeleton,
				CAssetPath::Null()
			);
			
			CSubPath LayerPath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CSubPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetFirstEditedSubPath(),
				m_MemberLayer,
				CSubPath::Null()
			);
			
			if(Value.IsNull() || LayerPath.IsNull())
			{
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconNone);
				SetText(_LSTRING("None"));
			}
			else
			{
				CSubPath LayerPath = m_pAssetsEditor->AssetsManager()->GetAssetValue<CSubPath>(
					m_pAssetsEditor->GetEditedAssetPath(),
					m_pAssetsEditor->GetFirstEditedSubPath(),
					m_MemberLayer,
					CSubPath::Null()
				);
				
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconLayer);
				SetText(AssetsManager()->GetAssetValue(Value, LayerPath, CAsset_Skeleton::LAYER_NAME, ""));
			}
		}
		
		gui::CButton::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_Layer(gui::CVListLayout* pList, int MemberSkeleton, int MemberLayer, const CLocalizableString& Text)
{
	CMemberLayerEdit* pWidget = new CMemberLayerEdit(
		m_pAssetsEditor,
		MemberSkeleton,
		MemberLayer
	);
	
	AddField(pList, pWidget, Text);
}
