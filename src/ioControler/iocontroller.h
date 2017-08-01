#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

/**
 * @file iocontroller.h
 */

class GameController;

/**
 * @brief The IoController class The abstract controller of input and output. It is the interface between the user and the game controller.
 */
class IoController
{
public:
    /**
     * @brief IoController The constructor.
     * @param gameController The game controller that this controller will use.
     */
    IoController(GameController *gameController);
    virtual ~IoController();
    /**
     * @brief launchGame Launch the game. This is pure virtual because it will depend of the how you want to play (graphics or console).
     */
    virtual void launchGame() = 0;

    /**
     * @brief getGameController Get the game controller.
     * @return The game controller.
     */
    GameController *getGameController() const;

private:
    /**
     * @brief gameController The game controller that this controller will use.
     */
    GameController *gameController;
};

#endif // INPUTCONTROLLER_H