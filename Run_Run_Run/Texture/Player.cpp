#include "Player.hpp"

Player::Player(std::pair<int, int> pos, const bool& faceRightStart)
    : startPos(pos), faceRightStart(faceRightStart) {
    animation = new Animation("Data//Textures//Player//player_ani.png", {6, 8}, 100);
    collision = new Collision(*this);

    setSize({50, 50});
    setRect(pos);

    player.loadIMG("Data//Textures//Player//player_ani.png");
    player.setSize({50, 50});
    player.setRect(getPos());

    face_Right = faceRightStart;
    animation->currFrame = {6, 7};
}

Player::~Player() {
    delete collision;
    delete animation;
}

void Player::update(const Uint32& deltaTime) {
    oldPos = getPos();
    player.setRect(getPos());

    handleMovement(deltaTime);
    applyGravity(deltaTime);

    limitPos();
    updateAnimation(deltaTime);

    canJump = false;
    pushBox = false;

    if (!start && !end && !attack.isActive && !teleportation) {
        movePos({(int)vel.first * (int)deltaTime / 1000,
                 (int)vel.second * (int)deltaTime / 1000});
        player.setRect(getPos());
    }

    if (start) attack.isActive = false;
}

void Player::handleMovement(const Uint32& deltaTime) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (canJump) vel.second = 0;
    vel.first = 0;

    if (teleportation > 0) {
        teleportation--;
        movePos({20 * (face_Right ? -1 : 1), 0});
        player.setRect(getPos());
    }

    if (!teleportation) {
        if (currentKeyStates[SDL_SCANCODE_D]) vel.first += speed;
        if (currentKeyStates[SDL_SCANCODE_A]) vel.first -= speed;
        if (currentKeyStates[SDL_SCANCODE_SPACE] && canJump) {
            Mix_PlayChannel(-1, jump, 0);
            vel.second = -sqrt(2.0f * 981.0f * jumHeight);
            canJump = false;
        }
         if (currentKeyStates[SDL_SCANCODE_E] && attack.isActive == false){
            Mix_PlayChannel(-1, slash, 0);
            attack.isActive = true;
            vel = {0, 0};
            attack.animation->currFrame = {6, 0};
        }
    }

    if (currentKeyStates[SDL_SCANCODE_F] && teleportation == 0 && timeClickS <= 0) {
        Mix_PlayChannel(-1, teleport, 0);
        teleportation = 8;
        timeClickS = 1000;
        vel = {0, 0};
    }

    timeClickS -= (int)deltaTime;
}

void Player::applyGravity(const Uint32& deltaTime) {
    if (!canJump && !teleportation) {
        vel.second += 981.0f * (float)deltaTime / 1000;
    }
}

void Player::updateAnimation(const Uint32& deltaTime) {
    if (updateStart(deltaTime) ||
        updateEnd(deltaTime) ||
        updatePushBox(deltaTime) ||
        updateWinGame(deltaTime) ||
        updateTeleportation(deltaTime) ||
        updateAttack(deltaTime)) {
        return;
    }
    updateMove(deltaTime);
}

bool Player::updateStart(const Uint32& deltaTime) {
    if (!start) return false;

    animation->currTime += deltaTime;
    if (animation->currTime >= animation->getSwitchTime()) {
        animation->currTime -= animation->getSwitchTime();
        if (animation->currFrame.second != 0) {
            animation->currFrame = {6, 0};
        } else {
            animation->currFrame.first--;
            if (animation->currFrame.first == 0) start = false;
        }
    }
    animation->update(face_Right);
    return start;
}

bool Player::updateEnd(const Uint32& deltaTime) {
    if (!end) return false;
    Mix_PlayChannel(-1, death, 0);

    if (animation->update(deltaTime, {6, 7}, face_Right)) delPlayer = true;
    if (delPlayer) reset();

    return !delPlayer;
}

bool Player::updateWinGame(const Uint32& deltaTime) {
    if (!wingame) return false;

    if (animation->update(deltaTime, {6, 0}, face_Right)) delPlayer = true;
    return !delPlayer;
}

bool Player::updatePushBox(const Uint32& deltaTime) {
    if (pushBox && vel.first != 0) {
        Mix_PlayChannel(-1, push, 0);
        animation->update(deltaTime, {4, 6}, face_Right);
        return true;
    }
    return false;
}

bool Player::updateTeleportation(const Uint32& deltaTime) {
    if (!teleportation) return false;

    animation->currFrame = {6, 1};
    face_Right = vel.first > 0 ? true : vel.first < 0 ? false : face_Right;
    animation->update(0, face_Right);
    return teleportation;
}

bool Player::updateAttack(const Uint32& deltaTime) {
    int offset = face_Right ? -50 : 50;
    attack.setRect({getPos().first + offset, getPos().second + 10});

    if (!attack.isActive) return false;

    if (animation->update(deltaTime, {6, 4}, face_Right)) {
        attack.isActive = false;
    }

    attack.animation->update(deltaTime, {4, 0}, face_Right);

    return attack.isActive;
}

void Player::updateMove(const Uint32& deltaTime) {
    if (vel.first == 0) {
        if (canJump) {
            animation->update(deltaTime, {6, 0}, face_Right);
        } else {
            animation->update(deltaTime, std::make_pair(4, 2), face_Right);
        }
    } else {
        face_Right = (vel.first > 0) ? false : true;

        if (canJump) {
            animation->update(deltaTime, {6, 1}, face_Right);
        } else {
            animation->update(deltaTime, std::make_pair(4, 2), face_Right);
        }
    }
}



void Player::limitPos() {
    if (getPos().first < 0) {
        setRect({0, getPos().second});
    }

    if (getPos().first + getSize().first > SCREEN_WIDTH) {
        setRect({SCREEN_WIDTH - getSize().first, getPos().second});
    }

    if (getPos().second > SCREEN_HEIGHT + 100) {
        end = true;
    }
}

void Player::render() {
    player.render(animation->getFlip(), animation->getRect());

    if (attack.isActive) attack.render();
}

void Player::reset() {
    animation->currFrame = {6, 7};
    start = true;
    end = false;
    delPlayer = false;
    canJump = false;
    setRect(startPos);
    face_Right = faceRightStart;
    _totalHearts--;
}
