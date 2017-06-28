#pragma once

#include "R3DRenderingSystem/Camera.h"
#include <map>

namespace Ranovae{
	namespace Rendering{

		class CCamera;

		//------------------------------------------------------------------------------
		//	Desc:		CCameraManager instance is a container for cameras, namely 
		//				CCamera instances. There is a map inside, the key of which 
		//				is the camera's name and is unique in whole map.
		//
		//------------------------------------------------------------------------------
		class CCameraManager
		{
		public:
			CCameraManager();
			virtual ~CCameraManager();

			CCamera * Give( const SFString& CameraName );

			//------------------------------------------------------------------------------
			//	Desc:	The overridden operator [](const SFString& CameraName ) can be 
			//			used to find the render queue by a specified name. The function 
			//			Give(const SFString& CameraName ) can be used to yield a named 
			//			camera, which is either newly created instance, or an existing 
			//			instance with the same name in the map.
			//
			//------------------------------------------------------------------------------
			CCamera * operator [](const SFString& CameraName );

			//------------------------------------------------------------------------------
			//	Desc:
			//
			//
			//  [6/14/2011 Ranovae/shamy]
			//------------------------------------------------------------------------------
			void	ClearResources();

		protected:
			std::map<SFString, CCamera*> m_Cameras;
		};
	}
}