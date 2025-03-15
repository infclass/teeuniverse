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

#include <editor/gui/view_map.h>

#include <editor/gui/view_map_stamp.h>
#include <editor/gui/view_map_fill.h>
#include <editor/gui/view_map_transform.h>
#include <editor/gui/view_map_vertexeditor.h>
#include <editor/gui/view_map_linedrawer.h>
#include <editor/gui/view_map_eraser.h>
#include <editor/gui/view_map_crop.h>
#include <editor/gui/view_map_object.h>
#include <editor/components/gui.h>
#include <client/maprenderer.h>
#include <client/components/assetsrenderer.h>
#include <client/gui/slider.h>
#include <client/gui/toggle.h>
#include <client/gui/filler.h>
#include <client/gui/float-edit.h>
#include <client/gui/listlayout.h>


class CGridAlignToggle : public gui::CToggle
{
protected:
	CViewMap* m_pViewMap;
	
protected:
	bool GetValue() override
	{
		return m_pViewMap->GetGridAlign();
	}

	void SetValue(bool Value) override
	{
		m_pViewMap->SetGridAlign(Value);
	}

public:
	CGridAlignToggle(CViewMap* pViewMap) :
		gui::CToggle(pViewMap->AssetsEditor(), "", pViewMap->AssetsEditor()->m_Path_Sprite_IconGridAligned),
		m_pViewMap(pViewMap)
	{
		SetToggleStyle(pViewMap->AssetsEditor()->m_Path_Toggle_Toolbar);
	}

	void OnMouseMove() override
	{
		if(m_VisibilityRect.IsInside(Context()->GetMousePos()))
			m_pViewMap->AssetsEditor()->SetHint(_LSTRING("Align to the grid"));
		
		gui::CToggle::OnMouseMove();
	}
};

class CZoomUnitButton : public gui::CButton
{
protected:
	CViewMap* m_pViewMap;	
	
protected:
	void MouseClickAction() override
	{
		m_pViewMap->SetCameraZoomToUnit();
	}
	
public:
	CZoomUnitButton(CViewMap* pViewMap) :
		gui::CButton(pViewMap->Context(), pViewMap->AssetsEditor()->m_Path_Sprite_IconZoomUnit),
		m_pViewMap(pViewMap)
	{
		
	}

	void OnMouseMove() override
	{
		if(m_VisibilityRect.IsInside(Context()->GetMousePos()))
			m_pViewMap->AssetsEditor()->SetHint(_LSTRING("Set the zoom to 100 %"));
		
		gui::CButton::OnMouseMove();
	}
};

class CZoomEdit : public gui::CFloatEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CViewMap* m_pMapView;

protected:
	float GetValue() const override
	{
		return m_pMapView->GetCameraZoom();
	}
	
	void SetValue(float Value) override
	{
		m_pMapView->SetCameraZoom(Value);
	}
	
public:
	CZoomEdit(CGuiEditor* pAssetsEditor, CViewMap* pMapView) :
		gui::CFloatEdit(pAssetsEditor, 1.0f),
		m_pAssetsEditor(pAssetsEditor),
		m_pMapView(pMapView)
	{
		Percent();
	}
};

class CSimpleToggle : public gui::CToggle
{
protected:
	CGuiEditor* m_pAssetsEditor;
	bool* m_pBoolean;
	CLocalizableString m_LHint;
	
protected:
	bool GetValue() override
	{
		return *m_pBoolean;
	}

	void SetValue(bool Value) override
	{
		*m_pBoolean = Value;
	}
	
public:
	CSimpleToggle(CGuiEditor* pAssetsEditor, bool* pBoolean, CAssetPath IconPath, const CLocalizableString& LHint) :
		gui::CToggle(pAssetsEditor, IconPath),
		m_pAssetsEditor(pAssetsEditor),
		m_pBoolean(pBoolean)
	{
		SetToggleStyle(pAssetsEditor->m_Path_Toggle_Toolbar);
		m_LHint = LHint;
	}

	void OnMouseMove() override
	{
		if(m_VisibilityRect.IsInside(Context()->GetMousePos()))
			m_pAssetsEditor->SetHint(m_LHint);
		
		gui::CToggle::OnMouseMove();
	}
};

class CLODToggle : public gui::CToggle
{
protected:
	CViewMap* m_pView;
	
protected:
	bool GetValue() override
	{
		return m_pView->GetLoD() > 0;
	}

