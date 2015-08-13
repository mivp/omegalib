/**************************************************************************************************
 * THE OMEGA LIB PROJECT
 *-------------------------------------------------------------------------------------------------
 * Copyright 2010-2015		Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Alessandro Febretti		febret@gmail.com
 *-------------------------------------------------------------------------------------------------
 * Copyright (c) 2010-2015, Electronic Visualization Laboratory, University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of conditions 
 * and the following disclaimer. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the documentation and/or other 
 * materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF 
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************************************/
/******************************************************************************
* THE OMEGA LIB PROJECT
*-----------------------------------------------------------------------------
* Copyright 2010-2015		Electronic Visualization Laboratory,
*							University of Illinois at Chicago
* Authors:
*  Alessandro Febretti		febret@gmail.com
*-----------------------------------------------------------------------------
* Copyright (c) 2010-2015, Electronic Visualization Laboratory,
* University of Illinois at Chicago
* All rights reserved.
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer. Redistributions in binary
* form must reproduce the above copyright notice, this list of conditions and
* the following disclaimer in the documentation and/or other materials provided
* with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*-----------------------------------------------------------------------------
* What's in this file
*	The omegalib renderer is the entry point for all of omegalib rendering code.
*	The renderer does not draw anything: it just manages rendering resources,
*	cameras and render passes.
******************************************************************************/
#ifndef __GPU_RESOURCE__
#define __GPU_RESOURCE__

#include "osystem.h"

// HACK: To be removed (see GpuManager::TextureUnit)
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8

// Forward decl
struct GLEWContextStruct;
typedef struct GLEWContextStruct GLEWContext;

namespace omega
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class OMEGA_API GpuContext: public ReferenceType
	{
	public:
		static const unsigned int MaxContexts = 64;
		enum TextureUnit {
			TextureUnitInvalid = 0,
			TextureUnit0 = GL_TEXTURE0, 
			TextureUnit1 = GL_TEXTURE1,
			TextureUnit2 = GL_TEXTURE2,
			TextureUnit3 = GL_TEXTURE3 };

		GpuContext(bool initializeGlew = true);
		~GpuContext();

		uint getId() { return myId; }
		GLEWContext* getGlewContext() { return myGlewContext; }
        void makeCurrent();
        //void setGlewContext(GLEWContext* ctx) { myGlewContext = ctx; }

	private:
		static uint mysNumContexts;
		static Lock mysContextLock;

		uint myId;
		GLEWContext* myGlewContext;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	class OMEGA_API GpuResource: public ReferenceType
	{
	public:
		GpuResource(GpuContext* ctx): myContext(ctx) { }
		GpuContext* getContext() { return myContext; }
		virtual void dispose() = 0;
	private:
		GpuContext* myContext;
	};
}; // namespace omega

#endif
