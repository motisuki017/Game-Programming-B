#version 150 core

// 出力：ピクセル色
out vec4 fragment;

// 定数：経過時間
uniform float time;

// 定数：マウス座標
uniform vec2 mousePos;

// 定数：ウィンドウサイズ
uniform vec2 windowSize;

// 定数：テクスチャ画像
uniform sampler2D image;

void main()
{
    // マウスからフラグメント＝ピクセルまでの距離
	float dist = length(gl_FragCoord.xy - mousePos.xy);

	// ピクセル座標をスクリーンサイズで割り、0～1.0の値に正規化
	vec2 texc = gl_FragCoord.xy;
	texc.x /= windowSize.x;
	texc.y /= windowSize.y;

	// 正規化された座標を用いてテクスチャのピクセル色をサンプリング
	fragment = texture(image, texc);

	// マウス位置に近いもののみ明るく表示する
	fragment *= min(1.0, 40.0 / dist);

	// 時間経過に応じて明るさを変化させる
	fragment *= (sin(time * 3.0) + 1.0) / 2.0;
}
