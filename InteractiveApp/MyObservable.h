#pragma once
#include "external/Observer2/Observer.h"

namespace InteractiveApp {
template <class TData>
class MyObservable : public NSLibrary::CObservable<TData> {
public:
  MyObservable(TData &&obs_data)
      : NSLibrary::CObservable<TData>(
            [this]() { return std::move(this->obs_data_); }),
        obs_data_(obs_data) {}
  void set(TData &&obs_data) {
    obs_data_ = std::move(obs_data);
    notify();
  }

private:
  TData obs_data_;
};
} // namespace InteractiveApp