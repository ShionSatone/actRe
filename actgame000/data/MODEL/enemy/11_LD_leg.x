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
 36;
 -1.90691;-0.59489;-1.83344;,
 0.02658;-0.59489;-2.63431;,
 0.00885;-20.19257;-1.28009;,
 -0.91092;-20.19258;-0.89911;,
 1.96007;-0.59489;-1.83344;,
 0.92863;-20.19258;-0.89911;,
 2.76095;-0.59489;0.10005;,
 1.30961;-20.19257;0.02066;,
 1.96007;-0.59489;2.03355;,
 0.92863;-20.19258;0.94044;,
 0.02658;-0.59489;2.83442;,
 0.00885;-20.19258;1.32142;,
 -1.90691;-0.59489;2.03355;,
 -0.91092;-20.19257;0.94044;,
 -2.70779;-0.59489;0.10005;,
 -1.29190;-20.19258;0.02066;,
 -1.90691;-0.59489;-1.83344;,
 -0.91092;-20.19258;-0.89911;,
 0.02658;-0.59489;-2.63431;,
 -1.90691;-0.59489;-1.83344;,
 0.02658;1.87736;0.10005;,
 1.96007;-0.59489;-1.83344;,
 2.76095;-0.59489;0.10005;,
 1.96007;-0.59489;2.03355;,
 0.02658;-0.59489;2.83442;,
 -1.90691;-0.59489;2.03355;,
 -2.70779;-0.59489;0.10005;,
 -0.91092;-20.19258;-0.89911;,
 0.00885;-20.19257;-1.28009;,
 0.00885;-21.18989;0.02066;,
 0.92863;-20.19258;-0.89911;,
 1.30961;-20.19257;0.02066;,
 0.92863;-20.19258;0.94044;,
 0.00885;-20.19258;1.32142;,
 -0.91092;-20.19257;0.94044;,
 -1.29190;-20.19258;0.02066;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,18,20;,
 3;22,21,20;,
 3;23,22,20;,
 3;24,23,20;,
 3;25,24,20;,
 3;26,25,20;,
 3;19,26,20;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;31,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;34,35,29;,
 3;35,27,29;;
 
 MeshMaterialList {
  1;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy.jpg";
   }
  }
 }
 MeshNormals {
  19;
  -0.653134;0.383153;-0.653154;,
  -0.000005;0.383398;-0.923583;,
  0.653297;0.382577;-0.653328;,
  0.924506;0.381168;-0.000025;,
  0.654074;0.379998;0.654056;,
  -0.000006;0.379751;0.925089;,
  -0.653912;0.380574;0.653883;,
  -0.924169;0.381983;-0.000024;,
  -0.619196;-0.482873;-0.619217;,
  -0.000006;-0.482641;-0.875818;,
  0.618981;-0.483413;-0.619011;,
  0.874665;-0.484728;-0.000025;,
  0.618063;-0.485823;0.618041;,
  -0.000009;-0.486051;0.873931;,
  -0.618279;-0.485283;0.618249;,
  -0.875086;-0.483967;-0.000022;,
  0.380882;0.842530;-0.380883;,
  -0.000001;-1.000000;-0.000002;,
  -0.380882;0.842530;0.380882;;
  24;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  3;1,0,16;,
  3;2,1,16;,
  3;3,2,16;,
  3;4,3,16;,
  3;5,4,18;,
  3;6,5,18;,
  3;7,6,18;,
  3;0,7,18;,
  3;8,9,17;,
  3;9,10,17;,
  3;10,11,17;,
  3;11,12,17;,
  3;12,13,17;,
  3;13,14,17;,
  3;14,15,17;,
  3;15,8,17;;
 }
 MeshTextureCoords {
  36;
  0.890722;0.461735;,
  0.894656;0.461735;,
  0.894656;0.414413;,
  0.890722;0.414413;,
  0.898589;0.461735;,
  0.898589;0.414413;,
  0.902523;0.461735;,
  0.902523;0.414413;,
  0.906457;0.461735;,
  0.906457;0.414413;,
  0.910390;0.461735;,
  0.910390;0.414413;,
  0.914324;0.461735;,
  0.914324;0.414413;,
  0.918258;0.461735;,
  0.918258;0.414413;,
  0.922191;0.461735;,
  0.922191;0.414413;,
  0.593569;0.611502;,
  0.612697;0.603579;,
  0.593569;0.585533;,
  0.574441;0.603579;,
  0.566518;0.584451;,
  0.574441;0.565323;,
  0.593569;0.557400;,
  0.612697;0.565323;,
  0.620620;0.584451;,
  0.986055;0.592170;,
  0.965340;0.583589;,
  0.965340;0.614056;,
  0.944625;0.592170;,
  0.936045;0.612885;,
  0.944625;0.633600;,
  0.965340;0.642180;,
  0.986055;0.633600;,
  0.994635;0.612885;;
 }
}