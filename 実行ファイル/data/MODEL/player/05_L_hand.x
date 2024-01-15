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
 79;
 -3.42412;2.66080;0.76843;,
 -4.07812;2.04281;1.42243;,
 -2.65267;2.04281;2.01287;,
 -2.65267;2.66080;1.08797;,
 -1.22723;2.04281;1.42243;,
 -1.88123;2.66080;0.76843;,
 -0.63679;2.04281;-0.00302;,
 -1.56168;2.66080;-0.00302;,
 -1.22723;2.04281;-1.42846;,
 -1.88123;2.66080;-0.77446;,
 -2.65267;2.04281;-2.01890;,
 -2.65267;2.66080;-1.09401;,
 -4.07812;2.04281;-1.42846;,
 -3.42412;2.66080;-0.77446;,
 -4.66856;2.04281;-0.00302;,
 -3.74366;2.66080;-0.00302;,
 -4.07812;2.04281;1.42243;,
 -3.42412;2.66080;0.76843;,
 -4.51511;1.11791;1.85942;,
 -2.65267;1.11791;2.63086;,
 -0.79024;1.11791;1.85942;,
 -0.01879;1.11791;-0.00302;,
 -0.79024;1.11791;-1.86545;,
 -2.65267;1.11791;-2.63690;,
 -4.51511;1.11791;-1.86545;,
 -5.28655;1.11791;-0.00302;,
 -4.51511;1.11791;1.85942;,
 -4.66856;0.02692;2.01287;,
 -2.65267;0.02692;2.84787;,
 -0.63679;0.02692;2.01287;,
 0.19822;0.02692;-0.00302;,
 -0.63679;0.02692;-2.01890;,
 -2.65267;0.02692;-2.85391;,
 -4.66856;0.02692;-2.01890;,
 -5.50356;0.02692;-0.00302;,
 -4.66856;0.02692;2.01287;,
 -4.51511;-1.06407;1.85942;,
 -2.65267;-1.06407;2.63086;,
 -0.79024;-1.06407;1.85942;,
 -0.01879;-1.06407;-0.00302;,
 -0.79024;-1.06407;-1.86545;,
 -2.65267;-1.06407;-2.63690;,
 -4.51511;-1.06407;-1.86545;,
 -5.28655;-1.06407;-0.00302;,
 -4.51511;-1.06407;1.85942;,
 -4.07812;-1.98896;1.42243;,
 -2.65267;-1.98896;2.01287;,
 -1.22723;-1.98896;1.42243;,
 -0.63679;-1.98896;-0.00302;,
 -1.22723;-1.98896;-1.42846;,
 -2.65267;-1.98896;-2.01890;,
 -4.07812;-1.98896;-1.42846;,
 -4.66856;-1.98896;-0.00302;,
 -4.07812;-1.98896;1.42243;,
 -3.42412;-2.60696;0.76843;,
 -2.65267;-2.60696;1.08797;,
 -1.88123;-2.60696;0.76843;,
 -1.56168;-2.60696;-0.00302;,
 -1.88123;-2.60696;-0.77446;,
 -2.65267;-2.60696;-1.09401;,
 -3.42412;-2.60696;-0.77446;,
 -3.74366;-2.60696;-0.00302;,
 -3.42412;-2.60696;0.76843;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;2.87781;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;,
 -2.65267;-2.82397;-0.00302;;
 
 64;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;1,18,19,2;,
 4;2,19,20,4;,
 4;4,20,21,6;,
 4;6,21,22,8;,
 4;8,22,23,10;,
 4;10,23,24,12;,
 4;12,24,25,14;,
 4;14,25,26,16;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;25,34,35,26;,
 4;27,36,37,28;,
 4;28,37,38,29;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;34,43,44,35;,
 4;36,45,46,37;,
 4;37,46,47,38;,
 4;38,47,48,39;,
 4;39,48,49,40;,
 4;40,49,50,41;,
 4;41,50,51,42;,
 4;42,51,52,43;,
 4;43,52,53,44;,
 4;45,54,55,46;,
 4;46,55,56,47;,
 4;47,56,57,48;,
 4;48,57,58,49;,
 4;49,58,59,50;,
 4;50,59,60,51;,
 4;51,60,61,52;,
 4;52,61,62,53;,
 3;3,63,0;,
 3;5,64,3;,
 3;7,65,5;,
 3;9,66,7;,
 3;11,67,9;,
 3;13,68,11;,
 3;15,69,13;,
 3;17,70,15;,
 3;54,71,55;,
 3;55,72,56;,
 3;56,73,57;,
 3;57,74,58;,
 3;58,75,59;,
 3;59,76,60;,
 3;60,77,61;,
 3;61,78,62;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\meteor.jpg";
   }
  }
 }
 MeshNormals {
  58;
  -0.269130;0.924737;0.269130;,
  0.000001;0.924737;0.380608;,
  0.269131;0.924736;0.269131;,
  0.380609;0.924736;-0.000001;,
  0.269132;0.924736;-0.269132;,
  0.000001;0.924736;-0.380608;,
  -0.269131;0.924736;-0.269131;,
  -0.380608;0.924737;-0.000001;,
  -0.498493;0.709231;0.498493;,
  0.000001;0.709231;0.704976;,
  0.498493;0.709231;0.498494;,
  0.704975;0.709232;-0.000001;,
  0.498493;0.709231;-0.498493;,
  0.000001;0.709232;-0.704975;,
  -0.498494;0.709231;-0.498493;,
  -0.704976;0.709231;-0.000001;,
  -0.652733;0.384549;0.652734;,
  0.000001;0.384548;0.923105;,
  0.652733;0.384550;0.652734;,
  0.923104;0.384551;-0.000001;,
  0.652733;0.384550;-0.652733;,
  0.000001;0.384551;-0.923104;,
  -0.652734;0.384550;-0.652733;,
  -0.923105;0.384549;-0.000001;,
  -0.707107;0.000000;0.707107;,
  0.000001;0.000000;1.000000;,
  0.707106;0.000000;0.707108;,
  1.000000;-0.000000;-0.000001;,
  0.707107;0.000000;-0.707107;,
  0.000001;0.000000;-1.000000;,
  -0.707108;-0.000000;-0.707106;,
  -1.000000;0.000000;-0.000001;,
  -0.652733;-0.384551;0.652733;,
  0.000001;-0.384551;0.923104;,
  0.652732;-0.384552;0.652733;,
  0.923103;-0.384553;-0.000001;,
  0.652732;-0.384553;-0.652732;,
  0.000001;-0.384553;-0.923103;,
  -0.652733;-0.384552;-0.652732;,
  -0.923104;-0.384551;-0.000001;,
  -0.498494;-0.709230;0.498494;,
  0.000001;-0.709230;0.704977;,
  0.498494;-0.709230;0.498494;,
  0.704976;-0.709231;-0.000001;,
  0.498494;-0.709230;-0.498494;,
  0.000001;-0.709231;-0.704976;,
  -0.498494;-0.709230;-0.498494;,
  -0.704977;-0.709230;-0.000001;,
  -0.269132;-0.924736;0.269132;,
  0.000001;-0.924735;0.380611;,
  0.269133;-0.924735;0.269134;,
  0.380612;-0.924735;-0.000001;,
  0.269134;-0.924734;-0.269135;,
  0.000001;-0.924735;-0.380612;,
  -0.269134;-0.924735;-0.269133;,
  -0.380611;-0.924735;-0.000001;,
  0.000000;1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;;
  64;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,16,8;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,24,16;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,40,32;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,48,40;,
  3;1,56,0;,
  3;2,56,1;,
  3;3,56,2;,
  3;4,56,3;,
  3;5,56,4;,
  3;6,56,5;,
  3;7,56,6;,
  3;0,56,7;,
  3;48,57,49;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,48;;
 }
 MeshTextureCoords {
  79;
  0.877461;0.180049;,
  0.877461;0.169110;,
  0.888401;0.169110;,
  0.888401;0.180049;,
  0.899340;0.169110;,
  0.899340;0.180049;,
  0.910280;0.169110;,
  0.910280;0.180049;,
  0.921220;0.169110;,
  0.921220;0.180049;,
  0.932160;0.169110;,
  0.932160;0.180049;,
  0.943099;0.169110;,
  0.943099;0.180049;,
  0.954039;0.169110;,
  0.954039;0.180049;,
  0.964979;0.169110;,
  0.964979;0.180049;,
  0.877461;0.158170;,
  0.888401;0.158170;,
  0.899340;0.158170;,
  0.910280;0.158170;,
  0.921220;0.158170;,
  0.932160;0.158170;,
  0.943099;0.158170;,
  0.954039;0.158170;,
  0.964979;0.158170;,
  0.877461;0.147230;,
  0.888401;0.147230;,
  0.899340;0.147230;,
  0.910280;0.147230;,
  0.921220;0.147230;,
  0.932160;0.147230;,
  0.943099;0.147230;,
  0.954039;0.147230;,
  0.964979;0.147230;,
  0.877461;0.136290;,
  0.888401;0.136290;,
  0.899340;0.136290;,
  0.910280;0.136290;,
  0.921220;0.136290;,
  0.932160;0.136290;,
  0.943099;0.136290;,
  0.954039;0.136290;,
  0.964979;0.136290;,
  0.877461;0.125351;,
  0.888401;0.125351;,
  0.899340;0.125351;,
  0.910280;0.125351;,
  0.921220;0.125351;,
  0.932160;0.125351;,
  0.943099;0.125351;,
  0.954039;0.125351;,
  0.964979;0.125351;,
  0.877461;0.114411;,
  0.888401;0.114411;,
  0.899340;0.114411;,
  0.910280;0.114411;,
  0.921220;0.114411;,
  0.932160;0.114411;,
  0.943099;0.114411;,
  0.954039;0.114411;,
  0.964979;0.114411;,
  0.882931;0.190989;,
  0.893871;0.190989;,
  0.904810;0.190989;,
  0.915750;0.190989;,
  0.926690;0.190989;,
  0.937629;0.190989;,
  0.948569;0.190989;,
  0.959509;0.190989;,
  0.882931;0.103471;,
  0.893871;0.103471;,
  0.904810;0.103471;,
  0.915750;0.103471;,
  0.926690;0.103471;,
  0.937629;0.103471;,
  0.948569;0.103471;,
  0.959509;0.103471;;
 }
}
