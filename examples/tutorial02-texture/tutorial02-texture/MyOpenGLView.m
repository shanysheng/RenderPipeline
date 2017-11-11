//
//  MyOpenGLView.m
//  OpenGL-Texture
//
//  Created by Mr_zhang on 17/4/18.
//  Copyright © 2017年 Mr_zhang. All rights reserved.
//

#import "MyOpenGLView.h"
#import "MyOpenGLTools.h"

@interface MyOpenGLView()
{
    EAGLContext *eaglContext;
    CAEAGLLayer *eaglLayer;
    
    GLuint renderBuffer;
    GLuint frameBuffer;
    
    GLuint positionSlot;
    GLuint colorSlot;
    GLuint texCoordSlor;
    GLuint ourTexture;
    
    GLuint texture;
}
@end

@implementation MyOpenGLView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if (self == [super initWithFrame:frame])
    {
        [self setUpLayer];
        
        [self setUpContext];
        
        [self setUpBuffer];
        
        [self linkShaderProgram];
        
        [self didDrawImageViaOpenGLES:[UIImage imageNamed:@"container.jpg"]];
        
        //[self render];
    }
    return self;
}

- (void)setUpLayer
{
    eaglLayer = [CAEAGLLayer layer];
    eaglLayer.frame = self.frame;
    eaglLayer.opaque = NO;
    [self.layer addSublayer:eaglLayer];
}

- (void)setUpContext
{
    eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!eaglContext)
        eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (![EAGLContext setCurrentContext:eaglContext])
        NSLog(@"set currentContext faile");
}

- (void)setUpBuffer
{
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    [eaglContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
    
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, frameBuffer);
}

- (void)linkShaderProgram
{
    NSString *vertexShaderPath = [[NSBundle mainBundle] pathForResource:@"vertextShader" ofType:@"vsh"];
    NSString *fragmentShaderPath = [[NSBundle mainBundle] pathForResource:@"fragmentShader" ofType:@"fsh"];
    
    GLuint shaderProgram = [MyOpenGLTools loadProgram:vertexShaderPath withFragmentShaderFilepath:fragmentShaderPath];
    glUseProgram(shaderProgram);
    
    positionSlot = glGetAttribLocation(shaderProgram, "Position");
    //colorSlot = glGetAttribLocation(shaderProgram, "color");
    texCoordSlor = glGetAttribLocation(shaderProgram, "TextureCoords");
    ourTexture = glGetUniformLocation(shaderProgram, "Texture");

    
}

- (void)render
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);

    GLfloat vertices[] = {
        //     ---- 位置 ----   ---- 纹理坐标 -----
        0.8f,  0.3f, 0.0f,     1.0f, 1.0f,   // 右上
        0.8f, -0.3f, 0.0f,     1.0f, 0.0f,   // 右下
        -0.8f, -0.3f, 0.0f,    0.0f, 0.0f,   // 左下
        -0.8f,  0.3f, 0.0f,    0.0f, 1.0f    // 左上
    };
    
    // 创建顶点缓冲对象VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionSlot);
    glVertexAttribPointer(texCoordSlor, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(texCoordSlor);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    [eaglContext presentRenderbuffer:GL_RENDERBUFFER];
    
}

- (void)didDrawImageViaOpenGLES:(UIImage *)image {
    // 将image绑定到GL_TEXTURE_2D上，即传递到GPU中
    texture = [self setupTexture:image];
    // 此时，纹理数据就可看做已经在纹理对象_textureID中了，使用时从中取出即可
    
    // 第一行和第三行不是严格必须的，默认使用GL_TEXTURE0作为当前激活的纹理单元
    glActiveTexture(GL_TEXTURE5); // 指定纹理单元GL_TEXTURE5
    glBindTexture(GL_TEXTURE_2D, texture); // 绑定，即可从_textureID中取出图像数据。
    glUniform1i(ourTexture, 5); // 与纹理单元的序号对应
    
    // 渲染需要的数据要从GL_TEXTURE_2D中得到。
    // GL_TEXTURE_2D与_textureID已经绑定
    [self render];
}

#pragma mark - setupTexture

/**
 *  加载image, 使用CoreGraphics将位图以RGBA格式存放. 将UIImage图像数据转化成OpenGL ES接受的数据.
 *  然后在GPU中将图像纹理传递给GL_TEXTURE_2D。
 *  @return 返回的是纹理对象，该纹理对象暂时未跟GL_TEXTURE_2D绑定（要调用bind）。
 *  即GL_TEXTURE_2D中的图像数据都可从纹理对象中取出。
 */
- (GLuint)setupTexture:(UIImage *)image {
    CGImageRef cgImageRef = [image CGImage];
    GLuint width = (GLuint)CGImageGetWidth(cgImageRef);
    GLuint height = (GLuint)CGImageGetHeight(cgImageRef);
    CGRect rect = CGRectMake(0, 0, width, height);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc(width * height * 4);
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGContextTranslateCTM(context, 0, height);
    CGContextScaleCTM(context, 1.0f, -1.0f);
    CGColorSpaceRelease(colorSpace);
    CGContextClearRect(context, rect);
    CGContextDrawImage(context, rect, cgImageRef);
    
    glEnable(GL_TEXTURE_2D);
    
    /**
     *  GL_TEXTURE_2D表示操作2D纹理
     *  创建纹理对象，
     *  绑定纹理对象，
     */
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    /**
     *  纹理过滤函数
     *  图象从纹理图象空间映射到帧缓冲图象空间(映射需要重新构造纹理图像,这样就会造成应用到多边形上的图像失真),
     *  这时就可用glTexParmeteri()函数来确定如何把纹理象素映射成像素.
     *  如何把图像从纹理图像空间映射到帧缓冲图像空间（即如何把纹理像素映射成像素）
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // S方向上的贴图模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // T方向上的贴图模式
    // 线性过滤：使用距离当前渲染像素中心最近的4个纹理像素加权平均值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    /**
     *  将图像数据传递给到GL_TEXTURE_2D中, 因其于textureID纹理对象已经绑定，所以即传递给了textureID纹理对象中。
     *  glTexImage2d会将图像数据从CPU内存通过PCIE上传到GPU内存。
     *  不使用PBO时它是一个阻塞CPU的函数，数据量大会卡。
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    // 结束后要做清理
    glBindTexture(GL_TEXTURE_2D, 0); //解绑
    CGContextRelease(context);
    free(imageData);
    
    return textureID;
}

- (void)renderUsingIndexVBO {
    GLfloat vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f    // 左上
    };
    
    
    
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionSlot);
    glVertexAttribPointer(texCoordSlor, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(3*sizeof(float)));
    glEnableVertexAttribArray(texCoordSlor);
    
    const GLubyte indices[] = {
        0,1,2,
        1,2,3
    };
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_BYTE, 0);
}






@end
