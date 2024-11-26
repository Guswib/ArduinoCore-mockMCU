#include "analogWave.h"

void analogWave::init(pin_size_t pinNumber) {

  buffer = nullptr;
  size = 0;
  index = 0;
  _amplitude = 1.1;

  dac_bits = 0;

}

analogWave::analogWave(pin_size_t pinNumber) {
;
}

analogWave::analogWave(pin_size_t pinNumber, uint16_t *_buffer, uint32_t _size,
                       uint32_t _offset) {
  
  buffer = _buffer;
  size = _size;
  index = _offset;
}

bool analogWave::freq(float freq_hz) {

  freq_max = (dac_max_samp_rate / (double)size);
  if (freq_hz >= freq_max) {
    return false;
  }

  float freq = freq_hz * size;
  float p = 1000000 / freq;

 

  return true;
}

bool analogWave::begin(float freq_hz) {

  return true;
}

template <typename T>
void _update(uint16_t *src, T *dts, float _amp, uint32_t _off, uint32_t _size,
             uint8_t _res) {
  uint16_t src_index = _off;

  for (uint16_t i = 0; i < _size; i++) {
    src_index = src_index % _size;
    uint16_t sample = *(src + src_index);
    src_index++;

    if (_amp < 1) {
      sample = (uint16_t)((float)sample * _amp);
    }
    T value = (T)map(sample, 0, (1 << 16), 0, (1 << _res));
    *(dts + i) = value;
  }
}

bool analogWave::update() {

  uint8_t *local_samples8 = nullptr;
  uint16_t *local_samples16 = nullptr;

  /*
   * calculate updated values on a new allocated buffer
   */
  return true;
}

uint32_t analogWave::num_of_sample() {
  return size;
}

void analogWave::amplitude(float a) {
  if (a >= 0 && a <= 1) {
    _amplitude = a;
  }
  update();
}

void analogWave::offset(uint32_t o) {
  if (o < size) {
    _offset = o;
  }
  update();
}

void analogWave::_pre_sync() {
;
}

void analogWave::sync(analogWave &w) {
;
}

void analogWave::start() {
  ;
}

void analogWave::stop() {
  ;
}



void analogWave::sine(float freq_hz) {

;
}

void analogWave::saw(float freq_hz) {
;
}

void analogWave::square(float freq_hz) {

 ;
}