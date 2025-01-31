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
 * Some parts of this file comes from other projects.
 * These parts are itendified in this file by the following block:
 * 
 * FOREIGN CODE BEGIN: ProjectName *************************************
 * 
 * FOREIGN CODE END: ProjectName ***************************************
 * 
 * If ProjectName is "TeeWorlds", then this part of the code follows the
 * TeeWorlds licence:
 *      (c) Magnus Auvinen. See LICENSE_TEEWORLDS in the root of the
 *      distribution for more information. If you are missing that file,
 *      acquire a complete release at teeworlds.com.
 */

#include "graphics_backend_sdl.h"

#include <shared/system/memory.h>
#include <shared/system/debug.h>
#include <shared/tl/threading.h>

PFNGLTEXIMAGE3DPROC glTexImage3D_Dyn;

/* FOREIGN CODE BEGIN: TeeWorlds **************************************/

// ------------ CGraphicsBackend_SDL

void CGraphicsBackend_SDL::ThreadFunc(void *pUser)
{
	CGraphicsBackend_SDL *pThis = (CGraphicsBackend_SDL *)pUser;

	while(!pThis->m_Shutdown)
	{
		pThis->m_Activity.wait();
		if(pThis->m_pBuffer)
		{
			#ifdef CONF_PLATFORM_MACOSX
				CAutoreleasePool AutoreleasePool;
			#endif
			pThis->m_pProcessor->RunBuffer(pThis->m_pBuffer);
			sync_barrier();
			pThis->m_pBuffer = nullptr;
			pThis->m_BufferDone.signal();
		}
	}
}

CGraphicsBackend_SDL::CGraphicsBackend_SDL()
{
	m_pBuffer = nullptr;
	m_pProcessor = nullptr;
	m_pThread = nullptr;
}

void CGraphicsBackend_SDL::StartProcessor(ICommandProcessor *pProcessor)
{
	m_Shutdown = false;
	m_pProcessor = pProcessor;
	m_pThread = thread_init(ThreadFunc, this, "Graphics thread");
	m_BufferDone.signal();
}

void CGraphicsBackend_SDL::StopProcessor()
{
	m_Shutdown = true;
	m_Activity.signal();
	thread_wait(m_pThread);
	thread_destroy(m_pThread);
}

void CGraphicsBackend_SDL::RunBuffer(CCommandBuffer *pBuffer)
{
	WaitForIdle();
	m_pBuffer = pBuffer;
	m_Activity.signal();
}

bool CGraphicsBackend_SDL::IsIdle() const
{
	return m_pBuffer == nullptr;
}

void CGraphicsBackend_SDL::WaitForIdle()
{
	while(m_pBuffer != nullptr)
		m_BufferDone.wait();
}


// ------------ CCommandProcessorFragment_General

void CCommandProcessorFragment_General::Cmd_Signal(const CCommandBuffer::SCommand_Signal *pCommand)
{
	pCommand->m_pSemaphore->signal();
}

bool CCommandProcessorFragment_General::RunCommand(const CCommandBuffer::SCommand * pBaseCommand)
{
	switch(pBaseCommand->m_Cmd)
	{
	case CCommandBuffer::CMD_NOP: break;
	case CCommandBuffer::CMD_SIGNAL: Cmd_Signal(static_cast<const CCommandBuffer::SCommand_Signal *>(pBaseCommand)); break;
	default: return false;
	}

	return true;
}

// ------------ CCommandProcessorFragment_OpenGL

int CCommandProcessorFragment_OpenGL::TexFormatToOpenGLFormat(int TexFormat)
{
	if(TexFormat == CCommandBuffer::TEXFORMAT_RGB) return GL_RGB;
	if(TexFormat == CCommandBuffer::TEXFORMAT_ALPHA) return GL_ALPHA;
	if(TexFormat == CCommandBuffer::TEXFORMAT_RGBA) return GL_RGBA;
	return GL_RGBA;
}

unsigned char CCommandProcessorFragment_OpenGL::Sample(int w, int h, const unsigned char *pData, int u, int v, int Offset, int ScaleW, int ScaleH, int Bpp)
{
	int Value = 0;
	for(int x = 0; x < ScaleW; x++)
		for(int y = 0; y < ScaleH; y++)
			Value += pData[((v+y)*w+(u+x))*Bpp+Offset];
	return Value/(ScaleW*ScaleH);
}

