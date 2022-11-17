#include <string>
#include <vector>
#include <random>

namespace Mercury
{

  class InputType
  {
  protected:
    explicit InputType() = default;

  public:
    virtual std::string GenerateRandomInput() = 0;
  };

  class InputIntType : InputType
  {
  public:
    explicit InputIntType();
    explicit InputIntType(int MinLimit, int MaxLimit);

    virtual std::string GenerateRandomInput() override;

  private:
    constexpr static int SpecialValues[] = {
        0, 1, 2, -1, -2,
        0x7fffffff, 0x80000000, 0x80000001,
        0x3fffffff, 0x40000000, 0x40000001,
        0xbfffffff, 0xc0000000, 0xc0000001};

  private:
    std::uniform_int_distribution<> NumberDistribution;
  };

  class InputCharType : InputType
  {
  public:
    InputCharType() = default;

    virtual std::string GenerateRandomInput() override;

  protected:
    static std::uniform_int_distribution<char> AsciiDistribution;
  };

  class InputStringType : InputCharType
  {
  public:
    explicit InputStringType(std::size_t MinLength, std::size_t MaxLength);

    virtual std::string GenerateRandomInput() override;

  private:
    static std::uniform_int_distribution<std::size_t> LengthDistribution;
  };

}
