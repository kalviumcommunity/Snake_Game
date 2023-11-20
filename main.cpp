#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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

template <typename T>
class GameObject
{
public:
    int x, y;
    GameObject(int startX, int startY) : x(startX), y(startY) {}
    virtual void Draw() const = 0;
    virtual ~GameObject() {}
};

class SnakeSegment : public GameObject<SnakeSegment>
{
public:
    SnakeSegment(int startX, int startY) : GameObject(startX, startY) {}
    void Draw() const override
    {
        cout << "S";
    }
};

class Food : public GameObject<Food>
{
public:
    Food(int startX, int startY) : GameObject(startX, startY) {}

    void Draw() const override
    {
        cout << "F";
    }
};

template <typename T>
class Snake : public GameObject<Snake<T>>
{
public:
    vector<T *> segments;
    Direction direction;

    Snake(int startX, int startY) : direction(Direction::RIGHT)
    {
        segments.push_back(new T(startX, startY));
    }

    ~Snake()
    {
        for (T *segment : segments)
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

        segments.insert(segments.begin(), new T(newX, newY));
        delete segments.back();
        segments.pop_back();
    }

    void Draw()
    {
        for (T *segment : segments)
        {
            segment->Draw();
        }
    }

    void EatFood()
    {
        int tailX = segments.back()->x;
        int tailY = segments.back()->y;
        segments.push_back(new T(tailX, tailY));
    }
};

template <typename T>
class Game
{
public:
    Snake<T> *snake;
    vector<GameObject<T> *> foods;

    Game() : snake(new Snake<T>(BOARD_WIDTH / 2, BOARD_HEIGHT / 2)) {}

    ~Game()
    {
        delete snake;
        for (GameObject<T> *food : foods)
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
        for (GameObject<T> *segment : snake->segments)
        {
            if (segment->x == x && segment->y == y)
                return true;
        }
        for (GameObject<T> *food : foods)
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

                for (GameObject<T> *segment : snake->segments)
                {
                    if (segment->x == j && segment->y == i)
                    {
                        segment->Draw();
                        isSnakeOrFood = true;
                        break;
                    }
                }

                for (GameObject<T> *food : foods)
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

void clearScreen()
{
    cout << "\033[2J\033[H";
}

int main()
{
    srand(time(0));
    cout << "Starting the game..." << endl;
    Game<GameObject<int>> game; // You can replace 'int' with the appropriate type for your game

    while (true)
    {
        clearScreen();
        game.Draw();
        game.Update();
    }

    return 0;
}
