//in vec4 vertexColor; // 从顶点着色器传来的输入变量 （名称相同，类型相同）

//out vec4 color; // 片段着色器输出的变量名(可以任意命名)，类型必须是vec4

//void main()
//{
//    color = vertexColor;
//}

//varying lowp vec4 DestinationColor;
//
//void main()
//{
//    gl_FragColor = DestinationColor;
//}

//varying highp vec3 ourColor;
//varying highp vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    gl_FragColor = texture2D(ourTexture,TexCoord);
//}

precision mediump float;

uniform sampler2D Texture;
varying vec2 TextureCoordsOut;

void main(void)
{
    vec4 mask = texture2D(Texture, TextureCoordsOut);
    gl_FragColor = vec4(mask.rgb, 1.0);
}
