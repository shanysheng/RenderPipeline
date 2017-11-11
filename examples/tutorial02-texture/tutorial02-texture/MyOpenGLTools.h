//
//  MyOpenGLTools.h
//  OpenGL-Texture
//
//  Created by Mr_zhang on 17/4/18.
//  Copyright © 2017年 Mr_zhang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

@interface MyOpenGLTools : NSObject

+ (GLuint)loadProgram:(NSString *)vertexShaderFilepath withFragmentShaderFilepath:(NSString *)fragmentShaderFilepath;

@end