	void SetValue(bool Value) override
	{
		m_pView->SetLoD(Value ? 1 : 0);
	}
	
public:
	CLODToggle(CGui* pContext, CViewMap* pView) :
		gui::CToggle(pContext, _LSTRING("Show map details")),
		m_pView(pView)
	{
		
	}
};

class CDisplaySettingsButton : public gui::CButton
{
protected:
	class CZoneOpacityButton : public gui::CButton
	{
	protected:
		CViewMap* m_pViewMap;
		float m_Opacity;
	
	protected:
		void MouseClickAction() override
		{
			m_pViewMap->SetZoneOpacity(m_Opacity);
		}
	
	public:
		CZoneOpacityButton(CViewMap* pViewMap, CAssetPath IconPath, float Opacity) :
			gui::CButton(pViewMap->Context(), IconPath),
			m_pViewMap(pViewMap),
			m_Opacity(Opacity)
		{ }
	};
	
	class CEntityStyleButton : public gui::CButton
	{
	protected:
		CViewMap* m_pViewMap;
		int m_Value;
	
	protected:
		void MouseClickAction() override
		{
			m_pViewMap->SetShowEntites(m_Value);
		}
	
	public:
		CEntityStyleButton(CViewMap* pViewMap, CAssetPath IconPath, int Value) :
			gui::CButton(pViewMap->Context(), IconPath),
			m_pViewMap(pViewMap),
			m_Value(Value)
		{ }
	};

	class CPopup : public gui::CPopup
	{
	protected:
		CViewMap* m_pViewMap;
		
	public:
		CPopup(CViewMap* pViewMap, const gui::CRect& CreatorRect) :
			gui::CPopup(pViewMap->Context(), CreatorRect, 280, -1, CPopup::ALIGNMENT_BOTTOM),
			m_pViewMap(pViewMap)
		{
			gui::CVListLayout* pLayout = new gui::CVListLayout(Context());
			Add(pLayout);
			
			{
				gui::CLabelHeader* pLabel = new gui::CLabelHeader(Context(), _LSTRING("Zones"));
				pLabel->NoTextClipping();
				pLayout->Add(pLabel, false);
			}
			
			{
				gui::CLabel* pLabel = new gui::CLabel(Context(), _LSTRING("Rendering mode of zones"));
				pLabel->NoTextClipping();
				pLayout->Add(pLabel, false);
			}
			
			{
				gui::CHListLayout* pLayout2 = new gui::CHListLayout(Context());
				pLayout->Add(pLayout2);
				
				pLayout2->Add(new CZoneOpacityButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconZoneRatio0, 0.0f), true);
				pLayout2->Add(new CZoneOpacityButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconZoneRatio1, 0.25f), true);
				pLayout2->Add(new CZoneOpacityButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconZoneRatio2, 0.5f), true);
				pLayout2->Add(new CZoneOpacityButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconZoneRatio3, 0.85f), true);
				pLayout2->Add(new CZoneOpacityButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconZoneRatio4, 1.0f), true);
			}
			
			pLayout->AddSeparator();
			
			{
				gui::CLabelHeader* pLabel = new gui::CLabelHeader(Context(), _LSTRING("Entities"));
				pLabel->NoTextClipping();
				pLayout->Add(pLabel, false);
			}
			
			{
				gui::CLabel* pLabel = new gui::CLabel(Context(), _LSTRING("Rendering mode of entities"));
				pLabel->NoTextClipping();
				pLayout->Add(pLabel, false);
			}
			
			{
				gui::CHListLayout* pLayout2 = new gui::CHListLayout(Context());
				pLayout->Add(pLayout2);
				
				pLayout2->Add(new CEntityStyleButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconEntityRatio0, 0), true);
				pLayout2->Add(new CEntityStyleButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconEntityRatio1, 1), true);
				pLayout2->Add(new CEntityStyleButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconEntityRatio2, 2), true);
				pLayout2->Add(new CEntityStyleButton(m_pViewMap, m_pViewMap->AssetsEditor()->m_Path_Sprite_IconEntityRatio3, 3), true);
			}
			
			pLayout->AddSeparator();
			
			{
				gui::CLabelHeader* pLabel = new gui::CLabelHeader(Context(), _LSTRING("Layers"));
				pLabel->NoTextClipping();
				pLayout->Add(pLabel, false);
			}
			
			{
				gui::CToggle* pToggle = new CLODToggle(Context(), m_pViewMap);
				pLayout->Add(pToggle, false);
			}
		}
	
		int GetInputToBlock() override { return CGui::BLOCKEDINPUT_ALL; }
	};
	
