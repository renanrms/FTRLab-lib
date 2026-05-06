// Stub do ambiente Arduino para compilação nativa em testes.
// Provê os tipos e funções mínimos para que o código do Device compile sem hardware real.

#ifndef ARDUINO_H
#define ARDUINO_H

#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>

// FreeRTOS stubs
typedef void *TaskHandle_t;
typedef void *SemaphoreHandle_t;
typedef int BaseType_t;
typedef unsigned int UBaseType_t;

#define portMAX_DELAY 0xffffffffUL
#define pdTRUE 1
#define pdFALSE 0
#define pdPASS 1
#define pdFAIL 0
#define tskIDLE_PRIORITY 0
#define configMAX_PRIORITIES 25
#define PRO_CPU_NUM 0

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Atributos ESP32 inexistentes em builds nativos
#define IRAM_ATTR

// Modos WiFi e status (espelhados de WiFi.h do Arduino/ESP32)
enum WiFiMode
{
  WIFI_OFF = 0,
  WIFI_STA = 1,
  WIFI_AP = 2,
  WIFI_AP_STA = 3
};

enum WiFiStatus
{
  WL_NO_SHIELD = 255,
  WL_IDLE_STATUS = 0,
  WL_NO_SSID_AVAIL = 1,
  WL_SCAN_COMPLETED = 2,
  WL_CONNECTED = 3,
  WL_CONNECT_FAILED = 4,
  WL_CONNECTION_LOST = 5,
  WL_DISCONNECTED = 6
};

// ─── String ──────────────────────────────────────────────────────────────────

class String
{
  std::string data;

public:
  String() : data("") {}
  String(const char *str) : data(str ? str : "") {}
  String(const std::string &str) : data(str) {}
  String(const String &other) : data(other.data) {}
  String(String &&other) noexcept : data(std::move(other.data)) {}

  // Construtores numéricos
  explicit String(int n) : data(std::to_string(n)) {}
  explicit String(unsigned int n) : data(std::to_string(n)) {}
  explicit String(long n) : data(std::to_string(n)) {}
  explicit String(unsigned long n) : data(std::to_string(n)) {}
  explicit String(long long n) : data(std::to_string(n)) {}
  explicit String(unsigned long long n) : data(std::to_string(n)) {}
  String(float n, int decimals = 2)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.*f", decimals, (double)n);
    data = buf;
  }
  String(double n, int decimals = 2)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.*f", decimals, n);
    data = buf;
  }

  String &operator=(const String &other)
  {
    data = other.data;
    return *this;
  }
  String &operator=(const char *str)
  {
    data = str ? str : "";
    return *this;
  }

  String operator+(const String &other) const { return String(data + other.data); }
  String operator+(const char *other) const { return String(data + (other ? other : "")); }
  String &operator+=(const String &other)
  {
    data += other.data;
    return *this;
  }
  String &operator+=(const char *other)
  {
    data += other ? other : "";
    return *this;
  }

  bool operator==(const String &other) const { return data == other.data; }
  bool operator!=(const String &other) const { return data != other.data; }
  bool operator<(const String &other) const { return data < other.data; }
  bool operator>(const String &other) const { return data > other.data; }

  // Concatenação com literal à esquerda: "str" + String(...)
  friend String operator+(const char *left, const String &right)
  {
    return String(std::string(left ? left : "") + right.data);
  }

  const char *c_str() const { return data.c_str(); }
  operator const char *() const { return data.c_str(); }
  int length() const { return (int)data.length(); }
  bool isEmpty() const { return data.empty(); }

  String substring(int from) const
  {
    if (from < 0)
      from = 0;
    if (from >= (int)data.size())
      return String();
    return String(data.substr(from));
  }
  String substring(int from, int to) const
  {
    if (from < 0)
      from = 0;
    if (to > (int)data.size())
      to = (int)data.size();
    if (from >= to)
      return String();
    return String(data.substr(from, to - from));
  }

  int indexOf(const String &str) const
  {
    size_t pos = data.find(str.data);
    return pos == std::string::npos ? -1 : (int)pos;
  }
  int indexOf(const char *str) const
  {
    if (!str)
      return -1;
    size_t pos = data.find(str);
    return pos == std::string::npos ? -1 : (int)pos;
  }
};

// ─── Serial ──────────────────────────────────────────────────────────────────

class SerialClass
{
public:
  void begin(unsigned long) {}
  template <typename T>
  void print(T) {}
  template <typename T>
  void print(T, int) {}
  template <typename T>
  void println(T) {}
  template <typename T>
  void println(T, int) {}
  void println() {}
};

inline SerialClass Serial;

// ─── ESP (chip info) ─────────────────────────────────────────────────────────

class EspClass
{
public:
  uint64_t getEfuseMac() { return 0x112233445566ULL; }
};

inline EspClass ESP;

// ─── GPIO ────────────────────────────────────────────────────────────────────

inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t, uint8_t) {}
inline int digitalRead(uint8_t) { return 0; }
inline void delay(unsigned long) {}
inline void delayMicroseconds(unsigned long) {}

// ─── FreeRTOS ────────────────────────────────────────────────────────────────

typedef void (*TaskFunction_t)(void *);
inline BaseType_t xTaskCreatePinnedToCore(TaskFunction_t, const char *, uint32_t, void *, UBaseType_t, TaskHandle_t *, BaseType_t) { return pdPASS; }
inline void vTaskDelete(TaskHandle_t) {}
inline void vTaskDelay(uint32_t) {}
inline SemaphoreHandle_t xSemaphoreCreateMutex() { return (SemaphoreHandle_t)malloc(1); }
inline void vSemaphoreDelete(SemaphoreHandle_t sem) { free(sem); }
inline BaseType_t xSemaphoreTake(SemaphoreHandle_t, uint32_t) { return pdTRUE; }
inline BaseType_t xSemaphoreGive(SemaphoreHandle_t) { return pdTRUE; }
inline UBaseType_t xPortGetCoreID() { return 0; }

#endif
