#pragma once
//���̺귯�� �߰� window ��Ƽ�̵��.lib
#pragma comment(lib,"winmm.lib")

#include <Windows.h>
#include <assert.h> //�ܾ� �̻��ϴٽ����� �ڵ���ü�� �ߴ�

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map>

//macro function
#define SAFE_DELETE(p) {if (p) {delete(p); (p)=nullptr;} }
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}



#include "./system/definition.h"
#include "./system/Renderer.h"
#include "./system/Collision.h"
#include "system/bulletm.h"
#include "system/SceneManager.h"