unsigned char* CCommandProcessorFragment_OpenGL::Rescale(int Width, int Height, int NewWidth, int NewHeight, int Format, const unsigned char* pData)
{
	unsigned char *pTmpData;
	int ScaleW = Width/NewWidth;
	int ScaleH = Height/NewHeight;

	int Bpp = 3;
	if(Format == CCommandBuffer::TEXFORMAT_RGBA)
		Bpp = 4;

	pTmpData = new unsigned char[NewWidth*NewHeight*Bpp];

	int c = 0;
	for(int y = 0; y < NewHeight; y++)
		for(int x = 0; x < NewWidth; x++, c++)
		{
			pTmpData[c*Bpp] = Sample(Width, Height, pData, x*ScaleW, y*ScaleH, 0, ScaleW, ScaleH, Bpp);
			pTmpData[c*Bpp+1] = Sample(Width, Height, pData, x*ScaleW, y*ScaleH, 1, ScaleW, ScaleH, Bpp);
			pTmpData[c*Bpp+2] = Sample(Width, Height, pData, x*ScaleW, y*ScaleH, 2, ScaleW, ScaleH, Bpp);
			if(Bpp == 4)
				pTmpData[c*Bpp+3] = Sample(Width, Height, pData, x*ScaleW, y*ScaleH, 3, ScaleW, ScaleH, Bpp);
		}

	return pTmpData;
}

void CCommandProcessorFragment_OpenGL::SetState(const CCommandBuffer::SState &State)
{
	// clip
	if(State.m_ClipEnable)
	{
		glScissor(State.m_ClipX, State.m_ClipY, State.m_ClipW, State.m_ClipH);
		glEnable(GL_SCISSOR_TEST);
	}
	else
		glDisable(GL_SCISSOR_TEST);
	

	// texture
	int SrcBlendMode = GL_ONE;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_3D);
	if(State.m_Texture >= 0 && State.m_Texture < CCommandBuffer::MAX_TEXTURES)
	{
		if(State.m_Dimension == 2 && (m_aTextures[State.m_Texture].m_State&CTexture::STATE_TEX2D))
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_aTextures[State.m_Texture].m_Tex2D);
		}
		else if(State.m_Dimension == 3 && (m_aTextures[State.m_Texture].m_State&CTexture::STATE_TEX3D))
		{
			glEnable(GL_TEXTURE_3D);
			glBindTexture(GL_TEXTURE_3D, m_aTextures[State.m_Texture].m_Tex3D);
		}
		else
			debug::ErrorStream("Graphics") << "invalid texture " << State.m_Texture << ", " << State.m_Dimension << ", " << m_aTextures[State.m_Texture].m_State << std::endl;

		if(m_aTextures[State.m_Texture].m_Format == CCommandBuffer::TEXFORMAT_RGBA)
			SrcBlendMode = GL_ONE;
		else
			SrcBlendMode = GL_SRC_ALPHA;
	}

	// blend
	switch(State.m_BlendMode)
	{
	case CCommandBuffer::BLEND_NONE:
		glDisable(GL_BLEND);
		break;
	case CCommandBuffer::BLEND_ALPHA:
		glEnable(GL_BLEND);
		glBlendFunc(SrcBlendMode, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case CCommandBuffer::BLEND_ADDITIVE:
		glEnable(GL_BLEND);
		glBlendFunc(SrcBlendMode, GL_ONE);
		break;
	default:
		debug::WarningStream("Graphics") << "unknown blendmode " << State.m_BlendMode << std::endl;
	};

	// wrap mode
	switch(State.m_WrapModeU)
	{
	case CGraphics::WRAP_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		break;
	case CGraphics::WRAP_CLAMP:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		break;
	default:
		debug::WarningStream("Graphics") << "unknown wrapmode " << State.m_WrapModeU << std::endl;
	};

	switch(State.m_WrapModeV)
	{
	case CGraphics::WRAP_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case CGraphics::WRAP_CLAMP:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	default:
		debug::WarningStream("Graphics") << "unknown wrapmode " << State.m_WrapModeV << std::endl;
	};

	if(State.m_Texture >= 0 && State.m_Texture < CCommandBuffer::MAX_TEXTURES && State.m_Dimension == 3)
	{
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		switch(State.m_WrapModeU)
		{
		case CGraphics::WRAP_REPEAT:
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			break;
		case CGraphics::WRAP_CLAMP:
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			break;
		default:
			debug::WarningStream("Graphics") << "unknown wrapmode " << State.m_WrapModeU << std::endl;
		};

		switch(State.m_WrapModeV)
		{
		case CGraphics::WRAP_REPEAT:
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case CGraphics::WRAP_CLAMP:
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		default:
			debug::WarningStream("Graphics") << "unknown wrapmode " << State.m_WrapModeV << std::endl;
		};
		
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}

	// screen mapping
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(State.m_ScreenTL.x, State.m_ScreenBR.x, State.m_ScreenBR.y, State.m_ScreenTL.y, 1.0f, 10.f);
}

