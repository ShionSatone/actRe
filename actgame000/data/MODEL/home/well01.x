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
 120;
 175.65660;-440.58990;180.82970;,
 175.65660;-440.58990;-192.85420;,
 175.65660;-857.83282;-192.85420;,
 175.65660;-857.83282;180.82970;,
 175.65660;-440.58990;-192.85420;,
 196.96490;-440.58990;-192.85420;,
 196.96490;-857.83282;-192.85420;,
 175.65660;-857.83282;-192.85420;,
 196.96490;-440.58990;-192.85420;,
 196.96500;-440.58990;180.82970;,
 196.96500;-857.83282;180.82970;,
 196.96490;-857.83282;-192.85420;,
 196.96500;-440.58990;180.82970;,
 175.65660;-440.58990;180.82970;,
 175.65660;-857.83282;180.82970;,
 196.96500;-857.83282;180.82970;,
 175.65660;-440.58990;-192.85420;,
 175.65660;-440.58990;180.82970;,
 175.65660;-857.83282;180.82970;,
 175.65660;-857.83282;-192.85420;,
 175.65660;-854.68213;180.82970;,
 175.65660;-854.68213;-192.85420;,
 175.65660;-1271.92493;-192.85420;,
 175.65660;-1271.92493;180.82970;,
 175.65660;-854.68213;-192.85420;,
 196.96490;-854.68213;-192.85420;,
 196.96490;-1271.92493;-192.85420;,
 175.65660;-1271.92493;-192.85420;,
 196.96490;-854.68213;-192.85420;,
 196.96500;-854.68213;180.82970;,
 196.96500;-1271.92493;180.82970;,
 196.96490;-1271.92493;-192.85420;,
 196.96500;-854.68213;180.82970;,
 175.65660;-854.68213;180.82970;,
 175.65660;-1271.92493;180.82970;,
 196.96500;-1271.92493;180.82970;,
 175.65660;-854.68213;-192.85420;,
 175.65660;-854.68213;180.82970;,
 175.65660;-1271.92493;180.82970;,
 175.65660;-1271.92493;-192.85420;,
 175.65660;-23.93580;180.82970;,
 175.65660;-23.93580;-192.85420;,
 175.65660;-441.17981;-192.85420;,
 175.65660;-441.17981;180.82970;,
 175.65660;-23.93580;-192.85420;,
 196.96490;-23.93580;-192.85420;,
 196.96490;-441.17981;-192.85420;,
 175.65660;-441.17981;-192.85420;,
 196.96490;-23.93580;-192.85420;,
 196.96500;-23.93580;180.82970;,
 196.96500;-441.17981;180.82970;,
 196.96490;-441.17981;-192.85420;,
 196.96500;-23.93580;180.82970;,
 175.65660;-23.93580;180.82970;,
 175.65660;-441.17981;180.82970;,
 196.96500;-441.17981;180.82970;,
 175.65660;-23.93580;-192.85420;,
 175.65660;-23.93580;180.82970;,
 175.65660;-441.17981;180.82970;,
 175.65660;-441.17981;-192.85420;,
 175.65660;-1687.86316;180.82970;,
 175.65660;-1687.86316;-192.85420;,
 175.65660;-2105.10596;-192.85420;,
 175.65660;-2105.10596;180.82970;,
 175.65660;-1687.86316;-192.85420;,
 196.96490;-1687.86316;-192.85420;,
 196.96490;-2105.10596;-192.85420;,
 175.65660;-2105.10596;-192.85420;,
 196.96490;-1687.86316;-192.85420;,
 196.96500;-1687.86316;180.82970;,
 196.96500;-2105.10596;180.82970;,
 196.96490;-2105.10596;-192.85420;,
 196.96500;-1687.86316;180.82970;,
 175.65660;-1687.86316;180.82970;,
 175.65660;-2105.10596;180.82970;,
 196.96500;-2105.10596;180.82970;,
 175.65660;-1687.86316;-192.85420;,
 175.65660;-1687.86316;180.82970;,
 175.65660;-2105.10596;180.82970;,
 175.65660;-2105.10596;-192.85420;,
 175.65660;-2101.95557;180.82970;,
 175.65660;-2101.95557;-192.85420;,
 175.65660;-2519.19824;-192.85420;,
 175.65660;-2519.19824;180.82970;,
 175.65660;-2101.95557;-192.85420;,
 196.96490;-2101.95557;-192.85420;,
 196.96490;-2519.19824;-192.85420;,
 175.65660;-2519.19824;-192.85420;,
 196.96490;-2101.95557;-192.85420;,
 196.96500;-2101.95557;180.82970;,
 196.96500;-2519.19824;180.82970;,
 196.96490;-2519.19824;-192.85420;,
 196.96500;-2101.95557;180.82970;,
 175.65660;-2101.95557;180.82970;,
 175.65660;-2519.19824;180.82970;,
 196.96500;-2519.19824;180.82970;,
 175.65660;-2101.95557;-192.85420;,
 175.65660;-2101.95557;180.82970;,
 175.65660;-2519.19824;180.82970;,
 175.65660;-2519.19824;-192.85420;,
 175.65660;-1271.20911;180.82970;,
 175.65660;-1271.20911;-192.85420;,
 175.65660;-1688.45300;-192.85420;,
 175.65660;-1688.45300;180.82970;,
 175.65660;-1271.20911;-192.85420;,
 196.96490;-1271.20911;-192.85420;,
 196.96490;-1688.45300;-192.85420;,
 175.65660;-1688.45300;-192.85420;,
 196.96490;-1271.20911;-192.85420;,
 196.96500;-1271.20911;180.82970;,
 196.96500;-1688.45300;180.82970;,
 196.96490;-1688.45300;-192.85420;,
 196.96500;-1271.20911;180.82970;,
 175.65660;-1271.20911;180.82970;,
 175.65660;-1688.45300;180.82970;,
 196.96500;-1688.45300;180.82970;,
 175.65660;-1271.20911;-192.85420;,
 175.65660;-1271.20911;180.82970;,
 175.65660;-1688.45300;180.82970;,
 175.65660;-1688.45300;-192.85420;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;;
 
 MeshMaterialList {
  4;
  36;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\roof.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\wall.jpg";
   }
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\well.jpg";
   }
  }
 }
 MeshNormals {
  6;
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
