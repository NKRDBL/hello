#pragma once

#include "processor.h"
#include <math.h>
#include <stdint.h>

class Effect : public Processor {
public:
  uint32_t getBufferSize() const override final { return 0U; }

  void init(float *) override final {
    bpm_ = 0.f;
    tick_serial_ = 0U;
    tick_counter_ = 0U;
    seen_serial_ = 0U;
    click_remaining_ = 0U;
    phase_ = 0.f;
  }

  void setParameter(uint8_t, int32_t) override final {}

  void setTempo(float tempo) override final {
    bpm_ = tempo;
  }

  void tempo4ppqnTick(uint32_t counter) override final {
    tick_counter_ = counter;
    ++tick_serial_;
  }

  void process(const float *__restrict in, float *__restrict out, uint32_t frames) override final {
    const uint32_t serial = tick_serial_;
    if (serial != seen_serial_) {
      seen_serial_ = serial;
      current_counter_ = tick_counter_;
      click_remaining_ = 2400U; // 50 ms
      phase_ = 0.f;
    }

    float bpm = bpm_;
    if (bpm < 1.f) bpm = 40.f;   // clearly low fallback if setTempo was never received
    if (bpm > 300.f) bpm = 300.f;

    float freq = bpm * ((current_counter_ & 3U) == 0U ? 3.f : 2.f);
    if (freq < 80.f) freq = 80.f;
    if (freq > 1200.f) freq = 1200.f;
    const float phase_step = 6.28318530718f * freq / getSampleRate();

    for (uint32_t i = 0; i < frames; ++i) {
      float click = 0.f;
      if (click_remaining_ > 0U) {
        const float env = click_remaining_ / 2400.f;
        click = 0.40f * sinf(phase_) * env;
        phase_ += phase_step;
        if (phase_ > 6.28318530718f) phase_ -= 6.28318530718f;
        --click_remaining_;
      }

      out[i * 2U] = in[i * 2U] * 0.15f + click;
      out[i * 2U + 1U] = in[i * 2U + 1U] * 0.15f + click;
    }
  }

private:
  volatile float bpm_ = 0.f;
  volatile uint32_t tick_serial_ = 0U;
  volatile uint32_t tick_counter_ = 0U;
  uint32_t seen_serial_ = 0U;
  uint32_t current_counter_ = 0U;
  uint32_t click_remaining_ = 0U;
  float phase_ = 0.f;
};
