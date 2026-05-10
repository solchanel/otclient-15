/*
 * Copyright (c) 2010-2025 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "staticdata.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace TaskBoard {

constexpr uint8_t TALISMAN_PATHS = 4;
constexpr uint8_t WEEKLY_BASE_SLOTS = 6;
constexpr uint8_t WEEKLY_EXPANDED_SLOTS = 9;
constexpr uint32_t SECONDS_PER_DAY = 24U * 60U * 60U;

uint8_t getTalismanMaxLevel(uint8_t pathIndex);
uint16_t getTalismanBonusHundredths(uint8_t level, uint8_t pathIndex);
uint8_t getRemainingDaysUntil(uint32_t unixTimestamp);
std::vector<uint16_t> getAllMonsterRaceIds();

std::map<std::string, uint32_t> toBountyHeaderMap(const TaskBoardBountyHeaderData& header);
std::map<std::string, uint32_t> toBountyMonsterMap(const TaskBoardBountyMonsterData& monster);
std::map<std::string, uint32_t> toTalismanMap(const TaskBoardTalismanData& talisman);
std::map<std::string, uint32_t> toPreferredSlotMap(const TaskBoardPreferredSlotData& slot);
std::map<std::string, uint32_t> toWeeklyHeaderMap(const TaskBoardWeeklyHeaderData& header);
std::map<std::string, uint32_t> toWeeklyMonsterMap(const TaskBoardWeeklyMonsterData& monster);
std::map<std::string, uint32_t> toWeeklyItemMap(const TaskBoardWeeklyItemData& item);
std::map<std::string, std::string> toShopItemMap(const TaskBoardShopItemData& item);

} // namespace TaskBoard