protected:
	CViewMap* m_pViewMap;	
	
protected:
	void MouseClickAction() override
	{
		Context()->DisplayPopup(new CPopup(m_pViewMap, m_DrawRect));
	}
	
public:
	CDisplaySettingsButton(CViewMap* pViewMap) :
		gui::CButton(pViewMap->Context(), pViewMap->AssetsEditor()->m_Path_Sprite_IconDisplaySettings),
		m_pViewMap(pViewMap)
	{
		
	}

	void OnMouseMove() override
	{
		if(m_VisibilityRect.IsInside(Context()->GetMousePos()))
			m_pViewMap->AssetsEditor()->SetHint(_LSTRING("Show map view options"));
		
		gui::CButton::OnMouseMove();
	}
};

CViewMap::ScopedGroupSetter::ScopedGroupSetter(CViewMap *pViewMap) :
	m_ViewMap(pViewMap)
{
	m_ViewMap->MapRenderer()->SetGroup(m_ViewMap->GetMapGroupPath());
}

CViewMap::ScopedGroupSetter::~ScopedGroupSetter()
{
	m_ViewMap->MapRenderer()->UnsetGroup();
}

/* VIEW MAP ***********************************************************/

CViewMap::CViewMap(CGuiEditor* pAssetsEditor) :
	CViewManager::CView(pAssetsEditor),
	m_GridAligned(false),
	m_CameraDraged(false),
	m_ZoneOpacity(0.5f),
	m_ShowGrid(false),
	m_ShowMeshes(false),
	m_ShowEntities(2),
	m_ZoomLockedToUnit(false),
	m_LoD(1),
	m_pCursorTool_MapStamp(nullptr),
	m_pCursorTool_MapFill(nullptr),
	m_pCursorTool_MapTransform(nullptr),
	m_pCursorTool_MapEdit(nullptr),
	m_pCursorTool_MapEraser(nullptr),
	m_pCursorTool_MapCrop(nullptr),
	m_pCursorTool_MapAddVertex(nullptr),
	m_pCursorTool_MapWeightVertex(nullptr)
{
	m_pCursorTool_MapStamp = new CCursorTool_MapStamp(this);
	m_pToolbar->Add(m_pCursorTool_MapStamp);
	
	m_pCursorTool_MapFill = new CCursorTool_MapFill(this);
	m_pToolbar->Add(m_pCursorTool_MapFill);
	
	m_pCursorTool_MapTransform = new CCursorTool_MapTransform(this);
	m_pToolbar->Add(m_pCursorTool_MapTransform);
	
	m_pCursorTool_MapAddVertex = new CCursorTool_MapLineDrawer(this);
	m_pToolbar->Add(m_pCursorTool_MapAddVertex);
	
	m_pCursorTool_MapEdit = new CCursorTool_MapVertexEditor(this);
	m_pToolbar->Add(m_pCursorTool_MapEdit);
	
	m_pCursorTool_MapEraser = new CCursorTool_MapEraser(this);
	m_pToolbar->Add(m_pCursorTool_MapEraser);
	
	m_pCursorTool_MapCrop = new CCursorTool_MapCrop(this);
	m_pToolbar->Add(m_pCursorTool_MapCrop);
	
	m_pCursorTool_MapWeightVertex = new CCursorTool_MapObjectWeightVertex(this);
	m_pToolbar->Add(m_pCursorTool_MapWeightVertex);
	
	m_pCursorTool_MapStamp->UpdateToolbar();
	m_pCursorTool_MapFill->UpdateToolbar();
	m_pCursorTool_MapTransform->UpdateToolbar();
	m_pCursorTool_MapEdit->UpdateToolbar();
	m_pCursorTool_MapEraser->UpdateToolbar();
	m_pCursorTool_MapCrop->UpdateToolbar();
	m_pCursorTool_MapAddVertex->UpdateToolbar();
	m_pCursorTool_MapWeightVertex->UpdateToolbar();
	
	m_pToolbar->Add(new gui::CFiller(Context()), true);
	m_pToolbar->Add(new CZoomUnitButton(this), false);
	m_pToolbar->Add(new CZoomEdit(AssetsEditor(), this), false, 75);
	m_pToolbar->AddSeparator();
	m_pToolbar->Add(new CSimpleToggle(AssetsEditor(), &m_ShowMeshes, AssetsEditor()->m_Path_Sprite_IconBigMesh, _LSTRING("Show/hide meshes")), false);
	m_pToolbar->Add(new CGridAlignToggle(this), false);
	m_pToolbar->Add(new CSimpleToggle(AssetsEditor(), &m_ShowGrid, AssetsEditor()->m_Path_Sprite_IconGrid, _LSTRING("Show/hide grid")), false);
	m_pToolbar->Add(new CDisplaySettingsButton(this), false);
	
	m_pMapRenderer.reset(new CMapRenderer(AssetsEditor()->EditorKernel()));
}

