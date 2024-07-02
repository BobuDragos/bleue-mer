#include "../../Engine/engine.h"

const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

Vector3 centers[9];

Vector3 A = Vector3(-0.5f, 0.75f);
Vector3 B = Vector3(-0.1667f, 0.75f);
Vector3 C = Vector3(0.1667f, 0.75f);
Vector3 D = Vector3(0.5f, 0.75f);

Vector3 E = Vector3(-0.5f, 0.5833f);
Vector3 F = Vector3(-0.1667f, 0.5833f);
Vector3 G = Vector3(0.1667f, 0.5833f);
Vector3 H = Vector3(0.5f, 0.5833f);

Vector3 I = Vector3(-0.5f, 0.4166f);
Vector3 J = Vector3(-0.1667f, 0.4166f);
Vector3 K = Vector3(0.1667f, 0.4166f);
Vector3 L = Vector3(0.5f, 0.4166f);

Vector3 M = Vector3(-0.5f, 0.25f);
Vector3 N = Vector3(-0.1667f, 0.25f);
Vector3 O = Vector3(0.1667f, 0.25f);
Vector3 P = Vector3(0.5f, 0.25f);

// Player and AI symbols
const char PLAYER = 'X';
const char AI = 'O';

void update();

int main()
{
    RenderEngine::setStart([]() {
        RenderEngine::background(Color(255));
        RenderEngine::strokeWeight(10);
        centers[0].x = (A.x + F.x) / 2;
        centers[0].y = (A.y + F.y) / 2;

        centers[1].x = (B.x + G.x) / 2;
        centers[1].y = (B.y + G.y) / 2;

        centers[2].x = (C.x + H.x) / 2;
        centers[2].y = (C.y + H.y) / 2;

        centers[3].x = (E.x + J.x) / 2;
        centers[3].y = (E.y + J.y) / 2;

        centers[4].x = (F.x + K.x) / 2;
        centers[4].y = (F.y + K.y) / 2;

        centers[5].x = (G.x + L.x) / 2;
        centers[5].y = (G.y + L.y) / 2;

        centers[6].x = (I.x + N.x) / 2;
        centers[6].y = (I.y + N.y) / 2;

        centers[7].x = (J.x + O.x) / 2;
        centers[7].y = (J.y + O.y) / 2;

        centers[8].x = (K.x + P.x) / 2;
        centers[8].y = (K.y + P.y) / 2;
    });
    RenderEngine::setUpdate(update);
    RenderEngine::Enabled(true);
}

bool isMovesLeft(char board[BOARD_SIZE][BOARD_SIZE])
{
    // Check if there are any empty spots left on the board
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == ' ')
            {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char board[BOARD_SIZE][BOARD_SIZE])
{
    // Evaluate the current state of the board
    // +10 for AI win, -10 for player win, 0 for draw
    // This function assumes the AI is 'O' and player is 'X'

    // Check rows for a win
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    // No winner, return 0 for a draw
    return 0;
}

