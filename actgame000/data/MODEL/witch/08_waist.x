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
 177;
 -17.11184;-53.15428;-0.23096;,
 -8.07178;-58.26846;6.37191;,
 -1.36402;-7.42238;4.49119;,
 -5.14710;-5.18360;1.50852;,
 9.08527;-52.53039;-15.48512;,
 0.04519;-47.41617;-22.08801;,
 1.69758;-3.32905;-6.24346;,
 5.35162;-5.52335;-3.29151;,
 -11.37231;-45.48057;-20.35511;,
 -3.19766;-2.57722;-5.32668;,
 -18.47902;-47.85734;-11.30165;,
 -6.36610;-3.48041;-1.63870;,
 -17.11184;-53.15428;-0.23096;,
 -5.14710;-5.18360;1.50852;,
 -8.07178;-58.26846;6.37191;,
 -17.11184;-53.15428;-0.23096;,
 -1.62510;-24.44710;-3.20964;,
 0.04519;-47.41617;-22.08801;,
 9.08527;-52.53039;-15.48512;,
 -11.37231;-45.48057;-20.35511;,
 -18.47902;-47.85734;-11.30165;,
 -5.14710;-5.18360;1.50852;,
 -1.36402;-7.42238;4.49119;,
 0.76804;4.00706;1.44841;,
 3.40217;-8.12974;3.54369;,
 6.14724;-7.79259;1.34013;,
 5.35162;-5.52335;-3.29151;,
 1.69758;-3.32905;-6.24346;,
 -3.19766;-2.57722;-5.32668;,
 -6.36610;-3.48041;-1.63870;,
 13.54444;-55.89864;5.84462;,
 20.45876;-50.01858;-2.94089;,
 6.45436;-4.59331;1.70425;,
 3.78410;-6.30405;3.75792;,
 18.82284;-45.79660;-14.28370;,
 5.55610;-2.91270;-2.99933;,
 9.59508;-45.70586;-21.53938;,
 1.86283;-2.75957;-6.18263;,
 -1.81910;-49.79957;-20.45756;,
 -2.97008;-4.56613;-5.54945;,
 -8.73342;-55.67964;-11.67205;,
 -6.02517;-7.01338;-2.02828;,
 20.45876;-50.01858;-2.94089;,
 13.54444;-55.89864;5.84462;,
 2.50175;-24.52406;-2.99453;,
 18.82284;-45.79660;-14.28370;,
 9.59508;-45.70586;-21.53938;,
 -1.81910;-49.79957;-20.45756;,
 -8.73342;-55.67964;-11.67205;,
 -4.74208;-7.95747;1.20781;,
 -0.92010;-8.08565;4.42960;,
 -0.86458;3.84655;1.32434;,
 3.78410;-6.30405;3.75792;,
 6.45436;-4.59331;1.70425;,
 5.55610;-2.91270;-2.99933;,
 1.86283;-2.75957;-6.18263;,
 -2.97008;-4.56613;-5.54945;,
 -6.02517;-7.01338;-2.02828;,
 -12.87215;-45.95548;17.81810;,
 -1.24009;-47.62580;21.24635;,
 1.42011;-3.32250;4.81447;,
 -3.31091;-2.70322;3.23850;,
 9.20819;-52.01674;15.58786;,
 5.49009;-5.11918;2.34955;,
 12.35224;-56.55611;4.15739;,
 7.16809;-6.51211;-0.63817;,
 -5.28185;-56.91445;-9.77753;,
 -15.73014;-52.52351;-4.11904;,
 -4.23676;-4.83097;-3.86814;,
 -0.03392;-6.66412;-6.34648;,
 -18.87419;-47.98415;7.31143;,
 -5.71369;-2.97594;0.66296;,
 -12.87215;-45.95548;17.81810;,
 -3.31091;-2.70322;3.23850;,
 -1.24009;-47.62580;21.24635;,
 -12.87215;-45.95548;17.81810;,
 -0.83466;-23.84102;2.30629;,
 9.20819;-52.01674;15.58786;,
 12.35224;-56.55611;4.15739;,
 -18.87419;-47.98415;7.31143;,
 -15.73014;-52.52351;-4.11904;,
 -3.31091;-2.70322;3.23850;,
 1.42011;-3.32250;4.81447;,
 1.63132;5.05293;-1.17788;,
 5.49009;-5.11918;2.34955;,
 7.16809;-6.51211;-0.63817;,
 4.56425;-7.24694;-4.75709;,
 -0.03392;-6.66412;-6.34648;,
 -4.23676;-4.83097;-3.86814;,
 -5.71369;-2.97594;0.66296;,
 -18.07282;-45.40167;11.37442;,
 -7.04662;-50.10667;16.08590;,
 -0.16762;-5.16887;4.92712;,
 -4.57559;-3.28793;2.85009;,
 3.97960;-54.81168;11.37442;,
 4.10925;-6.99385;2.85009;,
 -7.04662;-50.10667;-16.08591;,
 -18.07286;-45.40163;-11.37443;,
 -4.57559;-3.28793;-4.43145;,
 -0.16762;-5.16887;-6.50849;,
 -22.64009;-43.45274;0.00000;,
 -6.58905;-2.42877;0.00000;,
 -18.07282;-45.40167;11.37442;,
 -4.57559;-3.28793;2.85009;,
 -7.04662;-50.10667;16.08590;,
 -18.07282;-45.40167;11.37442;,
 -3.08082;-24.19964;0.00000;,
 3.97960;-54.81168;11.37442;,
 -18.07286;-45.40163;-11.37443;,
 -7.04662;-50.10667;-16.08591;,
 -22.64009;-43.45274;0.00000;,
 -4.57559;-3.28793;2.85009;,
 -0.16762;-5.16887;4.92712;,
 1.33110;4.62165;0.00000;,
 4.10925;-6.99385;2.85009;,
 6.12271;-7.85301;-0.00000;,
 4.10925;-6.99385;-4.43145;,
 -0.16762;-5.16887;-6.50849;,
 -4.57559;-3.28793;-4.43145;,
 -6.58905;-2.42877;0.00000;,
 -3.39676;-46.54513;20.08378;,
 8.11335;-44.18328;21.07199;,
 2.32709;-2.41423;4.49723;,
 -2.59037;-3.49640;3.90060;,
 17.18034;-45.69103;13.81525;,
 5.97663;-3.14081;1.29078;,
 18.49294;-50.18511;2.56455;,
 7.18157;-4.29566;-1.95059;,
 -9.29502;-55.88705;0.17894;,
 -10.60760;-51.39299;11.42963;,
 -5.35771;-4.81614;1.86933;,
 -4.58621;-6.65750;-2.83478;,
 -3.39676;-46.54513;20.08378;,
 -2.59037;-3.49640;3.90060;,
 8.11335;-44.18328;21.07199;,
 -3.39676;-46.54513;20.08378;,
 2.19294;-23.51388;2.83382;,
 17.18034;-45.69103;13.81525;,
 18.49294;-50.18511;2.56455;,
 -10.60760;-51.39299;11.42963;,
 -9.29502;-55.88705;0.17894;,
 -2.59037;-3.49640;3.90060;,
 2.32709;-2.41423;4.49723;,
 0.35084;5.20121;-1.54924;,
 5.97663;-3.14081;1.29078;,
 7.18157;-4.29566;-1.95059;,
 3.98079;-6.30192;-5.44460;,
 -0.80735;-7.37872;-6.08064;,
 -4.58621;-6.65750;-2.83478;,
 -5.35771;-4.81614;1.86933;,
 -3.14801;-54.73809;10.92422;,
 7.38505;-50.01077;15.44922;,
 -0.05663;-5.14016;4.92712;,
 -4.44100;-7.10790;2.85009;,
 17.91814;-45.28343;10.92422;,
 4.19733;-3.23094;2.85009;,
 22.28113;-43.32527;-0.00000;,
 6.20000;-2.33212;-0.00000;,
 17.91814;-45.28343;-10.92421;,
 4.19733;-3.23094;-4.43145;,
 7.38505;-50.01077;-15.44922;,
 -0.05663;-5.14016;-6.50849;,
 7.38505;-50.01077;15.44922;,
 -3.14801;-54.73809;10.92422;,
 3.08965;-24.11111;-0.00000;,
 17.91814;-45.28343;10.92422;,
 22.28113;-43.32527;-0.00000;,
 17.91814;-45.28343;-10.92421;,
 -4.44100;-7.10790;2.85009;,
 -0.05663;-5.14016;4.92712;,
 -1.67527;4.61957;0.00000;,
 4.19733;-3.23094;2.85009;,
 6.20000;-2.33212;-0.00000;,
 4.19733;-3.23094;-4.43145;,
 -0.05663;-5.14016;-6.50849;,
 -4.44100;-7.10790;-4.43145;,
 -6.44368;-8.00672;0.00000;;
 
 108;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;14,15,16;,
 3;17,18,16;,
 3;19,17,16;,
 3;20,19,16;,
 3;15,20,16;,
 3;21,22,23;,
 3;22,24,23;,
 3;24,25,23;,
 3;25,26,23;,
 3;26,27,23;,
 3;27,28,23;,
 3;28,29,23;,
 3;29,21,23;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 3;42,43,44;,
 3;45,42,44;,
 3;46,45,44;,
 3;47,46,44;,
 3;48,47,44;,
 3;49,50,51;,
 3;50,52,51;,
 3;52,53,51;,
 3;53,54,51;,
 3;54,55,51;,
 3;55,56,51;,
 3;56,57,51;,
 3;57,49,51;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 3;74,75,76;,
 3;77,74,76;,
 3;78,77,76;,
 3;79,80,76;,
 3;75,79,76;,
 3;81,82,83;,
 3;82,84,83;,
 3;84,85,83;,
 3;85,86,83;,
 3;86,87,83;,
 3;87,88,83;,
 3;88,89,83;,
 3;89,81,83;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;96,97,98,99;,
 4;97,100,101,98;,
 4;100,102,103,101;,
 3;104,105,106;,
 3;107,104,106;,
 3;108,109,106;,
 3;110,108,106;,
 3;105,110,106;,
 3;111,112,113;,
 3;112,114,113;,
 3;114,115,113;,
 3;115,116,113;,
 3;116,117,113;,
 3;117,118,113;,
 3;118,119,113;,
 3;119,111,113;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 3;134,135,136;,
 3;137,134,136;,
 3;138,137,136;,
 3;139,140,136;,
 3;135,139,136;,
 3;141,142,143;,
 3;142,144,143;,
 3;144,145,143;,
 3;145,146,143;,
 3;146,147,143;,
 3;147,148,143;,
 3;148,149,143;,
 3;149,141,143;,
 4;150,151,152,153;,
 4;151,154,155,152;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 3;162,163,164;,
 3;165,162,164;,
 3;166,165,164;,
 3;167,166,164;,
 3;168,169,170;,
 3;169,171,170;,
 3;171,172,170;,
 3;172,173,170;,
 3;173,174,170;,
 3;174,175,170;,
 3;175,176,170;,
 3;176,168,170;;
 
 MeshMaterialList {
  1;
  108;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\witch.jpg";
   }
  }
 }
 MeshNormals {
  140;
  -0.781086;0.157021;0.604358;,
  -0.560525;0.108240;0.821034;,
  0.673630;0.229837;-0.702423;,
  0.312885;0.314541;-0.896196;,
  -0.471665;0.367894;-0.801365;,
  -0.947996;0.294079;-0.121744;,
  -0.700107;0.280438;0.656662;,
  -0.289727;0.224832;0.930327;,
  0.411610;0.241066;0.878900;,
  0.816245;0.368022;0.445313;,
  0.813120;0.428747;-0.393716;,
  0.350742;0.520403;-0.778563;,
  -0.413640;0.586834;-0.696081;,
  -0.870043;0.492873;-0.010029;,
  0.662091;-0.421478;-0.619670;,
  -0.113151;0.372263;0.921204;,
  0.646586;0.131489;0.751424;,
  0.888069;0.242226;0.390717;,
  0.836350;0.361897;-0.411764;,
  0.211407;0.365044;-0.906670;,
  -0.549225;0.245428;-0.798822;,
  -0.811972;0.161749;-0.560838;,
  -0.761224;0.244123;0.600785;,
  -0.312579;0.240595;0.918917;,
  0.377538;0.265766;0.887037;,
  0.781006;0.418913;0.463186;,
  0.757347;0.569376;-0.319744;,
  0.143352;0.581827;-0.800580;,
  -0.584487;0.431740;-0.687004;,
  -0.920328;0.345853;-0.182705;,
  -0.736469;-0.519642;-0.433112;,
  -0.313685;0.332009;0.889591;,
  -0.538876;0.368072;0.757717;,
  0.178765;0.336421;0.924589;,
  0.785848;0.217933;0.578747;,
  0.935429;0.155197;0.317627;,
  -0.452346;0.111848;-0.884801;,
  -0.726616;0.174530;-0.664506;,
  -0.946100;0.310436;0.092329;,
  -0.476059;0.508498;0.717494;,
  0.203179;0.453906;0.867576;,
  0.773662;0.339044;0.535254;,
  0.940762;0.338414;0.021038;,
  0.576660;0.352041;-0.737245;,
  -0.152604;0.312204;-0.937678;,
  -0.641197;0.346723;-0.684579;,
  -0.861801;0.504180;0.055696;,
  -0.532146;-0.593947;-0.603364;,
  0.488429;0.559942;0.669255;,
  -0.576940;0.317227;0.752666;,
  0.091739;0.230487;0.968741;,
  0.462264;0.148760;0.874175;,
  -0.306960;0.247747;-0.918911;,
  -0.618738;0.312265;-0.720870;,
  -0.927530;0.370518;0.049044;,
  -0.486565;0.442738;0.753152;,
  0.131219;0.328647;0.935293;,
  0.618606;0.268557;0.738379;,
  0.930401;0.357374;0.081469;,
  0.733927;0.388182;-0.557374;,
  0.030371;0.442490;-0.896259;,
  -0.517116;0.496647;-0.697089;,
  -0.817771;0.570897;0.072982;,
  0.108832;-0.625122;-0.772902;,
  0.426090;0.413592;0.804605;,
  -0.476090;0.310446;0.822777;,
  0.257960;0.389434;0.884193;,
  0.839482;0.337564;0.425816;,
  0.952446;0.277766;0.125267;,
  -0.982518;0.078408;-0.168847;,
  -0.949554;0.177870;0.258281;,
  -0.468107;0.451182;0.759810;,
  0.235322;0.520558;0.820758;,
  0.791416;0.477038;0.382224;,
  0.858634;0.475600;-0.191187;,
  0.304955;0.390395;-0.868674;,
  -0.281077;0.348032;-0.894354;,
  -0.858861;0.280810;-0.428372;,
  -0.913101;0.357188;0.196631;,
  -0.190016;-0.679617;-0.708530;,
  0.465861;0.682861;0.562738;,
  -0.456656;0.132470;0.879726;,
  -0.085672;0.218173;0.972142;,
  0.579028;0.313766;0.752514;,
  0.927188;0.371362;0.049112;,
  0.621062;0.308785;-0.720370;,
  0.313054;0.241219;-0.918592;,
  -0.618218;0.260918;0.741437;,
  -0.127084;0.322669;0.937942;,
  0.486990;0.441870;0.753387;,
  0.816433;0.572776;0.073253;,
  0.517311;0.495951;-0.697439;,
  -0.028226;0.440182;-0.897465;,
  -0.735895;0.384220;-0.557524;,
  -0.932440;0.352143;0.080935;,
  0.199206;-0.477440;-0.855785;,
  0.088149;0.529272;0.843861;,
  0.433355;-0.321156;-0.842058;,
  -0.359150;-0.608043;0.708022;,
  -0.677400;-0.495859;0.543371;,
  0.378248;-0.683864;0.623906;,
  0.807153;-0.589805;0.025183;,
  0.686081;-0.623513;0.374866;,
  0.836560;0.506371;-0.209178;,
  -0.331583;0.766163;-0.550497;,
  -0.569068;-0.402331;-0.717141;,
  -0.692589;-0.671370;0.263787;,
  -0.100361;-0.674209;0.731690;,
  0.591801;-0.524233;0.612333;,
  0.830349;-0.405803;0.381896;,
  0.637443;0.740871;-0.211606;,
  -0.591585;0.593730;-0.545446;,
  -0.228610;-0.604049;-0.763454;,
  0.471336;-0.663846;-0.580647;,
  -0.787704;-0.469039;-0.399406;,
  -0.920461;-0.376879;-0.103511;,
  0.805395;-0.590013;0.056776;,
  0.770207;-0.491138;0.406897;,
  0.300020;0.415438;-0.858719;,
  -0.735913;0.676889;0.015953;,
  -0.196563;-0.495313;-0.846184;,
  0.415637;-0.640391;-0.645868;,
  -0.499236;-0.400616;-0.768290;,
  0.415637;-0.640393;0.645866;,
  0.127070;-0.537188;0.833836;,
  0.701507;-0.712663;-0.000002;,
  0.483841;0.499169;-0.718838;,
  -0.662001;0.743665;0.093363;,
  0.524530;-0.588276;-0.615467;,
  -0.747293;-0.621482;-0.235189;,
  -0.847745;-0.519191;0.108485;,
  0.897017;-0.435370;-0.076248;,
  0.907841;-0.342048;0.242545;,
  0.002634;0.405757;-0.913977;,
  -0.842398;0.523559;0.127480;,
  0.503697;-0.379411;-0.776104;,
  -0.418499;-0.630430;-0.653771;,
  -0.707524;-0.706689;0.000000;,
  -0.654810;-0.654037;0.378759;,
  0.082392;0.641931;-0.762323;;
  108;
  4;0,1,7,6;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,0,6,13;,
  3;97,14,14;,
  3;98,99,98;,
  3;100,98,98;,
  3;101,100,102;,
  3;14,101,14;,
  3;6,7,15;,
  3;7,8,15;,
  3;8,9,15;,
  3;9,10,103;,
  3;10,11,103;,
  3;11,12,104;,
  3;12,13,104;,
  3;13,6,15;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  3;30,105,30;,
  3;106,30,30;,
  3;107,106,107;,
  3;108,107,107;,
  3;109,108,109;,
  3;22,23,31;,
  3;23,24,31;,
  3;24,25,31;,
  3;25,26,110;,
  3;26,27,110;,
  3;27,28,111;,
  3;28,29,111;,
  3;29,22,31;,
  4;32,33,40,39;,
  4;33,34,41,40;,
  4;34,35,42,41;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,32,39,46;,
  3;112,113,47;,
  3;114,112,47;,
  3;115,114,47;,
  3;116,117,116;,
  3;113,116,116;,
  3;39,40,48;,
  3;40,41,48;,
  3;41,42,48;,
  3;42,43,118;,
  3;43,44,118;,
  3;44,45,118;,
  3;45,46,119;,
  3;46,39,119;,
  4;49,50,56,55;,
  4;50,51,57,56;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,49,55,62;,
  3;120,121,63;,
  3;122,120,63;,
  3;123,124,123;,
  3;125,123,123;,
  3;121,125,63;,
  3;55,56,64;,
  3;56,57,64;,
  3;57,58,64;,
  3;58,59,126;,
  3;59,60,126;,
  3;60,61,126;,
  3;61,62,127;,
  3;62,55,127;,
  4;65,66,72,71;,
  4;66,67,73,72;,
  4;67,68,74,73;,
  4;69,70,78,77;,
  4;70,65,71,78;,
  3;79,128,79;,
  3;129,79,79;,
  3;130,129,130;,
  3;131,132,131;,
  3;128,131,131;,
  3;71,72,80;,
  3;72,73,80;,
  3;73,74,80;,
  3;74,75,133;,
  3;75,76,133;,
  3;76,77,133;,
  3;77,78,134;,
  3;78,71,134;,
  4;81,82,88,87;,
  4;82,83,89,88;,
  4;83,84,90,89;,
  4;84,85,91,90;,
  4;85,86,92,91;,
  3;95,135,95;,
  3;136,95,95;,
  3;137,136,137;,
  3;138,137,137;,
  3;87,88,96;,
  3;88,89,96;,
  3;89,90,96;,
  3;90,91,139;,
  3;91,92,139;,
  3;92,93,139;,
  3;93,94,94;,
  3;94,87,94;;
 }
 MeshTextureCoords {
  177;
  0.112930;0.973330;,
  0.119810;0.973330;,
  0.119810;0.890480;,
  0.112930;0.890480;,
  0.133540;0.973330;,
  0.140430;0.973330;,
  0.140430;0.890480;,
  0.133540;0.890480;,
  0.147320;0.973330;,
  0.147320;0.890480;,
  0.154200;0.973330;,
  0.154200;0.890480;,
  0.161090;0.973330;,
  0.161090;0.890480;,
  0.556220;0.961610;,
  0.588390;0.948280;,
  0.556220;0.917920;,
  0.556220;0.870590;,
  0.524040;0.883920;,
  0.588390;0.883920;,
  0.601720;0.916100;,
  0.463380;0.927550;,
  0.448190;0.921260;,
  0.448190;0.943600;,
  0.433000;0.927550;,
  0.426710;0.942740;,
  0.433000;0.957930;,
  0.448190;0.964230;,
  0.463380;0.957930;,
  0.469670;0.942740;,
  0.059820;0.973330;,
  0.066700;0.973330;,
  0.066700;0.890480;,
  0.059820;0.890480;,
  0.073590;0.973330;,
  0.073590;0.890480;,
  0.080480;0.973330;,
  0.080480;0.890480;,
  0.087360;0.973330;,
  0.087360;0.890480;,
  0.094250;0.973330;,
  0.094250;0.890480;,
  0.510150;0.914960;,
  0.523480;0.947140;,
  0.555660;0.916780;,
  0.523480;0.882780;,
  0.555660;0.869450;,
  0.587840;0.882780;,
  0.601160;0.914960;,
  0.463640;0.927100;,
  0.448450;0.920810;,
  0.448450;0.943150;,
  0.433260;0.927100;,
  0.426960;0.942290;,
  0.433260;0.957490;,
  0.448450;0.963780;,
  0.463640;0.957490;,
  0.469930;0.942290;,
  0.283250;0.973330;,
  0.290130;0.973330;,
  0.290130;0.890480;,
  0.283250;0.890480;,
  0.297020;0.973330;,
  0.297020;0.890480;,
  0.303910;0.973330;,
  0.303910;0.890480;,
  0.019400;0.973330;,
  0.026280;0.973330;,
  0.026280;0.890480;,
  0.019400;0.890480;,
  0.033170;0.973330;,
  0.033170;0.890480;,
  0.040060;0.973330;,
  0.040060;0.890480;,
  0.556750;0.963950;,
  0.588930;0.950620;,
  0.556750;0.920260;,
  0.524570;0.950620;,
  0.511240;0.918440;,
  0.602260;0.918440;,
  0.588930;0.886260;,
  0.463020;0.927100;,
  0.447830;0.920810;,
  0.447830;0.943150;,
  0.432640;0.927100;,
  0.426340;0.942290;,
  0.432640;0.957490;,
  0.447830;0.963780;,
  0.463020;0.957490;,
  0.469310;0.942290;,
  0.317530;0.973330;,
  0.324420;0.973330;,
  0.324420;0.890480;,
  0.317530;0.890480;,
  0.331310;0.973330;,
  0.331310;0.890480;,
  0.223900;0.973330;,
  0.230780;0.973330;,
  0.230780;0.890480;,
  0.223900;0.890480;,
  0.237670;0.973330;,
  0.237670;0.890480;,
  0.244560;0.973330;,
  0.244560;0.890480;,
  0.557890;0.964720;,
  0.590070;0.951390;,
  0.557890;0.921040;,
  0.525710;0.951390;,
  0.590070;0.887040;,
  0.557890;0.873710;,
  0.603400;0.919220;,
  0.463260;0.927550;,
  0.448070;0.921260;,
  0.448070;0.943600;,
  0.432880;0.927550;,
  0.426590;0.942740;,
  0.432880;0.957930;,
  0.448070;0.964230;,
  0.463260;0.957930;,
  0.469550;0.942740;,
  0.346790;0.973330;,
  0.353680;0.973330;,
  0.353680;0.890480;,
  0.346790;0.890480;,
  0.360570;0.973330;,
  0.360570;0.890480;,
  0.367450;0.973330;,
  0.367450;0.890480;,
  0.256790;0.973330;,
  0.263680;0.973330;,
  0.263680;0.890480;,
  0.256790;0.890480;,
  0.270570;0.973330;,
  0.270570;0.890480;,
  0.556990;0.963950;,
  0.589170;0.950620;,
  0.556990;0.920260;,
  0.524810;0.950620;,
  0.511480;0.918440;,
  0.602500;0.918440;,
  0.589170;0.886260;,
  0.463480;0.927550;,
  0.448290;0.921260;,
  0.448290;0.943600;,
  0.433100;0.927550;,
  0.426800;0.942740;,
  0.433100;0.957930;,
  0.448290;0.964230;,
  0.463480;0.957930;,
  0.469770;0.942740;,
  0.174970;0.973330;,
  0.181860;0.973330;,
  0.181860;0.890480;,
  0.174970;0.890480;,
  0.188750;0.973330;,
  0.188750;0.890480;,
  0.195640;0.973330;,
  0.195640;0.890480;,
  0.202520;0.973330;,
  0.202520;0.890480;,
  0.209410;0.973330;,
  0.209410;0.890480;,
  0.557040;0.961610;,
  0.589220;0.948280;,
  0.557040;0.917920;,
  0.524860;0.948280;,
  0.511540;0.916100;,
  0.524860;0.883920;,
  0.463470;0.927550;,
  0.448280;0.921260;,
  0.448280;0.943600;,
  0.433090;0.927550;,
  0.426790;0.942740;,
  0.433090;0.957930;,
  0.448280;0.964230;,
  0.463470;0.957930;,
  0.469760;0.942740;;
 }
}
