/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR4_H_GUARD
#define PIPELINE_VECTOR4_H_GUARD

namespace pipeline{
    
  // Summary:
    //     Representation of four-dimensional vectors.
    public struct Vector4
    {
        public const float kEpsilon = 1e-005f;

        // Summary:
        //     W component of the vector.
        public float w;
        //
        // Summary:
        //     X component of the vector.
        public float x;
        //
        // Summary:
        //     Y component of the vector.
        public float y;
        //
        // Summary:
        //     Z component of the vector.
        public float z;

        //
        // Summary:
        //     Creates a new vector with given x, y components and sets z and w to zero.
        //
        // Parameters:
        //   x:
        //
        //   y:
        public Vector4(float x, float y);
        //
        // Summary:
        //     Creates a new vector with given x, y, z components and sets w to zero.
        //
        // Parameters:
        //   x:
        //
        //   y:
        //
        //   z:
        public Vector4(float x, float y, float z);
        //
        // Summary:
        //     Creates a new vector with given x, y, z, w components.
        //
        // Parameters:
        //   x:
        //
        //   y:
        //
        //   z:
        //
        //   w:
        public Vector4(float x, float y, float z, float w);

        public static Vector4 operator -(Vector4 a);
        public static Vector4 operator -(Vector4 a, Vector4 b);
        public static bool operator !=(Vector4 lhs, Vector4 rhs);
        public static Vector4 operator *(float d, Vector4 a);
        public static Vector4 operator *(Vector4 a, float d);
        public static Vector4 operator /(Vector4 a, float d);
        public static Vector4 operator +(Vector4 a, Vector4 b);
        public static bool operator ==(Vector4 lhs, Vector4 rhs);
        public static implicit operator Vector4(Vector2 v);
        public static implicit operator Vector4(Vector3 v);
        public static implicit operator Vector3(Vector4 v);
        public static implicit operator Vector2(Vector4 v);

        // Summary:
        //     Returns the length of this vector (Read Only).
        public float magnitude { get; }
        //
        // Summary:
        //     Returns this vector with a magnitude of 1 (Read Only).
        public Vector4 normalized { get; }
        //
        // Summary:
        //     Shorthand for writing Vector4(1,1,1,1).
        public static Vector4 one { get; }
        //
        // Summary:
        //     Returns the squared length of this vector (Read Only).
        public float sqrMagnitude { get; }
        //
        // Summary:
        //     Shorthand for writing Vector4(0,0,0,0).
        public static Vector4 zero { get; }

        public float this[int index] { get; set; }

        // Summary:
        //     Returns the distance between a and b.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Distance(Vector4 a, Vector4 b);
        //
        // Summary:
        //     Dot Product of two vectors.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Dot(Vector4 a, Vector4 b);
        public override bool Equals(object other);
        public override int GetHashCode();
        //
        // Summary:
        //     Linearly interpolates between two vectors.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector4 Lerp(Vector4 a, Vector4 b, float t);
        //
        // Summary:
        //     Linearly interpolates between two vectors.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
        public static float Magnitude(Vector4 a);
        //
        // Summary:
        //     Returns a vector that is made from the largest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector4 Max(Vector4 lhs, Vector4 rhs);
        //
        // Summary:
        //     Returns a vector that is made from the smallest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector4 Min(Vector4 lhs, Vector4 rhs);
        //
        // Summary:
        //     Moves a point current towards target.
        //
        // Parameters:
        //   current:
        //
        //   target:
        //
        //   maxDistanceDelta:
        public static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);
        //
        // Summary:
        //     Makes this vector have a magnitude of 1.
        public void Normalize();
        //
        //
        // Parameters:
        //   a:
        public static Vector4 Normalize(Vector4 a);
        //
        // Summary:
        //     Projects a vector onto another vector.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static Vector4 Project(Vector4 a, Vector4 b);
        //
        // Summary:
        //     Multiplies every component of this vector by the same component of scale.
        //
        // Parameters:
        //   scale:
        public void Scale(Vector4 scale);
        //
        // Summary:
        //     Multiplies two vectors component-wise.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static Vector4 Scale(Vector4 a, Vector4 b);
        //
        // Summary:
        //     Set x, y, z and w components of an existing Vector4.
        //
        // Parameters:
        //   new_x:
        //
        //   new_y:
        //
        //   new_z:
        //
        //   new_w:
        public void Set(float new_x, float new_y, float new_z, float new_w);
        public float SqrMagnitude();
        public static float SqrMagnitude(Vector4 a);
        //
        // Summary:
        //     Returns a nicely formatted string for this vector.
        //
        // Parameters:
        //   format:
        public override string ToString();
        //
        // Summary:
        //     Returns a nicely formatted string for this vector.
        //
        // Parameters:
        //   format:
        public string ToString(string format);
}

#endif
