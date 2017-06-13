/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_COLOR_H_GUARD
#define PIPELINE_COLOR_H_GUARD

namespace pipeline{
    
   // Summary:
    //     Representation of RGBA colors.
    public struct Color
    {
        // Summary:
        //     Alpha component of the color.
        public float a;
        //
        // Summary:
        //     Blue component of the color.
        public float b;
        //
        // Summary:
        //     Green component of the color.
        public float g;
        //
        // Summary:
        //     Red component of the color.
        public float r;

        //
        // Summary:
        //     Constructs a new Color with given r,g,b components and sets a to 1.
        //
        // Parameters:
        //   r:
        //     Red component.
        //
        //   g:
        //     Green component.
        //
        //   b:
        //     Blue component.
        public Color(float r, float g, float b);
        //
        // Summary:
        //     Constructs a new Color with given r,g,b,a components.
        //
        // Parameters:
        //   r:
        //     Red component.
        //
        //   g:
        //     Green component.
        //
        //   b:
        //     Blue component.
        //
        //   a:
        //     Alpha component.
        public Color(float r, float g, float b, float a);

        public static Color operator -(Color a, Color b);
        public static bool operator !=(Color lhs, Color rhs);
        public static Color operator *(Color a, Color b);
        public static Color operator *(Color a, float b);
        public static Color operator *(float b, Color a);
        public static Color operator /(Color a, float b);
        public static Color operator +(Color a, Color b);
        public static bool operator ==(Color lhs, Color rhs);
        public static implicit operator Vector4(Color c);
        public static implicit operator Color(Vector4 v);

        // Summary:
        //     Solid black. RGBA is (0, 0, 0, 1).
        public static Color black { get; }
        //
        // Summary:
        //     Solid blue. RGBA is (0, 0, 1, 1).
        public static Color blue { get; }
        //
        // Summary:
        //     Completely transparent. RGBA is (0, 0, 0, 0).
        public static Color clear { get; }
        //
        // Summary:
        //     Cyan. RGBA is (0, 1, 1, 1).
        public static Color cyan { get; }
        //
        // Summary:
        //     A version of the color that has had the gamma curve applied.
        public Color gamma { get; }
        //
        // Summary:
        //     Gray. RGBA is (0.5, 0.5, 0.5, 1).
        public static Color gray { get; }
        //
        // Summary:
        //     The grayscale value of the color. (Read Only)
        public float grayscale { get; }
        //
        // Summary:
        //     Solid green. RGBA is (0, 1, 0, 1).
        public static Color green { get; }
        //
        // Summary:
        //     English spelling for gray. RGBA is the same (0.5, 0.5, 0.5, 1).
        public static Color grey { get; }
        //
        // Summary:
        //     A linear value of an sRGB color.
        public Color linear { get; }
        //
        // Summary:
        //     Magenta. RGBA is (1, 0, 1, 1).
        public static Color magenta { get; }
        //
        // Summary:
        //     Returns the maximum color component value: Max(r,g,b).
        public float maxColorComponent { get; }
        //
        // Summary:
        //     Solid red. RGBA is (1, 0, 0, 1).
        public static Color red { get; }
        //
        // Summary:
        //     Solid white. RGBA is (1, 1, 1, 1).
        public static Color white { get; }
        //
        // Summary:
        //     Yellow. RGBA is (1, 0.92, 0.016, 1), but the color is nice to look at!
        public static Color yellow { get; }

        public float this[int index] { get; set; }

        public override bool Equals(object other);
        public override int GetHashCode();
        //
        // Summary:
        //     Creates an RGB colour from HSV input.
        //
        // Parameters:
        //   H:
        //     Hue [0..1].
        //
        //   S:
        //     Saturation [0..1].
        //
        //   V:
        //     Value [0..1].
        //
        //   hdr:
        //     Output HDR colours. If true, the returned colour will not be clamped to [0..1].
        //
        // Returns:
        //     An opaque colour with HSV matching the input.
        public static Color HSVToRGB(float H, float S, float V);
        //
        // Summary:
        //     Creates an RGB colour from HSV input.
        //
        // Parameters:
        //   H:
        //     Hue [0..1].
        //
        //   S:
        //     Saturation [0..1].
        //
        //   V:
        //     Value [0..1].
        //
        //   hdr:
        //     Output HDR colours. If true, the returned colour will not be clamped to [0..1].
        //
        // Returns:
        //     An opaque colour with HSV matching the input.
        public static Color HSVToRGB(float H, float S, float V, bool hdr);
        //
        // Summary:
        //     Linearly interpolates between colors a and b by t.
        //
        // Parameters:
        //   a:
        //     Color a
        //
        //   b:
        //     Color b
        //
        //   t:
        //     Float for combining a and b
        public static Color Lerp(Color a, Color b, float t);
        //
        // Summary:
        //     Linearly interpolates between colors a and b by t.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Color LerpUnclamped(Color a, Color b, float t);
        public static void RGBToHSV(Color rgbColor, out float H, out float S, out float V);
        //
        // Summary:
        //     Returns a nicely formatted string of this color.
        //
        // Parameters:
        //   format:
        public override string ToString();
        //
        // Summary:
        //     Returns a nicely formatted string of this color.
        //
        // Parameters:
        //   format:
        public string ToString(string format);
}

#endif
