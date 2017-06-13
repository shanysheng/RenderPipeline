/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR2_H_GUARD
#define PIPELINE_VECTOR2_H_GUARD

namespace pipeline{
    
   // Summary:
    //     Representation of 2D vectors and points.
    public struct Vector2
    {
        public const float kEpsilon = 1e-005f;

        // Summary:
        //     X component of the vector.
        public float x;
        //
        // Summary:
        //     Y component of the vector.
        public float y;

        //
        // Summary:
        //     Constructs a new vector with given x, y components.
        //
        // Parameters:
        //   x:
        //
        //   y:
        public Vector2(float x, float y);

        public static Vector2 operator -(Vector2 a);
        public static Vector2 operator -(Vector2 a, Vector2 b);
        public static bool operator !=(Vector2 lhs, Vector2 rhs);
        public static Vector2 operator *(float d, Vector2 a);
        public static Vector2 operator *(Vector2 a, float d);
        public static Vector2 operator /(Vector2 a, float d);
        public static Vector2 operator +(Vector2 a, Vector2 b);
        public static bool operator ==(Vector2 lhs, Vector2 rhs);
        public static implicit operator Vector3(Vector2 v);
        public static implicit operator Vector2(Vector3 v);

        // Summary:
        //     Shorthand for writing Vector2(0, -1).
        public static Vector2 down { get; }
        //
        // Summary:
        //     Shorthand for writing Vector2(-1, 0).
        public static Vector2 left { get; }
        //
        // Summary:
        //     Returns the length of this vector (Read Only).
        public float magnitude { get; }
        //
        // Summary:
        //     Returns this vector with a magnitude of 1 (Read Only).
        public Vector2 normalized { get; }
        //
        // Summary:
        //     Shorthand for writing Vector2(1, 1).
        public static Vector2 one { get; }
        //
        // Summary:
        //     Shorthand for writing Vector2(1, 0).
        public static Vector2 right { get; }
        //
        // Summary:
        //     Returns the squared length of this vector (Read Only).
        public float sqrMagnitude { get; }
        //
        // Summary:
        //     Shorthand for writing Vector2(0, 1).
        public static Vector2 up { get; }
        //
        // Summary:
        //     Shorthand for writing Vector2(0, 0).
        public static Vector2 zero { get; }

        public float this[int index] { get; set; }

        // Summary:
        //     Returns the angle in degrees between from and to.
        //
        // Parameters:
        //   from:
        //
        //   to:
        public static float Angle(Vector2 from, Vector2 to);
        //
        // Summary:
        //     Returns a copy of vector with its magnitude clamped to maxLength.
        //
        // Parameters:
        //   vector:
        //
        //   maxLength:
        public static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
        //
        // Summary:
        //     Returns the distance between a and b.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Distance(Vector2 a, Vector2 b);
        //
        // Summary:
        //     Dot Product of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static float Dot(Vector2 lhs, Vector2 rhs);
        public override bool Equals(object other);
        public override int GetHashCode();
        //
        // Summary:
        //     Linearly interpolates between vectors a and b by t.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector2 Lerp(Vector2 a, Vector2 b, float t);
        //
        // Summary:
        //     Linearly interpolates between vectors a and b by t.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
        //
        // Summary:
        //     Returns a vector that is made from the largest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector2 Max(Vector2 lhs, Vector2 rhs);
        //
        // Summary:
        //     Returns a vector that is made from the smallest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector2 Min(Vector2 lhs, Vector2 rhs);
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
        public static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);
        //
        // Summary:
        //     Makes this vector have a magnitude of 1.
        public void Normalize();
        //
        // Summary:
        //     Reflects a vector off the vector defined by a normal.
        //
        // Parameters:
        //   inDirection:
        //
        //   inNormal:
        public static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);
        //
        // Summary:
        //     Multiplies every component of this vector by the same component of scale.
        //
        // Parameters:
        //   scale:
        public void Scale(Vector2 scale);
        //
        // Summary:
        //     Multiplies two vectors component-wise.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static Vector2 Scale(Vector2 a, Vector2 b);
        //
        // Summary:
        //     Set x and y components of an existing Vector2.
        //
        // Parameters:
        //   new_x:
        //
        //   new_y:
        public void Set(float new_x, float new_y);
        [ExcludeFromDocs]
        public static Vector2 SmoothDamp(Vector2 current, Vector2 target, ref Vector2 currentVelocity, float smoothTime);
        [ExcludeFromDocs]
        public static Vector2 SmoothDamp(Vector2 current, Vector2 target, ref Vector2 currentVelocity, float smoothTime, float maxSpeed);
        public static Vector2 SmoothDamp(Vector2 current, Vector2 target, ref Vector2 currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
        public float SqrMagnitude();
        public static float SqrMagnitude(Vector2 a);
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
