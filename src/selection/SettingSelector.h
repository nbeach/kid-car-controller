#ifndef SettingSelector_h
#define SettingSelector_h

template <typename T> class SettingSelector {
  void (*callback)(T) = nullptr;
  int settingCount = 0;
  T *settings;
  int currentSettingIndex = 0;
  void emitChange();

public:
  SettingSelector(T *settings, int count, int defaultIndex);
  ~SettingSelector();
  void onChange(void (*callback)(T));
  bool increase();
  bool decrease();
  T currentSetting();
};

template <typename T>
SettingSelector<T>::SettingSelector(T *settings, int count, int defaultIndex) {
  this->settings = settings;
  this->settingCount = count;
  this->currentSettingIndex = defaultIndex;
}

template <typename T> SettingSelector<T>::~SettingSelector() {
  delete[] settings;
}

template <typename T> void SettingSelector<T>::onChange(void (*callback)(T)) {
  this->callback = callback;
}

template <typename T> void SettingSelector<T>::emitChange() {
  if (callback != nullptr)
    callback(settings[currentSettingIndex]);
}

template <typename T> bool SettingSelector<T>::increase() {
  if (currentSettingIndex < (settingCount - 1)) {
    currentSettingIndex++;
    emitChange();
    return true;
  }
  return false;
}

template <typename T> bool SettingSelector<T>::decrease() {
  if (currentSettingIndex > 0) {
    currentSettingIndex--;
    emitChange();
    return true;
  }
  return false;
}

template <typename T> T SettingSelector<T>::currentSetting() {
  return settings[currentSettingIndex];
}

#endif