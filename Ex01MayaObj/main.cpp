#include <windows.h>
#include "glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#ifdef min
#undef min
#endif

// デフォルトカメラ宣言のインクルード
#include "DefaultCamera.h"
// デフォルトカメラクラスのインスタンスを生成
DefaultCamera defaultCamera;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

/***** obj ファイル読み込み用 *****/
#include <vector>
#include <algorithm>
static const char* delim = " /\t\n";
static char* context = nullptr;
int ReadVector3(glm::vec3 &v, char* buf)
{
#define READ_VECTOR3_TOKEN(ELEMENT) tok = strtok_s(buf, delim, &context); \
    if (tok == nullptr) { return -1; } \
    v.ELEMENT = static_cast<float>(std::atof(tok));
	char* tok = nullptr;
	READ_VECTOR3_TOKEN(x);
	READ_VECTOR3_TOKEN(y);
	READ_VECTOR3_TOKEN(z);
	return 0;
}
int ReadVector2(glm::vec2& v, char* buf)
{
#define READ_VECTOR2_TOKEN(ELEMENT) tok = strtok_s(buf, delim, &context); \
    if (tok == nullptr) { return -1; } \
    v.ELEMENT = static_cast<float>(std::atof(tok))
	char* tok = nullptr;
	READ_VECTOR2_TOKEN(x);
	READ_VECTOR2_TOKEN(y);
	return 0;
}

bool LoadObjModel(std::vector<Vertex> &vertices, std::vector<uint32_t>& indices, const char* fileName)
{
	char buf[1024];
	char* tok = nullptr;

	FILE* fin = nullptr;
	fopen_s(&fin, fileName, "r");
	if (fin == nullptr)
	{
		return false;
	}
    vertices.clear();

    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> texcoord;

	int hr = 0;
	while (std::fgets(buf, 1024, fin) != nullptr)
	{
		tok = strtok_s(buf, delim, &context);
		if (tok == nullptr)
		{
		}
		else if (tok[0] == '#')
		{
			continue;
		}
		else if (strcmp(tok, "mtllib") == 0 || strcmp(tok, "usemtl") == 0)
		{
			continue;
		}
		else if (strcmp(tok, "s") == 0 || strcmp(tok, "g") == 0)
		{
			continue;
		}
		else if (strcmp(tok, "v") == 0)
		{
			glm::vec3 p;
			if (hr = ReadVector3(p, NULL), hr < 0)
			{
				break;
			}
			position.push_back(p);
		}
		else if (strcmp(tok, "vn") == 0)
		{
			glm::vec3 n;
			if (hr = ReadVector3(n, NULL), hr < 0)
			{
				break;
			}
			normal.push_back(n);
		}
		else if (strcmp(tok, "vt") == 0)
		{
			glm::vec2 t;
			if (hr = ReadVector2(t, NULL), hr < 0)
			{
				break;
			}
			texcoord.push_back(t);
		}
		else if (strcmp(tok, "f") == 0)
		{
			std::string str(buf + 2);
			std::vector<long> tmp;
			std::string::size_type offset = 0, prevOffset = 0;
			while (offset = std::min(str.find('\n', prevOffset), std::min(str.find('/', prevOffset), str.find(' ', prevOffset))), offset != std::string::npos)
			{
				if (prevOffset == offset)
				{
					prevOffset = offset + 1;
					tmp.push_back(-1);
				}
				else
				{
					std::string substr = str.substr(prevOffset, offset - prevOffset);
					tmp.push_back(atoi(substr.c_str()) - 1);
					prevOffset = offset + 1;
				}
			}

			switch (tmp.size())
			{
			case 9:
				for (int i = 0; i < 3; ++i)
				{
					long pi = tmp[i * 3 + 0];
					long ti = tmp[i * 3 + 1];
					long ni = tmp[i * 3 + 2];
                    
                    Vertex v;
                    v.position = position[pi];
					if (ni >= 0)
					{
                        v.normal = normal[ni];
					}
                    vertices.push_back(v);
                    indices.push_back(indices.size());
				}
				break;
			default:
				fclose(fin);
				position.clear();
				normal.clear();
                texcoord.clear();
				return false;
				break;
			}
		}
	}
	fclose(fin);
	return true;
}
/*** obj ファイル読み込み用 ***/

// OBJモデルを描画する関数：引数modelIDに識別番号（下記のobjModelID）を渡すと、描画される
// マテリアル情報はこの関数を呼ぶ直前に設定する
void drawObjModel(GLuint modelID)
{
	glPushMatrix(); // たぶんいらないけど念のためのpush
	{
		// ロードしたOBJモデルの描画
		glCallList(modelID);
	}
	glPopMatrix(); // 同上．念のためのpop
}

