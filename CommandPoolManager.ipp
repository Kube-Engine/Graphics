/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPoolManager
 */

inline void kF::Graphics::ScopedCommandPool::release(void) noexcept
{
   if (_pool) [[likely]]
      _manager->takeBack(_pool);
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
   const auto node = reinterpret_cast<Node *>(_Allocator.allocate(sizeof(Node), alignof(Node)))

   new (node) Node {
      pool: AutoCommandPool(parent(), queueType),
      next: nullptr
   };
   return node;
}

inline void kF::Graphics::CommandPoolManager::deallocate(Node * const node) noexcept
{
   node->~Node();
   _Allocator.deallocate(node, sizeof(Node), alignof(Node));
}