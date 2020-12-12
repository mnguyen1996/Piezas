/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, constructBoard)
{
  Piezas p;
  for(int i = 0; i < BOARD_ROWS; i++)
  {
    for(int j = 0; j < BOARD_COLS; j++)
    {
      ASSERT_EQ(p.pieceAt(i,j), Blank);
    }
  }
}

TEST(PiezasTest, structCheck)
{
	bool x = 1;
	Piezas p;
	for(int i = 0; i < BOARD_ROWS; i++)
  {
    for(int j = 0; j < BOARD_COLS; j++)
    {
      if(p.pieceAt(i,j) != Blank)
			{
				x = 0;
			}
    }
  }
	ASSERT_EQ(1, x);
}

TEST(PiezasTest, winCheckfalseO)
{
	Piezas p;
	p.reset();

	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(2);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(3);

	ASSERT_EQ(false, p.gameState() == O);
}

TEST(PiezasTest, winChecktrueX)
{
	Piezas p;
	p.reset();

	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(2);
	p.dropPiece(0);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(3);

	ASSERT_EQ(true, p.gameState() == X);
}

TEST(PiezasTest, winCheckfalseBlank)
{
	Piezas p;
	p.reset();

	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(3);

	ASSERT_EQ(false, p.gameState() == Blank);
}

TEST(PiezasTest, notCompleteGame)
{
	Piezas p;
	p.reset();

	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);

	ASSERT_EQ(true, p.gameState() == Invalid);
}

TEST(PiezasTest, checkGameState)
{
	Piezas p;
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, gameStateHorizonalWin)
{
	Piezas p;
	for (int i = 0; i < BOARD_COLS; i++)
	{
		p.dropPiece(i);
		p.dropPiece(-1);
	}
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			p.dropPiece(j);
		}
	}
	ASSERT_TRUE(p.gameState() == X);
}

TEST(PiezasTest, gameStateVerticalWin)
{
	Piezas p;
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		p.dropPiece(0);
		p.dropPiece(-1);
	}
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			p.dropPiece(j);
		}
	}
	ASSERT_TRUE(p.gameState() == X);
}
