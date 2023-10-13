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
 50;
 22.11180;-3.50820;-43.89740;,
 22.11180;-0.82060;-43.89740;,
 24.18670;5.25970;-31.14530;,
 24.18670;-3.40780;-31.14530;,
 20.23560;6.94680;-18.32170;,
 20.23560;-3.40780;-18.32170;,
 10.81490;3.94290;-7.84920;,
 10.81490;-3.40780;-7.84920;,
 1.01940;1.40930;0.65520;,
 1.01940;-1.57680;0.65520;,
 21.49580;-0.39920;-43.96470;,
 21.85710;8.02500;-31.39980;,
 18.03420;9.71210;-19.12530;,
 8.84380;6.70820;-9.11680;,
 0.57850;1.40930;0.37160;,
 20.87980;-0.39920;-44.03210;,
 19.52740;8.02500;-31.65430;,
 15.83280;9.71210;-19.92900;,
 6.87270;8.27820;-10.38450;,
 0.13760;1.40930;0.08810;,
 20.26380;-0.39920;-44.09940;,
 17.19780;8.02500;-31.90890;,
 13.63140;9.71210;-20.73270;,
 4.90160;8.27820;-11.65210;,
 -0.30330;1.40930;-0.19550;,
 19.64780;-1.09960;-44.16670;,
 14.86810;8.02500;-32.16340;,
 11.43000;9.71210;-21.53640;,
 2.93060;8.27820;-12.91980;,
 -0.74420;1.40930;-0.47910;,
 19.64780;-3.21410;-44.16670;,
 14.86810;-6.75860;-32.16340;,
 11.43000;-6.75860;-21.53640;,
 2.93060;-6.75860;-12.91980;,
 -0.74420;-1.57680;-0.47910;,
 20.26380;-3.92910;-44.09940;,
 17.19780;-6.75860;-31.90890;,
 13.63140;-6.75860;-20.73270;,
 4.90160;-6.75860;-11.65210;,
 -0.30330;-1.57680;-0.19550;,
 20.87980;-3.92910;-44.03210;,
 19.52740;-6.75860;-31.65430;,
 15.83280;-6.75860;-19.92900;,
 6.87270;-6.75860;-10.38450;,
 0.13760;-1.57680;0.08810;,
 21.49580;-3.92910;-43.96470;,
 21.85710;-6.75860;-31.39980;,
 18.03420;-6.75860;-19.12530;,
 8.84380;-6.75860;-9.11680;,
 0.57850;-1.57680;0.37160;;
 
 48;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;2,11,12,4;,
 4;4,12,13,6;,
 4;6,13,14,8;,
 4;10,15,16,11;,
 4;11,16,17,12;,
 4;12,17,18,13;,
 4;13,18,19,14;,
 4;15,20,21,16;,
 4;16,21,22,17;,
 4;17,22,23,18;,
 4;18,23,24,19;,
 4;20,25,26,21;,
 4;21,26,27,22;,
 4;22,27,28,23;,
 4;23,28,29,24;,
 4;25,30,31,26;,
 4;26,31,32,27;,
 4;27,32,33,28;,
 4;28,33,34,29;,
 4;30,35,36,31;,
 4;31,36,37,32;,
 4;32,37,38,33;,
 4;33,38,39,34;,
 4;35,40,41,36;,
 4;36,41,42,37;,
 4;37,42,43,38;,
 4;38,43,44,39;,
 4;40,45,46,41;,
 4;41,46,47,42;,
 4;42,47,48,43;,
 4;43,48,49,44;,
 4;45,0,3,46;,
 4;46,3,5,47;,
 4;47,5,7,48;,
 4;48,7,9,49;,
 4;39,24,29,34;,
 4;44,19,24,39;,
 4;49,14,19,44;,
 4;9,8,14,49;,
 4;30,25,20,35;,
 4;35,20,15,40;,
 4;40,15,10,45;,
 4;45,10,1,0;;
 
 MeshMaterialList {
  1;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\frag.jpg";
   }
  }
 }
 MeshNormals {
  63;
  0.911467;-0.372026;-0.175567;,
  0.937192;-0.343980;0.057862;,
  0.828663;-0.300861;0.472018;,
  0.600924;-0.379689;0.703368;,
  0.465073;-0.467155;0.751980;,
  0.880897;0.352921;-0.315384;,
  0.931415;0.361854;-0.039102;,
  0.809054;0.343514;0.476896;,
  0.560575;0.401589;0.724212;,
  0.655589;0.000000;0.755118;,
  0.265504;0.430048;-0.862882;,
  0.412952;0.870258;-0.268556;,
  0.392755;0.877653;0.274715;,
  0.187185;0.828577;0.527658;,
  0.045439;0.842437;0.536875;,
  0.095990;0.468848;-0.878048;,
  0.047309;0.933962;-0.354227;,
  0.039405;0.998064;0.048118;,
  -0.049827;0.933365;0.355453;,
  -0.144304;0.870128;0.471226;,
  0.005106;0.440190;-0.897890;,
  -0.034880;0.923085;-0.383011;,
  -0.010000;0.999813;-0.016545;,
  -0.159907;0.951968;0.261127;,
  -0.261300;0.875599;0.406261;,
  -0.084624;0.407806;-0.909138;,
  -0.119269;0.905140;-0.408040;,
  -0.010174;0.999803;-0.017069;,
  -0.160439;0.951580;0.262212;,
  -0.261307;0.875598;0.406259;,
  -0.929053;0.000000;-0.369948;,
  -0.940762;0.000000;-0.339067;,
  -0.854752;0.000000;-0.519037;,
  -0.861345;0.000000;-0.508020;,
  -0.959036;0.000000;-0.283285;,
  -0.175187;-0.944189;-0.278958;,
  -0.087851;-0.986262;-0.139889;,
  0.000000;-1.000000;-0.000000;,
  -0.105976;-0.980622;0.164769;,
  -0.207845;-0.923241;0.323152;,
  0.024077;-0.975139;-0.220283;,
  0.012114;-0.993765;-0.110832;,
  -0.105968;-0.980623;0.164772;,
  -0.207829;-0.923242;0.323159;,
  0.392004;-0.896271;-0.207442;,
  0.423484;-0.905029;-0.039791;,
  0.398127;-0.888522;0.228088;,
  0.154842;-0.905283;0.395584;,
  -0.026488;-0.891788;0.451678;,
  0.115375;0.831571;0.543303;,
  -0.366718;-0.871595;-0.325330;,
  -0.189545;-0.967366;-0.168152;,
  -0.105980;-0.980622;0.164768;,
  -0.207852;-0.923239;0.323151;,
  -0.540979;0.000000;0.841036;,
  -0.540979;0.000000;0.841036;,
  -0.540912;0.000000;0.841079;,
  -0.540912;0.000000;0.841079;,
  -0.540979;0.000000;0.841036;,
  0.108605;0.000000;-0.994085;,
  0.108605;0.000000;-0.994085;,
  0.108687;0.000000;-0.994076;,
  0.108605;0.000000;-0.994085;;
  48;
  4;0,5,6,1;,
  4;1,6,7,2;,
  4;2,7,8,3;,
  4;3,8,9,4;,
  4;5,10,11,6;,
  4;6,11,12,7;,
  4;7,12,13,8;,
  4;8,13,14,49;,
  4;10,15,16,11;,
  4;11,16,17,12;,
  4;12,17,18,13;,
  4;13,18,19,14;,
  4;15,20,21,16;,
  4;16,21,22,17;,
  4;17,22,23,18;,
  4;18,23,24,19;,
  4;20,25,26,21;,
  4;21,26,27,22;,
  4;22,27,28,23;,
  4;23,28,29,24;,
  4;30,30,31,31;,
  4;31,31,32,32;,
  4;32,32,33,33;,
  4;33,33,34,34;,
  4;50,35,36,51;,
  4;51,36,37,37;,
  4;37,37,38,52;,
  4;52,38,39,53;,
  4;35,40,41,36;,
  4;36,41,37,37;,
  4;37,37,42,38;,
  4;38,42,43,39;,
  4;40,44,45,41;,
  4;41,45,46,37;,
  4;37,46,47,42;,
  4;42,47,48,43;,
  4;44,0,1,45;,
  4;45,1,2,46;,
  4;46,2,3,47;,
  4;47,3,4,48;,
  4;54,54,55,55;,
  4;56,56,54,54;,
  4;57,57,56,56;,
  4;58,58,57,57;,
  4;59,25,20,60;,
  4;60,20,15,61;,
  4;61,15,10,61;,
  4;61,10,62,62;;
 }
 MeshTextureCoords {
  50;
  0.955056;0.174430;,
  0.955056;0.147985;,
  0.961182;0.088161;,
  0.961182;0.173441;,
  0.949517;0.071561;,
  0.949517;0.173441;,
  0.921707;0.101117;,
  0.921707;0.173441;,
  0.892789;0.126045;,
  0.892789;0.155426;,
  0.953238;0.143839;,
  0.954305;0.060952;,
  0.943019;0.044352;,
  0.915888;0.073908;,
  0.891488;0.126045;,
  0.951419;0.143839;,
  0.947427;0.060952;,
  0.936520;0.044352;,
  0.910069;0.058460;,
  0.890186;0.126045;,
  0.949601;0.143839;,
  0.940550;0.060952;,
  0.930021;0.044352;,
  0.904250;0.058460;,
  0.888885;0.126045;,
  0.947782;0.150731;,
  0.933672;0.060952;,
  0.923522;0.044352;,
  0.898431;0.058460;,
  0.887583;0.126045;,
  0.947782;0.171536;,
  0.933672;0.206411;,
  0.923522;0.206411;,
  0.898431;0.206411;,
  0.887583;0.155426;,
  0.949601;0.178571;,
  0.940550;0.206411;,
  0.930021;0.206411;,
  0.904250;0.206411;,
  0.888885;0.155426;,
  0.951419;0.178571;,
  0.947427;0.206411;,
  0.936520;0.206411;,
  0.910069;0.206411;,
  0.890186;0.155426;,
  0.953238;0.178571;,
  0.954305;0.206411;,
  0.943019;0.206411;,
  0.915888;0.206411;,
  0.891488;0.155426;;
 }
}