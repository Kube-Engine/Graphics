/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocation
 */

#include "Renderer.hpp"
#include "MemoryAllocation.hpp"

using namespace kF;
Graphics::MemoryAllocation::~MemoryAllocation(void) noexcept
{
    parent().memoryAllocator().deallocate(handle());
}


void Graphics::MemoryAllocation::createMemoryAllocation(const MemoryAllocationModel &model)
{
    handle() = parent().memoryAllocator().allocate(model);
}