CAssetPath CViewMap::GetMapGroupPath()
{
	switch(AssetsEditor()->GetEditedAssetPath().GetType())
	{
		case CAsset_MapGroup::TypeId:
			return AssetsEditor()->GetEditedAssetPath();
		case CAsset_MapLayerTiles::TypeId:
		{
			const CAsset_MapLayerTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerTiles>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
		case CAsset_MapLayerQuads::TypeId:
		{
			const CAsset_MapLayerQuads* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerQuads>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
		case CAsset_MapLayerObjects::TypeId:
		{
			const CAsset_MapLayerObjects* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerObjects>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
	}
	
	return CAssetPath::Null();
}

CAssetPath CViewMap::GetMapPath()
{
	switch(AssetsEditor()->GetEditedAssetPath().GetType())
	{
		case CAsset_Map::TypeId:
			return AssetsEditor()->GetEditedAssetPath();
		case CAsset_MapZoneTiles::TypeId:
		{
			const CAsset_MapZoneTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapZoneTiles>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
		case CAsset_MapZoneObjects::TypeId:
		{
			const CAsset_MapZoneObjects* pLayer = AssetsManager()->GetAsset<CAsset_MapZoneObjects>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
		case CAsset_MapEntities::TypeId:
		{
			const CAsset_MapEntities* pLayer = AssetsManager()->GetAsset<CAsset_MapEntities>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
				return pLayer->GetParentPath();
			break;
		}
		case CAsset_MapGroup::TypeId:
		{
			const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(AssetsEditor()->GetEditedAssetPath());
			if(pGroup)
				return pGroup->GetParentPath();
			break;
		}
		case CAsset_MapLayerTiles::TypeId:
		{
			const CAsset_MapLayerTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerTiles>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
			{
				const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(pLayer->GetParentPath());
				if(pGroup)
					return pGroup->GetParentPath();
			}
			break;
		}
		case CAsset_MapLayerQuads::TypeId:
		{
			const CAsset_MapLayerQuads* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerQuads>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
			{
				const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(pLayer->GetParentPath());
				if(pGroup)
					return pGroup->GetParentPath();
			}
			break;
		}
		case CAsset_MapLayerObjects::TypeId:
		{
			const CAsset_MapLayerObjects* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerObjects>(AssetsEditor()->GetEditedAssetPath());
			if(pLayer)
			{
				const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(pLayer->GetParentPath());
				if(pGroup)
					return pGroup->GetParentPath();
			}
			break;
		}
	}
	
	return CAssetPath::Null();
}

void CViewMap::Update(bool ParentEnabled)
{
	CView::Update(ParentEnabled);
	
	if(!GetCursorTool() || GetCursorTool()->IsDisabled())
	{
		switch(AssetsEditor()->GetEditedAssetPath().GetType())
		{
			case CAsset_MapEntities::TypeId:
			case CAsset_MapLayerTiles::TypeId:
			case CAsset_MapZoneTiles::TypeId:
			case CAsset_MapLayerQuads::TypeId:
				SetCursorTool(m_pCursorTool_MapStamp);
				break;
			case CAsset_MapZoneObjects::TypeId:
			case CAsset_MapLayerObjects::TypeId:
				SetCursorTool(m_pCursorTool_MapEdit);
				break;
			case CAsset_MapGroup::TypeId:
				SetCursorTool(m_pCursorTool_MapTransform);
				break;
		}
	}
	
	if(ParentEnabled && IsEnabled())
	{
		while(AssetsEditor()->m_BindCall_ZoomIn > 0)
		{
			AssetsEditor()->m_BindCall_ZoomIn--;
			SetCameraZoom(GetCameraZoom()*1.1f);
		}
		while(AssetsEditor()->m_BindCall_ZoomOut > 0)
		{
			AssetsEditor()->m_BindCall_ZoomOut--;
			SetCameraZoom(GetCameraZoom()/1.1f);
		}
		while(AssetsEditor()->m_BindCall_Zoom11 > 0)
		{
			AssetsEditor()->m_BindCall_Zoom11--;
			SetCameraZoomToUnit();
		}
	}
}

void CViewMap::RenderView()
{
	CAssetPath MapPath = GetMapPath();
	
	vec2 CameraPosition = AssetsManager()->GetAssetValue<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, 0.0f);
	float CameraZoom = GetCameraZoom();
	
	MapRenderer()->SetTime(AssetsEditor()->GetTime());
	MapRenderer()->SetCanvas(m_ViewRect, vec2(m_ViewRect.x + m_ViewRect.w/2, m_ViewRect.y + m_ViewRect.h/2));
	MapRenderer()->SetCamera(CameraPosition, CameraZoom);
	
	vec4 Color = 1.0f;
	if(m_ZoneOpacity > 0.5f)
	{
		Color.r = 1.0f - 2.0f*(m_ZoneOpacity-0.5f);
		Color.g = 1.0f - 2.0f*(m_ZoneOpacity-0.5f);
		Color.b = 1.0f - 2.0f*(m_ZoneOpacity-0.5f);
	}
	
	MapRenderer()->RenderMap(MapPath, Color, m_LoD, m_ShowMeshes);
	
	Color = 1.0f;
	if(m_ZoneOpacity < 0.5f)
		Color.a = 2.0f*m_ZoneOpacity;
	
	MapRenderer()->RenderMap_Zones(MapPath, Color);
	
	if(AssetsEditor()->GetEditedAssetPath().GetType() == CAsset_MapZoneTiles::TypeId)
	{
		const CAsset_MapZoneTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapZoneTiles>(AssetsEditor()->GetEditedAssetPath());
		if(pLayer)
		{
			const CAsset_ZoneType* pZoneType = AssetsManager()->GetAsset<CAsset_ZoneType>(pLayer->GetZoneTypePath());
			if(pZoneType && pZoneType->GetDataIntArraySize() > 0)
			{
				MapRenderer()->UnsetGroup();
				MapRenderer()->RenderZoneIntData(AssetsEditor()->GetEditedAssetPath(), pLayer->GetZoneTypePath());
			}
		}
	}

	RenderGrid();
	RenderEntities();
	RenderBoxes();
}

void CViewMap::RenderGrid()
{
	if(!m_ShowGrid)
		return;

	float Log = log((1.0 / GetCameraZoom()) * 32.0) / log(2.0);
	float Int = floor(Log);
	float Frac = Log - Int;
	float Alpha = 1.f - Frac;
	float Step = pow(2.0, Int);

	ScopedGroupSetter GroupSetter(this);
	MapRenderer()->RenderGrid(Step, vec4(1.0f, 1.0f, 1.0f, 0.5f * Alpha));
	MapRenderer()->RenderGrid(Step * 2.0f, vec4(1.0f, 1.0f, 1.0f, 0.5f * (1.0f - Alpha)));
}

void CViewMap::RenderEntities()
{
	const CAsset_Map* pMap = AssetsManager()->GetAsset<CAsset_Map>(GetMapPath());
	if(!pMap)
		return;

	CAsset_Map::CIteratorEntityLayer IterEntityLayer;
	for(IterEntityLayer = pMap->BeginEntityLayer(); IterEntityLayer != pMap->EndEntityLayer(); ++IterEntityLayer)
	{
		CAssetPath EntitiesPath = pMap->GetEntityLayer(*IterEntityLayer);

		const CAsset_MapEntities* pEntities = AssetsManager()->GetAsset<CAsset_MapEntities>(EntitiesPath);
		if(!pEntities)
			continue;

		if(!pEntities->GetVisibility())
			continue;

		vec4 Color = 1.0f;
		if(AssetsEditor()->GetEditedAssetPath().GetType() == CAsset_MapEntities::TypeId && EntitiesPath != AssetsEditor()->GetEditedAssetPath())
		{
			if(m_ShowEntities > 0)
				Color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
			else
				continue;
		}

		const std::vector<CAsset_MapEntities::CEntity>& Entities = pEntities->GetEntityArray();
		if(m_ShowEntities == 1 || m_ShowEntities == 2)
		{
			Graphics()->TextureClear();
			Graphics()->QuadsBegin();
			Graphics()->SetColor(vec4(1.0f, 1.0f, 1.0f, 0.75f), true);
			for(const CAsset_MapEntities::CEntity &Entity : Entities)
			{			vec2 Pivot;
				matrix2x2 Transform;
				Entity.GetTransform(AssetsManager(), MapRenderer()->GetTime(), &Transform, &Pivot);

				vec2 Position = Entity.GetPosition();
				vec2 TransformedPos = Transform * Position + Pivot;
				vec2 ScreenPos = MapRenderer()->MapPosToScreenPos(TransformedPos);
				CAssetPath TypePath = Entity.GetTypePath();

				const CAsset_EntityType* pEntityType = AssetsManager()->GetAsset<CAsset_EntityType>(TypePath);
				if(!pEntityType)
					continue;

				int i = 0;
				while(i < 32)
				{
					float Angle0 = 2.0f*Pi*static_cast<float>(i)/32.0f;
					float Angle1 = 2.0f*Pi*static_cast<float>(i+1)/32.0f;
					float Angle2 = 2.0f*Pi*static_cast<float>(i+2)/32.0f;

					vec2 P0 = MapRenderer()->MapPosToScreenPos(TransformedPos + vec2(std::cos(Angle0), std::sin(Angle0)) * pEntityType->GetCollisionRadius());
					vec2 P1 = MapRenderer()->MapPosToScreenPos(TransformedPos + vec2(std::cos(Angle1), std::sin(Angle1)) * pEntityType->GetCollisionRadius());
					vec2 P2 = MapRenderer()->MapPosToScreenPos(TransformedPos + vec2(std::cos(Angle2), std::sin(Angle2)) * pEntityType->GetCollisionRadius());

					CGraphics::CFreeformItem Freeform(
						P1.x, P1.y,
						P2.x, P2.y,
						P0.x, P0.y,
						ScreenPos.x, ScreenPos.y
					);
					Graphics()->QuadsDrawFreeform(&Freeform, 1);

					i += 2;
				}
			}

			Graphics()->QuadsEnd();
		}

		for(const CAsset_MapEntities::CEntity &Entity : Entities)
		{
			vec2 Pivot;
			matrix2x2 Transform;
			Entity.GetTransform(AssetsManager(), MapRenderer()->GetTime(), &Transform, &Pivot);

			vec2 Position = Entity.GetPosition();
			vec2 ScreenPos = MapRenderer()->MapPosToScreenPos(Transform * Position + Pivot);
			CAssetPath TypePath = Entity.GetTypePath();
			vec2 ScreenPivot = MapRenderer()->MapPosToScreenPos(Pivot);

			const CAsset_EntityType* pEntityType = AssetsManager()->GetAsset<CAsset_EntityType>(TypePath);
			if(pEntityType)
			{
				if(m_ShowEntities >= 2)
				{
					AssetsRenderer()->DrawSprite(pEntityType->GetGizmoPath(), ScreenPos, 1.0f, 0.0f, 0x0, Color);
				}

				if(m_ShowEntities < 3)
				{
					AssetsRenderer()->DrawSprite(AssetsEditor()->m_Path_Sprite_GizmoPivot, ScreenPivot, 1.0f, 0.0f, 0x0, Color);
				}
			}
			else
			{
				AssetsRenderer()->DrawSprite(AssetsEditor()->m_Path_Sprite_GizmoPivot, ScreenPivot, 1.0f, 0.0f, 0x0, Color);
			}
		}
	}
}

void CViewMap::RenderBoxes()
{
	if(AssetsEditor()->GetEditedAssetPath().GetType() == CAsset_MapLayerTiles::TypeId)
	{
		const CAsset_MapLayerTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerTiles>(AssetsEditor()->GetEditedAssetPath());
		if(pLayer)
		{
			ScopedGroupSetter GroupSetter(this);

			vec2 MinCorner = MapRenderer()->TilePosToScreenPos(vec2(pLayer->GetPositionX(), pLayer->GetPositionY()));
			vec2 MaxCorner = MapRenderer()->TilePosToScreenPos(vec2(pLayer->GetPositionX() + pLayer->GetTileWidth(), pLayer->GetPositionY() + pLayer->GetTileHeight()));

			gui::CRect Rect;
			Rect.x = MinCorner.x;
			Rect.y = MinCorner.y;
			Rect.w = MaxCorner.x - MinCorner.x;
			Rect.h = MaxCorner.y - MinCorner.y;
			AssetsRenderer()->DrawGuiRect(&Rect, AssetsEditor()->m_Path_Rect_Border);
		}
	}
	else if(AssetsEditor()->GetEditedAssetPath().GetType() == CAsset_MapZoneTiles::TypeId)
	{
		const CAsset_MapZoneTiles* pLayer = AssetsManager()->GetAsset<CAsset_MapZoneTiles>(AssetsEditor()->GetEditedAssetPath());
		if(pLayer)
		{
			ScopedGroupSetter GroupSetter(this);

			vec2 MinCorner = MapRenderer()->TilePosToScreenPos(vec2(pLayer->GetPositionX(), pLayer->GetPositionY()));
			vec2 MaxCorner = MapRenderer()->TilePosToScreenPos(vec2(pLayer->GetPositionX() + pLayer->GetTileWidth(), pLayer->GetPositionY() + pLayer->GetTileHeight()));

			gui::CRect Rect;
			Rect.x = MinCorner.x;
			Rect.y = MinCorner.y;
			Rect.w = MaxCorner.x - MinCorner.x;
			Rect.h = MaxCorner.y - MinCorner.y;
			AssetsRenderer()->DrawGuiRect(&Rect, AssetsEditor()->m_Path_Rect_Border);
		}
	}
	else if(AssetsEditor()->GetEditedAssetPath().GetType() == CAsset_MapGroup::TypeId)
	{
		const CAsset_MapGroup* pGroup = AssetsManager()->GetAsset<CAsset_MapGroup>(AssetsEditor()->GetEditedAssetPath());
		if(pGroup && pGroup->GetClipping())
		{
			vec2 MinCorner = MapRenderer()->MapPosToScreenPos(pGroup->GetClipPosition());
			vec2 MaxCorner = MapRenderer()->MapPosToScreenPos(pGroup->GetClipPosition() + pGroup->GetClipSize());

			gui::CRect Rect;
			Rect.x = MinCorner.x;
			Rect.y = MinCorner.y;
			Rect.w = MaxCorner.x - MinCorner.x;
			Rect.h = MaxCorner.y - MinCorner.y;
			AssetsRenderer()->DrawGuiRect(&Rect, AssetsEditor()->m_Path_Rect_Border);
		}
	}
}

void CViewMap::OnButtonClick(int Button)
{
	if(m_VisibilityRect.IsInside(Context()->GetMousePos()))
	{
		float CameraZoom = GetCameraZoom();
		
		if(Button == KEY_MOUSE_WHEEL_UP)
		{
			CameraZoom *= 1.1f;
			SetCameraZoom(CameraZoom);
			
			vec2 MousePos = vec2(Context()->GetMousePos().x, Context()->GetMousePos().y);
			vec2 MouseMapPos = MapRenderer()->ScreenPosToMapPos(MousePos);
			
			CAssetPath MapPath = GetMapPath();
			vec2 CameraPos = AssetsManager()->GetAssetValue<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, 0.0f);
			CameraPos = MouseMapPos + (CameraPos - MouseMapPos)/1.1f;
			AssetsManager()->SetAssetValue_Hard<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, CameraPos);
		}
		else if(Button == KEY_MOUSE_WHEEL_DOWN)
		{
			CameraZoom /= 1.1f;
			SetCameraZoom(CameraZoom);
			
			vec2 MousePos = vec2(Context()->GetMousePos().x, Context()->GetMousePos().y);
			vec2 MouseMapPos = MapRenderer()->ScreenPosToMapPos(MousePos);
			
			CAssetPath MapPath = GetMapPath();
			vec2 CameraPos = AssetsManager()->GetAssetValue<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, 0.0f);
			CameraPos = MouseMapPos + (CameraPos - MouseMapPos)*1.1f;
			AssetsManager()->SetAssetValue_Hard<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, CameraPos);
		}
		else if(Button == KEY_MOUSE_3 || (Button == KEY_MOUSE_1 && Input()->KeyIsPressed(KEY_LCTRL)))
		{
			m_CameraDraged = true;
			return;
		}
	}
	
	CView::OnButtonClick(Button);
}

