#include "pch.h"
#include "CppUnitTest.h"
#include "../Tehtava3-12/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(dealDamageTest)
		{
			int hp = 100;
			dealDamage(hp);
			Assert::AreEqual(0, hp);
		}

		TEST_METHOD(dealDamageTest2)
		{
			int hp = 50;
			dealDamage(hp);
			Assert::AreEqual(0, hp);
		}

		TEST_METHOD(FAKEdealDamageTest2)
		{
			int hp = 50;
			dealDamage(hp);
			Assert::AreEqual(-50, hp);
		}
	};
}