int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, bool isMaximizing)
{
    int score = evaluate(board);

    // If AI has won the game, return the score
    if (score == 10)
        return score;

    // If player has won the game, return the score
    if (score == -10)
        return score;

    // If there are no more moves left, it's a draw
    if (!isMovesLeft(board))
        return 0;

    // If maximizing turn (AI's turn)
    if (isMaximizing)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                // Check if cell is empty
                if (board[i][j] == ' ')
                {
                    // Make the move
                    board[i][j] = AI;

                    // Call minimax recursively and choose the maximum value
                    best = std::max(best, minimax(board, depth + 1, !isMaximizing));

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else // Minimizing turn (Player's turn)
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                // Check if cell is empty
                if (board[i][j] == ' ')
                {
                    // Make the move
                    board[i][j] = PLAYER;

                    // Call minimax recursively and choose the minimum value
                    best = std::min(best, minimax(board, depth + 1, !isMaximizing));

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void findBestMove(char board[BOARD_SIZE][BOARD_SIZE])
{
    int bestVal = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    // Traverse all cells, evaluate minimax function for all empty cells.
    // And return the cell with optimal value.
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            // Check if cell is empty
            if (board[i][j] == ' ')
            {
                // Make the move
                board[i][j] = AI;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = ' ';

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal)
                {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    // Make the best move
    board[bestMoveRow][bestMoveCol] = AI;
}

void drawGrid()
{
  ///// OUTSIDE
// TOP
RenderEngine::line(A, D);
// LEFT
RenderEngine::line(A, M);
// RIGHT
RenderEngine::line(D, P);
// BOTTOM
RenderEngine::line(M, P);

///// INSIDE
RenderEngine::line(E, H);
RenderEngine::line(I, L);
RenderEngine::line(B, N);
RenderEngine::line(C, O);

}

void update()
{
    RenderEngine::background(255);
    RenderEngine::stroke(0);
    RenderEngine::strokeWeight(10);
  drawGrid();
    float w = 1.0f / 3;
    float h = 1.0f / 3;
    int center_idx = 0;

    // Render squares
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            Vector3 size(0.25, 0.1); // Example size for the rectangles

            if (board[i][j] == 'X')
            {
                RenderEngine::stroke(Color::red);
            }
            else if (board[i][j] == 'O')
            {
                RenderEngine::stroke(Color::blue);
            }
            else if (board[i][j] == ' ')
            {
                RenderEngine::stroke(Color::white);
            }

            RenderEngine::rect(centers[center_idx++], size);
        }
    }

    static bool playerTurn = true; // true for player's turn, false for AI's turn

    if (playerTurn)
    {
        if (GameEngine::Input::getKeyDown(GameEngine::KEY_7) && board[0][0] == ' ')
        {
            board[0][0] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_8) && board[0][1] == ' ')
        {
            board[0][1] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_9) && board[0][2] == ' ')
        {
            board[0][2] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_4) && board[1][0] == ' ')
        {
            board[1][0] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_5) && board[1][1] == ' ')
        {
            board[1][1] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_6) && board[1][2] == ' ')
        {
            board[1][2] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_1) && board[2][0] == ' ')
        {
            board[2][0] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_2) && board[2][1] == ' ')
        {
            board[2][1] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
        else if (GameEngine::Input::getKeyDown(GameEngine::KEY_3) && board[2][2] == ' ')
        {
            board[2][2] = 'X';
            playerTurn = false; // Switch to AI's turn
        }
    }
    else
    {
        // AI's turn
        findBestMove(board);
        playerTurn = true; // Switch to player's turn
    }
}


// #include "../../Engine/engine.h"

// void start();
// void update();

// int main()
// {
//   // RenderEngine::setAwake(awake);
//   RenderEngine::setStart(start);
//   RenderEngine::setUpdate(update);
//   // RenderEngine::setFixedUpdate(fixedUpdate);
//   RenderEngine::Enabled(true);
// }


// const int BOARD_SIZE = 3;
// char board[BOARD_SIZE][BOARD_SIZE] = {
//   {' ', ' ', ' '},
//   {' ', ' ', ' '},
//   {' ', ' ', ' '}
// };

// void start()
// {
//   RenderEngine::background(0);
//   RenderEngine::strokeWeight(10);

//   // for (int i = 0; i < BOARD_SIZE; ++i) {
//   //   for (int j = 0; j < BOARD_SIZE; ++j) {
//   //     GameObject& cell = cells[i][j];
//   //     cell.transform.position = Vector3(BOARD_OFFSET_X + j * CELL_SIZE + CELL_SIZE / 2, BOARD_OFFSET_Y + i * CELL_SIZE + CELL_SIZE / 2);
//   //     cell.transform.scale = Vector3(CELL_SIZE - 10, CELL_SIZE - 10);
//   //     cell.renderer.color = Color::white;


//   //     cell.show();
//   //   }
//   // }

//   // dvd.rigidbody.velocity       = Vector3(0.01, 0.001);

//   // vWalls[0].transform.position = Vector3(-1,  0);
//   // vWalls[0].transform.scale    = Vector3(0.01, 2);
//   // 
//   // vWalls[1].transform.position = Vector3( 1,  0);
//   // vWalls[1].transform.scale    = Vector3(0.01, 2);

//   // hWalls[0].transform.position = Vector3( 0, -1);
//   // hWalls[0].transform.scale    = Vector3(2, 0.01);
//   // 
//   // hWalls[1].transform.position = Vector3( 0,  1);
//   // hWalls[1].transform.scale    = Vector3(2, 0.01);
// }



// Vector3 centers[9];




// // A ----      B ----      C----      D
// // -           -           -         -
// // -           -           -         -
// // E-----      F-----      G-----     H
// // -           -          -           -
// // -           -          -          -
// // I-----       J-----     K-----     L
// // -           -          -           -
// // -           -          -          -
// // M-----      N-----     O-----      P



