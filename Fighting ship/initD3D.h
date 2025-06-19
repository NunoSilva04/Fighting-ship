#ifndef InitD3D
#define InitD3D

#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX10.h>
#include <d3dcompiler.h>
#include <xnamath.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "D3DX10.lib")
#pragma comment(lib, "d3dcompiler.lib")

typedef struct triangle {
	XMFLOAT3 position;
	D3DXCOLOR color;
}triangle;

typedef struct texture {
	XMFLOAT3 position;
	XMFLOAT2 textCoord;
}texture;

typedef struct cbStructure {
	XMMATRIX cbObject;
}cbStructure;

typedef struct sprite {
	XMFLOAT3 position;
	XMFLOAT2 texCoord;
}sprite;

typedef struct billBoard {
	XMFLOAT2 texCoord;
}billBoard;

typedef struct fightingShipStruc {
	XMFLOAT3 position;
	XMFLOAT2 texCoord;
}fightingShipStruct;

typedef struct fireStruct {
	XMFLOAT3 position;
	XMFLOAT2 texCoord;
}fireStruct;

typedef struct fireBillBoard {
	XMFLOAT2 texCoord;
}fireBillBoard;

typedef struct laserStuct {
	XMFLOAT3 position;
	XMFLOAT2 texCoord;
}laserStruct;

typedef struct laserSpeed {
	float laserSpeedvar;
}laserSpeed;

typedef struct laserSpeedMatrix {
	XMMATRIX speed;
}laserSpeedMatrix;

typedef struct moveLaserPosition {
	float laserStartPosX;
	float laserStartPosY;
}moveLaserPosition;

class D3D {
public:
	//initalize
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devCon = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;

	//initalize depth
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;

	//triangle 
	ID3D11VertexShader* triangleVertexShader = nullptr;
	ID3D11PixelShader* trianglePixelShader = nullptr;
	ID3D11InputLayout* triangleInputLayout = nullptr;
	ID3D11Buffer* triangleVertexBuffer = nullptr;
	ID3D11Buffer* triangleIndicesBuffer = nullptr;

	//Random Texture
	ID3D11VertexShader* textureVertexShader = nullptr;
	ID3D11PixelShader* texturePixelShader = nullptr;
	ID3D11InputLayout* textureInputLayout = nullptr;
	ID3D11Buffer* textureVertexBuffer = nullptr;
	ID3D11Buffer* textureIndicesBuffer = nullptr;
	ID3D11SamplerState* textureSamplerState = nullptr;
	ID3D11ShaderResourceView* textureShaderResourceView = nullptr;

	//World View
	ID3D11Buffer* worldCb = nullptr;
	cbStructure cbInformation;
	XMMATRIX WVP;
	XMMATRIX World;

	//Camera
	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	//triangle translation
	XMMATRIX triangleTranslation;
	float movePosTriangle = 0.0f;

	//Texture Translation
	XMMATRIX textureTranslation;
	float movePosTexture = 0.0f;

	//Sprite
	ID3D11VertexShader* spriteVertexShader = nullptr;
	ID3D11PixelShader* spritePixelShader = nullptr;
	ID3D11InputLayout* spriteInputLayout = nullptr;
	ID3D11Buffer* spriteVertexBuffer = nullptr;
	ID3D11Buffer* spriteIndicesBuffer = nullptr;
	ID3D11SamplerState* spriteSamplerState = nullptr;
	ID3D11ShaderResourceView* spriteShaderResourceView = nullptr;
	sprite spriteVertices[4];

	//Sprite sheet BillBoard and Animation
	billBoard billBoardVertices[100];
	int runThroughBillBoard = 0, totalBillBoardArray = 0;
	float currTime = 0.0f, lastTime = 0.0f;

	//Blend state
	ID3D11RasterizerState* spriteRasterizerState = nullptr;
	ID3D11BlendState* spriteBlendState = nullptr;

	//Fighting ship
	ID3D11VertexShader* fightingShipVertexShader = nullptr;
	ID3D11PixelShader* fightingShipPixelShader = nullptr;
	ID3D11InputLayout* fightingShipInputLayout = nullptr;
	ID3D11Buffer* fightingShipVertexBuffer = nullptr;
	ID3D11Buffer* fightingShipIndexBuffer = nullptr;
	ID3D11SamplerState* fightingShipSamplerState = nullptr;
	ID3D11ShaderResourceView* fightingShipShaderResourceView = nullptr;
	fightingShipStruc fightingShipVertices[4];
	XMMATRIX fightingShipWorld;
	//move ship
	float moveUpDown = 0.0f;
	float moveLeftRight = 0.0f;

