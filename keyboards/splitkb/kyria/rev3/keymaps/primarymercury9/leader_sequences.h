#pragma once
#include <stdbool.h>
#include "quantum.h"
#include "qmk-vim/src/vim.h"

#if defined(LEADER_ENABLE)
extern bool is_leader_active;

void leader_start_user(void);
void leader_end_user(void);
#endif
