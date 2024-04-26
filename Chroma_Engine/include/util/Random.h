#pragma once

namespace chroma
{
	class Random
	{
	public:
		Random();

		//! Returns a Random Int between minInclusive and maxInclusive
		static int GetInt(int minInclusive, int maxInclusive);
	};
}