void CCommandProcessorFragment_OpenGL::Cmd_Init(const SCommand_Init *pCommand)
{
	m_pTextureMemoryUsage = pCommand->m_pTextureMemoryUsage;
}

void CCommandProcessorFragment_OpenGL::Cmd_Texture_Update(const CCommandBuffer::SCommand_Texture_Update *pCommand)
{
	if(m_aTextures[pCommand->m_Slot].m_State&CTexture::STATE_TEX2D)
	{
		glBindTexture(GL_TEXTURE_2D, m_aTextures[pCommand->m_Slot].m_Tex2D);
		glTexSubImage2D(GL_TEXTURE_2D, 0, pCommand->m_X, pCommand->m_Y, pCommand->m_Width, pCommand->m_Height,
			TexFormatToOpenGLFormat(pCommand->m_Format), GL_UNSIGNED_BYTE, pCommand->m_pData);
	}
	delete[] pCommand->m_pData;
}

void CCommandProcessorFragment_OpenGL::Cmd_Texture_Destroy(const CCommandBuffer::SCommand_Texture_Destroy *pCommand)
{
	if(m_aTextures[pCommand->m_Slot].m_State&CTexture::STATE_TEX2D)
		glDeleteTextures(1, &m_aTextures[pCommand->m_Slot].m_Tex2D);
	if(m_aTextures[pCommand->m_Slot].m_State&CTexture::STATE_TEX3D)
		glDeleteTextures(1, &m_aTextures[pCommand->m_Slot].m_Tex3D);
	*m_pTextureMemoryUsage -= m_aTextures[pCommand->m_Slot].m_MemSize;
	m_aTextures[pCommand->m_Slot].m_State = CTexture::STATE_EMPTY;
	m_aTextures[pCommand->m_Slot].m_MemSize = 0;
}

