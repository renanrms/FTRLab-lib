#include <unity.h>
#include "FTRLab/Device.hpp"
#include "FTRLab/DeviceBuilder.hpp"
#include "MockNetworkProvider.hpp"
#include "MockDiscoveryServiceProvider.hpp"
#include "MockKeyValueStoreProvider.hpp"
#include "MockTickerProvider.hpp"
#include "MockTimeProvider.hpp"
#include "MockGpioProvider.hpp"
#include "MockSensor.hpp"

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
  INetworkProvider *network            = device->networkProvider;
  IDiscoveryServiceProvider *discovery = device->discoveryServiceProvider;
  IKeyValueStoreProvider *keyValueStore = device->keyValueStoreProvider;
  ITickerProvider *ticker              = device->tickerProvider;
  ITimeProvider *timeProvider          = device->timeProvider;
  IGpioProvider *gpio                  = device->gpioProvider;
  Device::resetInstance();
  device = nullptr;
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

// ─── Setters ──────────────────────────────────────────────────────────────────

void test_setTargetSampleRate_converts_hz_to_microseconds()
{
  device->setTargetSampleRate(100.0f);
  TEST_ASSERT_EQUAL_INT64(10000, device->targetTakingPeriod);
}

void test_setTargetSendingFrequency_converts_hz_to_microseconds()
{
  device->setTargetSendingFrequency(10.0f);
  TEST_ASSERT_EQUAL_INT64(100000, device->targetSendingPeriod);
}

void test_addSensor_appends_sensors_in_order()
{
  MockSensor s1, s2;
  device->addSensor(&s1);
  device->addSensor(&s2);

  TEST_ASSERT_EQUAL_UINT(2, device->sensors.size());
  TEST_ASSERT_EQUAL_PTR(&s1, device->sensors[0]);
  TEST_ASSERT_EQUAL_PTR(&s2, device->sensors[1]);
}

// ─── Measurement pipeline ─────────────────────────────────────────────────────

void test_takeMeasurement_enqueues_one_measurement_with_correct_index_and_value()
{
  MockSensor sensor;
  device->takeMeasurement(&sensor, 3);

  TEST_ASSERT_EQUAL_UINT(1, device->measurements.size());
  TEST_ASSERT_EQUAL_UINT(3, device->measurements.front().index);
  TEST_ASSERT_EQUAL_STRING("42.0", device->measurements.front().measure.c_str());
}

void test_takeMeasurement_timestamp_is_midpoint_of_micros_in_seconds()
{
  // MockTimeProvider avança 1000 μs por chamada; t1=1000, t2=2000 → midpoint=1500 μs = 0.0015 s
  MockSensor sensor;
  device->takeMeasurement(&sensor, 0);

  TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.0015, device->measurements.front().timestamp);
}

void test_takeMeasurement_handles_sensor_exception_without_crash()
{
  MockSensor sensor;
  sensor.shouldThrow = true;
  device->takeMeasurement(&sensor, 0);

  TEST_ASSERT_EQUAL_UINT(0, device->measurements.size());
}

void test_takeAllMeasurements_enqueues_one_measurement_per_sensor()
{
  MockSensor s1, s2, s3;
  device->addSensor(&s1);
  device->addSensor(&s2);
  device->addSensor(&s3);

  device->takeAllMeasurements();

  TEST_ASSERT_EQUAL_UINT(3, device->measurements.size());
}

void test_takeAllMeasurements_assigns_sequential_indices()
{
  MockSensor s1, s2;
  device->addSensor(&s1);
  device->addSensor(&s2);

  device->takeAllMeasurements();

  Measurement first = device->measurements.front();
  device->measurements.pop();
  Measurement second = device->measurements.front();

  TEST_ASSERT_EQUAL_UINT(0, first.index);
  TEST_ASSERT_EQUAL_UINT(1, second.index);
}

// ─── Send pipeline ────────────────────────────────────────────────────────────

void test_sendMeasurementsBatch_formats_json_payload()
{
  device->measurements.push({0u, 1.5, "42.0"});

  unsigned sent = device->sendMeasurementsBatch();

  auto *net = static_cast<MockNetworkProvider *>(device->networkProvider);
  TEST_ASSERT_EQUAL_UINT(1, sent);
  TEST_ASSERT_EQUAL_STRING("\n{\"measurements\":[[\"0\",1.500000,42.0]]}\n",
                           net->lastPrinted.c_str());
}

void test_sendMeasurementsBatch_empty_queue()
{
  unsigned sent = device->sendMeasurementsBatch();

  auto *net = static_cast<MockNetworkProvider *>(device->networkProvider);
  TEST_ASSERT_EQUAL_UINT(0, sent);
  TEST_ASSERT_EQUAL_STRING("\n{\"measurements\":[]}\n", net->lastPrinted.c_str());
}

void test_sendMeasurements_empty_queue_returns_zero_without_printing()
{
  unsigned total = device->sendMeasurements();

  auto *net = static_cast<MockNetworkProvider *>(device->networkProvider);
  TEST_ASSERT_EQUAL_UINT(0, total);
  TEST_ASSERT_EQUAL_STRING("", net->lastPrinted.c_str());
}

void test_sendMeasurements_drains_queue_completely()
{
  device->measurements.push({0u, 1.0, "10.0"});
  device->measurements.push({1u, 2.0, "20.0"});

  unsigned total = device->sendMeasurements();

  TEST_ASSERT_EQUAL_UINT(2, total);
  TEST_ASSERT_TRUE(device->measurements.empty());
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

  RUN_TEST(test_setTargetSampleRate_converts_hz_to_microseconds);
  RUN_TEST(test_setTargetSendingFrequency_converts_hz_to_microseconds);
  RUN_TEST(test_addSensor_appends_sensors_in_order);

  RUN_TEST(test_takeMeasurement_enqueues_one_measurement_with_correct_index_and_value);
  RUN_TEST(test_takeMeasurement_timestamp_is_midpoint_of_micros_in_seconds);
  RUN_TEST(test_takeMeasurement_handles_sensor_exception_without_crash);
  RUN_TEST(test_takeAllMeasurements_enqueues_one_measurement_per_sensor);
  RUN_TEST(test_takeAllMeasurements_assigns_sequential_indices);

  RUN_TEST(test_sendMeasurementsBatch_formats_json_payload);
  RUN_TEST(test_sendMeasurementsBatch_empty_queue);
  RUN_TEST(test_sendMeasurements_empty_queue_returns_zero_without_printing);
  RUN_TEST(test_sendMeasurements_drains_queue_completely);

  UNITY_END();
  return 0;
}
