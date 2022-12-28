#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "cube_solver.h"

static void _swap(char*, int, int);

const char *corner_LUT[][2] = 
{ 
    // defines setup and "unfo" moves for shooting to a certain target
    [3] = { "R D'",     "D R'"  },
    [4] = { "R2",       "R2"    },
    [5] = { "R' F",     "F' R"  },
    [6] = { "F",        "F'"    },
    [7] = { "R'",       "R"     },
    [8] = { "F2 D",     "D' F2" },
    [9] = { "L D L'",   "L D' L'"},
    [10] = { "F2",      "F2"    },
    [11] = { "F' D",    "D' F"  },
    [12] = { "F'",      "F"     },
    [13] = { "D2 R",    "R' D2" },
    [14] = { "D",       "D'"    },
    [15] = { "D' F'",   "F D"   }, 
    [16] = { "",        ""      },
    [17] = { "F D",     "D' F'" },
    [18] = { "D2 F'",   "F D2"  },
    [19] = { "R",       "R'"    },
    [20] = { "D'",      "D"     },
    [21] = { "D F'",    "F D'"  },
    [22] = { "D2",      "D2"    },
    [23] = { "D' R",    "R' D"  }
};

const int corner_swaps[][3] =
{
    // each entry denotes where each buffer sticker will end up.
    // i.e if shooting to sticker 3, corners[0] goes to sticker 3, corners[1] goes to sticker 5, and corners[2] goes to sticker 4
    [3] = {3, 5, 4},
    [4] = {4, 3, 5},
    [5] = {5, 4, 3},
    [6] = {6, 7, 8},
    [7] = {7, 8, 6},
    [8] = {8, 6, 7},
    [9] = {9, 11, 10},
    [10] = {10, 9, 11},
    [11] = {11, 10, 9},
    [12] = {12, 13, 14},
    [13] = {13, 14, 12},
    [14] = {14, 12, 13},
    [15] = {15, 17, 16},
    [16] = {16, 15, 17},
    [17] = {17, 16, 15},
    [18] = {18, 19, 20},
    [19] = {19, 20, 18},
    [20] = {20, 18, 19},
    [21] = {21, 23, 22},
    [22] = {22, 21, 23},
    [23] = {23, 22, 21}
};

const char *edge_LUT[][2] = 
{
    [0] = {"R2 U' R2",                  "R2 U R2"                   },
    [1] = {"R2 U' L2 R2 D U' F U L'",   "L U' F' U D' R2 L2 U R2"   },
    [4] = {"R2 U R2",                   "R2 U' R2"                  },
    [5] = {"R F' L' R'",                "R L F R'"                  },
    [6] = {"",                          ""                          },
    [7] = {"L2 D U' F U L'",            "L U' F' U D' L2"           },
    [8] = {"L",                         "L'"                        },
    [9] = {"U B' U'",                   "U B U'"                    },
    [10] = {"L'",                       "L"                         },
    [11] = {"U' F U",                   "U' F' U"                   },
    [12] = {"U2 R U2",                  "U2 R' U2"                  },
    [13] = {"U' F' U",                  "U' F U"                    },
    [14] = {"U2 R' U2",                 "U2 R U2"                   },
    [15] = {"U B U'",                   "U B' U'"                   },
    [16] = {"D' L2",                    "L2 D"                      },
    [17] = {"U' F U L'",                "L U' F' U"                 },
    [18] = {"D2 L2",                    "L2 D2"                     },
    [19] = {"U2 R' U' B U'",            "U B' U R U2"               },
    [20] = {"D L2",                     "L2 D'"                     },
    [21] = {"D2 U' F U L'",             "L U' F' U D2"              },
    [22] = {"L2",                       "L2"                        },
    [23] = {"D U' F U L'",              "L U' F' U D'"              }
};

const int edge_swaps[][2] =
{
    [0] = {0, 1},
    [1] = {1, 0},
    [4] = {4, 5},
    [5] = {5, 4},
    [6] = {6, 7},
    [7] = {7, 6},
    [8] = {8, 9},
    [9] = {9, 8},
    [10] = {10, 11},
    [11] = {11, 10},
    [12] = {12, 13},
    [13] = {13, 12},
    [14] = {14, 15},
    [15] = {15, 14},
    [16] = {16, 17},
    [17] = {17, 16},
    [18] = {18, 19},
    [19] = {19, 18},
    [20] = {20, 21},
    [21] = {21, 20},
    [22] = {22, 23},
    [23] = {23, 22}
};