void CViewMap::OnButtonRelease(int Button)
{
	if(m_CameraDraged && (Button == KEY_MOUSE_1 || Button == KEY_MOUSE_3))
	{
		m_CameraDraged = false;
	}
	
	CView::OnButtonRelease(Button);
}

void CViewMap::OnMouseMove()
{
	ivec2 MousePos = Context()->GetMousePos();
	
	if(m_VisibilityRect.IsInside(MousePos))
	{
		vec2 MapPos = MapRenderer()->ScreenPosToMapPos(vec2(MousePos.x, MousePos.y));
		
		CLocalizableString LString(_("Map position: ({float:XCoord}   {float:YCoord})"));
		LString.AddDouble("XCoord", MapPos.x);
		LString.AddDouble("YCoord", MapPos.y);
		AssetsEditor()->SetCoordinates(LString);
	}
	
	if(m_CameraDraged)
	{
		CAssetPath MapPath = GetMapPath();
		float CameraZoom = AssetsManager()->GetAssetValue<float>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAZOOM, 1.0f);
		vec2 CameraPos = AssetsManager()->GetAssetValue<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, 0.0f);
		
		ivec2 MouseRelPos = Context()->GetMouseRelPos();
		CameraPos -= vec2(MouseRelPos.x, MouseRelPos.y)/CameraZoom;
		
		AssetsManager()->SetAssetValue_Hard<vec2>(MapPath, CSubPath::Null(), CAsset_Map::CAMERAPOSITION, CameraPos);
		return;
	}
	
	CView::OnMouseMove();
}

