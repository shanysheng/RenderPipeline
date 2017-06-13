/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR3_H_GUARD
#define PIPELINE_VECTOR3_H_GUARD

namespace pipeline{
    
    // Summary:
    //     Representation of 3D vectors and points.
    public struct Vector3
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
        //     Z component of the vector.
        public float z;

        //
        // Summary:
        //     Creates a new vector with given x, y components and sets z to zero.
        //
        // Parameters:
        //   x:
        //
        //   y:
        public Vector3(float x, float y);
        //
        // Summary:
        //     Creates a new vector with given x, y, z components.
        //
        // Parameters:
        //   x:
        //
        //   y:
        //
        //   z:
        public Vector3(float x, float y, float z);

        public static Vector3 operator -(Vector3 a);
        public static Vector3 operator -(Vector3 a, Vector3 b);
        public static bool operator !=(Vector3 lhs, Vector3 rhs);
        public static Vector3 operator *(float d, Vector3 a);
        public static Vector3 operator *(Vector3 a, float d);
        public static Vector3 operator /(Vector3 a, float d);
        public static Vector3 operator +(Vector3 a, Vector3 b);
        public static bool operator ==(Vector3 lhs, Vector3 rhs);

        // Summary:
        //     Shorthand for writing Vector3(0, 0, -1).
        public static Vector3 back { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(0, -1, 0).
        public static Vector3 down { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(0, 0, 1).
        public static Vector3 forward { get; }
        [Obsolete("Use Vector3.forward instead.")]
        public static Vector3 fwd { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(-1, 0, 0).
        public static Vector3 left { get; }
        //
        // Summary:
        //     Returns the length of this vector (Read Only).
        public float magnitude { get; }
        //
        // Summary:
        //     Returns this vector with a magnitude of 1 (Read Only).
        public Vector3 normalized { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(1, 1, 1).
        public static Vector3 one { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(1, 0, 0).
        public static Vector3 right { get; }
        //
        // Summary:
        //     Returns the squared length of this vector (Read Only).
        public float sqrMagnitude { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(0, 1, 0).
        public static Vector3 up { get; }
        //
        // Summary:
        //     Shorthand for writing Vector3(0, 0, 0).
        public static Vector3 zero { get; }

        public float this[int index] { get; set; }

        // Summary:
        //     Returns the angle in degrees between from and to.
        //
        // Parameters:
        //   from:
        //     The angle extends round from this vector.
        //
        //   to:
        //     The angle extends round to this vector.
        public static float Angle(Vector3 from, Vector3 to);
        [Obsolete("Use Vector3.Angle instead. AngleBetween uses radians instead of degrees and was deprecated for this reason")]
        public static float AngleBetween(Vector3 from, Vector3 to);
        //
        // Summary:
        //     Returns a copy of vector with its magnitude clamped to maxLength.
        //
        // Parameters:
        //   vector:
        //
        //   maxLength:
        public static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
        //
        // Summary:
        //     Cross Product of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector3 Cross(Vector3 lhs, Vector3 rhs);
        //
        // Summary:
        //     Returns the distance between a and b.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Distance(Vector3 a, Vector3 b);
        //
        // Summary:
        //     Dot Product of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static float Dot(Vector3 lhs, Vector3 rhs);
        public override bool Equals(object other);
        [Obsolete("Use Vector3.ProjectOnPlane instead.")]
        public static Vector3 Exclude(Vector3 excludeThis, Vector3 fromThat);
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
        public static Vector3 Lerp(Vector3 a, Vector3 b, float t);
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
        public static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
        public static float Magnitude(Vector3 a);
        //
        // Summary:
        //     Returns a vector that is made from the largest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector3 Max(Vector3 lhs, Vector3 rhs);
        //
        // Summary:
        //     Returns a vector that is made from the smallest components of two vectors.
        //
        // Parameters:
        //   lhs:
        //
        //   rhs:
        public static Vector3 Min(Vector3 lhs, Vector3 rhs);
        //
        // Summary:
        //     Moves a point current in a straight line towards a target point.
        //
        // Parameters:
        //   current:
        //
        //   target:
        //
        //   maxDistanceDelta:
        public static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
        //
        // Summary:
        //     Makes this vector have a magnitude of 1.
        public void Normalize();
        //
        //
        // Parameters:
        //   value:
        public static Vector3 Normalize(Vector3 value);
        public static void OrthoNormalize(ref Vector3 normal, ref Vector3 tangent);
        public static void OrthoNormalize(ref Vector3 normal, ref Vector3 tangent, ref Vector3 binormal);
        //
        // Summary:
        //     Projects a vector onto another vector.
        //
        // Parameters:
        //   vector:
        //
        //   onNormal:
        public static Vector3 Project(Vector3 vector, Vector3 onNormal);
        //
        // Summary:
        //     Projects a vector onto a plane defined by a normal orthogonal to the plane.
        //
        // Parameters:
        //   vector:
        //
        //   planeNormal:
        public static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);
        //
        // Summary:
        //     Reflects a vector off the plane defined by a normal.
        //
        // Parameters:
        //   inDirection:
        //
        //   inNormal:
        public static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
        //
        // Summary:
        //     Rotates a vector current towards target.
        //
        // Parameters:
        //   current:
        //
        //   target:
        //
        //   maxRadiansDelta:
        //
        //   maxMagnitudeDelta:
        public static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);
        //
        // Summary:
        //     Multiplies every component of this vector by the same component of scale.
        //
        // Parameters:
        //   scale:
        public void Scale(Vector3 scale);
        //
        // Summary:
        //     Multiplies two vectors component-wise.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static Vector3 Scale(Vector3 a, Vector3 b);
        //
        // Summary:
        //     Set x, y and z components of an existing Vector3.
        //
        // Parameters:
        //   new_x:
        //
        //   new_y:
        //
        //   new_z:
        public void Set(float new_x, float new_y, float new_z);
        //
        // Summary:
        //     Spherically interpolates between two vectors.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector3 Slerp(Vector3 a, Vector3 b, float t);
        //
        // Summary:
        //     Spherically interpolates between two vectors.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
        [ExcludeFromDocs]
        public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime);
        [ExcludeFromDocs]
        public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed);
        public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
        public static float SqrMagnitude(Vector3 a);
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
}

#endif
