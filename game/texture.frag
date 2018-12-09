#version 150 core

// 出力：フラグメント＝画素の色[R, G, B, A]
out vec4 fragment;

// 入力：頂点の法線ベクトル
in vec3 vsNormal;
// 入力：テクスチャ座標
in vec2 vsTexcoord;
// 入力：視線ベクトル
in vec3 vsView;
// 入力：ライトベクトル
in vec3 vsLight;

// 定数：ライトの色
uniform vec4 vLightDiffuse;
// 定数：経過時間
uniform float time;
// 定数：マウス位置
uniform vec2 mousePos;
// 定数：ウィンドウサイズ
uniform vec2 windowSize;
// 定数：テクスチャ画像
uniform sampler2D image;

void main()
{
    // テクスチャ読み込み
	vec4 modelDiffuse = texture(image, vsTexcoord);
	// Lambertシェーディング
    vec3 diffuse = (vLightDiffuse.xyz * modelDiffuse.xyz) * max(dot(vsLight, vsNormal), 0.0f);
    fragment = vec4(diffuse, modelDiffuse.w);
}