	//Fire of the fighting Ship
	ID3D11VertexShader* fireVertexShader = nullptr;
	ID3D11PixelShader* firePixelShader = nullptr;
	ID3D11InputLayout* fireInputLayout = nullptr;
	ID3D11Buffer* fireVertexBuffer = nullptr;
	ID3D11Buffer* fireIndexBuffer = nullptr;
	ID3D11SamplerState* fireSamplerState = nullptr;
	ID3D11ShaderResourceView* fireShaderResourceView = nullptr;
	XMMATRIX fireWorld;
	fireStruct fireVertices[4];
	//Animate the fire
	fireBillBoard fireBillBoardVertices[150];
	int numFireBillBoardVertices = 0, runThroughFireBillBoardVertices = 0;
	float currFireTime = 0.0f, prevFireTime = 0.0f;

	//Laser of the fighting ship
	ID3D11VertexShader* laserVertexShader = nullptr;
	ID3D11PixelShader* laserPixelShader = nullptr;
	ID3D11InputLayout* laserInputLayout = nullptr;
	ID3D11Buffer* laserVertexBuffer = nullptr;
	ID3D11Buffer* laserIndexBuffer = nullptr;
	ID3D11ShaderResourceView* laserShaderResourceView = nullptr;
	ID3D11SamplerState* laserSamplerState = nullptr;
	laserStruct laserVertices[80];
	XMMATRIX laserWorld;
	//Delay of the laser
	float delay = 0.0f;
	bool shootLaser = true, startDelay = false;
	//Move laser
	moveLaserPosition moveLaserPositionArray[20];
	//check player laser
	bool playerShootLaser = false;
	//run through laser array
	int runThroughLaserArray = 0;
	int numLasersDisplayed = 0;
	laserSpeed laserSpeedArray[20];
	laserSpeedMatrix eachLaserSpeedMatrix[20];
	//Check laser out of field postion
	float outFieldVision;

	//Blend state 
	ID3D11BlendState* noBlendState = nullptr;


public:
	//initalization
	void initD3D(HWND hWnd);
	void renderFrame();
	void cleanD3D();

	//triangle
	void initTriangleShaders();
	void initTriangleVertexBuffer();
	void initTriangleIndicesBuffer();
	void renderTriangle();
	void updateTriangle();

	//Random texture
	void initTextureShaders();
	void initTextureVertexBuffer();
	void initTextureIndicesBuffer();
	void initTextureSampler();
	void renderTexture();
	void updateTexture();

	//World
	void initWorldcb();
	void renderWorldcb();
	
	//Camera
	void initCamera();

	//Sprite
	void initSpriteShaders();
	void initSpriteVertexBuffer();
	void initSpriteIndicesBuffer();
	void initSpriteSampler();
	void renderSprite();
	void updateSprite();

	//blend state
	void initSpriteRasterizerState();
	void initSpriteBlendState();

	//Sprite sheet BillBoard and Animation
	void spriteSheetBillBoard();
	void animateSpriteSheet();

	//fighting ship
	void initFightingShipShaders();
	void initFightingShipVertexBuffer();
	void initFightingShipIndexBuffer();
	void initFightingShipSamplerState();
	void renderFightingShip();
	void updateFightingShip();
	//Move ship
	void moveFightingShip();

	//Fire of the Fighting Ship
	void initFireShaders();
	void initFireVertexBuffer();
	void initFireIndexBuffer();
	void initFireSamplerState();
	void renderFire();
	void updateFire();
	//Animate fire
	void initFireBillBoardSheet();
	void animateFire();

	//Laser
	void initLaserShaders();
	void initLaserVertexBuffer();
	void initLaserIndexBuffer();
	void initLaserSamplerState();
	void updateLaserWorld();
	void renderLaser();
	//Shoot laser
	void shootLaserFunc();
	void checkPlayerShootLaser();
	void initLaserSpeedMatrixArray();
};

#endif // !InitD3D

