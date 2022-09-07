///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_CODEC_H
#define PERCEPTION_COMMUNICATION_I_CODEC_H

#include <type_traits>

namespace perception
{
namespace communication
{

/// @brief Interface for Conversion of the Types from Independent to Platform and vice-versa.
///
/// @tparam IndependentType - Platform Independent Type (used to communicate within the System)
/// @tparam PlatformType - Platform Dependent Type (used to communicate outside of the System)
///
/// @warning IndependentType and PlatformType must be POD (Plain-Old DataType). Otherwise Codec is compile-time
/// disabled with type error - (i.e. Compilation may FAIL)
template <typename IndependentType_,
          typename PlatformType_,
          std::enable_if_t<std::is_pod<IndependentType_>::value, bool> = true,
          std::enable_if_t<std::is_pod<PlatformType_>::value, bool> = true>
class ICodec
{
  public:
    /// @brief Alias for Independent Type
    using IndependentType = IndependentType_;

    /// @brief Alias for Platform Type
    using PlatformType = PlatformType_;

    /// @brief Default Destructor
    virtual ~ICodec() = default;

    /// @brief Encode to Middleware (i.e. Convert Independent to PlatformType)
    ///
    /// @param independent_type [in] - Platform Independent Type
    ///
    /// @return platform_type
    virtual PlatformType EncodeToMiddleware(const IndependentType& independent_type) const = 0;

    /// @brief Decode from Middleware (i.e. Convert PlatformType to IndependentType)
    ///
    /// @param platform_type [in] - Platform Dependent Type
    ///
    /// @return independent_type
    virtual IndependentType DecodeFromMiddleware(const PlatformType& platform_type) const = 0;
};

}  // namespace communication
}  // namespace perception
#endif  /// PERCEPTION_COMMUNICATION_I_CODEC_H
