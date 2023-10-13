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
 55;
 -3.44000;-7.95592;3.42252;,
 0.02351;-18.07252;4.97200;,
 1.23263;0.02382;5.28526;,
 -3.53628;0.08645;6.79540;,
 3.42998;-7.97646;3.42278;,
 3.76594;0.02449;3.42328;,
 4.41054;-7.93610;-0.02067;,
 4.51530;0.06097;-0.27561;,
 3.42971;-7.88447;-3.44246;,
 3.77777;0.02524;-3.35262;,
 1.39240;-7.85764;-5.37399;,
 1.49058;-0.00480;-5.30577;,
 -3.40245;-7.88316;-4.97261;,
 -3.37651;0.09705;-6.54352;,
 -4.37899;-7.89090;-1.39836;,
 -4.88096;0.54447;-4.03884;,
 -4.65625;-7.90779;-0.02043;,
 -4.28080;-7.93258;1.70939;,
 -4.77775;0.53989;4.68420;,
 -5.20878;0.55992;-0.09815;,
 0.00838;-18.48274;4.90357;,
 -3.42682;-18.45342;3.48158;,
 -0.02028;-8.33042;-0.07842;,
 3.44316;-18.47396;3.48185;,
 4.42374;-18.43360;0.03840;,
 3.44289;-18.38197;-3.38340;,
 1.40575;-18.35514;-5.31493;,
 -3.38927;-18.38066;-4.91353;,
 -4.40764;-18.40455;0.03804;,
 -4.34783;-18.38834;-1.33884;,
 -4.24964;-18.43003;1.76801;,
 -3.53628;0.08645;6.79540;,
 1.23263;0.02382;5.28526;,
 -0.82093;6.45549;-0.16249;,
 3.76594;0.02449;3.42328;,
 4.51530;0.06097;-0.27561;,
 3.77777;0.02524;-3.35262;,
 1.49058;-0.00480;-5.30577;,
 -3.37651;0.09705;-6.54352;,
 -4.88096;0.54447;-4.03884;,
 -5.20878;0.55992;-0.09815;,
 -4.77775;0.53989;4.68420;,
 -3.42682;-18.45342;3.48158;,
 0.00838;-18.48274;4.90357;,
 3.44316;-18.47396;3.48185;,
 4.42374;-18.43360;0.03840;,
 3.44289;-18.38197;-3.38340;,
 1.40575;-18.35514;-5.31493;,
 -3.38927;-18.38066;-4.91353;,
 -4.34783;-18.38834;-1.33884;,
 -4.40764;-18.40455;0.03804;,
 -4.24964;-18.43003;1.76801;,
 -3.42682;-18.45342;3.48158;,
 -3.44000;-7.95592;3.42252;,
 -3.53628;0.08645;6.79540;;
 
 36;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;16,17,18,19;,
 3;20,21,22;,
 3;23,20,22;,
 3;24,23,22;,
 3;25,24,22;,
 3;26,25,22;,
 3;27,26,22;,
 4;28,29,27,22;,
 4;21,30,28,22;,
 3;31,32,33;,
 3;32,34,33;,
 3;34,35,33;,
 3;35,36,33;,
 3;36,37,33;,
 3;37,38,33;,
 4;38,39,40,33;,
 4;40,41,31,33;,
 4;42,43,1,0;,
 4;43,44,4,1;,
 4;44,45,6,4;,
 4;45,46,8,6;,
 4;46,47,10,8;,
 4;47,48,12,10;,
 4;48,49,14,12;,
 4;50,51,17,16;,
 4;14,49,50,16;,
 4;15,14,16,19;,
 4;17,51,52,53;,
 4;18,17,53,54;;
 
 MeshMaterialList {
  1;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  48;
  0.666546;-0.449914;-0.594385;,
  -0.000994;-0.440542;-0.897732;,
  -0.670621;-0.438883;-0.598038;,
  -0.915337;-0.402669;-0.003947;,
  -0.779140;-0.421118;0.464328;,
  -0.294674;-0.475038;0.829160;,
  0.076763;-0.453032;0.888183;,
  0.907194;-0.416893;-0.056566;,
  0.098547;0.270990;0.957524;,
  0.336988;0.312317;0.888199;,
  0.779404;0.348966;0.520338;,
  0.943752;0.330417;-0.012526;,
  0.800297;0.342428;-0.492207;,
  0.402101;0.333490;-0.852701;,
  0.151778;0.306478;-0.939699;,
  -0.942521;0.334126;0.003760;,
  0.629897;0.759194;0.163871;,
  -0.618485;-0.129415;0.775066;,
  0.136710;-0.102677;0.985276;,
  0.787746;-0.037863;0.614835;,
  0.999897;-0.013419;-0.005123;,
  0.854237;-0.011817;-0.519750;,
  0.364066;-0.029886;-0.930893;,
  -0.002262;-0.048547;-0.998818;,
  -0.998942;-0.044804;0.010316;,
  0.903740;-0.405893;0.136036;,
  -0.972167;-0.053135;-0.228182;,
  -0.942573;0.168756;-0.288233;,
  0.876875;-0.412372;-0.247062;,
  -0.950816;-0.073856;0.300822;,
  -0.935298;0.147811;0.321510;,
  -0.944145;-0.061057;-0.323824;,
  -0.884941;0.296472;-0.359143;,
  -0.868065;-0.438033;0.233647;,
  0.199464;0.653025;-0.730598;,
  -0.717491;0.696566;0.001725;,
  -0.873367;0.268403;0.406435;,
  -0.688707;-0.035571;0.724167;,
  0.000454;-0.080112;0.996786;,
  0.749646;-0.043066;0.660436;,
  0.999999;0.001252;-0.000857;,
  0.854810;-0.001843;-0.518938;,
  0.331248;-0.004890;-0.943531;,
  -0.083388;-0.005713;-0.996501;,
  -0.965255;-0.003515;-0.261285;,
  -0.981441;-0.008783;-0.191563;,
  -0.999792;-0.013241;0.015531;,
  -0.954696;-0.005906;0.297523;;
  36;
  4;17,18,9,8;,
  4;18,19,10,9;,
  4;19,20,11,10;,
  4;20,21,12,11;,
  4;21,22,13,12;,
  4;22,23,14,13;,
  4;31,26,27,32;,
  4;24,29,30,15;,
  3;1,0,1;,
  3;2,1,1;,
  3;3,2,33;,
  3;4,3,33;,
  3;5,4,33;,
  3;6,5,6;,
  4;7,25,25,7;,
  4;0,28,7,7;,
  3;8,9,16;,
  3;9,10,16;,
  3;10,11,16;,
  3;11,12,16;,
  3;12,13,16;,
  3;13,14,34;,
  4;32,27,15,35;,
  4;15,30,36,35;,
  4;37,38,18,17;,
  4;38,39,19,18;,
  4;39,40,20,19;,
  4;40,41,21,20;,
  4;41,42,22,21;,
  4;42,43,23,22;,
  4;44,45,26,31;,
  4;46,47,29,24;,
  4;26,45,46,24;,
  4;27,26,24,15;,
  4;29,47,37,17;,
  4;30,29,17,36;;
 }
 MeshTextureCoords {
  55;
  0.231653;0.363762;,
  0.232975;0.363762;,
  0.232975;0.357402;,
  0.231653;0.357402;,
  0.234297;0.363762;,
  0.234297;0.357402;,
  0.235618;0.363762;,
  0.235618;0.357402;,
  0.236940;0.363762;,
  0.236940;0.357402;,
  0.238262;0.363762;,
  0.238262;0.357402;,
  0.239583;0.363762;,
  0.239583;0.357402;,
  0.240376;0.363762;,
  0.240376;0.357402;,
  0.240905;0.363762;,
  0.241566;0.363762;,
  0.241566;0.357402;,
  0.240905;0.357402;,
  0.253106;0.231532;,
  0.271718;0.223822;,
  0.253106;0.206263;,
  0.234493;0.223822;,
  0.226784;0.205210;,
  0.234493;0.186598;,
  0.253106;0.178888;,
  0.271718;0.186598;,
  0.279427;0.205210;,
  0.276344;0.197765;,
  0.275573;0.214516;,
  0.152064;0.046920;,
  0.123948;0.035274;,
  0.123948;0.076627;,
  0.095831;0.046920;,
  0.084185;0.075037;,
  0.095831;0.103153;,
  0.123948;0.114799;,
  0.152064;0.103153;,
  0.159052;0.086283;,
  0.163710;0.075037;,
  0.157887;0.060979;,
  0.231653;0.373302;,
  0.232975;0.373302;,
  0.234297;0.373302;,
  0.235618;0.373302;,
  0.236940;0.373302;,
  0.238262;0.373302;,
  0.239583;0.373302;,
  0.240376;0.373302;,
  0.240905;0.373302;,
  0.241566;0.373302;,
  0.242227;0.373302;,
  0.242227;0.363762;,
  0.242227;0.357402;;
 }
}
