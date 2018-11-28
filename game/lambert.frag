#version 150 core

// 出力値：フラグメント＝画素の色[R, G, B, A]
out vec4 fragment;

// 入力値：頂点の法線ベクトル
in vec3 vsNormal;
// 入力値：視線ベクトル
in vec3 vsView;
// 入力値：ライトベクトル
in vec3 vsLight;

// 定数：ライトの色
uniform vec4 vLightDiffuse;
// 定数：モデルの色
uniform vec4 vModelDiffuse;
// 定数：経過時間
uniform float time;
// 定数：マウス位置
uniform vec2 mousePos;
// 定数：ウィンドウサイズ
uniform vec2 windowSize;

void main()
{
	// Lambertシェーディング
    vec3 diffuse = (vLightDiffuse.xyz * vModelDiffuse.xyz) * max(dot(vsLight, vsNormal), 0.0f);
    fragment = vec4(diffuse, vModelDiffuse.w);
}
