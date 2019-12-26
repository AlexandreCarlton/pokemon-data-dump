#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#include <array>

// https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_base_stats_data_structure_in_Generation_I
// Little endian.

enum class GrowthRate : uint8_t
{
  MEDIUM_FAST = 0,
  MEDIUM_SLOW = 3,
  FAST = 4,
  SLOW = 5,
};

enum class Type : uint8_t
{
  NORMAL = 0x00,
  FIGHTING = 0x01,
  FLYING = 0x02,
  POISON = 0x03,
  GROUND = 0x04,
  ROCK = 0x05,
  BIRD = 0x06,
  BUG = 0x07,
  GHOST = 0x08,
  // 0x09 - 0x13 are blank
  FIRE = 0x14,
  WATER = 0x15,
  GRASS = 0x16,
  ELECTRIC = 0x17,
  PSYCHIC = 0x18,
  ICE = 0x19,
  DRAGON = 0x1A,
};

#pragma pack(push, 1)
struct BaseStats
{
  uint8_t PokedexNumber;
  uint8_t BaseHP;
  uint8_t BaseAttack;
  uint8_t BaseDefense;
  uint8_t BaseSpeed;
  uint8_t BaseSpecial;
  Type Type1;
  Type Type2;
  uint8_t CatchRate;
  uint8_t BaseExpYield;
  uint8_t FrontspriteDimensions;
  uint16_t FrontSpritePointer; // high nibble is width, low is height
  uint16_t BackSpritePointer;
  uint32_t Level1Attacks; // should probably be an array
  GrowthRate growthRate;
  uint8_t TMHMFlags[7]; // bit #i is set if it can learn TM #i. HMs are TM 51-55. Starts from LSB of first byte.
  uint8_t _Padding;
};
#pragma pack(pop)

static_assert(sizeof(BaseStats) == 28, "Base status structure size should be 28 bytes");

int main(int argc, char *argv[])
{
  (void) argc; (void) argv;

  std::ifstream ifs("Pokemon - Yellow Version (USA, Europe).gbc", std::ios::binary);
  std::array<char, 1024 * 1024> buffer;
  ifs.read(buffer.data(), buffer.size());

  if (!ifs.is_open())
  {
    throw std::runtime_error("File not found");
  }

  uint32_t species_data_location = 0x383DE;
  for (size_t i = species_data_location; i < species_data_location + 151 * sizeof(BaseStats); i += sizeof(BaseStats))
  {
      BaseStats& stats = *reinterpret_cast<BaseStats*>(&buffer[i]);
      std::cout
        << "Number: " << static_cast<uint32_t>(stats.PokedexNumber) << ", "
        << "HP: " << static_cast<uint32_t>(stats.BaseHP) << ", "
        << "Attack: " << static_cast<uint32_t>(stats.BaseAttack) << ", "
        << "Defense: " << static_cast<uint32_t>(stats.BaseDefense) << ", "
        << "Special: " << static_cast<uint32_t>(stats.BaseSpecial) << ", "
        << "Speed: " << static_cast<uint32_t>(stats.BaseSpeed)
        << std::endl;
  }


  return 0;
}