float CViewMap::GetCameraZoom()
{
	return (m_ZoomLockedToUnit ? 1.0f : AssetsManager()->GetAssetValue<float>(GetMapPath(), CSubPath::Null(), CAsset_Map::CAMERAZOOM, 1.0f));
}

void CViewMap::SetCameraZoom(float Value)
{
	Value = clamp(Value, 0.01f, 100.0f);
	m_ZoomLockedToUnit = false;
	AssetsManager()->SetAssetValue_Hard<float>(GetMapPath(), CSubPath::Null(), CAsset_Map::CAMERAZOOM, Value);
}

void CViewMap::SetCameraZoomToUnit()
{
	m_ZoomLockedToUnit = !m_ZoomLockedToUnit;
}

void CViewMap::MemorizeZoneData(const CAssetPath& AssetPath, const std::vector<int>& DataInt)
{
	for(unsigned int i=0; i<m_ZoneDataMemory.size(); i++)
	{
		if(m_ZoneDataMemory[i].first == AssetPath)
		{
			m_ZoneDataMemory[i].second = DataInt;
			break;
		}
	}
	
	m_ZoneDataMemory.emplace_back();
	m_ZoneDataMemory.back().first = AssetPath;
	m_ZoneDataMemory.back().second = DataInt;
}

const std::vector<int>* CViewMap::GetMemorizedZoneData(const CAssetPath& AssetPath)
{
	for(unsigned int i=0; i<m_ZoneDataMemory.size(); i++)
	{
		if(m_ZoneDataMemory[i].first == AssetPath)
			return &m_ZoneDataMemory[i].second;
	}
	
	return nullptr;
}

void CViewMap::CCursorTool::ApplyGridAlignment(vec2 *pPoint, const vec2 &Offset) const
{
	bool HalfStepAlignment = Input()->KeyIsPressed(KEY_LSHIFT);
	if(m_pViewMap->GetGridAlign() || HalfStepAlignment)
	{
		vec2 AlignedPoint = *pPoint;
		AlignedPoint -= Offset;
		AlignedPoint = m_pViewMap->MapRenderer()->MapPosToTilePos(AlignedPoint);
		int Factor = 1;
		if(HalfStepAlignment)
		{
			Factor = 2;
			if (m_pViewMap->MapRenderer()->GetCameraZoom() >= 8.0f)
			{
				Factor = 8;
			}
			else if (m_pViewMap->MapRenderer()->GetCameraZoom() >= 4.0f)
			{
				Factor = 4;
			}
		}

		AlignedPoint *= Factor;
		AlignedPoint = vec2(floor(AlignedPoint.x + 0.5), floor(AlignedPoint.y + 0.5));
		AlignedPoint = m_pViewMap->MapRenderer()->TilePosToMapPos(AlignedPoint);
		AlignedPoint /= Factor;

		AlignedPoint += Offset;
		*pPoint = AlignedPoint;
	}
}
