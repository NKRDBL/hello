#pragma once

#include "processor.h"
#include "unit_genericfx.h"
#include <stdint.h>

class Effect : public Processor {
public:
  static constexpr uint32_t kBufferFloats = 0x30000U; // 768 KiB, stereo ring buffer
  static constexpr uint32_t kDelayFrames = 48000U;    // 1 second at 48 kHz

  uint32_t getBufferSize() const override final { return kBufferFloats; }

  void init(float *allocated_buffer) override final {
    buffer_ = allocated_buffer;
    write_ = 0;
    read_ = 0;
    playback_frames_ = 0;
    raw_hook_ = nullptr;
  }

  void teardown() override final {
    buffer_ = nullptr;
    raw_hook_ = nullptr;
  }

  void setRawInputProvider(unit_runtime_genericfx_get_raw_input_ptr hook) {
    raw_hook_ = hook;
  }

  void setParameter(uint8_t, int32_t) override final {}

  void process(const float *__restrict in, float *__restrict out, uint32_t frames) override final {
    // The returned pointer is refreshed on every render call as required by the API.
    const float *raw = raw_hook_ ? raw_hook_() : nullptr;

    for (uint32_t i = 0; i < frames; ++i) {
      if (buffer_ && raw) {
        buffer_[write_] = raw[i * 2U];
        buffer_[write_ + 1U] = raw[i * 2U + 1U];
        write_ += 2U;
        if (write_ >= kBufferFloats) write_ = 0U;
      }

      if (buffer_ && playback_frames_ > 0U) {
        out[i * 2U] = buffer_[read_];
        out[i * 2U + 1U] = buffer_[read_ + 1U];
        read_ += 2U;
        if (read_ >= kBufferFloats) read_ = 0U;
        --playback_frames_;
      } else {
        out[i * 2U] = in[i * 2U];
        out[i * 2U + 1U] = in[i * 2U + 1U];
      }
    }
  }

  void touchEvent(uint8_t, uint8_t phase, uint32_t, uint32_t) override final {
    if (phase == k_unit_touch_phase_began && buffer_) {
      const uint32_t delay_floats = kDelayFrames * 2U;
      read_ = (write_ + kBufferFloats - delay_floats) % kBufferFloats;
      playback_frames_ = kDelayFrames;
    }
  }

private:
  float *buffer_ = nullptr;
  uint32_t write_ = 0;
  uint32_t read_ = 0;
  uint32_t playback_frames_ = 0;
  unit_runtime_genericfx_get_raw_input_ptr raw_hook_ = nullptr;
};
