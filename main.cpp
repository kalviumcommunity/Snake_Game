#include <iostream>
#include <vector>

// Class for the Snake Game
class SnakeGame
{
public:
    SnakeGame(int width, int height);

    void start();
    void update();
    void render();
    void gameOver();

private:
    int width_;
    int height_;
    bool gameOver_;
    int score_;

    // Class for the Snake
    class Snake
    {
    public:
        Snake(int x, int y);

        void move();
        void grow();
        bool checkCollision(int x, int y);

    private:
        std::vector<std::pair<int, int>> body_;
        int direction_;
    };

    // Class for the Food (Apple)
    class Food
    {
    public:
        Food(int width, int height);

        void respawn();
        int getX() const;
        int getY() const;

    private:
        int x_;
        int y_;
        int width_;
        int height_;
    };

    Snake snake_;
    Food food_;
};

// The Main Function
int main()
{
    SnakeGame game(20, 10); 
    game.start();          
    return 0;
}