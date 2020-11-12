/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Unit tests of renderer
 */

#include <gtest/gtest.h>

#include <Kube/Graphics/MemoryAllocationModel.hpp>

using namespace kF;

TEST(MemoryAllocationModel, Constructor)
{
    {
        Graphics::MemoryAllocationModel model(Graphics::BufferHandle{}, Graphics::MemoryUsage::GpuOnly);
        ASSERT_EQ(model.bindType(), Graphics::MemoryAllocationModel::BindType::Buffer);
        ASSERT_EQ(model.memoryUsage(), Graphics::MemoryUsage::GpuOnly);
    }
    {
        Graphics::MemoryAllocationModel model(Graphics::ImageHandle{}, Graphics::MemoryUsage::CpuToGpu);
        ASSERT_EQ(model.bindType(), Graphics::MemoryAllocationModel::BindType::Image);
        ASSERT_EQ(model.memoryUsage(), Graphics::MemoryUsage::CpuToGpu);
    }
}
