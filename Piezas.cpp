#include "Piezas.h"
#include <vector>

using std::vector;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  board.resize(BOARD_ROWS, vector<Piece>(BOARD_COLS, Blank));
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for (int row = 0; row < BOARD_ROWS; row++)
  {
    for(int column = 0; column < BOARD_COLS; column++)
    {
      board[row][column] = Blank;
    }
  }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  if (column > BOARD_COLS - 1)
  {
    if (turn == O)
    {
      return turn = X;
    }
    if (turn == X)
    {
      return turn = O;
    }
    else
    {
      return Invalid;
    }
  }
  if(board[0][column] != Blank)
  {
    if (turn == O)
    {
      return turn = X;
    }
    if (turn == X)
    {
      return turn = O;
    }
    else
    {
      return Invalid;
    }
  }
  if(board[2][column] == Blank)
  {
    board[2][column] = turn;
    if (turn == O)
    {
      return turn = X;
    }
    if (turn == X)
    {
      return turn = O;
    }
  }
  else if(board[0][column] == Blank)
  {
    board[0][column] = turn;
    if (turn == O)
    {
      return turn = X;
    }
    if (turn == X)
    {
      return turn = O;
    }
  }
  else if(board[1][column] == Blank)
  {
    board[1][column] = turn;
    if (turn == O)
    {
      return turn = X;
    }
    if (turn == X)
    {
      return turn = O;
    }
  }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if (row < 0 || row >= BOARD_ROWS)
    {
      return Invalid;
    }
    if (column < 0 || column >= BOARD_COLS)
    {
      return Invalid;
    }
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    int cX = 0;
    int cO = 0;
    int hX = 0;
    int hO = 0;
    int row = 0;
    int column = 0;
    bool isWinner = true;

    while (row < BOARD_ROWS)
    {
      while (column < BOARD_COLS)
      {
        if (board[row][column] == Blank)
        {
          isWinner = false;
        }
        column++;
       }
      row++;
    }

    if (isWinner == false)
    {
      return Invalid;
    }
    row = 0;
    column = 0;

    while (row < BOARD_ROWS)
    {
      while(column < BOARD_COLS)
      {
        if(board[row][column] != hO)
        {
          cX++;
          if(cX > hX)
          {
            hX = cX;
          }
          cO = 0;
        }
        else
        {
          cO++;
          if(cO > hO)
          {
            hO = cO;
          }
          cX = 0;
        }
        column++;
      }
      cX = 0;
      cO = 0;
      row++;
    }

    cX = 0;
    cO = 0;
    row = 0;
    column = 0;
    while(column < BOARD_COLS)
    {
      while(row < BOARD_ROWS)
      {
        if(board[row][column] != hO)
        {
          cX++;
          if(cX > hX)
          {
            hX = cX;
          }
          cO = 0;
        }
        row++;
      }
      cX = 0;
      cO = 0;
      column++;
    }
    if(hX < hO)
    {
      return O;
    }
    else if(hO < hX)
    {
      return X;
    }
    else
    {
      return Blank;
    }
    return Blank;
}
