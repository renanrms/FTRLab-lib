#include "FTRLab/Device.hpp"

void Device::setKeyValueStoreProvider(IKeyValueStoreProvider *keyValueStoreProvider)
{
  this->keyValueStoreProvider = keyValueStoreProvider;
}
