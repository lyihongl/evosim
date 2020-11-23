typedef struct actions{
    float v_x, v_y, theta;
} actions;

void calculate_action(actions& output, float*** input);