// ロードするOBJモデルの識別番号を表す変数
GLuint objModelID = 0;

// ウィンドウサイズ変更時に呼ばれる関数
void resize(int w, int h)
{
	// ビューポート変換：ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);
	// 投影変換行列の操作を開始
	glMatrixMode(GL_PROJECTION);
	// 投影変換行列を単位行列に初期化
	glLoadIdentity();
	// 透視投影行列を設定
	gluPerspective(30.0, (double)w / (double)h, 1.0e-2, 1.0e3);

	// ウィンドウリサイズ時にはカメラに新しいスクリーンサイズを登録する
	defaultCamera.OnResize(w, h);
}

void mouse_button(int button, int state, int x, int y)
{
	// マウスが押されたときには，その情報をカメラに送る
	// カメラパラメータの変更方法はカメラ自身が決める
	defaultCamera.OnMouseButton(button, state, x, y);
}

void mouse_drag(int x, int y)
{
	// マウスがドラッグされたときには，その情報をカメラに送る
	// カメラパラメータの変更方法はカメラ自身が決める
	defaultCamera.OnMouseMove(x, y);
}

// 現在時刻を秒単位（浮動小数点形式）で取得する関数．windowsの高性能タイマーを利用
double queryTimeInSeconds()
{
	LARGE_INTEGER freq, count;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&count);
	return (double)count.QuadPart / (double)freq.QuadPart;
}

void idle(void)
{
	glutPostRedisplay();
}

// 描画関数
void display(void)
{
	// ウィンドウ塗りつぶし　＋　Zバッファのクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// モデリング変換と視野変換行列の操作を開始
	glMatrixMode(GL_MODELVIEW);
	// モデリング変換行列と視野変換行列を単位行列に初期化
	glLoadIdentity();
	// 視野変換行列を設定：　デフォルトカメラの内部で適切に処理される
	defaultCamera.SetViewMatrix();
	// 現在時刻を秒単位で取得
	double msec = queryTimeInSeconds();

	// ライト位置
	float lightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	// 拡散反射光
	float lightDiffuse[3] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	// 鏡面反射光
	float lightSpecular[3] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	// 環境光
	float lightAmbient[3] = { 0.25f, 0.25f, 0.25f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	glPushMatrix();
	{
		// +Y軸周りに負方向の回転
		glRotated(-msec * 5.0, 0, 1.0, 0);

		// 環境光
		float ambient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		// 拡散反射
		float diffuse[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		// 鏡面反射
		float specular[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		// 発光成分（ライトに関係なくモデル自身が放つ輝度）
		float emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

		// ロードしたOBJモデルの描画
		drawObjModel(objModelID);
	}
	glPopMatrix();

	// 次のフレームの描画
	glutIdleFunc(idle);
	// 描画バッファの切り替え
	glutSwapBuffers();
}

// main関数
int main(int argc, char* argv[])
{
	// ウィンドウサイズ
	glutInitWindowSize(640, 480);
	// ウィンドウ位置
	glutInitWindowPosition(300, 300);
	// GLUTおよびOpenGLの初期化
	glutInit(&argc, argv);
	// ディスプレイ表示モード設定　：　フレームバッファはRGBAフォーマットとし，かつZバッファ（深度バッファ）も利用
	// さらにアニメーション対応のため，ダブルバッファの使用を指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// 新しいウィンドウ生成
	glutCreateWindow(argv[0]);
	// 描画関数の登録
	glutDisplayFunc(display);
	// ウィンドウサイズ変更時に呼ばれる関数を登録
	glutReshapeFunc(resize);
	// マウスのボタンが押されたときに呼び出す関数の登録
	glutMouseFunc(mouse_button);
	// マウスドラッグ中に呼び出す関数の登録
	glutMotionFunc(mouse_drag);
	// ウィンドウ塗りつぶし色
	glClearColor(0.0, 0.2, 0.0, 1.0);
	// Zバッファ法による隠面消去の有効化
	glEnable(GL_DEPTH_TEST);
	// ライティング処理を有効化
	glEnable(GL_LIGHTING);
	// ゼロ番目のライトを点灯
	glEnable(GL_LIGHT0);

	// OBJモデルのロード
	objModelID = LoadObjModel("./model.obj");

	// GLUTメインループ
	glutMainLoop();
	// Zバッファ法による隠面消去の無効化
	glDisable(GL_DEPTH_TEST);

	return 0;
}
