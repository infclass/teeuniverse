/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverses.
 * 
 * TeeUniverses is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverses is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverses.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __EDITOR_IMAGEPICKER__
#define __EDITOR_IMAGEPICKER__

#include <client/gui/widget.h>

class CImagePicker : public gui::CWidget
{
protected:
	class CGuiEditor* m_pAssetsEditor;
	CAssetPath m_ImagePath;
	bool m_SelectionEnabled;
	ivec2 m_Pivot;
	bool m_DragSelection;

protected:
	virtual void OnImagePicked(int MinX, int MinY, int MaxX, int MaxY) {};

public:
	CImagePicker(CGuiEditor* pAssetsEditor, CAssetPath ImagePath);
	
	virtual void UpdateBoundingSize();
	virtual void Render();
	
	virtual void OnButtonClick(int Button);
	virtual void OnButtonRelease(int Button);
	
	inline void SetImage(const CAssetPath& ImagePath) { m_ImagePath = ImagePath; }
	inline void EnableSelection() { m_SelectionEnabled = true; }
};

#endif