void CCommandProcessorFragment_OpenGL::Cmd_Texture_Create(const CCommandBuffer::SCommand_Texture_Create *pCommand)
{
	int Width = pCommand->m_Width;
	int Height = pCommand->m_Height;
	int GridWidth = pCommand->m_GridWidth;
	int GridHeight = pCommand->m_GridHeight;
	int Depth = 1;
	unsigned char* pTexData = pCommand->m_pData;

	// resample if needed
	if(pCommand->m_Format == CCommandBuffer::TEXFORMAT_RGBA || pCommand->m_Format == CCommandBuffer::TEXFORMAT_RGB)
	{
		int MaxTexSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MaxTexSize);
		if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_TEXTURE3D)
		{
			int Max3DTexSize;
			glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &Max3DTexSize);
			if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_TEXTURE2D)
				MaxTexSize = min(MaxTexSize, Max3DTexSize*16);
			else
				MaxTexSize = Max3DTexSize*16;
		}
		if(Width > MaxTexSize || Height > MaxTexSize)
		{
			do
			{
				Width>>=1;
				Height>>=1;
			}
			while(Width > MaxTexSize || Height > MaxTexSize);

			unsigned char* pTmpData = Rescale(pCommand->m_Width, pCommand->m_Height, Width, Height, pCommand->m_Format, static_cast<const unsigned char *>(pCommand->m_pData));
			delete[] pTexData;
			pTexData = pTmpData;
		}
		else if(Width > GridWidth && Height > GridHeight && (pCommand->m_Flags&CCommandBuffer::TEXFLAG_QUALITY) == 0)
		{
			Width>>=1;
			Height>>=1;

			unsigned char* pTmpData = Rescale(pCommand->m_Width, pCommand->m_Height, Width, Height, pCommand->m_Format, static_cast<const unsigned char *>(pCommand->m_pData));
			delete[] pTexData;
			pTexData = pTmpData;
		}
	}

	// use premultiplied alpha for rgba textures
	if(pCommand->m_Format == CCommandBuffer::TEXFORMAT_RGBA)
	{
		unsigned char *pTexels = (unsigned char *)pTexData;
		for(int i = 0; i < Width * Height; ++i)
		{
			const float a = (pTexels[i*4+3]/255.0f);
			pTexels[i*4+0] = (unsigned char)(pTexels[i*4+0] * a);
			pTexels[i*4+1] = (unsigned char)(pTexels[i*4+1] * a);
			pTexels[i*4+2] = (unsigned char)(pTexels[i*4+2] * a);
		}
	}
	m_aTextures[pCommand->m_Slot].m_Format = pCommand->m_Format;
	
	//
	int Oglformat = TexFormatToOpenGLFormat(pCommand->m_Format);
	int StoreOglformat = TexFormatToOpenGLFormat(pCommand->m_StoreFormat);

	if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_COMPRESSED)
	{
		switch(StoreOglformat)
		{
			case GL_RGB: StoreOglformat = GL_COMPRESSED_RGB_ARB; break;
			case GL_ALPHA: StoreOglformat = GL_COMPRESSED_ALPHA_ARB; break;
			case GL_RGBA: StoreOglformat = GL_COMPRESSED_RGBA_ARB; break;
			default: StoreOglformat = GL_COMPRESSED_RGBA_ARB;
		}
	}

	// 2D texture
	if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_TEXTURE2D)
	{
		glGenTextures(1, &m_aTextures[pCommand->m_Slot].m_Tex2D);
		m_aTextures[pCommand->m_Slot].m_State |= CTexture::STATE_TEX2D;
		glBindTexture(GL_TEXTURE_2D, m_aTextures[pCommand->m_Slot].m_Tex2D);
		if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_NOMIPMAPS)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, StoreOglformat, Width, Height, 0, Oglformat, GL_UNSIGNED_BYTE, pTexData);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, StoreOglformat, Width, Height, Oglformat, GL_UNSIGNED_BYTE, pTexData);
		}

		// calculate memory usage
		m_aTextures[pCommand->m_Slot].m_MemSize = Width*Height*pCommand->m_PixelSize;
		int TexWidth = Width;
		int TexHeight = Height;
		while(TexWidth > 2 && TexHeight > 2)
		{
			TexWidth>>=1;
			TexHeight>>=1;
			m_aTextures[pCommand->m_Slot].m_MemSize += TexWidth*TexHeight*pCommand->m_PixelSize;
		}
	}
	
	// 3D texture
	if(pCommand->m_Flags&CCommandBuffer::TEXFLAG_TEXTURE3D)
	{
		Width /= GridWidth;
		Height /= GridHeight;
		Depth = GridWidth*GridHeight;

		// copy and reorder texture data
		int MemSize = Width*Height*Depth*pCommand->m_PixelSize;
		unsigned char *pTmpData = new unsigned char[MemSize];

		const int TileSize = (Height * Width) * pCommand->m_PixelSize;
		const int TileRowSize = Width * pCommand->m_PixelSize;
		const int ImagePitch = Width*GridWidth * pCommand->m_PixelSize;
		mem_zero(pTmpData, MemSize);
		for(int i = 0; i < Depth; i++)
		{
			const int px = (i%GridWidth) * Width;
			const int py = (i/GridWidth) * Height;
			const char *pTileData = (const char *)pTexData + (py * Width*GridWidth + px) * pCommand->m_PixelSize;
			for(int y = 0; y < Height; y++)
				mem_copy(pTmpData + i*TileSize + y*TileRowSize, pTileData + y * ImagePitch, TileRowSize);
		}

		delete[] pTexData;
		pTexData = pTmpData;
		
		//
		glGenTextures(1, &m_aTextures[pCommand->m_Slot].m_Tex3D);
		m_aTextures[pCommand->m_Slot].m_State |= CTexture::STATE_TEX3D;
		glBindTexture(GL_TEXTURE_3D, m_aTextures[pCommand->m_Slot].m_Tex3D);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage3D_Dyn(GL_TEXTURE_3D, 0, StoreOglformat, Width, Height, Depth, 0, Oglformat, GL_UNSIGNED_BYTE, pTexData);

		m_aTextures[pCommand->m_Slot].m_MemSize += Width*Height*pCommand->m_PixelSize;
	}	

	*m_pTextureMemoryUsage += m_aTextures[pCommand->m_Slot].m_MemSize;

	delete[] pTexData;
}

