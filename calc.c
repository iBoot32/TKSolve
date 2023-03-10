#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 24

char temp[ARR_SIZE] = "WRGBOWYGRBRYOGYBYOWBRWOG";

int swaps[18][12][2] = {
	{ {3, 20}, {4, 19}, {5, 18}, {18, 17}, {19, 16}, {20, 15}, {15, 8}, {16, 7}, {17, 6}, {6, 5}, {7, 4}, {8, 3}} , // R
	{ {20, 3}, {19, 4}, {18, 5}, {17, 18}, {16, 19}, {15, 20}, {8, 15}, {7, 16}, {6, 17}, {5, 6}, {4, 7}, {3, 8}} ,
	{ {4, 16}, {16, 4}, {7, 19}, {19, 7}, {3, 15}, {15, 3}, {6, 18}, {18, 6}, {8, 20}, {20, 8}, {5, 17}, {17, 5}} , //could possibly reduce this to swaps, then use tuple swapping

	{ {0, 3}, {1, 5}, {2, 4}, {3, 6}, {4, 8}, {5, 7}, {6, 9}, {7, 11}, {8, 10}, {9, 0}, {10, 2}, {11, 1}} ,
	{ {3, 0}, {5, 1}, {4, 2}, {6, 3}, {8, 4}, {7, 5}, {9, 6}, {11, 7}, {10, 8}, {0, 9}, {2, 10}, {1, 11}} ,
	{ {0, 6}, {1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11}, {6, 0}, {7, 1}, {8, 2}, {9, 3}, {10, 4}, {11, 5}} ,

	{ {0, 11}, {1, 10}, {2, 9}, {9, 14}, {10, 13}, {11, 12}, {12, 23}, {13, 22}, {14, 21}, {21, 2}, {22, 1}, {23, 0}},
	{ {11, 0}, {10, 1}, {9, 2}, {14, 9}, {13, 10}, {12, 11}, {23, 12}, {22, 13}, {21, 14}, {2, 21}, {1, 22}, {0, 23}},
	{ {0, 12}, {1, 13}, {2, 14}, {9, 21}, {10, 22}, {11, 23}, {12, 0}, {13, 1}, {14, 2}, {21, 9}, {22, 10}, {23, 11}},

	{ {12, 15}, {13, 17}, {14, 16}, {15, 18}, {16, 20}, {17, 19}, {18, 21}, {19, 23}, {20, 22}, {21, 12}, {22, 14}, {23, 13}},
	{ {15, 12}, {17, 13}, {16, 14}, {18, 15}, {20, 16}, {19, 17}, {21, 18}, {23, 19}, {22, 20}, {12, 21}, {14, 22}, {13, 23}},
	{ {12, 18}, {13, 19}, {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 12}, {19, 13}, {20, 14}, {21, 15}, {22, 16}, {23, 17}},

	{ {9, 7}, {10, 6}, {11, 8}, {6, 16}, {7, 15}, {8, 17}, {15, 13}, {16, 12}, {17, 14}, {12, 10}, {13, 9}, {14, 11}},
	{ {7, 9}, {6, 10}, {8, 11}, {16, 6}, {15, 7}, {17, 8}, {13, 15}, {12, 16}, {14, 17}, {10, 12}, {9, 13}, {11, 14}},
	{ {9, 15}, {10, 16}, {11, 17}, {6, 12}, {7, 13}, {8, 14}, {15, 9}, {16, 10}, {17, 11}, {12, 6}, {13, 7}, {14, 8}},

	{ {0, 22}, {1, 21}, {2, 23}, {21, 19}, {22, 18}, {23, 20}, {18, 4}, {19, 3}, {20, 5}, {3, 1}, {4, 0}, {5, 2}},
	{ {22, 0}, {21, 1}, {23, 2}, {19, 21}, {18, 22}, {20, 23}, {4, 18}, {3, 19}, {5, 20}, {1, 3}, {0, 4}, {2, 5}},
	{ {0, 18}, {1, 19}, {2, 20}, {21, 3}, {22, 4}, {23, 5}, {18, 0}, {19, 1}, {20, 2}, {3, 21}, {4, 22}, {5, 23}}
};


void calc(char cornerarray[], char moves[], int num)
{
  for (int i = 0; i < num; i++)
  {
    memcpy(temp, cornerarray, ARR_SIZE / sizeof(char));
    for (int z = 0; z < 12; z++)
    {
      temp[swaps[moves[i] - 97][z][1]] = cornerarray[swaps[moves[i] - 97][z][0]];
    }
    memcpy(cornerarray, temp, ARR_SIZE / sizeof(char));
  }
}