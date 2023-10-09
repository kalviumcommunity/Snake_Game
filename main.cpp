#include <iostream>
using namespace std;

class Snake
{
public:
    // It will contain the dimensional variables

    void Draw()
    {
        // This will contain the draw function code.
    }

    void Update()
    {
        // This will contain the update function code.
    }

    void Reset()
    {
        // This will contain the Reset function code.
    }
};

class Food
{
    public :
        // This will contain the Food parameters.
        void Draw()
        {
            // this will contain the texture and appearance of food
        }
        void GenerateRandomCell()
        {
            // this will contain the generateRandomCell functionalities
        }

        void GenerateRandomPos(){
            // this will contain the generateRandomPos functionalities
        }
};

class Game
{
    public: 
        // This will contain the game board parameters. 

        void Draw()
        {
            // Will Call the draw methods here
        }

        void Update()
        {
            // Will Call the update methods here
        }

        void CheckCollisionWithFood()
        {
            // Will Add conditionals for checking collision with food here
        }

        void CheckCollisionWithEdges()
        {
            // Will Add conditionals for checking collision with edges here
        }

        void GameOver()
        {
            // Will Add gameOver functionalities here
        }

        void CheckCollisionWithTail()
        {
            // Will Add conditionals for checking collision with tail here
        }
};

int main()
{
    cout << "Starting the game..." << endl;
    Game game = Game();
    return 0;
}