xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 330;
 1488.88779;1060.66051;-1049.54842;,
 -1511.11221;1060.66051;-1049.54819;,
 -1511.11221;1500.00000;11.11228;,
 1488.88779;1500.00000;11.11215;,
 1488.88779;1200.00000;11.11215;,
 -1511.11221;1200.00000;11.11228;,
 -1511.11221;848.52751;-837.41524;,
 1488.88779;848.52751;-837.41535;,
 1488.88767;0.00000;-1488.88790;,
 -1511.11233;0.00000;-1488.88767;,
 -1511.11221;0.00000;-1188.88767;,
 1488.88779;0.00000;-1188.88790;,
 1488.88779;-1060.66051;-1049.54842;,
 -1511.11221;-1060.66051;-1049.54819;,
 -1511.11221;-848.52751;-837.41524;,
 1488.88779;-848.52751;-837.41535;,
 1488.88779;-1500.00000;11.11215;,
 -1511.11221;-1500.00000;11.11228;,
 -1511.11221;-1200.00000;11.11228;,
 1488.88779;-1200.00000;11.11215;,
 1488.88779;-1060.66051;1071.77261;,
 -1511.11221;-1060.66051;1071.77284;,
 -1511.11221;-848.52751;859.64127;,
 1488.88779;-848.52751;859.64115;,
 1488.88790;0.00000;1511.11210;,
 -1511.11210;0.00000;1511.11233;,
 -1511.11221;0.00000;1211.11233;,
 1488.88779;0.00000;1211.11210;,
 1488.88779;1060.66051;1071.77261;,
 -1511.11221;1060.66051;1071.77284;,
 -1511.11221;848.52751;859.64127;,
 1488.88779;848.52751;859.64115;,
 1488.88779;1500.00000;11.11215;,
 -1511.11221;1500.00000;11.11228;,
 -1511.11221;1200.00000;11.11228;,
 1488.88779;1200.00000;11.11215;,
 1488.88779;848.52751;-837.41535;,
 1488.88779;1060.66051;-1049.54842;,
 -1511.11221;1060.66051;-1049.54819;,
 -1511.11221;848.52751;-837.41524;,
 -1511.11221;1200.00000;11.11228;,
 -1511.11221;1500.00000;11.11228;,
 1488.88779;0.00000;-1188.88790;,
 1488.88767;0.00000;-1488.88790;,
 -1511.11233;0.00000;-1488.88767;,
 -1511.11221;0.00000;-1188.88767;,
 1488.88779;-848.52751;-837.41535;,
 1488.88779;-1060.66051;-1049.54842;,
 -1511.11221;-1060.66051;-1049.54819;,
 -1511.11221;-848.52751;-837.41524;,
 1488.88779;-1200.00000;11.11215;,
 1488.88779;-1500.00000;11.11215;,
 -1511.11221;-1500.00000;11.11228;,
 -1511.11221;-1200.00000;11.11228;,
 1488.88779;-848.52751;859.64115;,
 1488.88779;-1060.66051;1071.77261;,
 -1511.11221;-1060.66051;1071.77284;,
 -1511.11221;-848.52751;859.64127;,
 1488.88779;0.00000;1211.11210;,
 1488.88790;0.00000;1511.11210;,
 -1511.11210;0.00000;1511.11233;,
 -1511.11221;0.00000;1211.11233;,
 1488.88779;848.52751;859.64115;,
 1488.88779;1060.66051;1071.77261;,
 -1511.11221;1060.66051;1071.77284;,
 -1511.11221;848.52751;859.64127;,
 4472.87659;1060.66051;-1049.54853;,
 1472.87533;1060.66051;-1049.54842;,
 1472.87533;1500.00000;11.11215;,
 4472.87659;1500.00000;11.11202;,
 4472.87659;1200.00000;11.11202;,
 1472.87533;1200.00000;11.11215;,
 1472.87533;848.52751;-837.41535;,
 4472.87659;848.52751;-837.41547;,
 4472.87659;0.00000;-1488.88802;,
 1472.87521;0.00000;-1488.88790;,
 1472.87533;0.00000;-1188.88790;,
 4472.87659;0.00000;-1188.88802;,
 4472.87659;-1060.66051;-1049.54853;,
 1472.87533;-1060.66051;-1049.54842;,
 1472.87533;-848.52751;-837.41535;,
 4472.87659;-848.52751;-837.41547;,
 4472.87659;-1500.00000;11.11202;,
 1472.87384;-1500.00000;11.11215;,
 1472.87533;-1200.00000;11.11215;,
 4472.87659;-1200.00000;11.11202;,
 4472.87659;-1060.66051;1071.77250;,
 1472.87533;-1060.66051;1071.77261;,
 1472.87533;-848.52751;859.64115;,
 4472.87659;-848.52751;859.64104;,
 4472.87659;0.00000;1511.11198;,
 1472.87544;0.00000;1511.11210;,
 1472.87533;0.00000;1211.11210;,
 4472.87659;0.00000;1211.11198;,
 4472.87659;1060.66051;1071.77250;,
 1472.87533;1060.66051;1071.77261;,
 1472.87533;848.52751;859.64115;,
 4472.87659;848.52751;859.64104;,
 4472.87659;1500.00000;11.11202;,
 1472.87533;1500.00000;11.11215;,
 1472.87533;1200.00000;11.11215;,
 4472.87659;1200.00000;11.11202;,
 4472.87659;848.52751;-837.41547;,
 4472.87659;1060.66051;-1049.54853;,
 1472.87533;1060.66051;-1049.54842;,
 1472.87533;848.52751;-837.41535;,
 1472.87533;1200.00000;11.11215;,
 1472.87533;1500.00000;11.11215;,
 4472.87659;0.00000;-1188.88802;,
 4472.87659;0.00000;-1488.88802;,
 1472.87521;0.00000;-1488.88790;,
 1472.87533;0.00000;-1188.88790;,
 4472.87659;-848.52751;-837.41547;,
 4472.87659;-1060.66051;-1049.54853;,
 1472.87533;-1060.66051;-1049.54842;,
 1472.87533;-848.52751;-837.41535;,
 4472.87659;-1200.00000;11.11202;,
 4472.87659;-1500.00000;11.11202;,
 1472.87384;-1500.00000;11.11215;,
 1472.87533;-1200.00000;11.11215;,
 4472.87659;-848.52751;859.64104;,
 4472.87659;-1060.66051;1071.77250;,
 1472.87533;-1060.66051;1071.77261;,
 1472.87533;-848.52751;859.64115;,
 4472.87659;0.00000;1211.11198;,
 4472.87659;0.00000;1511.11198;,
 1472.87544;0.00000;1511.11210;,
 1472.87533;0.00000;1211.11210;,
 4472.87659;848.52751;859.64104;,
 4472.87659;1060.66051;1071.77250;,
 1472.87533;1060.66051;1071.77261;,
 1472.87533;848.52751;859.64115;,
 -1496.78272;1060.66051;-1049.54819;,
 -4496.78284;1060.66051;-1049.54807;,
 -4496.78284;1500.00000;11.11241;,
 -1496.78272;1500.00000;11.11228;,
 -1496.78272;1200.00000;11.11228;,
 -4496.78284;1200.00000;11.11241;,
 -4496.78284;848.52751;-837.41512;,
 -1496.78272;848.52751;-837.41524;,
 -1496.78284;0.00000;-1488.88767;,
 -4496.78284;0.00000;-1488.88756;,
 -4496.78284;0.00000;-1188.88756;,
 -1496.78272;0.00000;-1188.88767;,
 -1496.78272;-1060.66051;-1049.54819;,
 -4496.78284;-1060.66051;-1049.54807;,
 -4496.78284;-848.52751;-837.41512;,
 -1496.78272;-848.52751;-837.41524;,
 -1496.78272;-1500.00000;11.11228;,
 -4496.78284;-1500.00000;11.11241;,
 -4496.78284;-1200.00000;11.11241;,
 -1496.78272;-1200.00000;11.11228;,
 -1496.78272;-1060.66051;1071.77284;,
 -4496.78284;-1060.66051;1071.77296;,
 -4496.78284;-848.52751;859.64138;,
 -1496.78272;-848.52751;859.64127;,
 -1496.78261;0.00000;1511.11233;,
 -4496.78284;0.00000;1511.11244;,
 -4496.78284;0.00000;1211.11244;,
 -1496.78272;0.00000;1211.11233;,
 -1496.78272;1060.66051;1071.77284;,
 -4496.78284;1060.66051;1071.77296;,
 -4496.78284;848.52751;859.64138;,
 -1496.78272;848.52751;859.64127;,
 -1496.78272;1500.00000;11.11228;,
 -4496.78284;1500.00000;11.11241;,
 -4496.78284;1200.00000;11.11241;,
 -1496.78272;1200.00000;11.11228;,
 -1496.78272;848.52751;-837.41524;,
 -1496.78272;1060.66051;-1049.54819;,
 -4496.78284;1060.66051;-1049.54807;,
 -4496.78284;848.52751;-837.41512;,
 -4496.78284;1200.00000;11.11241;,
 -4496.78284;1500.00000;11.11241;,
 -1496.78272;0.00000;-1188.88767;,
 -1496.78284;0.00000;-1488.88767;,
 -4496.78284;0.00000;-1488.88756;,
 -4496.78284;0.00000;-1188.88756;,
 -1496.78272;-848.52751;-837.41524;,
 -1496.78272;-1060.66051;-1049.54819;,
 -4496.78284;-1060.66051;-1049.54807;,
 -4496.78284;-848.52751;-837.41512;,
 -1496.78272;-1200.00000;11.11228;,
 -1496.78272;-1500.00000;11.11228;,
 -4496.78284;-1500.00000;11.11241;,
 -4496.78284;-1200.00000;11.11241;,
 -1496.78272;-848.52751;859.64127;,
 -1496.78272;-1060.66051;1071.77284;,
 -4496.78284;-1060.66051;1071.77296;,
 -4496.78284;-848.52751;859.64138;,
 -1496.78272;0.00000;1211.11233;,
 -1496.78261;0.00000;1511.11233;,
 -4496.78284;0.00000;1511.11244;,
 -4496.78284;0.00000;1211.11244;,
 -1496.78272;848.52751;859.64127;,
 -1496.78272;1060.66051;1071.77284;,
 -4496.78284;1060.66051;1071.77296;,
 -4496.78284;848.52751;859.64138;,
 7461.66000;1060.66051;-1049.54865;,
 4461.66138;1060.66051;-1049.54853;,
 4461.66275;1500.00000;11.11202;,
 7461.66000;1500.00000;11.11189;,
 7461.66000;1200.00000;11.11189;,
 4461.66138;1200.00000;11.11202;,
 4461.66138;848.52751;-837.41547;,
 7461.66000;848.52751;-837.41564;,
 7461.66000;0.00000;-1488.88813;,
 4461.66138;0.00000;-1488.88802;,
 4461.66138;0.00000;-1188.88802;,
 7461.66000;0.00000;-1188.88813;,
 7461.66000;-1060.66051;-1049.54865;,
 4461.66138;-1060.66051;-1049.54853;,
 4461.66138;-848.52751;-837.41547;,
 7461.66000;-848.52751;-837.41564;,
 7461.66000;-1500.00000;11.11189;,
 4461.66138;-1500.00000;11.11202;,
 4461.66138;-1200.00000;11.11202;,
 7461.66000;-1200.00000;11.11189;,
 7461.66000;-1060.66051;1071.77238;,
 4461.66138;-1060.66051;1071.77250;,
 4461.66138;-848.52751;859.64104;,
 7461.66000;-848.52751;859.64087;,
 7461.66000;0.00000;1511.11187;,
 4461.66138;0.00000;1511.11198;,
 4461.66138;0.00000;1211.11198;,
 7461.66000;0.00000;1211.11187;,
 7461.66000;1060.66051;1071.77238;,
 4461.66138;1060.66051;1071.77250;,
 4461.66138;848.52751;859.64104;,
 7461.66000;848.52751;859.64087;,
 7461.66000;1500.00000;11.11189;,
 4461.66275;1500.00000;11.11202;,
 4461.66138;1200.00000;11.11202;,
 7461.66000;1200.00000;11.11189;,
 7461.66000;848.52751;-837.41564;,
 7461.66000;1060.66051;-1049.54865;,
 4461.66138;1060.66051;-1049.54853;,
 4461.66138;848.52751;-837.41547;,
 4461.66138;1200.00000;11.11202;,
 4461.66275;1500.00000;11.11202;,
 7461.66000;0.00000;-1188.88813;,
 7461.66000;0.00000;-1488.88813;,
 4461.66138;0.00000;-1488.88802;,
 4461.66138;0.00000;-1188.88802;,
 7461.66000;-848.52751;-837.41564;,
 7461.66000;-1060.66051;-1049.54865;,
 4461.66138;-1060.66051;-1049.54853;,
 4461.66138;-848.52751;-837.41547;,
 7461.66000;-1200.00000;11.11189;,
 7461.66000;-1500.00000;11.11189;,
 4461.66138;-1500.00000;11.11202;,
 4461.66138;-1200.00000;11.11202;,
 7461.66000;-848.52751;859.64087;,
 7461.66000;-1060.66051;1071.77238;,
 4461.66138;-1060.66051;1071.77250;,
 4461.66138;-848.52751;859.64104;,
 7461.66000;0.00000;1211.11187;,
 7461.66000;0.00000;1511.11187;,
 4461.66138;0.00000;1511.11198;,
 4461.66138;0.00000;1211.11198;,
 7461.66000;848.52751;859.64087;,
 7461.66000;1060.66051;1071.77238;,
 4461.66138;1060.66051;1071.77250;,
 4461.66138;848.52751;859.64104;,
 -4461.66000;1060.66051;-1049.54807;,
 -7461.66000;1060.66051;-1049.54796;,
 -7461.66000;1500.00000;11.11254;,
 -4461.66000;1500.00000;11.11241;,
 -4461.66000;1200.00000;11.11241;,
 -7461.66000;1200.00000;11.11254;,
 -7461.66000;848.52751;-837.41495;,
 -4461.66000;848.52751;-837.41512;,
 -4461.66000;0.00000;-1488.88756;,
 -7461.66000;0.00000;-1488.88744;,
 -7461.66000;0.00000;-1188.88744;,
 -4461.66000;0.00000;-1188.88756;,
 -4461.66000;-1060.66051;-1049.54807;,
 -7461.66000;-1060.66051;-1049.54796;,
 -7461.66000;-848.52751;-837.41495;,
 -4461.66000;-848.52751;-837.41512;,
 -4461.66000;-1500.00000;11.11241;,
 -7461.66000;-1500.00000;11.11254;,
 -7461.66000;-1200.00000;11.11254;,
 -4461.66000;-1200.00000;11.11241;,
 -4461.66000;-1060.66051;1071.77296;,
 -7461.66000;-1060.66051;1071.77307;,
 -7461.66000;-848.52751;859.64155;,
 -4461.66000;-848.52751;859.64138;,
 -4461.66000;0.00000;1511.11244;,
 -7461.66000;0.00000;1511.11256;,
 -7461.66000;0.00000;1211.11256;,
 -4461.66000;0.00000;1211.11244;,
 -4461.66000;1060.66051;1071.77296;,
 -7461.66000;1060.66051;1071.77307;,
 -7461.66000;848.52751;859.64155;,
 -4461.66000;848.52751;859.64138;,
 -4461.66000;1500.00000;11.11241;,
 -7461.66000;1500.00000;11.11254;,
 -7461.66000;1200.00000;11.11254;,
 -4461.66000;1200.00000;11.11241;,
 -4461.66000;848.52751;-837.41512;,
 -4461.66000;1060.66051;-1049.54807;,
 -7461.66000;1060.66051;-1049.54796;,
 -7461.66000;848.52751;-837.41495;,
 -7461.66000;1200.00000;11.11254;,
 -7461.66000;1500.00000;11.11254;,
 -4461.66000;0.00000;-1188.88756;,
 -4461.66000;0.00000;-1488.88756;,
 -7461.66000;0.00000;-1488.88744;,
 -7461.66000;0.00000;-1188.88744;,
 -4461.66000;-848.52751;-837.41512;,
 -4461.66000;-1060.66051;-1049.54807;,
 -7461.66000;-1060.66051;-1049.54796;,
 -7461.66000;-848.52751;-837.41495;,
 -4461.66000;-1200.00000;11.11241;,
 -4461.66000;-1500.00000;11.11241;,
 -7461.66000;-1500.00000;11.11254;,
 -7461.66000;-1200.00000;11.11254;,
 -4461.66000;-848.52751;859.64138;,
 -4461.66000;-1060.66051;1071.77296;,
 -7461.66000;-1060.66051;1071.77307;,
 -7461.66000;-848.52751;859.64155;,
 -4461.66000;0.00000;1211.11244;,
 -4461.66000;0.00000;1511.11244;,
 -7461.66000;0.00000;1511.11256;,
 -7461.66000;0.00000;1211.11256;,
 -4461.66000;848.52751;859.64138;,
 -4461.66000;1060.66051;1071.77296;,
 -7461.66000;1060.66051;1071.77307;,
 -7461.66000;848.52751;859.64155;;
 
 320;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;8,9,1;,
 3;8,1,0;,
 3;7,6,10;,
 3;7,10,11;,
 3;12,13,9;,
 3;12,9,8;,
 3;11,10,14;,
 3;11,14,15;,
 3;16,17,13;,
 3;16,13,12;,
 3;15,14,18;,
 3;15,18,19;,
 3;20,21,17;,
 3;20,17,16;,
 3;19,18,22;,
 3;19,22,23;,
 3;24,25,21;,
 3;24,21,20;,
 3;23,22,26;,
 3;23,26,27;,
 3;28,29,25;,
 3;28,25,24;,
 3;27,26,30;,
 3;27,30,31;,
 3;32,33,29;,
 3;32,29,28;,
 3;31,30,34;,
 3;31,34,35;,
 3;4,36,37;,
 3;4,37,3;,
 3;38,39,40;,
 3;38,40,41;,
 3;36,42,43;,
 3;36,43,37;,
 3;44,45,39;,
 3;44,39,38;,
 3;42,46,47;,
 3;42,47,43;,
 3;48,49,45;,
 3;48,45,44;,
 3;46,50,51;,
 3;46,51,47;,
 3;52,53,49;,
 3;52,49,48;,
 3;50,54,55;,
 3;50,55,51;,
 3;56,57,53;,
 3;56,53,52;,
 3;54,58,59;,
 3;54,59,55;,
 3;60,61,57;,
 3;60,57,56;,
 3;58,62,63;,
 3;58,63,59;,
 3;64,65,61;,
 3;64,61,60;,
 3;62,4,3;,
 3;62,3,63;,
 3;41,40,65;,
 3;41,65,64;,
 3;66,67,68;,
 3;66,68,69;,
 3;70,71,72;,
 3;70,72,73;,
 3;74,75,67;,
 3;74,67,66;,
 3;73,72,76;,
 3;73,76,77;,
 3;78,79,75;,
 3;78,75,74;,
 3;77,76,80;,
 3;77,80,81;,
 3;82,83,79;,
 3;82,79,78;,
 3;81,80,84;,
 3;81,84,85;,
 3;86,87,83;,
 3;86,83,82;,
 3;85,84,88;,
 3;85,88,89;,
 3;90,91,87;,
 3;90,87,86;,
 3;89,88,92;,
 3;89,92,93;,
 3;94,95,91;,
 3;94,91,90;,
 3;93,92,96;,
 3;93,96,97;,
 3;98,99,95;,
 3;98,95,94;,
 3;97,96,100;,
 3;97,100,101;,
 3;70,102,103;,
 3;70,103,69;,
 3;104,105,106;,
 3;104,106,107;,
 3;102,108,109;,
 3;102,109,103;,
 3;110,111,105;,
 3;110,105,104;,
 3;108,112,113;,
 3;108,113,109;,
 3;114,115,111;,
 3;114,111,110;,
 3;112,116,117;,
 3;112,117,113;,
 3;118,119,115;,
 3;118,115,114;,
 3;116,120,121;,
 3;116,121,117;,
 3;122,123,119;,
 3;122,119,118;,
 3;120,124,125;,
 3;120,125,121;,
 3;126,127,123;,
 3;126,123,122;,
 3;124,128,129;,
 3;124,129,125;,
 3;130,131,127;,
 3;130,127,126;,
 3;128,70,69;,
 3;128,69,129;,
 3;107,106,131;,
 3;107,131,130;,
 3;132,133,134;,
 3;132,134,135;,
 3;136,137,138;,
 3;136,138,139;,
 3;140,141,133;,
 3;140,133,132;,
 3;139,138,142;,
 3;139,142,143;,
 3;144,145,141;,
 3;144,141,140;,
 3;143,142,146;,
 3;143,146,147;,
 3;148,149,145;,
 3;148,145,144;,
 3;147,146,150;,
 3;147,150,151;,
 3;152,153,149;,
 3;152,149,148;,
 3;151,150,154;,
 3;151,154,155;,
 3;156,157,153;,
 3;156,153,152;,
 3;155,154,158;,
 3;155,158,159;,
 3;160,161,157;,
 3;160,157,156;,
 3;159,158,162;,
 3;159,162,163;,
 3;164,165,161;,
 3;164,161,160;,
 3;163,162,166;,
 3;163,166,167;,
 3;136,168,169;,
 3;136,169,135;,
 3;170,171,172;,
 3;170,172,173;,
 3;168,174,175;,
 3;168,175,169;,
 3;176,177,171;,
 3;176,171,170;,
 3;174,178,179;,
 3;174,179,175;,
 3;180,181,177;,
 3;180,177,176;,
 3;178,182,183;,
 3;178,183,179;,
 3;184,185,181;,
 3;184,181,180;,
 3;182,186,187;,
 3;182,187,183;,
 3;188,189,185;,
 3;188,185,184;,
 3;186,190,191;,
 3;186,191,187;,
 3;192,193,189;,
 3;192,189,188;,
 3;190,194,195;,
 3;190,195,191;,
 3;196,197,193;,
 3;196,193,192;,
 3;194,136,135;,
 3;194,135,195;,
 3;173,172,197;,
 3;173,197,196;,
 3;198,199,200;,
 3;198,200,201;,
 3;202,203,204;,
 3;202,204,205;,
 3;206,207,199;,
 3;206,199,198;,
 3;205,204,208;,
 3;205,208,209;,
 3;210,211,207;,
 3;210,207,206;,
 3;209,208,212;,
 3;209,212,213;,
 3;214,215,211;,
 3;214,211,210;,
 3;213,212,216;,
 3;213,216,217;,
 3;218,219,215;,
 3;218,215,214;,
 3;217,216,220;,
 3;217,220,221;,
 3;222,223,219;,
 3;222,219,218;,
 3;221,220,224;,
 3;221,224,225;,
 3;226,227,223;,
 3;226,223,222;,
 3;225,224,228;,
 3;225,228,229;,
 3;230,231,227;,
 3;230,227,226;,
 3;229,228,232;,
 3;229,232,233;,
 3;202,234,235;,
 3;202,235,201;,
 3;236,237,238;,
 3;236,238,239;,
 3;234,240,241;,
 3;234,241,235;,
 3;242,243,237;,
 3;242,237,236;,
 3;240,244,245;,
 3;240,245,241;,
 3;246,247,243;,
 3;246,243,242;,
 3;244,248,249;,
 3;244,249,245;,
 3;250,251,247;,
 3;250,247,246;,
 3;248,252,253;,
 3;248,253,249;,
 3;254,255,251;,
 3;254,251,250;,
 3;252,256,257;,
 3;252,257,253;,
 3;258,259,255;,
 3;258,255,254;,
 3;256,260,261;,
 3;256,261,257;,
 3;262,263,259;,
 3;262,259,258;,
 3;260,202,201;,
 3;260,201,261;,
 3;239,238,263;,
 3;239,263,262;,
 3;264,265,266;,
 3;264,266,267;,
 3;268,269,270;,
 3;268,270,271;,
 3;272,273,265;,
 3;272,265,264;,
 3;271,270,274;,
 3;271,274,275;,
 3;276,277,273;,
 3;276,273,272;,
 3;275,274,278;,
 3;275,278,279;,
 3;280,281,277;,
 3;280,277,276;,
 3;279,278,282;,
 3;279,282,283;,
 3;284,285,281;,
 3;284,281,280;,
 3;283,282,286;,
 3;283,286,287;,
 3;288,289,285;,
 3;288,285,284;,
 3;287,286,290;,
 3;287,290,291;,
 3;292,293,289;,
 3;292,289,288;,
 3;291,290,294;,
 3;291,294,295;,
 3;296,297,293;,
 3;296,293,292;,
 3;295,294,298;,
 3;295,298,299;,
 3;268,300,301;,
 3;268,301,267;,
 3;302,303,304;,
 3;302,304,305;,
 3;300,306,307;,
 3;300,307,301;,
 3;308,309,303;,
 3;308,303,302;,
 3;306,310,311;,
 3;306,311,307;,
 3;312,313,309;,
 3;312,309,308;,
 3;310,314,315;,
 3;310,315,311;,
 3;316,317,313;,
 3;316,313,312;,
 3;314,318,319;,
 3;314,319,315;,
 3;320,321,317;,
 3;320,317,316;,
 3;318,322,323;,
 3;318,323,319;,
 3;324,325,321;,
 3;324,321,320;,
 3;322,326,327;,
 3;322,327,323;,
 3;328,329,325;,
 3;328,325,324;,
 3;326,268,267;,
 3;326,267,327;,
 3;305,304,329;,
 3;305,329,328;;
 
 MeshMaterialList {
  1;
  320;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.770000;0.749210;0.247940;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.120000;0.116760;0.038640;;
  }
 }
 MeshNormals {
  196;
  0.000000;0.990602;0.136773;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  -0.000000;-0.990602;-0.136773;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136773;0.990602;,
  0.000000;0.603748;0.797175;,
  -0.000000;0.990602;-0.136773;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  0.000000;-0.990602;0.136773;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136773;0.990602;,
  0.000000;0.797175;0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136774;0.990602;,
  0.000000;0.797175;0.603748;,
  -0.000000;0.990602;-0.136774;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  -0.000000;-0.990602;-0.136774;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136774;0.990602;,
  0.000000;0.603748;0.797175;,
  0.000000;0.990602;0.136774;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  0.000000;0.990602;0.136773;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  -0.000000;-0.990602;-0.136773;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136773;0.990602;,
  0.000000;0.603748;0.797175;,
  -0.000000;0.990602;-0.136773;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136773;0.990602;,
  0.000000;0.797175;0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136774;0.990602;,
  0.000000;0.797175;0.603748;,
  -0.000000;0.990602;-0.136774;,
  -0.000000;0.603748;-0.797176;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  -0.000000;-0.990602;-0.136774;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136774;0.990602;,
  0.000000;0.603748;0.797175;,
  0.000000;0.990602;0.136774;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797176;,
  0.000000;0.990602;0.136773;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  -0.000000;-0.990602;-0.136773;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136773;0.990602;,
  0.000000;0.603748;0.797175;,
  -0.000000;0.990602;-0.136773;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  0.000000;-0.990602;0.136773;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136773;0.990602;,
  0.000000;0.797175;0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136774;0.990602;,
  0.000000;0.797175;0.603748;,
  -0.000000;0.990602;-0.136774;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.990602;-0.136774;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136774;0.990602;,
  0.000000;0.603748;0.797175;,
  0.000000;0.990602;0.136774;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  0.000000;0.990602;0.136773;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  -0.000000;-0.990602;-0.136773;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136773;0.990602;,
  0.000000;0.603748;0.797175;,
  -0.000000;0.990602;-0.136773;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  0.000000;-0.990602;0.136773;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136773;0.990602;,
  0.000000;0.797175;0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136774;0.990602;,
  0.000000;0.797175;0.603748;,
  -0.000000;0.990602;-0.136774;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  -0.000000;-0.990602;-0.136774;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136774;0.990602;,
  0.000000;0.603748;0.797175;,
  0.000000;0.990602;0.136774;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  0.000000;0.990602;0.136773;,
  -0.000000;-0.990602;-0.136773;,
  0.000000;-0.136773;0.990602;,
  0.000000;0.603748;0.797175;,
  -0.000000;0.990602;-0.136773;,
  0.000000;-0.990602;0.136773;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136773;0.990602;,
  0.000000;0.797175;0.603748;,
  0.000000;-0.990602;0.136774;,
  0.000000;-0.603748;0.797175;,
  0.000000;0.136774;0.990602;,
  0.000000;0.797175;0.603748;,
  -0.000000;0.990602;-0.136774;,
  -0.000000;0.603748;-0.797175;,
  -0.000000;-0.136773;-0.990602;,
  -0.000000;-0.797175;-0.603748;,
  -0.000000;-0.990602;-0.136774;,
  0.000000;-0.797175;0.603748;,
  0.000000;-0.136774;0.990602;,
  0.000000;0.603748;0.797175;,
  0.000000;0.990602;0.136774;,
  -0.000000;0.797175;-0.603748;,
  -0.000000;0.136773;-0.990602;,
  -0.000000;-0.603748;-0.797175;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000002;0.000000;,
  -1.000000;0.000004;0.000000;,
  -1.000000;0.000003;0.000000;,
  -1.000000;0.000002;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000002;-0.000000;,
  -1.000000;0.000003;0.000000;,
  -1.000000;0.000003;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000002;0.000000;;
  320;
  3;1,9,8;,
  3;1,8,0;,
  3;16,24,25;,
  3;16,25,17;,
  3;2,10,9;,
  3;2,9,1;,
  3;17,25,26;,
  3;17,26,18;,
  3;3,11,10;,
  3;3,10,2;,
  3;18,26,27;,
  3;18,27,19;,
  3;4,12,11;,
  3;4,11,3;,
  3;19,27,28;,
  3;19,28,20;,
  3;5,13,12;,
  3;5,12,4;,
  3;20,28,29;,
  3;20,29,21;,
  3;6,14,13;,
  3;6,13,5;,
  3;21,29,30;,
  3;21,30,22;,
  3;7,15,14;,
  3;7,14,6;,
  3;22,30,31;,
  3;22,31,23;,
  3;0,8,15;,
  3;0,15,7;,
  3;23,31,24;,
  3;23,24,16;,
  3;151,152,153;,
  3;151,153,151;,
  3;154,155,156;,
  3;154,156,156;,
  3;152,157,158;,
  3;152,158,153;,
  3;159,160,155;,
  3;159,155,154;,
  3;157,151,161;,
  3;157,161,158;,
  3;162,156,160;,
  3;162,160,159;,
  3;151,151,151;,
  3;151,151,161;,
  3;156,156,156;,
  3;156,156,162;,
  3;151,163,164;,
  3;151,164,151;,
  3;165,166,156;,
  3;165,156,156;,
  3;163,167,168;,
  3;163,168,164;,
  3;169,170,166;,
  3;169,166,165;,
  3;167,151,161;,
  3;167,161,168;,
  3;162,156,170;,
  3;162,170,169;,
  3;151,151,151;,
  3;151,151,161;,
  3;156,156,156;,
  3;156,156,162;,
  3;33,41,40;,
  3;33,40,32;,
  3;48,56,57;,
  3;48,57,49;,
  3;34,42,41;,
  3;34,41,33;,
  3;49,57,58;,
  3;49,58,50;,
  3;35,43,42;,
  3;35,42,34;,
  3;50,58,59;,
  3;50,59,51;,
  3;36,44,43;,
  3;36,43,35;,
  3;51,59,60;,
  3;51,60,52;,
  3;37,45,44;,
  3;37,44,36;,
  3;52,60,61;,
  3;52,61,53;,
  3;38,46,45;,
  3;38,45,37;,
  3;53,61,62;,
  3;53,62,54;,
  3;39,47,46;,
  3;39,46,38;,
  3;54,62,63;,
  3;54,63,55;,
  3;32,40,47;,
  3;32,47,39;,
  3;55,63,56;,
  3;55,56,48;,
  3;151,151,151;,
  3;151,151,151;,
  3;171,172,156;,
  3;171,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;173,174,172;,
  3;173,172,171;,
  3;151,151,151;,
  3;151,151,151;,
  3;175,176,174;,
  3;175,174,173;,
  3;151,151,151;,
  3;151,151,151;,
  3;177,178,176;,
  3;177,176,175;,
  3;151,151,151;,
  3;151,151,151;,
  3;179,180,178;,
  3;179,178,177;,
  3;151,151,151;,
  3;151,151,151;,
  3;181,182,180;,
  3;181,180,179;,
  3;151,151,151;,
  3;151,151,151;,
  3;162,156,182;,
  3;162,182,181;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,162;,
  3;65,73,72;,
  3;65,72,64;,
  3;80,87,88;,
  3;80,88,81;,
  3;66,74,73;,
  3;66,73,65;,
  3;81,88,89;,
  3;81,89,82;,
  3;67,75,74;,
  3;67,74,66;,
  3;82,89,90;,
  3;82,90,83;,
  3;68,76,75;,
  3;68,75,67;,
  3;83,90,91;,
  3;83,91,84;,
  3;69,77,76;,
  3;69,76,68;,
  3;84,91,29;,
  3;84,29,85;,
  3;70,78,77;,
  3;70,77,69;,
  3;85,29,92;,
  3;85,92,86;,
  3;71,79,78;,
  3;71,78,70;,
  3;86,92,93;,
  3;86,93,23;,
  3;64,72,79;,
  3;64,79,71;,
  3;23,93,87;,
  3;23,87,80;,
  3;151,183,184;,
  3;151,184,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;183,185,186;,
  3;183,186,184;,
  3;156,156,156;,
  3;156,156,156;,
  3;185,151,161;,
  3;185,161,186;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,161;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,187,188;,
  3;151,188,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;187,189,190;,
  3;187,190,188;,
  3;156,156,156;,
  3;156,156,156;,
  3;189,151,161;,
  3;189,161,190;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,161;,
  3;156,156,156;,
  3;156,156,156;,
  3;95,103,102;,
  3;95,102,94;,
  3;110,118,119;,
  3;110,119,111;,
  3;96,104,103;,
  3;96,103,95;,
  3;111,119,120;,
  3;111,120,112;,
  3;97,105,104;,
  3;97,104,96;,
  3;112,120,121;,
  3;112,121,113;,
  3;98,106,105;,
  3;98,105,97;,
  3;113,121,122;,
  3;113,122,114;,
  3;99,107,106;,
  3;99,106,98;,
  3;114,122,123;,
  3;114,123,115;,
  3;100,108,107;,
  3;100,107,99;,
  3;115,123,124;,
  3;115,124,116;,
  3;101,109,108;,
  3;101,108,100;,
  3;116,124,125;,
  3;116,125,117;,
  3;94,102,109;,
  3;94,109,101;,
  3;117,125,118;,
  3;117,118,110;,
  3;151,151,151;,
  3;151,151,151;,
  3;191,156,192;,
  3;191,192,193;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,191;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;194,195,156;,
  3;194,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;193,192,195;,
  3;193,195,194;,
  3;65,73,130;,
  3;65,130,126;,
  3;135,143,144;,
  3;135,144,136;,
  3;66,74,73;,
  3;66,73,65;,
  3;136,144,145;,
  3;136,145,137;,
  3;67,75,74;,
  3;67,74,66;,
  3;137,145,146;,
  3;137,146,138;,
  3;127,131,75;,
  3;127,75,67;,
  3;138,146,147;,
  3;138,147,139;,
  3;69,132,131;,
  3;69,131,127;,
  3;139,147,148;,
  3;139,148,140;,
  3;128,133,132;,
  3;128,132,69;,
  3;140,148,149;,
  3;140,149,141;,
  3;129,134,133;,
  3;129,133,128;,
  3;141,149,150;,
  3;141,150,142;,
  3;126,130,134;,
  3;126,134,129;,
  3;142,150,143;,
  3;142,143,135;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;,
  3;151,151,151;,
  3;151,151,151;,
  3;156,156,156;,
  3;156,156,156;;
 }
 MeshTextureCoords {
  330;
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}