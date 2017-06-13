/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_QUATERNION_H_GUARD
#define PIPELINE_QUATERNION_H_GUARD

namespace pipeline{
    
  // Summary:
    //     Quaternions are used to represent rotations.
    public struct Quaternion
    {
        public const float kEpsilon = 1e-006f;

        // Summary:
        //     W component of the Quaternion. Don't modify this directly unless you know
        //     quaternions inside out.
        public float w;
        //
        // Summary:
        //     X component of the Quaternion. Don't modify this directly unless you know
        //     quaternions inside out.
        public float x;
        //
        // Summary:
        //     Y component of the Quaternion. Don't modify this directly unless you know
        //     quaternions inside out.
        public float y;
        //
        // Summary:
        //     Z component of the Quaternion. Don't modify this directly unless you know
        //     quaternions inside out.
        public float z;

        //
        // Summary:
        //     Constructs new Quaternion with given x,y,z,w components.
        //
        // Parameters:
        //   x:
        //
        //   y:
        //
        //   z:
        //
        //   w:
        public Quaternion(float x, float y, float z, float w);

        public static bool operator !=(Quaternion lhs, Quaternion rhs);
        public static Quaternion operator *(Quaternion lhs, Quaternion rhs);
        public static Vector3 operator *(Quaternion rotation, Vector3 point);
        public static bool operator ==(Quaternion lhs, Quaternion rhs);

        // Summary:
        //     Returns the euler angle representation of the rotation.
        public Vector3 eulerAngles { get; set; }
        //
        // Summary:
        //     The identity rotation (Read Only).
        public static Quaternion identity { get; }

        public float this[int index] { get; set; }

        // Summary:
        //     Returns the angle in degrees between two rotations a and b.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Angle(Quaternion a, Quaternion b);
        //
        // Summary:
        //     Creates a rotation which rotates angle degrees around axis.
        //
        // Parameters:
        //   angle:
        //
        //   axis:
        public static Quaternion AngleAxis(float angle, Vector3 axis);
        [Obsolete("Use Quaternion.AngleAxis instead. This function was deprecated because it uses radians instead of degrees")]
        public static Quaternion AxisAngle(Vector3 axis, float angle);
        //
        // Summary:
        //     The dot product between two rotations.
        //
        // Parameters:
        //   a:
        //
        //   b:
        public static float Dot(Quaternion a, Quaternion b);
        public override bool Equals(object other);
        //
        // Summary:
        //     Returns a rotation that rotates z degrees around the z axis, x degrees around
        //     the x axis, and y degrees around the y axis (in that order).
        //
        // Parameters:
        //   euler:
        public static Quaternion Euler(Vector3 euler);
        //
        // Summary:
        //     Returns a rotation that rotates z degrees around the z axis, x degrees around
        //     the x axis, and y degrees around the y axis (in that order).
        //
        // Parameters:
        //   x:
        //
        //   y:
        //
        //   z:
        public static Quaternion Euler(float x, float y, float z);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public static Quaternion EulerAngles(Vector3 euler);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public static Quaternion EulerAngles(float x, float y, float z);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public static Quaternion EulerRotation(Vector3 euler);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public static Quaternion EulerRotation(float x, float y, float z);
        //
        // Summary:
        //     Creates a rotation which rotates from fromDirection to toDirection.
        //
        // Parameters:
        //   fromDirection:
        //
        //   toDirection:
        public static Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection);
        public override int GetHashCode();
        //
        // Summary:
        //     Returns the Inverse of rotation.
        //
        // Parameters:
        //   rotation:
        public static Quaternion Inverse(Quaternion rotation);
        //
        // Summary:
        //     Interpolates between a and b by t and normalizes the result afterwards. The
        //     parameter t is clamped to the range [0, 1].
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Quaternion Lerp(Quaternion a, Quaternion b, float t);
        //
        // Summary:
        //     Interpolates between a and b by t and normalizes the result afterwards. The
        //     parameter t is not clamped.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Quaternion LerpUnclamped(Quaternion a, Quaternion b, float t);
        //
        // Summary:
        //     Creates a rotation with the specified forward and upwards directions.
        //
        // Parameters:
        //   forward:
        //     The direction to look in.
        //
        //   upwards:
        //     The vector that defines in which direction up is.
        [ExcludeFromDocs]
        public static Quaternion LookRotation(Vector3 forward);
        //
        // Summary:
        //     Creates a rotation with the specified forward and upwards directions.
        //
        // Parameters:
        //   forward:
        //     The direction to look in.
        //
        //   upwards:
        //     The vector that defines in which direction up is.
        public static Quaternion LookRotation(Vector3 forward, Vector3 upwards);
        //
        // Summary:
        //     Rotates a rotation from towards to.
        //
        // Parameters:
        //   from:
        //
        //   to:
        //
        //   maxDegreesDelta:
        public static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta);
        //
        // Summary:
        //     Set x, y, z and w components of an existing Quaternion.
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
        [Obsolete("Use Quaternion.AngleAxis instead. This function was deprecated because it uses radians instead of degrees")]
        public void SetAxisAngle(Vector3 axis, float angle);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public void SetEulerAngles(Vector3 euler);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public void SetEulerAngles(float x, float y, float z);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public void SetEulerRotation(Vector3 euler);
        [Obsolete("Use Quaternion.Euler instead. This function was deprecated because it uses radians instead of degrees")]
        public void SetEulerRotation(float x, float y, float z);
        //
        // Summary:
        //     Creates a rotation which rotates from fromDirection to toDirection.
        //
        // Parameters:
        //   fromDirection:
        //
        //   toDirection:
        public void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection);
        //
        // Summary:
        //     Creates a rotation with the specified forward and upwards directions.
        //
        // Parameters:
        //   view:
        //     The direction to look in.
        //
        //   up:
        //     The vector that defines in which direction up is.
        [ExcludeFromDocs]
        public void SetLookRotation(Vector3 view);
        //
        // Summary:
        //     Creates a rotation with the specified forward and upwards directions.
        //
        // Parameters:
        //   view:
        //     The direction to look in.
        //
        //   up:
        //     The vector that defines in which direction up is.
        public void SetLookRotation(Vector3 view, Vector3 up);
        //
        // Summary:
        //     Spherically interpolates between a and b by t. The parameter t is clamped
        //     to the range [0, 1].
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Quaternion Slerp(Quaternion a, Quaternion b, float t);
        //
        // Summary:
        //     Spherically interpolates between a and b by t. The parameter t is not clamped.
        //
        // Parameters:
        //   a:
        //
        //   b:
        //
        //   t:
        public static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t);
        public void ToAngleAxis(out float angle, out Vector3 axis);
        [Obsolete("Use Quaternion.ToAngleAxis instead. This function was deprecated because it uses radians instead of degrees")]
        public void ToAxisAngle(out Vector3 axis, out float angle);
        [Obsolete("Use Quaternion.eulerAngles instead. This function was deprecated because it uses radians instead of degrees")]
        public Vector3 ToEuler();
        [Obsolete("Use Quaternion.eulerAngles instead. This function was deprecated because it uses radians instead of degrees")]
        public Vector3 ToEulerAngles();
        [Obsolete("Use Quaternion.eulerAngles instead. This function was deprecated because it uses radians instead of degrees")]
        public static Vector3 ToEulerAngles(Quaternion rotation);
        //
        // Summary:
        //     Returns a nicely formatted string of the Quaternion.
        //
        // Parameters:
        //   format:
        public override string ToString();
        //
        // Summary:
        //     Returns a nicely formatted string of the Quaternion.
        //
        // Parameters:
        //   format:
        public string ToString(string format);
}

#endif
