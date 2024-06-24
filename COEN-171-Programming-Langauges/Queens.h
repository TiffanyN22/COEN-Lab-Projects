/*
 * Solve the n-Pieces problem of trying to place n identical pieces on
 * an n x n chessboard.
 *
 * 	Knights		      Bishops		      Rooks	  	    Queens		Amazons
 * 2	6	       	    4	      	      2		          0		      0
 * 3	36	        	26	      	    6		          0		      0
 * 4	412	   	      260	    	      24	         	2		      0
 * 5	9386		      3368	  	      120		        10		    0
 * 6	257318		    53744	   	      720		        4		      0
 * 7	8891854		    1022320		      5040		      40		    0
 * 8	379978716	    XXXXXXXX	      40320	  	    92		    0
 * 9	19206532478	  22522960	      362880		    352		    0
 * 10	1120204619108	15915225216	    3628800		    724		    4
 */

# ifndef QUEENS_H
# define QUEENS_H
# include <cstdlib>

// An abstract chess piece that cannot be instantiated.
class Piece {
protected:
    int _row, _column;

public:
  int row() const {
    return _row;
  }

  int column() const {
    return _column;
  }

  void place(int row, int col){
    _row = row;
    _column = col;
  }

  virtual bool menaces(const Piece *p) const = 0;
};

struct Rooks: virtual public Piece {
  virtual bool menaces(const Piece *p) const{
    bool rows = (_row == p->row());
    bool col = (_column == p->column());
    return rows || col;
  }
};

struct Bishop: virtual public Piece {
  virtual bool menaces(const Piece *p) const{
    int rows = abs(_row - p->row());
    int col = abs(_column - p->column());
    return rows == col;
  }
};

struct Knight: virtual public Piece {
  virtual bool menaces(const Piece *p) const{
    int rows = abs(_row - p->row());
    int col = abs(_column - p->column());
    return (rows == 1 && col == 2) || (rows == 2 && col == 1);
  }
};

struct Queens: public Rooks, Bishop {
  bool menaces(const Piece *p) const{
    return (Rooks::menaces(p) || Bishop::menaces(p));
  }
};

struct Amazon: public Queens, Knight {
  bool menaces(const Piece *p) const{
    return (Queens::menaces(p) || Knight::menaces(p));
  }
};

# endif /* QUEENS_H */
