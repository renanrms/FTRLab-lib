#include <unity.h>
#include "FTRLab/Device.hpp"
#include "FTRLab/boards/esp32/ESP32DeviceBuilder.hpp"

static Device *device = nullptr;

void setUp(void)
{
  device = ESP32DeviceBuilder().build();
}

void tearDown(void)
{
  INetworkProvider *network              = device->networkProvider;
  IDiscoveryServiceProvider *discovery   = device->discoveryServiceProvider;
  IKeyValueStoreProvider *keyValueStore  = device->keyValueStoreProvider;
  ITickerProvider *ticker                = device->tickerProvider;
  ITimeProvider *timeProvider            = device->timeProvider;
  IGpioProvider *gpio                    = device->gpioProvider;
  delete device; device = nullptr;
  delete network; delete discovery; delete keyValueStore;
  delete ticker; delete timeProvider; delete gpio;
}

// ─── Key-value store ──────────────────────────────────────────────────────────

void test_key_value_store_persists_and_retrieves_string()
{
  device->keyValueStoreProvider->putString("it_key", "it_value");

  TEST_ASSERT_TRUE(device->keyValueStoreProvider->isKey("it_key"));
  TEST_ASSERT_EQUAL_STRING("it_value", device->keyValueStoreProvider->getString("it_key").c_str());
}

void test_key_value_store_returns_default_for_missing_key()
{
  TEST_ASSERT_FALSE(device->keyValueStoreProvider->isKey("it_missing"));
  TEST_ASSERT_EQUAL_STRING("default", device->keyValueStoreProvider->getString("it_missing", "default").c_str());
}

// ─── GPIO ─────────────────────────────────────────────────────────────────────

void test_gpio_set_pin_modes_without_crash()
{
  device->gpioProvider->pinMode(2, OUTPUT);
  device->gpioProvider->pinMode(5, INPUT_PULLUP);
  TEST_PASS();
}

void test_gpio_digital_write_without_crash()
{
  device->gpioProvider->pinMode(2, OUTPUT);
  device->gpioProvider->digitalWrite(2, HIGH);
  device->gpioProvider->digitalWrite(2, LOW);
  TEST_PASS();
}

// ─── Entry point (Arduino framework) ─────────────────────────────────────────

void setup()
{
  Serial.begin(115200);

  UNITY_BEGIN();

  RUN_TEST(test_key_value_store_persists_and_retrieves_string);
  RUN_TEST(test_key_value_store_returns_default_for_missing_key);
  RUN_TEST(test_gpio_set_pin_modes_without_crash);
  RUN_TEST(test_gpio_digital_write_without_crash);

  UNITY_END();
}

void loop() {}
