#include "ColorGenerator.h"
#include "..\world\World.h"
#include "..\..\Render Engine\toolbox\maths\maths_func.h"

ColorGenerator::ColorGenerator() {
	m_colorProfile.insert(pair<float, Color>(-6.0f, SEA_COLOR));
	m_colorProfile.insert(pair<float, Color>(-2.0f, COAST_COLOR));
	m_colorProfile.insert(pair<float, Color>(4.0f, BACK_COLOR));
	m_colorProfile.insert(pair<float, Color>(10.5f, SNOW_COLOR));
}

Color ColorGenerator::getColor(float height, WorldConfigs configs) {
	//计算altitude
	float factor = World::MAX_ALTITUDE / (configs.getMaxHeight() - configs.getWaterHeight());
	float aboveWater = height - configs.getWaterHeight();
	float altitude = factor * aboveWater;

	//遍历colorProfile，找到height所处的颜色区间
	map<float, Color>::iterator it, previous, next;
	for (it = m_colorProfile.begin(), previous = m_colorProfile.begin(); it != m_colorProfile.end(); it++) {
		if (it->first > altitude) {
			next = it;
			break;
		}
		previous = it;
	}
	float blend = Maths::clamp((altitude - previous->first) / (next->first - previous->first), 0, 1);
	return Color::interpolateColors(previous->second, next->second, blend);
}
