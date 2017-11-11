//
//  MyOpenGLTools.m
//  OpenGL-Texture
//
//  Created by Mr_zhang on 17/4/18.
//  Copyright © 2017年 Mr_zhang. All rights reserved.
//

#import "MyOpenGLTools.h"

@implementation MyOpenGLTools

+ (GLuint)loadShaderProgram:(GLenum)type withFilepath:(NSString *)shaderFilepath
{
    NSError *error;
    NSString *shaderString = [NSString stringWithContentsOfFile:shaderFilepath encoding:NSUTF8StringEncoding error:&error];
    if (!shaderString)
    {
        NSLog(@"Error: loading shader file:%@  %@",shaderFilepath,error.localizedDescription);
        return 0;
    }
    return [self loadShader:type withString:shaderString];
}

+ (GLuint)loadShader:(GLenum)type withString:(NSString *)shaderString
{
    GLuint shader = glCreateShader(type);
    if (shader == 0)
    {
        NSLog(@"Error: failed to create shader.");
        return 0;
    }
    // Load the shader soure (加载着色器源码)
    const char *shaderStringUTF8 = [shaderString UTF8String];
    // 要编译的着色器对象作为第一个参数，第二个参数指定了传递的源码字符串数量，第三个着色器是顶点的真正的源码，第四个设置为NULL；
    glShaderSource(shader, 1, &shaderStringUTF8, NULL);
    // 编译着色器
    glCompileShader(shader);
    
    // 检查编译是否成功
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint infolen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolen);
        
        if (infolen > 1)
        {
            char *infolog = malloc(sizeof(char) * infolen);
            glGetShaderInfoLog(shader, infolen, NULL, infoLog);
            NSLog(@"compile faile,error:%s",infoLog);
            free(infolog);
        }
        
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


/**
 创建顶点着色器和片段着色器
 
 @param vertexShaderFilepath 顶点着色器路径
 @param fragmentShaderFilepath 片段着色器路径
 @return 链接成功后的着色器程序
 */
+ (GLuint)loadProgram:(NSString *)vertexShaderFilepath withFragmentShaderFilepath:(NSString *)fragmentShaderFilepath
{
    // Create vertexShader (创建顶点着色器)
    GLuint vertexShader = [self loadShaderProgram:GL_VERTEX_SHADER withFilepath:vertexShaderFilepath];
    if (vertexShader == 0)
        return 0;
    
    // Create fragmentShader (创建片段着色器)
    GLuint fragmentShader = [self loadShaderProgram:GL_FRAGMENT_SHADER withFilepath:fragmentShaderFilepath];
    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        return 0;
    }
    
    // Create the program object (创建着色器程序)
    GLuint shaderProgram = glCreateProgram();
    if (shaderProgram == 0)
        return 0;
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link the program (链接着色器程序)
    glLinkProgram(shaderProgram);
    
    // Check the link status (检查是否链接成功)
    GLint linked;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        glDeleteProgram(shaderProgram);
        NSLog(@"Link shaderProgram failed");
        return 0;
    }
    
    // Free up no longer needed shader resources (释放不再需要的着色器资源)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

@end
