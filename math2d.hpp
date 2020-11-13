#define MATRIX_ROWS 50
#define MATRIX_COLS 50
typedef struct position{
    float x, y;
}position;

typedef struct decision_matrix{
    float matrix[MATRIX_COLS][MATRIX_ROWS];
} decision_matrix;
