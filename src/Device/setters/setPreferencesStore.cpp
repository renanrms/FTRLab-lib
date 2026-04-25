#include "FTRLab/Device.hpp"

void Device::setPreferencesStore(IKeyValueStoreProvider *preferencesStore)
{
  this->keyValueStoreProvider = preferencesStore;
}
