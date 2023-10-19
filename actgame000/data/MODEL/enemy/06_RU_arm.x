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
 12.06688;-2.25516;2.41119;,
 12.06688;0.15603;3.40994;,
 -0.12210;0.15765;2.38435;,
 -0.12210;-1.52834;1.68599;,
 12.06688;2.56721;2.41119;,
 -0.12210;1.84364;1.68599;,
 12.06688;3.56596;0.00000;,
 -0.12210;2.54200;0.00000;,
 12.06688;2.56721;-2.41119;,
 -0.12210;1.84364;-1.68599;,
 12.06688;0.15603;-3.40994;,
 -0.12210;0.15765;-2.38435;,
 12.06688;-2.25516;-2.41119;,
 -0.12210;-1.52834;-1.68599;,
 12.06688;-3.25392;-0.00000;,
 -0.12210;-2.22670;0.00000;,
 12.06688;-2.25516;2.41119;,
 -0.12210;-1.52834;1.68599;,
 12.06688;0.15603;3.40994;,
 12.06688;-2.25516;2.41119;,
 13.95118;0.15766;0.00000;,
 12.06688;2.56721;2.41119;,
 12.06688;3.56596;0.00000;,
 12.06688;2.56721;-2.41119;,
 12.06688;0.15603;-3.40994;,
 12.06688;-2.25516;-2.41119;,
 12.06688;-3.25392;-0.00000;,
 -0.12210;-1.52834;1.68599;,
 -0.12210;0.15765;2.38435;,
 -1.71287;0.15765;0.00000;,
 -0.12210;1.84364;1.68599;,
 -0.12210;2.54200;0.00000;,
 -0.12210;1.84364;-1.68599;,
 -0.12210;0.15765;-2.38435;,
 -0.12210;-1.52834;-1.68599;,
 -0.12210;-2.22670;0.00000;;
 
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
  26;
  -0.083937;-0.704610;0.704613;,
  -0.083844;0.000002;0.996479;,
  -0.083751;0.704624;0.704621;,
  -0.083712;0.996490;0.000000;,
  -0.083751;0.704624;-0.704621;,
  -0.083844;0.000002;-0.996479;,
  -0.083937;-0.704610;-0.704613;,
  -0.083976;-0.996468;0.000000;,
  -0.519264;-0.604303;0.604304;,
  -0.519226;0.000001;0.854637;,
  -0.519187;0.604337;0.604336;,
  -0.519171;0.854670;0.000000;,
  -0.519187;0.604337;-0.604336;,
  -0.519226;0.000001;-0.854637;,
  -0.519264;-0.604303;-0.604304;,
  -0.519280;-0.854604;0.000000;,
  1.000000;0.000115;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.875257;0.000030;0.483658;,
  0.875326;-0.341894;0.341925;,
  0.875187;0.342102;0.342072;,
  0.875158;0.483836;0.000000;,
  0.875187;0.342102;-0.342072;,
  0.875257;0.000030;-0.483658;,
  0.875326;-0.341894;-0.341925;,
  0.875355;-0.483480;-0.000000;;
  24;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  3;18,19,16;,
  3;20,18,16;,
  3;21,20,16;,
  3;22,21,16;,
  3;23,22,16;,
  3;24,23,16;,
  3;25,24,16;,
  3;19,25,16;,
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
  0.278212;0.712591;,
  0.282884;0.712591;,
  0.282884;0.656388;,
  0.278212;0.656388;,
  0.287555;0.712591;,
  0.287555;0.656388;,
  0.292227;0.712591;,
  0.292227;0.656388;,
  0.296899;0.712591;,
  0.296899;0.656388;,
  0.301571;0.712591;,
  0.301571;0.656388;,
  0.306243;0.712591;,
  0.306243;0.656388;,
  0.310915;0.712591;,
  0.310915;0.656388;,
  0.315587;0.712591;,
  0.315587;0.656388;,
  0.396386;0.808413;,
  0.425955;0.796165;,
  0.396386;0.768269;,
  0.366817;0.796165;,
  0.354570;0.766596;,
  0.366817;0.737028;,
  0.396386;0.724780;,
  0.425955;0.737028;,
  0.438203;0.766596;,
  0.436280;0.563531;,
  0.411887;0.553427;,
  0.411887;0.589304;,
  0.387494;0.563531;,
  0.377390;0.587925;,
  0.387494;0.612318;,
  0.411887;0.622422;,
  0.436280;0.612318;,
  0.446384;0.587925;;
 }
}