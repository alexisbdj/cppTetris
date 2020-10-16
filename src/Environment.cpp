/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Environment
*/

#include <iostream>
#include "Environment.hpp"

namespace Tetris {

Environment::Environment() : action_queue(), gameWidth(10), gameHeight(25), gameMatrix(gameWidth, gameHeight),
currentTetr(sevenBag.getNext(), tetrstats, gameMatrix), ghost(currentTetr), timePerFall(sf::seconds(1)), timeLeftToFall(timePerFall),
gravityMultiplier(1), hasLost(false), currentHold(0)
{
    for (int i = 0; i < 4; i++) {
        this->nextQueue.push_back(sevenBag.getNext());
    }
    this->setGravity(1);
    groundcollision = 0;
    combo = 0;
    didHold = false;
}

Environment::~Environment()
{
}

bool Environment::didLost()
{
    return hasLost;
}

TetrminoId Environment::getCurrentHold()
{
    return currentHold;
}

void Environment::performAction(Tetris::Action action, GameMode &gamemode)
{
    if (action == Tetris::Action::MoveLeft) {
        this->currentTetr.move(this->gameMatrix, sf::Vector2i(-1, 0));
        groundcollision = 0;
    }
    else if (action == Tetris::Action::MoveRight){
        this->currentTetr.move(this->gameMatrix, sf::Vector2i(1, 0));
        groundcollision = 0;
    }
    else if (action == Tetris::Action::SoftDropOn)
        this->gravityMultiplier = softDropMultiplier;
    else if (action == Tetris::Action::SoftDropOff)
        this->gravityMultiplier = 1;
    else if (action == Tetris::Action::HardDrop) {
        while (!this->currentTetr.fall(this->gameMatrix));
        lock(gamemode);
    }
    else if (action == Tetris::RotateLeft) {
        this->currentTetr.rotate(this->gameMatrix, this->tetrstats, -1);
        groundcollision = 0;
    }
    else if (action == Tetris::RotateRight) {
        this->currentTetr.rotate(this->gameMatrix, this->tetrstats, 1);
        groundcollision = 0;
    }
    else if (action == Tetris::Hold)
        hold();
}

ActiveTetrimino &Environment::getGhost()
{
    return ghost;
}

void Environment::updateGhost()
{
    ghost = currentTetr;
    while (ghost.move(gameMatrix, sf::Vector2i(0, -1)));
}

void Environment::hold()
{
    if (didHold)
        return;
    TetrminoId current = currentTetr.getCurrentId();
    TetrminoId newId;
    if (this->currentHold == 0) {
        newId = takeFromNextQueue();
    }
    else
        newId = currentHold;
    currentHold = current;
    try {
        currentTetr = ActiveTetrimino(newId, tetrstats, gameMatrix);
    }
    catch (const CantSpawnError &error) {
        hasLost = true;
    }
    didHold = true;
}

void Environment::setGravity(float g)
{
    this->timePerFall = sf::seconds(1 / g);
    this->softDropMultiplier = (5 / (g / 5));
    if (this->softDropMultiplier < 1)
        this->softDropMultiplier = 1;
}

void Environment::frame(sf::Time deltaTime, GameMode &gamemode)
{
    if (hasLost)
        return;
    while (this->action_queue.size() > 0) {
        Tetris::Action currentAction = this->action_queue.front();
        performAction(currentAction, gamemode);
        this->action_queue.pop();
    }
    if (hasLost)
        return;
    timeLeftToFall -= deltaTime * gravityMultiplier;
    if (timeLeftToFall.asSeconds() < 0) {
        timeLeftToFall += timePerFall;
        if (this->currentTetr.fall(this->gameMatrix)) {
            groundcollision += (1 / gravityMultiplier);
            if (groundcollision >= 1) {
                lock(gamemode);
                groundcollision = 0;
            }
        }
        else {
            groundcollision = 0;
        }
    }
    updateGhost();
}

bool Environment::isTspin()
{
    sf::Vector2i corners[4] = {
            {0, 2},
            {2, 2},
            {2, 4},
            {0, 4},
    };
    int counter = 0;
    if (this->currentTetr.getCurrentId() != 3)
        return false;
    sf::Vector2u pos = currentTetr.getPosition();
    for (int i = 0; i < 4; i++) {
        if (gameMatrix(corners[i].x + pos.x, corners[i].y + pos.y) != 0)
            counter++;
    }
    return counter >= 3;
}

bool Environment::addToActionQueue(Tetris::Action action)
{
    if (action < 0 || action >= Tetris::Action::Count)
        return false;
    this->action_queue.push(action);
    return true;
}

Tetriminos &Environment::getTetriStats()
{
    return tetrstats;
}

const std::vector<TetrminoId> &Environment::getNext() const
{
    return this->nextQueue;
}

void Environment::lock(GameMode &gamemode)
{
    didHold = false;
    sf::Vector2u pos = currentTetr.getPosition();
    Matrix<unsigned char> mat = currentTetr.getMatrix();
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (mat(x, y) != 0)
                this->gameMatrix(x + pos.x, y + pos.y) = mat(x, y);
        }
    }
    checklines(gamemode);
    try {
        currentTetr = ActiveTetrimino(takeFromNextQueue(), tetrstats, gameMatrix);
    }
    catch (const CantSpawnError &error) {
        hasLost = true;
    }
}

bool Environment::checkLine(int y)
{
    for (int x = 0; x < gameWidth; x++) {
        if (gameMatrix(x, y) == 0)
            return false;
    }
    return true;
}

void Environment::clearLine(int y)
{
    for (int n = y; n < gameHeight; n++) {
        for (int x = 0; x < gameWidth; x++) {
            if ((n + 1) >= gameHeight) {
                gameMatrix(x, n) = 0;
            }
            else {
                gameMatrix(x, n) = gameMatrix(x, n + 1);
            }
        }
    }
}

void Environment::checklines(GameMode &gamemode)
{
    int lines = 0;
    bool tspin = isTspin();
    combo++;
    for (int y = 0; y < gameHeight; y++) {
        while (checkLine(y)) {
            clearLine(y);
            lines++;
        }
    }
    if (lines > 0)
        gamemode.lineCleared(lines, tspin, combo, *this);
    else
        combo = 0;
}

TetrminoId Environment::takeFromNextQueue()
{
    TetrminoId id = this->nextQueue[0];
    this->nextQueue.erase(nextQueue.begin());
    nextQueue.push_back(sevenBag.getNext());
    return id;
}

TetrminoId &Environment::at(int x, int y)
{
    return this->gameMatrix(x, y);
}

ActiveTetrimino &Environment::getActive()
{
    return this->currentTetr;
}

}