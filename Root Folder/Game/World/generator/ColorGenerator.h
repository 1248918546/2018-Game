#pragma once
#pragma once

#include "..\..\Render Engine\toolbox\color.h"
#include "..\worldConfig\worldConfigs.h"

#include <map>

using namespace std;

class ColorGenerator {
private:
	const Color SEA_COLOR = Color(214.0f, 237.0f, 146.0f, true);
	const Color COAST_COLOR = Color(210.0f, 193.0f, 134.0f, true);
	const Color BACK_COLOR = Color(111.0f, 80.0f, 45.0f, true);
	const Color SNOW_COLOR = Color(0.7f, 0.7f, 0.75f);

	map<float, Color> m_colorProfile;

public:
	ColorGenerator();
	Color getColor(float height, WorldConfigs configs);    //��ȡheight���ڸ߶ȶ�Ӧ����ɫ
};