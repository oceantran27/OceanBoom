#include "Bomb.h"

#define EXPLOSION_TIME 2000


Bomb::Bomb()
{
	m_timer_id = 0;
}

Bomb::~Bomb()
{
	//
}


void Bomb::plant() {
    if (!is_active()) {
        start_timer();
    }
}

void Bomb::explode() {
    stop_timer();
    printf("Bom exploded!\n");
}

Uint32 Bomb::timer_callback(Uint32 interval, void* param) {
    Bomb* bom = static_cast<Bomb*>(param);
    bom->explode();
    return 0;
}

void Bomb::start_timer() {
    m_timer_id = SDL_AddTimer(2000, timer_callback, this);
}

void Bomb::stop_timer() {
    SDL_RemoveTimer(m_timer_id);
    m_timer_id = 0;
}


