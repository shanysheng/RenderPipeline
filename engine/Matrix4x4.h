/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_MATRIX4X4_H_GUARD
#define PIPELINE_MATRIX4X4_H_GUARD

namespace pipeline{
    
   // Summary:
    //     A standard 4x4 transformation matrix.
    public struct Matrix4x4
    {
        public float m00;
        public float m01;
        public float m02;
        public float m03;
        public float m10;
        public float m11;
        public float m12;
        public float m13;
        public float m20;
        public float m21;
        public float m22;
        public float m23;
        public float m30;
        public float m31;
        public float m32;
        public float m33;

        public static bool operator !=(Matrix4x4 lhs, Matrix4x4 rhs);
        public static Matrix4x4 operator *(Matrix4x4 lhs, Matrix4x4 rhs);
        public static Vector4 operator *(Matrix4x4 lhs, Vector4 v);
        public static bool operator ==(Matrix4x4 lhs, Matrix4x4 rhs);

        // Summary:
        //     The determinant of the matrix.
        public float determinant { get; }
        //
        // Summary:
        //     Returns the identity matrix (Read Only).
        public static Matrix4x4 identity { get; }
        //
        // Summary:
        //     The inverse of this matrix (Read Only).
        public Matrix4x4 inverse { get; }
        //
        // Summary:
        //     Is this the identity matrix?
        public bool isIdentity { get; }
        //
        // Summary:
        //     Returns the transpose of this matrix (Read Only).
        public Matrix4x4 transpose { get; }
        //
        // Summary:
        //     Returns a matrix with all elements set to zero (Read Only).
        public static Matrix4x4 zero { get; }

        public float this[int index] { get; set; }
        public float this[int row, int column] { get; set; }

        public static float Determinant(Matrix4x4 m);
        public override bool Equals(object other);
        //
        // Summary:
        //     Get a column of the matrix.
        //
        // Parameters:
        //   i:
        public Vector4 GetColumn(int i);
        public override int GetHashCode();
        //
        // Summary:
        //     Returns a row of the matrix.
        //
        // Parameters:
        //   i:
        public Vector4 GetRow(int i);
        public static Matrix4x4 Inverse(Matrix4x4 m);
        //
        // Summary:
        //     Transforms a position by this matrix (generic).
        //
        // Parameters:
        //   v:
        public Vector3 MultiplyPoint(Vector3 v);
        //
        // Summary:
        //     Transforms a position by this matrix (fast).
        //
        // Parameters:
        //   v:
        public Vector3 MultiplyPoint3x4(Vector3 v);
        //
        // Summary:
        //     Transforms a direction by this matrix.
        //
        // Parameters:
        //   v:
        public Vector3 MultiplyVector(Vector3 v);
        //
        // Summary:
        //     Creates an orthogonal projection matrix.
        //
        // Parameters:
        //   left:
        //
        //   right:
        //
        //   bottom:
        //
        //   top:
        //
        //   zNear:
        //
        //   zFar:
        public static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
        //
        // Summary:
        //     Creates a perspective projection matrix.
        //
        // Parameters:
        //   fov:
        //
        //   aspect:
        //
        //   zNear:
        //
        //   zFar:
        public static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);
        //
        // Summary:
        //     Creates a scaling matrix.
        //
        // Parameters:
        //   v:
        public static Matrix4x4 Scale(Vector3 v);
        //
        // Summary:
        //     Sets a column of the matrix.
        //
        // Parameters:
        //   i:
        //
        //   v:
        public void SetColumn(int i, Vector4 v);
        //
        // Summary:
        //     Sets a row of the matrix.
        //
        // Parameters:
        //   i:
        //
        //   v:
        public void SetRow(int i, Vector4 v);
        //
        // Summary:
        //     Sets this matrix to a translation, rotation and scaling matrix.
        //
        // Parameters:
        //   pos:
        //
        //   q:
        //
        //   s:
        public void SetTRS(Vector3 pos, Quaternion q, Vector3 s);
        //
        // Summary:
        //     Returns a nicely formatted string for this matrix.
        //
        // Parameters:
        //   format:
        public override string ToString();
        //
        // Summary:
        //     Returns a nicely formatted string for this matrix.
        //
        // Parameters:
        //   format:
        public string ToString(string format);
        public static Matrix4x4 Transpose(Matrix4x4 m);
        //
        // Summary:
        //     Creates a translation, rotation and scaling matrix.
        //
        // Parameters:
        //   pos:
        //
        //   q:
        //
        //   s:
        public static Matrix4x4 TRS(Vector3 pos, Quaternion q, Vector3 s);
}

#endif
