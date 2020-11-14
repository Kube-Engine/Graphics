/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPoolManager
 */

#include "Renderer.hpp"
#include "CommandPoolManager.hpp"

using namespace kF;

Graphics::CommandPoolManager::CommandPoolManager(void) noexcept
   : _cachedFrames(parent().cachedFrameCount())
{
}

Graphics::CommandPoolManager::~CommandPoolManager(void) noexcept_ndebug
{
   kFAssert(!_activeScopedCount.load(),
      throw std::logic_error("Graphics::CommandPoolManager::~CommandPoolManager: Can't destroy manager as there are "
         + std::to_string(_activeScopedCount.load()) + " active scoped command pools"));
   for (auto &cache : _cachedFrames.caches()) {
      for (auto &pool : cache) {
         auto current = pool.head.load();
         decltype(current) next;
         while (current) {
            next = current->next;
            deallocate(current);
            current = next;
         }
      }
   }
}

Graphics::CommandPoolManager::ScopedCommandPool Graphics::CommandPoolManager::acquire(const QueueType queueType)
{
   auto &cachedPool = _cachedFrames.currentCache()[static_cast<std::size_t>(queueType)];
   auto expected = cachedPool.head.load();
   decltype(expected) desired;

#if KUBE_DEBUG_BUILD
   ++_activeScopedCount;
#endif
   while (true) {
      if (expected) [[likely]]
         desired = expected->next;
      else [[unlikely]]
         return ScopedCommandPool(allocate(queueType), this);
      if (cachedPool.head.compare_exchange_weak(expected, desired)) [[likely]]
         break;
   }
   return ScopedCommandPool(expected, this);
}

void Graphics::CommandPoolManager::takeBack(Node * const node) noexcept
{
   auto &cachedPool = _cachedFrames.currentCache()[static_cast<std::size_t>(node->pool.queueType())];
   const auto desired = node;
   auto expected = cachedPool.head.load();

   while (true) {
      if (expected) [[likely]]
         node->next = expected;
      else [[unlikely]]
         node->next = nullptr;
      if (cachedPool.head.compare_exchange_weak(expected, desired)) [[likely]]
         break;
   }
#if KUBE_DEBUG_BUILD
   --_activeScopedCount;
#endif
}