/**
 * Chisa
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DonutHelper.hpp"
#include <math.h>

namespace donut {

TEST(DonutIntegerTest, AddTest)
{
	SOURCE_TEST_INT(3, "1+2;")
}

TEST(DonutIntegerTest, AddTripleTest)
{
	SOURCE_TEST_INT(4, "2+1+1;")
}

TEST(DonutIntegerTest, ImplicitConvertTest)
{
	INIT_DONUT;
	ASSERT_ANY_THROW( heap->createInt(10)->toBool(heap) );
	ASSERT_ANY_THROW( heap->createInt(10)->toFloat(heap) );
	ASSERT_NO_THROW( heap->createInt(10)->toInt(heap) );
	ASSERT_ANY_THROW( heap->createInt(10)->toString(heap) );
}

TEST(DonutIntegerTest, LiteralTest)
{
	SOURCE_TEST_INT(1, "1;");
	//2^(31-2)-1 -> 536870911
	SOURCE_TEST_INT(536870911, "536870911;");
	SOURCE_TEST_INT(-536870911, "-536870911;");
}

TEST(DonutIntegerTest, SubTest)
{
	SOURCE_TEST_INT(-1, "1-2;");
}

TEST(DonutIntegerTest, MulTest)
{
	SOURCE_TEST_INT(12, "3*4;");
}

TEST(DonutIntegerTest, DivTest)
{
	SOURCE_TEST_INT(4, "9/2;");
}

TEST(DonutIntegerTest, ModTest)
{
	SOURCE_TEST_INT(1, "9%4;");
}

TEST(DonutIntegerTest, LtTest)
{
	SOURCE_TEST_TRUE("4<9");
	SOURCE_TEST_FALSE("9<4");
}
TEST(DonutIntegerTest, GtTest)
{
	SOURCE_TEST_TRUE("9>4");
	SOURCE_TEST_FALSE("4>9");
}

TEST(DonutIntegerTest, LeTest)
{
	SOURCE_TEST_TRUE("4<=9");
	SOURCE_TEST_FALSE("9<=4");
	SOURCE_TEST_TRUE("4<=4");
}
TEST(DonutIntegerTest, GeTest)
{
	SOURCE_TEST_TRUE("9>=4");
	SOURCE_TEST_FALSE("4>=9");
	SOURCE_TEST_TRUE("4>=4");
}
TEST(DonutIntegerTest, EqTest)
{
	SOURCE_TEST_TRUE("4==4");
	SOURCE_TEST_FALSE("5==4");
}
TEST(DonutIntegerTest, NeTest)
{
	SOURCE_TEST_TRUE("5!=4");
	SOURCE_TEST_FALSE("4!=4");
}

TEST(DonutIntegerTest, PlusTest)
{
	SOURCE_TEST_INT(4, "+4");
	SOURCE_TEST_INT(-4, "+(-4)");
}

TEST(DonutIntegerTest, BitAndTest)
{
	SOURCE_TEST_INT(0, "1&4");
	SOURCE_TEST_INT(1, "1&1");
}

TEST(DonutIntegerTest, BitOrTest)
{
	SOURCE_TEST_INT(5, "1|4");
	SOURCE_TEST_INT(1, "1|1");
}

TEST(DonutIntegerTest, MinusTest)
{
	SOURCE_TEST_INT(-4, "-4");
	SOURCE_TEST_INT(4, "-(-4)");
}

TEST(DonutIntegerTest, FloatCastTest)
{
	SOURCE_TEST_FLOAT(-4.0f, "(-4).toFloat()");
}

TEST(DonutIntegerTest, FloatAddTest)
{
	SOURCE_TEST_THROW("1+1.1");
}

TEST(DonutIntegerTest, FloatAddWithCastTest)
{
	SOURCE_TEST_FLOAT(2.1, "(1).toFloat()+1.1");
}

TEST(DonutIntegerTest, ToStringTest)
{
	SOURCE_TEST_STR("12345", "(12345).toString();");
}

}