// void update()
// {

//   RenderEngine::background(Color(255));

//   float w = 1.0f / 3;
//   float h = 1.0f / 3;

//   RenderEngine::strokeWeight(10);
//   RenderEngine::stroke(Color(0));


//   // RenderEngine::line(Vector3(0.2, 0.1) , Vector3(0.7, 0.1));



// Vector3 A = Vector3(-0.5f, 0.75f);
// Vector3 B = Vector3(-0.1667f, 0.75f);
// Vector3 C = Vector3(0.1667f, 0.75f);
// Vector3 D = Vector3(0.5f, 0.75f);

// Vector3 E = Vector3(-0.5f, 0.5833f);
// Vector3 F = Vector3(-0.1667f, 0.5833f);
// Vector3 G = Vector3(0.1667f, 0.5833f);
// Vector3 H = Vector3(0.5f, 0.5833f);

// Vector3 I = Vector3(-0.5f, 0.4166f);
// Vector3 J = Vector3(-0.1667f, 0.4166f);
// Vector3 K = Vector3(0.1667f, 0.4166f);
// Vector3 L = Vector3(0.5f, 0.4166f);

// Vector3 M = Vector3(-0.5f, 0.25f);
// Vector3 N = Vector3(-0.1667f, 0.25f);
// Vector3 O = Vector3(0.1667f, 0.25f);
// Vector3 P = Vector3(0.5f, 0.25f);

// ///// OUTSIDE
// // TOP
// RenderEngine::line(A, D);
// // LEFT
// RenderEngine::line(A, M);
// // RIGHT
// RenderEngine::line(D, P);
// // BOTTOM
// RenderEngine::line(M, P);

// ///// INSIDE
// RenderEngine::line(E, H);
// RenderEngine::line(I, L);
// RenderEngine::line(B, N);
// RenderEngine::line(C, O);


//     centers[0].x = (A.x + F.x) / 2;
//     centers[0].y = (A.y + F.y) / 2;

//     centers[1].x = (B.x + G.x) / 2;
//     centers[1].y = (B.y + G.y) / 2;

//     centers[2].x = (C.x + H.x) / 2;
//     centers[2].y = (C.y + H.y) / 2;

//     centers[3].x = (E.x + J.x) / 2;
//     centers[3].y = (E.y + J.y) / 2;

//     centers[4].x = (F.x + K.x) / 2;
//     centers[4].y = (F.y + K.y) / 2;

//     centers[5].x = (G.x + L.x) / 2;
//     centers[5].y = (G.y + L.y) / 2;

//     centers[6].x = (I.x + N.x) / 2;
//     centers[6].y = (I.y + N.y) / 2;

//     centers[7].x = (J.x + O.x) / 2;
//     centers[7].y = (J.y + O.y) / 2;

//     centers[8].x = (K.x + P.x) / 2;
//     centers[8].y = (K.y + P.y) / 2;

//   int center_idx = 0;
//     // Render squares
//   for (int i = 0; i < BOARD_SIZE; ++i) 
//   {
//     for (int j = 0; j < BOARD_SIZE; ++j) 
//     {
//       Vector3 size(0.25, 0.1); // Example size for the rectangles

//       if (board[i][j] == 'X') {
//         RenderEngine::stroke(Color::red);
//       } else if (board[i][j] == 'O') {
//         RenderEngine::stroke(Color::blue);
//       } else if (board[i][j] == ' ') {
//         RenderEngine::stroke(Color::white);
//       }

//       RenderEngine::rect(centers[center_idx++], size);
//     }
//   }

//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_Q) && board[0][0] == ' ') {
//             board[0][0] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_W) && board[0][1] == ' ') {
//             board[0][1] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_E) && board[0][2] == ' ') {
//             board[0][2] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_R) && board[1][0] == ' ') {
//             board[1][0] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_T) && board[1][1] == ' ') {
//             board[1][1] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_Y) && board[1][2] == ' ') {
//             board[1][2] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_U) && board[2][0] == ' ') {
//             board[2][0] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_I) && board[2][1] == ' ') {
//             board[2][1] = 'X';
//         }
//         if (GameEngine::Input::getKeyDown(GameEngine::KEY_O) && board[2][2] == ' ') {
//             board[2][2] = 'X';
//         }
// }



