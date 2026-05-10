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

#include "taskboard.h"
#include "thingtypemanager.h"

#include <algorithm>
#include <ctime>
#include <limits>

namespace TaskBoard {

uint8_t getTalismanMaxLevel(const uint8_t pathIndex)
{
    switch (pathIndex) {
        case 0:
        case 1:
        case 2:
            return 166;
        case 3:
            return 180;
        default:
            return 166;
    }
}

uint16_t getTalismanBonusHundredths(const uint8_t level, const uint8_t pathIndex)
{
    if (level == 0) {
        return 0;
    }

    switch (pathIndex) {
        case 0:
        case 1:
        case 2: {
            if (level <= 26) {
                return static_cast<uint16_t>(250 + (static_cast<uint32_t>(level) - 1U) * 50U);
            }
            return static_cast<uint16_t>(std::min<uint32_t>(1500U + (static_cast<uint32_t>(level) - 26U) * 25U, 5000U));
        }
        case 3: {
            if (level <= 20) {
                return static_cast<uint16_t>(static_cast<uint32_t>(level) * 100U);
            }
            return static_cast<uint16_t>(std::min<uint32_t>(2000U + (static_cast<uint32_t>(level) - 20U) * 50U, 10000U));
        }
        default:
            return 0;
    }
}

uint8_t getRemainingDaysUntil(const uint32_t unixTimestamp)
{
    if (unixTimestamp == 0) {
        return 0;
    }

    const auto now = static_cast<uint32_t>(std::time(nullptr));
    if (unixTimestamp <= now) {
        return 0;
    }

    const auto remainingSeconds = unixTimestamp - now;
    const auto rawDays = (remainingSeconds + SECONDS_PER_DAY - 1U) / SECONDS_PER_DAY;
    return static_cast<uint8_t>(std::min<uint32_t>(rawDays, 255U));
}

std::vector<uint16_t> getAllMonsterRaceIds()
{
    const auto races = g_things.getRacesByName("");
    std::vector<uint16_t> raceIds;
    raceIds.reserve(races.size());

    for (const auto& race : races) {
        if (race.boss || race.raceId == 0 || race.raceId > std::numeric_limits<uint16_t>::max()) {
            continue;
        }
        raceIds.emplace_back(static_cast<uint16_t>(race.raceId));
    }

    std::sort(raceIds.begin(), raceIds.end());
    raceIds.erase(std::unique(raceIds.begin(), raceIds.end()), raceIds.end());
    return raceIds;
}

std::map<std::string, uint32_t> toBountyHeaderMap(const TaskBoardBountyHeaderData& header)
{
    return {
        { "rerollPoints", header.rerollPoints },
        { "claimDaily", header.claimDaily },
        { "difficulty", header.difficulty }
    };
}

std::map<std::string, uint32_t> toBountyMonsterMap(const TaskBoardBountyMonsterData& monster)
{
    return {
        { "taskIndex", monster.taskIndex },
        { "raceId", monster.raceId },
        { "currentKills", monster.currentKills },
        { "totalKills", monster.totalKills },
        { "rewardXp", monster.rewardXp },
        { "rewardPoints", monster.rewardPoints },
        { "rewardReroll", monster.rewardReroll },
        { "rarity", monster.rarity },
        { "isActive", monster.isActive },
        { "isCompleted", monster.isCompleted }
    };
}

std::map<std::string, uint32_t> toTalismanMap(const TaskBoardTalismanData& talisman)
{
    return {
        { "currentValue", talisman.currentValue },
        { "nextValue", talisman.nextValue },
        { "upgradeCost", talisman.upgradeCost },
        { "isActiveUpgrade", talisman.isActiveUpgrade }
    };
}

std::map<std::string, uint32_t> toPreferredSlotMap(const TaskBoardPreferredSlotData& slot)
{
    return {
        { "slot", slot.slot },
        { "locked", slot.locked },
        { "preferred", slot.preferred },
        { "unwanted", slot.unwanted },
        { "price", slot.price }
    };
}

std::map<std::string, uint32_t> toWeeklyHeaderMap(const TaskBoardWeeklyHeaderData& header)
{
    return {
        { "difficulty", header.difficulty },
        { "currentPlayerLevel", header.currentPlayerLevel },
        { "remainingDays", header.remainingDays },
        { "totalTaskSlots", header.totalTaskSlots },
        { "maxExperience", header.maxExperience },
        { "maxDeliveryExperience", header.maxDeliveryExperience },
        { "completedKillTasks", header.completedKillTasks },
        { "completedDeliveryTasks", header.completedDeliveryTasks },
        { "pointsEarned", header.pointsEarned },
        { "soulsealsEarned", header.soulsealsEarned },
        { "extraSlot", header.extraSlot }
    };
}

std::map<std::string, uint32_t> toWeeklyMonsterMap(const TaskBoardWeeklyMonsterData& monster)
{
    return {
        { "raceId", monster.raceId },
        { "current", monster.current },
        { "total", monster.total },
        { "state", monster.state }
    };
}

std::map<std::string, uint32_t> toWeeklyItemMap(const TaskBoardWeeklyItemData& item)
{
    return {
        { "slotIndex", item.slotIndex },
        { "itemId", item.itemId },
        { "current", item.current },
        { "total", item.total },
        { "claimed", item.claimed },
        { "state", item.state }
    };
}

std::map<std::string, std::string> toShopItemMap(const TaskBoardShopItemData& item)
{
    return {
        { "id", std::to_string(item.id) },
        { "offerType", std::to_string(item.offerType) },
        { "title", item.title },
        { "description", item.description },
        { "price", std::to_string(item.price) },
        { "bought", std::to_string(item.bought) },
        { "lookType", std::to_string(item.lookType) },
        { "lookAddons", std::to_string(item.lookAddons) },
        { "itemId", std::to_string(item.itemId) },
        { "maxPurchases", std::to_string(item.maxPurchases) },
        { "currentPurchases", std::to_string(item.currentPurchases) },
        { "nextCost", std::to_string(item.nextCost) }
    };
}

} // namespace TaskBoard
