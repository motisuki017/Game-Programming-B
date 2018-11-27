#version 150 core

out vec4 fragment;
uniform float time;
uniform vec2 mousePos;
uniform vec2 windowSize;
uniform sampler2D image;

void main()
{
    // 画素からマウス位置までの距離
	float phase = length(mousePos.xy - gl_FragCoord.xy);
    // 画素からマウス位置へ向かう単位ベクトル（長さ1のベクトル）
	vec2 diff = normalize(mousePos.xy - gl_FragCoord.xy);
	// 拡大率を正規分布に従って計算（マウス位置に近いほど大きく拡大されるように）
	float mod = exp(-phase / 100.0) * phase;
	// 表示するテクスチャの画素を決定
	vec2 texc;
	texc.x = (gl_FragCoord.x + mod * diff.x) / windowSize.x;
	texc.y = (gl_FragCoord.y + mod * diff.y) / windowSize.y;
	// テクスチャマッピング
	fragment = texture(image, texc.xy);
}
