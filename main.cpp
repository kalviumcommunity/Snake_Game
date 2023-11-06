#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 10;
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GameObject
{
public:
    int x, y;
    GameObject(int startX, int startY) : x(startX), y(startY) {}
    virtual void Draw() const = 0;
    virtual ~GameObject() {}
};

class SnakeSegment : public GameObject
{
public:
    SnakeSegment(int startX, int startY) : GameObject(startX, startY) {}
    void Draw() const override
    {
        cout << "S";
    }
};

class Food : public GameObject
{
public:
    Food(int startX, int startY) : GameObject(startX, startY) {}

    void Draw() const override
    {
        cout << "F";
    }
};

class Snake
{
public:
    vector<SnakeSegment *> segments;
    Direction direction;

    Snake(int startX, int startY) : direction(Direction::RIGHT)
    {
        segments.push_back(new SnakeSegment(startX, startY));
    }

    ~Snake()
    {
        for (SnakeSegment *segment : segments)
        {
            delete segment;
        }
    }

    void Move()
    {
        int newX = segments.front()->x;
        int newY = segments.front()->y;

        switch (direction)
        {
        case Direction::UP:
            newY--;
            break;
        case Direction::RIGHT:
            newX++;
            break;
        case Direction::DOWN:
            newY++;
            break;
        case Direction::LEFT:
            newX--;
            break;
        }
        segments.insert(segments.begin(), new SnakeSegment(newX, newY));
        delete segments.back();
        segments.pop_back();
    }

    void Draw()
    {
        for (SnakeSegment *segment : segments)
        {
            segment->Draw();
        }
    }

    void EatFood()
    {
        int tailX = segments.back()->x;
        int tailY = segments.back()->y;
        segments.push_back(new SnakeSegment(tailX, tailY));
    }
};

class Game
{
public:
    Snake *snake;
    vector<Food *> foods;

    Game() : snake(new Snake(BOARD_WIDTH / 2, BOARD_HEIGHT / 2)) {}

    ~Game()
    {
        delete snake;
        for (Food *food : foods)
        {
            delete food;
        }
    }

    void GenerateFood()
    {
        int x, y;
        do
        {
            x = rand() % BOARD_WIDTH;
            y = rand() % BOARD_HEIGHT;
        } while (isOccupied(x, y));
        foods.push_back(new Food(x, y));
    }

    bool isOccupied(int x, int y)
    {
        for (SnakeSegment *segment : snake->segments)
        {
            if (segment->x == x && segment->y == y)
                return true;
        }
        for (Food *food : foods)
        {
            if (food->x == x && food->y == y)
                return true;
        }
        return false;
    }

    void Draw()
    {
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                bool isSnakeOrFood = false;

                for (SnakeSegment *segment : snake->segments)
                {
                    if (segment->x == j && segment->y == i)
                    {
                        segment->Draw();
                        isSnakeOrFood = true;
                        break;
                    }
                }

                for (Food *food : foods)
                {
                    if (food->x == j && food->y == i)
                    {
                        food->Draw();
                        isSnakeOrFood = true;
                        break;
                    }
                }

                if (!isSnakeOrFood)
                {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }

    void Update()
    {
        snake->Move();

        int headX = snake->segments.front()->x;
        int headY = snake->segments.front()->y;

        for (size_t i = 1; i < snake->segments.size(); i++)
        {
            if (snake->segments[i]->x == headX && snake->segments[i]->y == headY)
            {
                // Game over
                exit(0);
            }
        }

        for (size_t i = 0; i < foods.size(); i++)
        {
            if (foods[i]->x == headX && foods[i]->y == headY)
            {
                snake->EatFood();
                delete foods[i];
                foods.erase(foods.begin() + i);
                GenerateFood();
                break;
            }
        }
    }
};

int main()
{
    srand(time(0));
    cout << "Starting the game..." << endl;
    Game game;

    while (true)
    {
        system("cls");
        game.Draw();
        game.Update();
    }

    return 0;
}