char solved_edge_definition[]   = "WBWRWGWOBOGOGRBRYGYRYBYO";
char solved_corner_definition[] = "WOBWRBWRGWOGYOGYRGYRBYOB"; 

bool is_solved(char* component, char* solved_array)
{
    // checks if any sticker doesn't match a solved cube
    for (int i = 0; i < 24; i++)
    {
        if (component[i] != solved_array[i])
        {
            return false;
        } 
    }
    return true;
}

int find_target_corner()
{
    // loop through solved corner definition, use strchr() to see at what index the buffer piece belongs
    for (int solved_idx = 0; solved_idx < 24; solved_idx += 3)
    {
        char piece[3] = { solved_corner_definition[solved_idx], solved_corner_definition[solved_idx + 1], solved_corner_definition[solved_idx + 2] };
        if (strchr(piece, corners[0]) != NULL && strchr(piece, corners[1]) != NULL && strchr(piece, corners[2]) != NULL)
        {
            return solved_idx + (strchr(piece, corners[0]) - piece);
        }
    }
    return -1;
}

int find_target_edge()
{
    // loop through solved edge definition, use strchr() to see at what index the buffer piece belongs
    for (int solved_idx = 0; solved_idx < 24; solved_idx += 2)
    {
        char piece[2] = { solved_edge_definition[solved_idx], solved_edge_definition[solved_idx + 1] };
        if (strchr(piece, edges[2]) != NULL && strchr(piece, edges[3]) != NULL)
        {
            return solved_idx + (strchr(piece, edges[2]) - piece);
        }
    }
    return -1;
}

void update_corners(char* arr, int target) 
{
    // uses a table to swap each corner sticker to its new location
    for (int i = 0; i < 3; i++)
    {
        _swap(arr, i, corner_swaps[target][i]);
    }
}

void update_edges(char* arr, int target) 
{
    // uses a table to swap each edge sticker to its new location
    for (int i = 0; i < 2; i++)
    {
        _swap(arr, i + 2, edge_swaps[target][i]);
    }
}

void solve_cube(char* cornerstate, char* edgestate)
{
    memcpy(corners, cornerstate, 24);
    memcpy(edges, edgestate, 24);
    int number_swaps = 0;

    while (is_solved(corners, solved_corner_definition) == false)
    {
        solve_corner(corners);
        number_swaps++;
    }
    //printf("\n");

    // if did uneven number of swaps, two edges will have been switched 
    if (number_swaps % 2 != 0)
    {
        _swap(edges, 0, 6);
        _swap(edges, 1, 7);
    }
    
    while (is_solved(edges, solved_edge_definition) == false)
    {
        solve_edge(edges);
    }

    //printf("\n [*] SOLVED\n");
}

void solve_corner(char* cornerstate)
{
    int target = find_target_corner();

    // if buffer is shooting to buffer we need to start a new cycle (i.e. shoot to a new unsolved piece)
    if (target == 0 || target == 1|| target == 2)
    {
        for (int i = 3; i < 24; i++)
        {
            if (cornerstate[i] != solved_corner_definition[i])
            {
                target = i;
                break;
            }
        } 
    }

    // update corners based on the desired swap 
    update_corners(cornerstate, target);
    //printf("%s {y perm} %s\n", corner_LUT[target][0], corner_LUT[target][1]);
}

void solve_edge(char* edgestate)
{
    int target = find_target_edge();

    // if buffer is shooting to buffer we need to start a new cycle (i.e. shoot to a new unsolved piece)
    if (target == 2 || target == 3)
    {
        for (int i = 0; i < 24; i++)
        {
            if (edgestate[i] != solved_edge_definition[i] && i != 2 && i != 3)
            {
                target = i;
                break;
            }
        } 
    }
    // update edges based on the desired swap 
    update_edges(edgestate, target);
    //printf("%s {t perm} %s\n", edge_LUT[target][0], edge_LUT[target][1]);
}

static void _swap(char* str, int i, int j)
{
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}