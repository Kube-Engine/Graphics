/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Unit tests of renderer
 */

#include <gtest/gtest.h>

#include <Kube/Graphics/MemoryAllocationModel.hpp>

using namespace kF;

TEST(MemoryAllocationModel, InitDestroy)
{
    {
        Graphics::MemoryAllocationModel model(Graphics::DeviceBuffer{}, Graphics::MemoryUsage::DeviceOnly);
        ASSERT_EQ(model.memoryUsage(), Graphics::MemoryUsage::DeviceOnly);
        ASSERT_EQ(model.memoryType(), Graphics::MemoryType::Buffer);
    }
    {
        Graphics::MemoryAllocationModel model(Graphics::DeviceImage{}, Graphics::MemoryUsage::DeviceToHost);
        ASSERT_EQ(model.memoryUsage(), Graphics::MemoryUsage::DeviceToHost);
        ASSERT_EQ(model.memoryType(), Graphics::MemoryType::Image);
    }
}
