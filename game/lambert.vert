#version 150 core

// 出力：頂点の法線ベクトル
out vec3 vsNormal;
// 出力：視線ベクトル
out vec3 vsView;
// 出力：ライトベクトル
out vec3 vsLight;

// 入力：頂点位置
in vec3 position;
// 入力：頂点の法線ベクトル
in vec3 normal;

// 定数：モデルの座標変換行列TRS
uniform mat4 mModel;
// 定数：視野変換行列
uniform mat4 mView;
// 定数：射影変換行列
uniform mat4 mProjection;
// 定数：モデルの座標系からみたライト位置
uniform vec3 vLocalLight;
// 定数：モデルの座標系からみたカメラ位置
uniform vec3 vLocalCamera;
// 定数：経過時間
uniform float time;
// 定数：マウス位置
uniform vec2 mousePos;
// 定数：ウィンドウサイズ
uniform vec2 windowSize;

void main()
{
    // スクリーン上におけるモデルの頂点座標を求める座標変換
    gl_Position = mProjection * mView * mModel * vec4(position, 1.0f);

	// 頂点の法線ベクトルは、モデルの座標系におけるベクトルのまま
    vsNormal    = normal;

	// 頂点位置からカメラ位置に向かう単位ベクトル
    vsView      = normalize(vLocalCamera - position.xyz);

	// 頂点位置からライト位置に向かう単位ベクトル
    vsLight     = normalize(vLocalLight - position.xyz);
}
