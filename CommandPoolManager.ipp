/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPoolManager
 */

inline void kF::Graphics::CommandPoolManager::ScopedCommandPool::release(void) noexcept
{
   if (_node) [[likely]]
      _manager->takeBack(_node);
}

inline void kF::Graphics::CommandPoolManager::acquireNextFrame(void) noexcept_ndebug
{
   kFAssert(!_activeScopedCount.load(),
      throw std::logic_error("Graphics::CommandPoolManager::acquireNextFrame: Can't acquire next frame as there are "
         + std::to_string(_activeScopedCount.load()) + " active scoped command pools"));
   _cachedFrames.incrementFrame();
}

inline kF::Graphics::CommandPoolManager::Node *kF::Graphics::CommandPoolManager::allocate(const QueueType queueType) noexcept
{
   return new (_Allocator.allocate(sizeof(Node), alignof(Node))) Node {
      pool: AutoCommandPool(parent(), queueType),
      next: nullptr
   };
}

inline void kF::Graphics::CommandPoolManager::deallocate(Node * const node) noexcept
{
   node->~Node();
   _Allocator.deallocate(node, sizeof(Node), alignof(Node));
}