/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include "MemoryAllocator.hpp"

using namespace kF;

Graphics::MemoryAllocation Graphics::MemoryAllocator::allocate(const MemoryAllocationModel &model)
{
    
}

void Graphics::MemoryAllocator::deallocate(const MemoryAllocation allocation)
{

}

Graphics::MemoryAllocation Graphics::MemoryAllocator::allocate(const std::vector<MemoryAllocationModel> &models)
{

}

void Graphics::MemoryAllocator::deallocate(const std::vector<MemoryAllocation> &allocations)
{

}