void CCommandProcessorFragment_OpenGL::Cmd_Clear(const CCommandBuffer::SCommand_Clear *pCommand)
{
	glClearColor(pCommand->m_Color.r, pCommand->m_Color.g, pCommand->m_Color.b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CCommandProcessorFragment_OpenGL::Cmd_SetSize(const CCommandBuffer::SCommand_SetSize *pCommand)
{
	glViewport(0, 0, pCommand->m_Width, pCommand->m_Height);
}

void CCommandProcessorFragment_OpenGL::Cmd_Render(const CCommandBuffer::SCommand_Render *pCommand)
{
	SetState(pCommand->m_State);
	
	glVertexPointer(3, GL_FLOAT, sizeof(CCommandBuffer::SVertex), (char*)pCommand->m_pVertices);
	glTexCoordPointer(3, GL_FLOAT, sizeof(CCommandBuffer::SVertex), (char*)pCommand->m_pVertices + sizeof(float)*3);
	glColorPointer(4, GL_FLOAT, sizeof(CCommandBuffer::SVertex), (char*)pCommand->m_pVertices + sizeof(float)*6);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	switch(pCommand->m_PrimType)
	{
	case CCommandBuffer::PRIMTYPE_QUADS:
		glDrawArrays(GL_QUADS, 0, pCommand->m_PrimCount*4);
		break;
	case CCommandBuffer::PRIMTYPE_LINES:
		glDrawArrays(GL_LINES, 0, pCommand->m_PrimCount*2);
		break;
	default:
		debug::WarningStream("Graphics") << "unknown primtype " << pCommand->m_Cmd << std::endl;
	};
}

void CCommandProcessorFragment_OpenGL::Cmd_Screenshot(const CCommandBuffer::SCommand_Screenshot *pCommand)
{
	// fetch image data
	GLint aViewport[4] = {0,0,0,0};
	glGetIntegerv(GL_VIEWPORT, aViewport);

	int w = pCommand->m_W == -1 ? aViewport[2] : pCommand->m_W;
	int h = pCommand->m_H == -1 ? aViewport[3] : pCommand->m_H;
	int x = pCommand->m_X;
	int y = aViewport[3] - pCommand->m_Y - 1 - (h - 1);
	
	// we allocate one more row to use when we are flipping the texture
	unsigned char *pPixelData = new unsigned char[w*(h+1)*3];
	unsigned char *pTempRow = pPixelData+w*h*3;

	// fetch the pixels
	GLint Alignment;
	glGetIntegerv(GL_PACK_ALIGNMENT, &Alignment);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, pPixelData);
	glPixelStorei(GL_PACK_ALIGNMENT, Alignment);

	// flip the pixel because opengl works from bottom left corner
	for(int ty = 0; ty < h/2; ty++)
	{
		mem_copy(pTempRow, pPixelData+ty*w*3, w*3);
		mem_copy(pPixelData+ty*w*3, pPixelData+(h-ty-1)*w*3, w*3);
		mem_copy(pPixelData+(h-ty-1)*w*3, pTempRow,w*3);
	}

	// fill in the information
	pCommand->m_pImage->m_Width = w;
	pCommand->m_pImage->m_Height = h;
	pCommand->m_pImage->m_Format = CImageInfo::FORMAT_RGB;
	pCommand->m_pImage->m_pData = pPixelData;
}

CCommandProcessorFragment_OpenGL::CCommandProcessorFragment_OpenGL()
{
	mem_zero(m_aTextures, sizeof(m_aTextures));
	m_pTextureMemoryUsage = nullptr;
}

bool CCommandProcessorFragment_OpenGL::RunCommand(const CCommandBuffer::SCommand * pBaseCommand)
{
	switch(pBaseCommand->m_Cmd)
	{
	case CMD_INIT:
		Cmd_Init(static_cast<const SCommand_Init *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_TEXTURE_CREATE:
		Cmd_Texture_Create(static_cast<const CCommandBuffer::SCommand_Texture_Create *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_TEXTURE_DESTROY:
		Cmd_Texture_Destroy(static_cast<const CCommandBuffer::SCommand_Texture_Destroy *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_TEXTURE_UPDATE:
		Cmd_Texture_Update(static_cast<const CCommandBuffer::SCommand_Texture_Update *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_CLEAR:
		Cmd_Clear(static_cast<const CCommandBuffer::SCommand_Clear *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_SETSIZE:
		Cmd_SetSize(static_cast<const CCommandBuffer::SCommand_SetSize *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_RENDER:
		Cmd_Render(static_cast<const CCommandBuffer::SCommand_Render *>(pBaseCommand));
		break;
	case CCommandBuffer::CMD_SCREENSHOT:
		Cmd_Screenshot(static_cast<const CCommandBuffer::SCommand_Screenshot *>(pBaseCommand));
		break;
	default: return false;
	}

	return true;
}


// ------------ CCommandProcessorFragment_SDL

void CCommandProcessorFragment_SDL::Cmd_Init(const SCommand_Init *pCommand)
{
	m_GLContext = pCommand->m_GLContext;
	m_pWindow = pCommand->m_pWindow;
	SDL_GL_MakeCurrent(m_pWindow, m_GLContext);

	// set some default settings
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_ALPHA_TEST);
	glDepthMask(0);
}

void CCommandProcessorFragment_SDL::Cmd_Shutdown(const SCommand_Shutdown *pCommand)
{
	SDL_GL_MakeCurrent(nullptr, nullptr);
}

void CCommandProcessorFragment_SDL::Cmd_Swap(const CCommandBuffer::SCommand_Swap *pCommand)
{
	SDL_GL_SwapWindow(m_pWindow);

	if(pCommand->m_Finish)
		glFinish();
}

void CCommandProcessorFragment_SDL::Cmd_VSync(const CCommandBuffer::SCommand_VSync *pCommand)
{
	*pCommand->m_pRetOk = SDL_GL_SetSwapInterval(pCommand->m_VSync) == 0;
}

void CCommandProcessorFragment_SDL::Cmd_VideoModes(const CCommandBuffer::SCommand_VideoModes *pCommand)
{
	SDL_DisplayMode mode;
	int maxModes = SDL_GetNumDisplayModes(pCommand->m_Screen),
		numModes = 0;

	for(int i = 0; i < maxModes; i++)
	{
		if(SDL_GetDisplayMode(pCommand->m_Screen, i, &mode) < 0)
		{
			debug::WarningStream("Graphics") << "unable to get display mode: " << SDL_GetError() << std::endl;
			continue;
		}

		bool alreadyFound = false;
		for(int j = 0; j < numModes; j++)
		{
			if(pCommand->m_pModes[j].m_Width == mode.w && pCommand->m_pModes[j].m_Height == mode.h)
			{
				alreadyFound = true;
				break;
			}
		}
		if(alreadyFound)
			continue;

		pCommand->m_pModes[numModes].m_Width = mode.w;
		pCommand->m_pModes[numModes].m_Height = mode.h;
		pCommand->m_pModes[numModes].m_Red = 8;
		pCommand->m_pModes[numModes].m_Green = 8;
		pCommand->m_pModes[numModes].m_Blue = 8;
		numModes++;
	}
	*pCommand->m_pNumModes = numModes;
}

CCommandProcessorFragment_SDL::CCommandProcessorFragment_SDL()
{
}

bool CCommandProcessorFragment_SDL::RunCommand(const CCommandBuffer::SCommand *pBaseCommand)
{
	switch(pBaseCommand->m_Cmd)
	{
	case CCommandBuffer::CMD_SWAP: Cmd_Swap(static_cast<const CCommandBuffer::SCommand_Swap *>(pBaseCommand)); break;
	case CCommandBuffer::CMD_VSYNC: Cmd_VSync(static_cast<const CCommandBuffer::SCommand_VSync *>(pBaseCommand)); break;
	case CCommandBuffer::CMD_VIDEOMODES: Cmd_VideoModes(static_cast<const CCommandBuffer::SCommand_VideoModes *>(pBaseCommand)); break;
	case CMD_INIT: Cmd_Init(static_cast<const SCommand_Init *>(pBaseCommand)); break;
	case CMD_SHUTDOWN: Cmd_Shutdown(static_cast<const SCommand_Shutdown *>(pBaseCommand)); break;
	default: return false;
	}

	return true;
}

// ------------ CCommandProcessor_SDL_OpenGL

void CCommandProcessor_SDL_OpenGL::RunBuffer(CCommandBuffer *pBuffer)
{
	unsigned CmdIndex = 0;
	while(1)
	{
		const CCommandBuffer::SCommand *pBaseCommand = pBuffer->GetCommand(&CmdIndex);
		if(pBaseCommand == nullptr)
			break;
		
		if(m_OpenGL.RunCommand(pBaseCommand))
			continue;
		
		if(m_SDL.RunCommand(pBaseCommand))
			continue;

		if(m_General.RunCommand(pBaseCommand))
			continue;
		
		debug::ErrorStream("Graphics") << "unknown command " << pBaseCommand->m_Cmd << std::endl;
	}
}

// ------------ CGraphicsBackend_SDL

int CGraphicsBackend_SDL::Init(const char *pName, int *pScreen, int *pWidth, int *pHeight, int FsaaSamples, int Flags, int *pDesktopWidth, int *pDesktopHeight)
{
	if(!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{
			debug::ErrorStream("Graphics") << "unable to init SDL video: " << SDL_GetError() << std::endl;
			return -1;
		}
	}

	// set screen
	SDL_Rect ScreenPos;
	m_NumScreens = SDL_GetNumVideoDisplays();
	if(m_NumScreens > 0)
	{
		*pScreen = clamp(*pScreen, 0, m_NumScreens-1);
		if(SDL_GetDisplayBounds(*pScreen, &ScreenPos) != 0)
		{
			debug::ErrorStream("Graphics") << "unable to retrieve screen information: " << SDL_GetError() << std::endl;
			return -1;
		}
	}
	else
	{
		debug::ErrorStream("Graphics") << "unable to retrieve number of screens: " << SDL_GetError() << std::endl;
		return -1;
	}

	// store desktop resolution for settings reset button
	SDL_DisplayMode DisplayMode;
	if(SDL_GetDesktopDisplayMode(*pScreen, &DisplayMode))
	{
		debug::ErrorStream("Graphics") << "unable to get desktop resolution: " << SDL_GetError() << std::endl;
		return -1;
	}
	bool IsDesktopChanged = *pDesktopWidth == 0 || *pDesktopHeight == 0 || *pDesktopWidth != DisplayMode.w || *pDesktopHeight != DisplayMode.h;

	*pDesktopWidth = DisplayMode.w;
	*pDesktopHeight = DisplayMode.h;

	// use desktop resolution as default resolution
	if (*pWidth == 0 || *pWidth == 0)
	{
		*pWidth = DisplayMode.w;
		*pHeight = DisplayMode.h;
	}

	// set flags
	int SdlFlags = SDL_WINDOW_OPENGL;
	if(Flags & INITFLAG_RESIZABLE)
		SdlFlags |= SDL_WINDOW_RESIZABLE;
	if(Flags & INITFLAG_BORDERLESS)
		SdlFlags |= SDL_WINDOW_BORDERLESS;
	if(Flags & INITFLAG_FULLSCREEN)
#if defined(CONF_PLATFORM_MACOSX)	// Todo SDL: remove this when fixed (game freezes when losing focus in fullscreen)
		SdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;	// always use "fake" fullscreen
	*pWidth = DisplayMode.w;
	*pHeight = DisplayMode.h;
#else
		SdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
	
	if(IsDesktopChanged)
	{
		SdlFlags |= SDL_WINDOW_MAXIMIZED;

		SdlFlags &= ~SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	// set gl attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if(FsaaSamples)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, FsaaSamples);
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	}

	// create window
	m_pWindow = SDL_CreateWindow(
		pName,
		SDL_WINDOWPOS_CENTERED_DISPLAY(*pScreen),
		SDL_WINDOWPOS_CENTERED_DISPLAY(*pScreen),
		*pWidth,
		*pHeight,
		SdlFlags);
	
	if(m_pWindow == nullptr)
	{
		debug::ErrorStream("Graphics") << "unable to create window: " << SDL_GetError() << std::endl;
		return -1;
	}

	// create gl context
	m_GLContext = SDL_GL_CreateContext(m_pWindow);
	if(m_GLContext == nullptr)
	{
		debug::ErrorStream("Graphics") << "unable to create OpenGL context: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	glTexImage3D_Dyn = (PFNGLTEXIMAGE3DPROC) SDL_GL_GetProcAddress("glTexImage3D");
	if(!glTexImage3D_Dyn)
	{
		debug::ErrorStream("Graphics") << "glTexImage3D not supported" << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GetWindowSize(m_pWindow, pWidth, pHeight);

	SDL_GL_SetSwapInterval(Flags & INITFLAG_VSYNC ? 1 : 0);
	SDL_GL_MakeCurrent(nullptr, nullptr);

	// start the command processor
	m_pProcessor = new CCommandProcessor_SDL_OpenGL;
	StartProcessor(m_pProcessor);

	// issue init commands for OpenGL and SDL
	CCommandBuffer CmdBuffer(1024, 512);
	CCommandProcessorFragment_OpenGL::SCommand_Init CmdOpenGL;
	CmdOpenGL.m_pTextureMemoryUsage = &m_TextureMemoryUsage;
	CmdBuffer.AddCommand(CmdOpenGL);
	CCommandProcessorFragment_SDL::SCommand_Init CmdSDL;
	CmdSDL.m_pWindow = m_pWindow;
	CmdSDL.m_GLContext = m_GLContext;
	CmdBuffer.AddCommand(CmdSDL);
	RunBuffer(&CmdBuffer);
	WaitForIdle();

	// return
	return 0;
}

int CGraphicsBackend_SDL::Shutdown()
{
	// issue a shutdown command
	CCommandBuffer CmdBuffer(1024, 512);
	CCommandProcessorFragment_SDL::SCommand_Shutdown Cmd;
	CmdBuffer.AddCommand(Cmd);
	RunBuffer(&CmdBuffer);
	WaitForIdle();
			
	// stop and delete the processor
	StopProcessor();
	delete m_pProcessor;
	m_pProcessor = nullptr;

	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_pWindow);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return 0;
}

int CGraphicsBackend_SDL::MemoryUsage() const
{
	return m_TextureMemoryUsage;
}

void CGraphicsBackend_SDL::Minimize()
{
	SDL_MinimizeWindow(m_pWindow);
}

void CGraphicsBackend_SDL::Maximize()
{
	SDL_MaximizeWindow(m_pWindow);
}

bool CGraphicsBackend_SDL::Fullscreen(bool State)
{
#if defined(CONF_PLATFORM_MACOSX)	// Todo SDL: remove this when fixed (game freezes when losing focus in fullscreen)
	return SDL_SetWindowFullscreen(m_pWindow, State ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) == 0;
#else
	return SDL_SetWindowFullscreen(m_pWindow, State ? SDL_WINDOW_FULLSCREEN : 0) == 0;
#endif
}

void CGraphicsBackend_SDL::SetWindowBordered(bool State)
{
	SDL_SetWindowBordered(m_pWindow, SDL_bool(State));
}

bool CGraphicsBackend_SDL::SetWindowScreen(int Index)
{
	if(Index >= 0 && Index < m_NumScreens)
	{
		SDL_Rect ScreenPos;
		if(SDL_GetDisplayBounds(Index, &ScreenPos) == 0)
		{
			SDL_SetWindowPosition(m_pWindow, ScreenPos.x, ScreenPos.y);
			return true;
		}
	}

	return false;
}

int CGraphicsBackend_SDL::GetWindowScreen()
{
	return SDL_GetWindowDisplayIndex(m_pWindow);
}

int CGraphicsBackend_SDL::WindowActive()
{
	return SDL_GetWindowFlags(m_pWindow)&SDL_WINDOW_INPUT_FOCUS;
}

int CGraphicsBackend_SDL::WindowOpen()
{
	return SDL_GetWindowFlags(m_pWindow)&SDL_WINDOW_SHOWN;

}

/* FOREIGN CODE END: TeeWorlds ****************************************/
