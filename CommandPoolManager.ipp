/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPoolManager
 */

inline void kF::Graphics::CommandPoolManager::ScopedCommandPool::release(void) noexcept
{
   if (_node) [[likely]]
      _manager->takeBack(_node);
}

inline void kF::Graphics::CommandPoolManager::onFrameAquired(const FrameIndex frameIndex) noexcept_ndebug
{
   kFAssert(!_activeScopedCount.load(),
      throw std::logic_error("Graphics::CommandPoolManager::onFrameAquired: Can't acquire next frame as there are "
         + std::to_string(_activeScopedCount.load()) + " active scoped command pools"));
   _cachedFrames.setCurrentFrame(frameIndex);
   for (auto &pool : _cachedFrames.currentCache()) {
      auto current = pool.head.load();
      while (current != nullptr) {
         current->pool.clear();
         current = current->next;
      }
   }
}

inline kF::Graphics::CommandPoolManager::Node *kF::Graphics::CommandPoolManager::allocate(const QueueType queueType) noexcept
{
   return new (_Allocator.allocate(sizeof(Node), alignof(Node))) Node {
      pool: AutoCommandPool(queueType),
      next: nullptr
   };
}

inline void kF::Graphics::CommandPoolManager::deallocate(Node * const node) noexcept
{
   node->~Node();
   _Allocator.deallocate(node, sizeof(Node), alignof(Node));
}