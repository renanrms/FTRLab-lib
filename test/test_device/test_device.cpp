#include <unity.h>
#include "FTRLab/Device.hpp"
#include "FTRLab/DeviceBuilder.hpp"
#include "MockNetworkProvider.hpp"
#include "MockDiscoveryServiceProvider.hpp"
#include "MockKeyValueStoreProvider.hpp"
#include "MockTickerProvider.hpp"
#include "MockTimeProvider.hpp"
#include "MockGpioProvider.hpp"

static Device *device = nullptr;

void setUp(void)
{
  device = DeviceBuilder()
               .withNetworkProvider(new MockNetworkProvider())
               .withDiscoveryServiceProvider(new MockDiscoveryServiceProvider())
               .withKeyValueStoreProvider(new MockKeyValueStoreProvider())
               .withTickerProvider(new MockTickerProvider())
               .withTimeProvider(new MockTimeProvider())
               .withGpioProvider(new MockGpioProvider())
               .build();
}

void tearDown(void)
{
  // Save pointers before deleting device to avoid accessing freed memory
  INetworkProvider *network           = device->networkProvider;
  IDiscoveryServiceProvider *discovery = device->discoveryServiceProvider;
  IKeyValueStoreProvider *keyValueStore = device->keyValueStoreProvider;
  ITickerProvider *ticker             = device->tickerProvider;
  ITimeProvider *timeProvider         = device->timeProvider;
  IGpioProvider *gpio                 = device->gpioProvider;
  delete device; device = nullptr;
  delete network; delete discovery; delete keyValueStore;
  delete ticker; delete timeProvider; delete gpio;
}

// ─── Tests ────────────────────────────────────────────────────────────────────

void test_setDevicePins_configures_pin_modes()
{
  device->setDevicePins(5, 2);

  auto *gpio = static_cast<MockGpioProvider *>(device->gpioProvider);
  TEST_ASSERT_EQUAL(INPUT_PULLUP, gpio->pinModes[5]);
  TEST_ASSERT_EQUAL(OUTPUT, gpio->pinModes[2]);
}

void test_forceMdnsUpdate_publishes_device_name()
{
  device->setName("Distância HC-SR04");
  device->forceMdnsUpdate();

  auto *discovery = static_cast<MockDiscoveryServiceProvider *>(device->discoveryServiceProvider);
  TEST_ASSERT_EQUAL_STRING("Distância HC-SR04", discovery->txtRecords["name"].c_str());
}

void test_forceMdnsUpdate_advertises_available_when_no_client_connected()
{
  static_cast<MockNetworkProvider *>(device->networkProvider)->clientConnected_ = false;
  device->forceMdnsUpdate();

  auto *discovery = static_cast<MockDiscoveryServiceProvider *>(device->discoveryServiceProvider);
  TEST_ASSERT_EQUAL_STRING("true", discovery->txtRecords["available"].c_str());
}

void test_forceMdnsUpdate_advertises_unavailable_when_client_connected()
{
  static_cast<MockNetworkProvider *>(device->networkProvider)->clientConnected_ = true;
  device->forceMdnsUpdate();

  auto *discovery = static_cast<MockDiscoveryServiceProvider *>(device->discoveryServiceProvider);
  TEST_ASSERT_EQUAL_STRING("false", discovery->txtRecords["available"].c_str());
}

void test_forceMdnsUpdate_reports_time_not_synced_by_default()
{
  device->forceMdnsUpdate();

  auto *discovery = static_cast<MockDiscoveryServiceProvider *>(device->discoveryServiceProvider);
  TEST_ASSERT_EQUAL_STRING("false", discovery->txtRecords["timeSynced"].c_str());
}

void test_setupMdns_schedules_periodic_mdns_update()
{
  device->setName("Timer Test");
  device->setupMdns();

  static_cast<MockTickerProvider *>(device->tickerProvider)->tick();

  auto *discovery = static_cast<MockDiscoveryServiceProvider *>(device->discoveryServiceProvider);
  TEST_ASSERT_EQUAL_STRING("Timer Test", discovery->txtRecords["name"].c_str());
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main(int argc, char **argv)
{
  UNITY_BEGIN();

  RUN_TEST(test_setDevicePins_configures_pin_modes);
  RUN_TEST(test_forceMdnsUpdate_publishes_device_name);
  RUN_TEST(test_forceMdnsUpdate_advertises_available_when_no_client_connected);
  RUN_TEST(test_forceMdnsUpdate_advertises_unavailable_when_client_connected);
  RUN_TEST(test_forceMdnsUpdate_reports_time_not_synced_by_default);
  RUN_TEST(test_setupMdns_schedules_periodic_mdns_update);

  UNITY_END();
  return 0;
}
