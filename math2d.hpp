#define MATRIX_ROWS 50
#define MATRIX_COLS 50
class position{
    public:
        position();
        position(float x, float y);
        float x, y;
};

position::position(){
    x = 0;
    y = 0;
}
position::position(float x, float y):x{x}, y{y}{
}

class decision_matrix{
    public:
        decision_matrix();
        float matrix[MATRIX_COLS][MATRIX_ROWS];
};

decision_matrix::decision_matrix(){
    for(int i = 0; i<MATRIX_COLS; i++){
        for(int j = 0; j<MATRIX_COLS; j++){
            this->matrix[i][j] = 0;
        }
    }
}
