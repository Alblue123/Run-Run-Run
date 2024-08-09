#include "Player.hpp"

Player::Player(std::pair<int, int> pos, const bool& face)
    :
      faceRight(face),
      posStart(pos),
      face_Right(face)
{

    animation = new Animation("Data//Textures//Player//player_ani.png", {6, 8}, 100);
    animation->currFrame = {6, 0};

    setSize({40, 40});
    setRect(pos);

    collision = new Collision(*this);
    player.loadIMG("Data//Textures//Player//player_ani.png");
    player.setSize({40, 40});
    player.setRect(getPos());
}

Player::~Player() {
    if (collision != nullptr) {
        delete collision;
    }

    if (animation != nullptr){
        delete animation;
    }
}

void Player::updateAnimation(const Uint32& deltaTime) {
    std::function<bool(const Uint32&)> updates[] = {
        [&](const Uint32& dt) { return updateStart(dt); },
        [&](const Uint32& dt) { return updateEnd(dt); },
    };
    for (auto& update : updates) {
        if (update(deltaTime)) {
            return;
        }
    }

    updateMove(deltaTime);
}

void Player::render(){
    player.render(animation->getFlip(), animation->getRect());
}

void Player::update(const Uint32& deltaTime) {
    posOld = getPos();
    player.setRect(posOld);

    /*if (moveQuick > 0) {
        HandleQuickMove();
    }*/
    handleInput(deltaTime);
    if (!canJump) {
        applyGravity(deltaTime);
    }

    updateAnimation(deltaTime);

    resetState();

    if (shouldMovePlayer()) {
        movePlayer(deltaTime);
    }
}

void Player::handleInput(const Uint32& deltaTime) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    vel.first = 0;
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        vel.first += speed;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        vel.first -= speed;
    }
    if (currentKeyStates[SDL_SCANCODE_SPACE] && canJump) {
        jump();
    }
}

void Player::jump() {
    vel.second = -sqrt(2.0f * 981.0f * jumHeight);
    canJump = false;
}

void Player::applyGravity(const Uint32& deltaTime) {
    vel.second += 981.0f * static_cast<float>(deltaTime) / 1000;
}

void Player::resetState() {
    canJump = false;
    animation->update(0, faceRight);
}

bool Player::shouldMovePlayer() const {
    return !start && !end;
}

void Player::movePlayer(const Uint32& deltaTime) {
    movePos({static_cast<int>(vel.first * deltaTime / 1000),
          static_cast<int>(vel.second * deltaTime / 1000)});
    player.setRect(getPos());
}

bool Player::updateStart(const Uint32& deltaTime) {
    if (!start) {
        return false;
    }

    animation->currTime += deltaTime;
    if (animation->currTime >= animation->getSwitchTime()) {
        animation->currTime -= animation->getSwitchTime();

        if (animation->currFrame.second != 0) {
            animation->currFrame = {6, 0};
        } else {
            if (--animation->currFrame.first == 0) {
                start = false;
            }
        }
    }

    animation->update(faceRight);
    return start;
}

bool Player::updateEnd(const Uint32& deltaTime) {
    if (!end) {
        return false;
    }

    if (animation->update(deltaTime, {6, 0}, faceRight)) {
        deletePlayer = true;
    }

    if (deletePlayer) {
        reset();
    }

    return !deletePlayer;
}

void Player::updateMove(const Uint32& deltaTime) {
    auto updateAnimation = [&](const std::pair<int, int>& frameRange) {
        animation->update(deltaTime, frameRange, faceRight);
    };

    if (vel.first == 0) {
        if (canJump) {
            updateAnimation({4, 2});
        } /*else {
            updateAnimation(vel.second < 0 ? std::make_pair(3, 7) : std::make_pair(3, 6));
        }*/
    } else {
        faceRight = vel.first < 0;

        if (canJump) {
            updateAnimation({6, 1});
        } /*else {
            updateAnimation(vel.second < 0 ? std::make_pair(3, 7) : std::make_pair(3, 6));
        }*/
    }
}

void Player::reset() {
    animation->currFrame = {6, 0};
    start = true;
    end = false;
    deletePlayer = false;
    canJump = false;

    setRect(posStart);
    faceRight = face_Right;
}

