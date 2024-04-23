#pragma once

namespace chroma
{
	class Random
	{
	public:
		Random();

		static int GetInt(int minInclusive, int maxInclusive);
	};
}